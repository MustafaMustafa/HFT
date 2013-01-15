/*
 *
 * Author: M. Mustafa
 *
 * 
 **********************************************************
 *
 */

#include "Stiostream.h"
#include "StPixelSlowSimMaker.h"
#include "StHit.h"
#include "StEventTypes.h"
#include "StEvent.h"
#include "StPxlHit.h"
#include "StMcEvent.hh"
#include "StMcHit.hh"
#include "StMcPixelHit.hh"
#include "StMcEventTypes.hh"
#include "tables/St_g2t_ist_hit_Table.h"
#include "tables/St_g2t_pix_hit_Table.h"
#include "tables/St_HitError_Table.h"
#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "StarClassLibrary/StRandom.hh"
#include "tables/St_HitError_Table.h"
#include <fstream>
#include "TFile.h"
#include "TTree.h"

ClassImp(StPixelSlowSimMaker)

using namespace std;
  
StPixelSlowSimMaker::~StPixelSlowSimMaker(){ /*noop*/ }

int StPixelSlowSimMaker::Init()
{
  LOG_INFO<<"StPixelSlowSimMaker::Init()"<<endm;
  Int_t seed=time(NULL);
  mRandom = new StRandom();
  mRandom->setSeed(seed);

  return kStOk;
}

//____________________________________________________________
Int_t StPixelSlowSimMaker::InitRun(Int_t RunNo)
{
  return kStOk;
}
//____________________________________________________________

Int_t StPixelSlowSimMaker::Make()
{
  LOG_INFO<<"StPixelSlowSimMaker::Make()"<<endm;

  // Get the input data structures from StEvent and StMcEvent
  StEvent* rcEvent =  (StEvent*) GetInputDS("StEvent");
  if (! rcEvent) {LOG_INFO << "No StEvent on input" << endl; return kStWarn;}

  StMcEvent* mcEvent = (StMcEvent *) GetInputDS("StMcEvent");
  if (! mcEvent) {LOG_INFO << "No StMcEvent on input" << endl; return kStWarn;}

  TDataSetIter geant(GetInputDS("geant"));
  if (! gGeoManager) GetDataBase("VmcGeometry");
  St_g2t_pix_hit *g2t_pix_hit=(St_g2t_pix_hit *)geant("g2t_pix_hit");
  g2t_pix_hit_st* g2tPix=0;
  if(g2t_pix_hit) g2tPix=g2t_pix_hit->GetTable();

  StPxlHitCollection *pixHitCol = new StPxlHitCollection;
  if (!pixHitCol)
  {
      gMessMgr->Info() << "StPixelSlowSimMaker -E- no PixelHitCollection!\n";
      abort();
  }

  //Get MC Pixel hit collection. This contains all pixel hits.
  StMcPixelHitCollection* mcPixHitCol = mcEvent->pixelHitCollection();

  if (mcPixHitCol)
  {
    Int_t nMcHits = mcPixHitCol->numberOfHits();
    LOG_DEBUG<<"There are "<<nMcHits<<" mc pixel hits"<<endm;

    if(nMcHits)
    {
      Int_t id = pixHitCol->numberOfHits();

      for (UInt_t iSec=0; iSec<mcPixHitCol->numberOfLayers(); iSec++)
      {
	if (mcPixHitCol->layer(iSec))
	{
	  LOG_DEBUG<<"Sector "<<iSec+1<<endm;

	  UInt_t nSecHits = mcPixHitCol->layer(iSec)->hits().size();
	  LOG_DEBUG << " Number of hits in sector "<< iSec+1 <<" =" << nSecHits << endm;

	  for (UInt_t iHit = 0; iHit<nSecHits; iHit++)
	  {
	    StMcHit *mcH = mcPixHitCol->layer(iSec)->hits()[iHit];
	    StMcPixelHit* mcHit=dynamic_cast<StMcPixelHit*>(mcH);

	    Int_t vid=g2tPix[iHit].volume_id;
	    Int_t layer=vid/1000000;
	    Int_t ladder=(vid%1000000)/10000;
	    TString Path("");
	    Path= Form("/HALL_1/CAVE_1/IDSM_1/PXMO_1/PXLA_%i/LADR_%i/PLAC_1",layer,ladder);
	    gGeoManager->RestoreMasterVolume();
	    gGeoManager->CdTop();
	    gGeoManager->cd(Path);

	    Double_t globalPixHitPos[3]={mcHit->position().x(),mcHit->position().y(),mcHit->position().z()};
	    Double_t localPixHitPos[3]={0,0,0};

	    gGeoManager->GetCurrentMatrix()->MasterToLocal(globalPixHitPos,localPixHitPos);
	  }
	}
      }
    }

    gMessMgr->Info() <<"StPxlSlowSimMaker::Make() -I- Loaded "<<nMcHits<<"pixel hits. \n";
  }
  else
  {
    gMessMgr->Info() <<"No pixel hits found.\n";
  }
  
  rcEvent->setPixelHitCollection(pixHitCol);
  LOG_DEBUG <<" size of hit collection : "<<pixHitCol->numberOfHits()<<endm;
  return kStOK;
}