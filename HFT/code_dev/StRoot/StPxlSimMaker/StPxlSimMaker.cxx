/*
 **********************************************************
 * $Log: StPxlSimMaker.cxx,v $
 * Revision 1.4  2014/06/25 19:21:57  mstftsm
 * pxl DB DataSet has been change to pxl_db. Name changed in this code.
 *
 * Revision 1.3  2014/03/13 17:00:19  mstftsm
 * StPxlSimMaker has a method to switch on random seed for StRandom generatos in simulators. Default is not a random seed.
 *
 * Revision 1.1  2013/05/12 21:43:33  jeromel
 * Initial revision, code peer review closed 2013/05/06
 *
 * Revision 1.4  2013/05/03 15:08:19  mstftsm
 *
 */

#include "StPxlSimMaker.h"
#include "StPxlFastSim.h"
#include "StPxlISim.h"
#include "StMcEvent/StMcPxlHitCollection.hh"
#include "StEvent/StPxlHitCollection.h"

#include "StPxlPileupAdder.h"

#include "Stiostream.h"
#include "StHit.h"
#include "StEventTypes.h"
#include "StEvent.h"
#include "StMcEvent.hh"
#include "StMcEventTypes.hh"

#include "TGeoManager.h"
#include "TGeoMatrix.h"

#include "TObjectSet.h"
#include "TString.h"

ClassImp(StPxlSimMaker)

using namespace std;

StPxlSimMaker::StPxlSimMaker(const Char_t* name) : StMaker(name) , mPxlSimulator(0), mUseFastSim(kFALSE), mUseDIGMAPSSim(kFALSE) , mUseIdealGeom(kTRUE), mUseDbGeom(kFALSE), mUseRandomSeed(kFALSE),mAddPileup(kFALSE)
{
}
//____________________________________________________________
StPxlSimMaker::~StPxlSimMaker()
{
   delete mPxlSimulator;
}
//____________________________________________________________
Int_t StPxlSimMaker::Init()
{
   LOG_INFO << "StPxlSimMaker::Init()" << endm;

   mUseDIGMAPSSim = IAttr("useDIGMAPSSim");

   //if(mUseDIGMAPSSim)
   //{
   // mPxlSimulator = new StPxlSlowSim();
   //}
   //else
   //{
   // temporary till DIGMAPS algorithm is added and option added in StMaker
   mUseFastSim = kTRUE;

   if(mAddPileup)
   {
	   mPileupAdder = new StPxlPileupAdder();
   }

   mPxlSimulator = new StPxlFastSim("pxlFastSim",mUseRandomSeed);

   LOG_INFO << "StPxlSimMaker: using StPxlFastSim " << endm;
   //}

   return kStOk;
}

//____________________________________________________________
Int_t StPxlSimMaker::InitRun(Int_t RunNo)
{
   LOG_INFO << "StPxlSimMaker::InitRun" << endm;

   TDataSet *hitErrSet = GetDataBase("Calibrations/tracker/PixelHitError");
   if (!hitErrSet)
   {
      LOG_ERROR << "StPxlSimMaker - E - could not Get Calibrations/tracker." << endm;
      return kStErr;
   }

   TObjectSet *pxlDbDataSet = 0; 
   if(mUseDbGeom)
   {
	   pxlDbDataSet = (TObjectSet*)GetDataSet("pxl_db");
	   if (!pxlDbDataSet)
	   {
		   LOG_ERROR << "StPxlSimMaker - E - pxlDb  is not available" << endm;
		   return kStErr;
	   }
   }

   if(mAddPileup)
   {
	   mPileupAdder->init(mPileupFile,pxlDbDataSet);
   }

   return mPxlSimulator->initRun(*hitErrSet, pxlDbDataSet, RunNo);
}
//____________________________________________________________

Int_t StPxlSimMaker::Make()
{
   LOG_INFO << "StPxlSimMaker::Make()" << endm;

   // Get the input data structures from StEvent and StMcEvent
   StEvent* rcEvent = (StEvent*) GetInputDS("StEvent");
   if (! rcEvent)
   {
      LOG_INFO << "No StEvent on input" << endl;
      return kStWarn;
   }

   StMcEvent* mcEvent = (StMcEvent *) GetInputDS("StMcEvent");
   if (! mcEvent)
   {
      LOG_INFO << "No StMcEvent on input" << endl;
      return kStWarn;
   }

   //Get MC Pxl hit collection. This contains all PXL hits.
   StMcPxlHitCollection* mcPxlHitCol = mcEvent->pxlHitCollection();
   if (!mcPxlHitCol)
   {
      LOG_INFO << "StPxlSimMaker no PXL hits in this StMcEvent!" << endm;
      return kStOk;
   }

   // add pile up 
   if(mAddPileup)
   {
	   mPileupAdder->addPxlHits(*mcPxlHitCol);
   }

   if (mUseIdealGeom && !gGeoManager) GetDataBase("VmcGeometry");
   if (mUseIdealGeom && !gGeoManager)
   {
      LOG_ERROR << " StPxlSimMaker - E - gGeoManager is not available." << endm;
      return kStErr;
   }

   // call the requested simulator
   if (mUseFastSim)
   {
      StPxlHitCollection *pxlHitCol = new StPxlHitCollection;
      if (!pxlHitCol)
      {
         LOG_ERROR << "StPxlSimMaker -E- no PxlHitCollection in this StEvent!" << endm;
         return kStErr;
      }

      mPxlSimulator->addPxlHits(*mcPxlHitCol, *pxlHitCol);

      rcEvent->setPxlHitCollection(pxlHitCol);
      LOG_DEBUG << " size of hit collection : " << pxlHitCol->numberOfHits() << endm;
   }
   else if (mUseDIGMAPSSim)
   {
      // for testing
      /*StPxlRawHitCollection* pxlRawHitCol = 0;

      TObjectSet* pxlRawHitDataSet = (TObjectSet*)GetDataSet("pxlRawHit");

      if (!pxlRawHitDataSet)
      {
           pxlRawHitDataSet = new TObjectSet("pxlRawHit");
           m_DataSet = pxlRawHitDataSet;
           pxlRawHitCol = new StPxlRawHitCollection();
           pxlRawHitDataSet->AddObject(pxlRawHitCol);
      }
      else
      {
          pxlRawHitCol= (StPxlRawHitCollection*)pxlRawHitDataSet->GetObject();
      }

      if(!pxlRawHitCol)
      {
      LOG_ERROR << "Make() - no pxlRawHitCollection."<<endm;
      return kStErr;
      }

      mPxlSimulator->addPxlRawHits(*mcPxlHitCol,*pxlRawHitCol); */
   }


   return kStOK;
}
/*
 **********************************************************
 * $Log: StPxlSimMaker.cxx,v $
 * Revision 1.4  2014/06/25 19:21:57  mstftsm
 * pxl DB DataSet has been change to pxl_db. Name changed in this code.
 *
 * Revision 1.3  2014/03/13 17:00:19  mstftsm
 * StPxlSimMaker has a method to switch on random seed for StRandom generatos in simulators. Default is not a random seed.
 *
 * Revision 1.1  2013/05/12 21:43:33  jeromel
 * Initial revision, code peer review closed 2013/05/06
 *
 * Revision 1.4  2013/05/03 15:08:19  mstftsm
 *
 */

