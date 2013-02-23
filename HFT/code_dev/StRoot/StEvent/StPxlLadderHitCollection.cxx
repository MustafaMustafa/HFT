/***************************************************************************
 *
 * $Id: StPxlLadderHitCollection.cxx,v 1.3 2013/01/31 01:13:03 qiuh Exp $
 *
 * Author: Thomas Ullrich, Jan 2006
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StPxlLadderHitCollection.cxx,v $
 *
 **************************************************************************/
#include "StPxlLadderHitCollection.h"
#include "StPxlHit.h"

ClassImp(StPxlLadderHitCollection)

StPxlLadderHitCollection::StPxlLadderHitCollection() { /* noop */ }

StPxlLadderHitCollection::~StPxlLadderHitCollection() { /* noop */ }

StPxlSensorHitCollection* 
StPxlLadderHitCollection::sensor(unsigned int i)
{
  return (i < mNumberOfSensors) ? &(mSensors[i]) : 0;
}

const StPxlSensorHitCollection* 
StPxlLadderHitCollection::sensor(unsigned int i) const
{ 
  return (i < mNumberOfSensors) ? &(mSensors[i]) : 0;
}

unsigned int StPxlLadderHitCollection::numberOfHits() const
{
  unsigned int sum = 0;
  for ( int i=0; i < mNumberOfSensors; i++) {
    sum += mSensors[i].hits().size();
  }
  return sum;
}
