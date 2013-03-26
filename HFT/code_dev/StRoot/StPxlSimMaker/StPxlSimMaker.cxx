/*
 *
 * Author: A. Rose, LBL, Y. Fisyak, BNL, M. Miller, MIT, M. Mustafa
 *
 *
 **********************************************************
 * $Log: $
 */

#include "StPxlSimMaker.h"
#include "StPxlFastSim.h"
#include "StPxlISim.h"
#include "StMcPxlHitCollection.hh"
#include "StPxlHitCollection.h"

#include "Stiostream.h"
#include "StHit.h"
#include "StEventTypes.h"
#include "StEvent.h"
#include "StMcEvent.hh"
#include "StMcEventTypes.hh"

#include "TGeoManager.h"

ClassImp(StPxlSimMaker)

using namespace std;

StPxlSimMaker::StPxlSimMaker(const Char_t* name) : StMaker(name)
{
   mUseFastSim = kFALSE;
   mUseDIGMAPSSim = kFALSE;
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
   mUseFastSim = kTRUE;
   mPxlSimulator = new StPxlFastSim();
   LOG_INFO << "StPxlSimMaker: using StPxlFastSim " << endm;
   //}

   return kStOk;
}

//____________________________________________________________
Int_t StPxlSimMaker::InitRun(Int_t RunNo)
{
   LOG_INFO << "StPxlSimMaker::InitRun" << endm;

   TDataSet *set = GetDataBase("Calibrations/tracker");

   if (!set)
   {
      LOG_ERROR << "StPxlSimMaker - E - could not Get Calibrations/tracker." << endm;
   }

   return mPxlSimulator->initRun(*set, RunNo);
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

   if (!gGeoManager) GetDataBase("VmcGeometry");
   if (!gGeoManager)
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

      //Get MC Pxl hit collection. This contains all PXL hits.
      StMcPxlHitCollection* mcPxlHitCol = mcEvent->pxlHitCollection();

      if (mcPxlHitCol)
      {
         mPxlSimulator->addPxlHits(*mcPxlHitCol, *pxlHitCol);
      }
      else
      {
         LOG_INFO << "StPxlSimMaker no PXL hits in this StMcEvent!" << endm;
      }

      rcEvent->setPxlHitCollection(pxlHitCol);
      LOG_DEBUG << " size of hit collection : " << pxlHitCol->numberOfHits() << endm;
   }
   else if (mUseDIGMAPSSim)
   {
      // mPxlSimulator->addPxlRawHits();
   }


   return kStOK;
}
/*
 *
 * Author: A. Rose, LBL, Y. Fisyak, BNL, M. Miller, MIT, M. Mustafa
 *
 *
 **********************************************************
 * $Log: StPixelFastSimMaker.cxx,v $
 * Revision 1.44  2012/12/18 18:46:59  margetis
 * update for DEV13 geometry
 *
 * Revision 1.43  2010/09/01 20:31:47  fisyak
 * clean up unused varaibles
 *
 * Revision 1.42  2009/02/06 20:48:48  wleight
 * UPGR15 Update
 *
 * Revision 1.41  2009/01/26 14:50:46  fisyak
 * Clean up
 *
 * Revision 1.40  2007/12/03 20:42:43  wleight
 * Replaced couts with LOG_DEBUGs
 *
 * Revision 1.37  2007/11/13 19:09:51  wleight
 * Corrected bug causing pixel fast simulator to crash when there were no pixel and/or ist hits in the event
 *
 * Revision 1.36  2007/11/06 16:20:06  wleight
 * Digitized Pixel, removed all hit smearing, and implemented idTruth
 *
 * Revision 1.34  2007/10/18 16:31:44  fisyak
 * Add pile-up from weixie
 *
 * Revision 1.33  2007/10/18 14:25:13  didenko
 * updates for pile-up events
 *
 * Revision 1.32  2007/10/16 19:53:08  fisyak
 * rename Hft => Pxl, remove Hpd, Igt and Fst
 *
 * Revision 1.31  2007/10/16 19:50:46  fisyak
 * rename Hft => Pxl, remove Hpd, Igt and Fst
 *
 * Revision 1.30  2007/09/09 17:00:32  fisyak
 * Fix bug 1056
 *
 * Revision 1.29  2007/09/08 00:33:05  andrewar
 * Modifications for pileup hit read in.
 *
 * Revision 1.28  2007/05/17 13:18:52  andrewar
 * Removed cout in shiftHit.
 *
 * Revision 1.27  2007/05/16 15:06:55  andrewar
 * Switched cout's to LOG_INFO.
 *
 * Revision 1.26  2007/04/28 17:56:36  perev
 * Redundant StChain.h removed
 *
 * Revision 1.25  2007/04/27 18:41:29  wleight
 * Removed smearing of the coordinate not controlled by the strips in the 17cm layer
 *
 * Revision 1.24  2007/04/27 14:59:10  wleight
 * Corrected another error in the creation of new hits
 *
 * Revision 1.23  2007/04/26 04:08:41  perev
 * Remove StBFChain dependency
 *
 * Revision 1.22  2007/04/25 17:44:59  wleight
 * Corrected error in assignment of reconstructed IST hits
 *
 * Revision 1.21  2007/04/23 18:11:30  andrewar
 * Removed references to Hpd (includes were obsolete)
 *
 * Revision 1.19  2007/04/23 16:32:47  wleight
 * Added explicit casting for Double_t to int in calculating strip number
 *
 * Revision 1.18  2007/04/22 22:57:23  wleight
 * The two hits in the 17 cm layer are no longer combined into 1
 *
 * Revision 1.17  2007/04/16 19:10:52  wleight
 * Added IST simulation (digitization but no clustering)
 *
 * Revision 1.16  2007/04/13 19:17:15  andrewar
 * Removed misleading errors. Changed cout and printf to gMessMgr.
 *
 * Revision 1.15  2007/04/06 21:46:36  andrewar
 * Removed some debug messages.
 *
 * Revision 1.14  2007/04/06 14:55:11  andrewar
 * Shift of HFT hit to face of ladder.
 *
 * Revision 1.13  2007/03/28 13:33:45  mmiller
 * Removed cout/printf's.
 *
 * Revision 1.12  2006/12/21 18:11:59  wleight
 * Fixed UPGR09 compatibility so it works with all versions
 *
 * Revision 1.11  2006/12/20 16:50:21  wleight
 * Added fix for UPGR09 problem with layer number mismatch
 *
 * Revision 1.10  2006/12/15 02:17:20  wleight
 * Ist now gets hit smearing parameters from the database
 *
 * Revision 1.9  2006/12/14 23:52:51  andrewar
 * Added Sevil's hit error db loader.
 *
 * Revision 1.7  2006/11/29 21:42:07  andrewar
 * Update with Pixel resolution smearing.
 *
 * Revision 1.6  2006/11/28 22:37:42  wleight
 * Fixed minor smearing bug
 *
 * Revision 1.4  2006/10/13 20:15:45  fisyak
 * Add Hpd fast simulation (Sevil)
 *
 * Revision 1.3  2006/02/17 21:44:29  andrewar
 * Remover streaming of each Pixel hit.
 *
 * Revision 1.2  2006/02/08 20:57:33  fisyak
 * Set proper Detector Id
 *
 * Revision 1.1  2006/02/03 20:11:56  fisyak
 * The initial revision
 *
 *
 */

