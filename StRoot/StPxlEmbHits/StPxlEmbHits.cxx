#include "TGeoMatrix.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TMath.h"

#include "StMessMgr.h"
#include "StarMagField.h"
#include "SystemOfUnits.h"
#include "StEvent.h"
#include "StMcEvent.hh"
#include "StMcVertex.hh"
#include "StMcTrack.hh"
#include "StMcPxlHit.hh"
#include "StThreeVectorD.hh"
#include "StPhysicalHelixD.hh"
#include "StParticleDefinition.hh"
#include "StMcPxlHitCollection.hh"
#include "StMcEvent/StMcVertex.hh"

#include "StPxlDbMaker/StPxlDb.h"
#include "../StHistograms/StHistograms.h"
#include "StPxlEmbHits.h"

ClassImp(StPxlEmbHits);

StPxlEmbHits::StPxlEmbHits(const Char_t *name) : StMaker(name), mMcEvent(NULL), mPxlDb(NULL),
   mPionsHists(NULL), mKaonsHists(NULL), mProtonsHists(NULL)
{
   mPionsHists = new StHistograms("idealPions");
   mKaonsHists = new StHistograms("idealKaons");
   mProtonsHists = new StHistograms("idealProtons");
}

Int_t StPxlEmbHits::Init()
{
   LOG_INFO << "StPxlEmbHits::Init() " << endm;
   return kStOK;
}

Int_t StPxlEmbHits::InitRun(Int_t runNumber)
{
   TObjectSet *pxlDbDataSet = (TObjectSet *)GetDataSet("pxl_db");
   if (pxlDbDataSet)
   {
      mPxlDb = (StPxlDb *)pxlDbDataSet->GetObject();
      assert(mPxlDb);
   }
   else
   {
      LOG_ERROR << "InitRun : no pxlDb" << endm;
      return kStFatal;
   }

   float center[3] = {0, 0, 0};
   float B[3] = {0, 0, 0};
   StarMagField::Instance()->BField(center, B);
   mBField   = B[2];

   return kStOK;
}

Int_t StPxlEmbHits::Make()
{
   mMcEvent = (StMcEvent *) GetInputDS("StMcEvent");

   if (!mMcEvent)
   {
      LOG_WARN << "StPxlEmbHits::Make : No StMcEvent" << endm;
      return kStWarn;
   }

   mPionsHists->addEvent(mMcEvent);
   mKaonsHists->addEvent(mMcEvent);
   mProtonsHists->addEvent(mMcEvent);

   StMcPxlHitCollection* mcPxlHitColEmb = (StMcPxlHitCollection*)mMcEvent->pxlHitCollection();
   McTrk2RealGeo(*mcPxlHitColEmb);

   return kStOK;
}
void StPxlEmbHits::McTrk2RealGeo(StMcPxlHitCollection& mcPxlHitCol)
{
   LOG_INFO << "Re-projecting MC tracks to geometry..." << endm;

   StSPtrVecMcTrack& tracks = mMcEvent->tracks();
   size_t nMcTracks = tracks.size();
   LOG_INFO << "nMcTracks = " << nMcTracks << endm;

   for (size_t iTk = 0; iTk < nMcTracks; ++iTk)
   {
      StMcTrack *Trk = tracks[iTk];
      if (!Trk) continue;

      if (Trk->pt() < 0.15 || fabs(Trk->momentum().pseudoRapidity()) > 1.0) continue;
      StHistograms* hists = NULL;
      if (Trk->geantId() == 8 || Trk->geantId() == 9) hists = mPionsHists;
      else if (Trk->geantId() == 11 || Trk->geantId() == 12) hists = mKaonsHists;
      else if (Trk->geantId() == 14 || Trk->geantId() == 15) hists = mProtonsHists;
      else continue;

      StPhysicalHelixD tHelix(Trk->momentum(), Trk->startVertex()->position(),
                              mBField * kilogauss, Trk->particleDefinition()->charge());

      std::vector<StMcPxlHit*> projHits;

      for (int sector = 1; sector <= 10; ++sector)
      {
         for (int ladder = 1; ladder <= 4; ++ladder)
         {
            for (int sensor = 1; sensor <= 10; ++sensor)
            {

               TGeoHMatrix *interceptionM = (TGeoHMatrix *)mPxlDb->geoHMatrixSensorOnGlobal(sector, ladder, sensor);
               if (!interceptionM) continue;
               Double_t *Rotat = interceptionM->GetRotationMatrix();
               Double_t *Trans = interceptionM->GetTranslation();
               const StThreeVectorD senNorm(Rotat[1], Rotat[4], Rotat[7]);
               const StThreeVectorD senCent(Trans);

               Double_t s = tHelix.pathLength(senCent, senNorm);
               if (s < 0) continue;

               StThreeVectorD XXX = tHelix.at(s);

               Double_t xg[3] = {XXX.x(), XXX.y(), XXX.z()};
               Double_t xl[3] = {0, 0, 0};
               interceptionM->MasterToLocal(xg, xl);

               if (!IsOnSensor(xl)) continue;

               StMcPxlHit* newHit = new StMcPxlHit(xl, Trk->momentum(), Trk->energy(),
                                                   0.002,                     //step size in volume  NEEDTOFIX ~0.002
                                                   0,                         //Time of flight NEEDTOFIX but is ~0
                                                   Trk->key(),
                                                   sensor * 100 + ladder * 10000 + sector * 1000000, //STAR volume id from g2t
                                                   Trk);
               projHits.push_back(newHit);
            }
         }
      }

      LOG_INFO << " runNumber/eventNumber/mcTrackIndex/geantId: " << mMcEvent->runNumber() << "/" << mMcEvent->eventNumber() << "/" << iTk << "/" << Trk->geantId() << endm;
      LOG_INFO << " pT/eta " << Trk->momentum().perp() << "/" << Trk->momentum().pseudoRapidity() << endm;
      hists->addHits(Trk->pxlHits(), projHits);

      for (size_t ii = 0; ii < projHits.size(); ++ii) delete projHits[ii];
   }
}

bool StPxlEmbHits::IsOnSensor(Double_t LocalPosition[3])
{
   Float_t Rphiwidth = 1.9210; // From StPxlSimMaker/StPxlISim.h
   Float_t Zlength   = 1.9872; //

   return fabs(LocalPosition[0]) < Rphiwidth / 2. && fabs(LocalPosition[2]) < Zlength / 2.0;
}

Int_t StPxlEmbHits::Finish()
{
   mPionsHists->closeFile();
   mKaonsHists->closeFile();
   mProtonsHists->closeFile();
}
