/***************************************************************************
 *
 * $Id: $
 * $Log: $
 *
 * Author: Fabrice Retiere/Kai Schweda, Aug 2003
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 **************************************************************************/
#include "StMcPxlLadderHitCollection.hh"
#include "StMcPxlHit.hh"
static const char rcsid[] = "$Id: $";

ClassImp(StMcPxlLadderHitCollection)

//_____________________________________________________________________________
StMcPxlLadderHitCollection::StMcPxlLadderHitCollection()
{
   /* noop */
}
//_____________________________________________________________________________
StMcPxlLadderHitCollection::~StMcPxlLadderHitCollection()
{
   /* noop */
}

StMcPxlSensorHitCollection*
StMcPxlLadderHitCollection::sensor(unsigned int i)
{
   return (i < mNumberOfSensors) ? &(mSensors[i]) : 0;
}

const StMcPxlSensorHitCollection*
StMcPxlLadderHitCollection::sensor(unsigned int i) const
{
   return (i < mNumberOfSensors) ? &(mSensors[i]) : 0;
}

unsigned int StMcPxlLadderHitCollection::numberOfHits() const
{
   unsigned int sum = 0;
   for (int iSen = 0; iSen < mNumberOfSensors; iSen++)
   {
      sum += mSensors[iSen].hits().size();
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
