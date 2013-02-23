/***************************************************************************
 *
 * $Id: $
 *
 * Author:
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
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
   //
   // Usually this wouldn't be necessary but mHits
   // is a polymorphic container and StPxlHit
   // provides its own new/delete operator.
   //
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
