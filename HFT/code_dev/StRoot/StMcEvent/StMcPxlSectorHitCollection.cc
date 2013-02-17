/***************************************************************************
 *
 * $Id: $
 * $Log: $
 *
 * Author: Fabrice Retiere/Kai Schweda, Aug 2003
 ***************************************************************************
 *
 * Description: Monte Carlo PXL Layer Hit Collection class
 *
 ***************************************************************************
 *
 **************************************************************************/
#include "TBrowser.h"
#include "StMcPxlSectorHitCollection.hh"
#include "StMcPxlHit.hh"
static const char rcsid[] = "$Id: $";

ClassImp(StMcPxlSectorHitCollection)

//_____________________________________________________________________________
StMcPxlSectorHitCollection::StMcPxlSectorHitCollection() { /* noop */ }
//_____________________________________________________________________________
StMcPxlSectorHitCollection::~StMcPxlSectorHitCollection(){ Clear();   }

//_____________________________________________________________________________
void StMcPxlSectorHitCollection::Clear(const char*)
{
  for (int i=0; i<(int)mHits.size(); i++) 
  {
    delete mHits[i]; mHits[i] = 0;
  }
  mHits.clear();
}
//_____________________________________________________________________________
void StMcPxlSectorHitCollection::Browse(TBrowser *b)
{
  // Browse this event (called by TBrowser).
   for (int i=0; i<(int)mHits.size(); i++) {
     TObject *obj = mHits[i]; if (!obj) continue;
     TString ts(obj->GetName()); ts+="#"; ts+=i;
     b->Add(obj,ts.Data());
   }
}

//_____________________________________________________________________________
const StSPtrVecMcPxlHit& StMcPxlSectorHitCollection::hits() const { return mHits; }

//_____________________________________________________________________________
StSPtrVecMcPxlHit& StMcPxlSectorHitCollection::hits() { return mHits; }

//_____________________________________________________________________________
unsigned long StMcPxlSectorHitCollection::numberOfHits() const
{
  return mHits.size();
}

/***************************************************************************
 *
 * $Id: StMcPixelLayerHitCollection.cc,v 2.3 2012/03/01 16:48:29 perev Exp $
 *
 * Author: Fabrice Retiere/Kai Schweda, Aug 2003
 ***************************************************************************
 *
 * Description: Monte Carlo Pixel Layer Hit Collection class
 *
 ***************************************************************************
 *
 * $Log: StMcPixelLayerHitCollection.cc,v $
 * Revision 2.3  2012/03/01 16:48:29  perev
 * method Browse() added
 *
 * Revision 2.2  2005/01/27 23:40:47  calderon
 * Adding persistency to StMcEvent as a step for Virtual MonteCarlo.
 *
 * Revision 2.1  2003/08/20 18:50:21  calderon
 * Addition of Tof classes and Pixel classes.  Modified track, event, and
 * container code to reflect this.
 * Fix bug in StMcVertex and in clearing of some hit collections.
 *
 *
 *
 **************************************************************************/
