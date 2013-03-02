/***************************************************************************
 *
 * $Id: $
 * $Log: $
 *
 **************************************************************************/
#include "StMcPxlSensorHitCollection.hh"
#include "StMcPxlHit.hh"

ClassImp(StMcPxlSensorHitCollection)

StMcPxlSensorHitCollection::StMcPxlSensorHitCollection()
{
   /* noop */
}

StMcPxlSensorHitCollection::~StMcPxlSensorHitCollection()
{
   for (unsigned int i = 0; i < mHits.size(); i++)
   {
      delete mHits[i];
      mHits[i] = 0;
   }
}

const StSPtrVecMcPxlHit&
StMcPxlSensorHitCollection::hits() const
{
   return mHits;
}

StSPtrVecMcPxlHit&
StMcPxlSensorHitCollection::hits()
{
   return mHits;
}
