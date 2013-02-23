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
#include "StMcPxlSectorHitCollection.hh"
#include "StMcPxlHit.hh"
static const char rcsid[] = "$Id: $";

ClassImp(StMcPxlSectorHitCollection)

//_____________________________________________________________________________
StMcPxlSectorHitCollection::StMcPxlSectorHitCollection()
{
   /* noop */
}
//_____________________________________________________________________________
StMcPxlSectorHitCollection::~StMcPxlSectorHitCollection()
{
   /* noop */
}

StMcPxlLadderHitCollection*
StMcPxlSectorHitCollection::ladder(unsigned int i)
{
   return (i < mNumberOfLadders) ? &(mLadders[i]) : 0;
}

const StMcPxlLadderHitCollection*
StMcPxlSectorHitCollection::ladder(unsigned int i) const
{
   return (i < mNumberOfLadders) ? &(mLadders[i]) : 0;
}

unsigned int StMcPxlSectorHitCollection::numberOfHits() const
{
   unsigned int sum = 0;
   for (int iLadder = 0; iLadder < mNumberOfLadders; iLadder++)
   {
      for (int iSensor = 0; iSensor < mLadders[iSensor].numberOfSensors(); iSensor++)
      {
         sum += mLadders[iLadder].sensor(iSensor)->hits().size();
      }
   }
   return sum;
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
