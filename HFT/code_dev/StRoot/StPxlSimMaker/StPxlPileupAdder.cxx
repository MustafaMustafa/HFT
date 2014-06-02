/*
 *
 * Author: M. Mustafa
 */

#include <stdio.h>

#include "StMessMgr.h"
#include "Stypes.h"
#include "Stiostream.h"
#include "StPxlPileupAdder.h"
#include "StMcEvent/StMcPxlHitCollection.hh"
#include "StMcEvent/StMcPxlHit.hh"
#include "StThreeVectorF.hh"


StPxlPileupAdder::~StPxlPileupAdder()
{
}
//____________________________________________________________
Int_t StPxlPileupAdder::initRun()
{
   // run is not used in the current implementation, but might be necessary in the future.
   LOG_INFO << "StPxlPileupAdder::init()" << endm;

   return kStOk;
}
//____________________________________________________________
Int_t StPxlPileupAdder::addPxlHits(StMcPxlHitCollection& mcPxlHitCol)
{
   return kStOK;
}
