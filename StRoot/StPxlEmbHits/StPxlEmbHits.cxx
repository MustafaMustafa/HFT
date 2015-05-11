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

#include "StPxlDbMaker/StPxlDb.h"
#include "StPxlEmbHits.h"

ClassImp(StPxlEmbHits);

StPxlEmbHits::StPxlEmbHits(const Char_t *name) : StMaker(name), mMcEvent(NULL), mPxlDb(NULL)
{
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

   StMcPxlHitCollection* mcPxlHitColEmb = new StMcPxlHitCollection();
   McTrk2RealGeo(*mcPxlHitColEmb);
   mMcEvent->setPxlHitCollection(mcPxlHitColEmb);

   return kStOK;
}
void StPxlEmbHits::McTrk2RealGeo(StMcPxlHitCollection& mcPxlHitCol)
{

   LOG_INFO << "StPxlEmbHits::Projecting the simulated track to the reco geometry via physical helix " << endm;

   StSPtrVecMcTrack& tracks = mMcEvent->tracks();
   size_t nMcTracks = tracks.size();

   Int_t count = 0, counttrk = 0;

   for (size_t i = 0; i < nMcTracks; ++i)
   {
      StMcTrack *Trk = tracks[i];
      if (!Trk) continue;
      counttrk += Trk->pxlHits().size();

      StPhysicalHelixD tHelix(Trk->momentum(), Trk->startVertex()->position(),
                              mBField*kilogauss, Trk->particleDefinition()->charge());

      for (int sector = 1; sector <= 10; ++sector)
      {
         for (int ladder = 1; ladder <= 4; ++ladder)
         {
            for (int sensor = 1; sensor <= 10; ++sensor)
            {

               TGeoHMatrix *interceptionM = (TGeoHMatrix *)mPxlDb->geoHMatrixSensorOnGlobal(sector, ladder, sensor);
               if (!interceptionM) continue;
               cout<<"sector/ladder/sensor = "<<sector<<"/"<<ladder<<"/"<<sensor<<endl;
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
               mcPxlHitCol.addHit(newHit);

               count++;
            }
         }
      }
   }

   LOG_INFO << "StPxlEmbHits::Number of McTracks       : " << nMcTracks << endm;
   LOG_INFO << "StPxlEmbHits::Number of Interceptions  : " << count << endm;
}

bool StPxlEmbHits::IsOnSensor(Double_t LocalPosition[3])
{
   Float_t Rphiwidth = 1.9210; // From StPxlSimMaker/StPxlISim.h
   Float_t Zlength   = 1.9872; //

   return fabs(LocalPosition[0]) < Rphiwidth/2. && fabs(LocalPosition[2]) < Zlength/2.0;
}
