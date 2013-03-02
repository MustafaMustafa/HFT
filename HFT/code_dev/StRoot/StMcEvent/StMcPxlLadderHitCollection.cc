/***************************************************************************
 *
 * $Id: $
 * $Log: $
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
