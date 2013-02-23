/***************************************************************************
 *
 * $Id: StPxlSectorHitCollection.cxx,v 1.3 2013/01/31 01:13:03 qiuh Exp $
 *
 * Author: Thomas Ullrich, Jan 2006
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StPxlSectorHitCollection.cxx,v $
 *
 **************************************************************************/
#include "StPxlSectorHitCollection.h"
#include "StPxlHit.h"

ClassImp(StPxlSectorHitCollection)

StPxlSectorHitCollection::StPxlSectorHitCollection() { /* noop */ }

StPxlSectorHitCollection::~StPxlSectorHitCollection() { /* noop */ }

StPxlLadderHitCollection* 
StPxlSectorHitCollection::ladder(unsigned int i)
{
  return (i < mNumberOfLadders) ? &(mLadders[i]) : 0;
}

const StPxlLadderHitCollection* 
StPxlSectorHitCollection::ladder(unsigned int i) const
{ 
  return (i < mNumberOfLadders) ? &(mLadders[i]) : 0;
}

unsigned int StPxlSectorHitCollection::numberOfHits() const
{
  unsigned int sum = 0;
  for ( int i=0; i < mNumberOfLadders; i++) {
    for ( int j=0; j < mLadders[i].numberOfSensors(); j++) {
      sum += mLadders[i].sensor(j)->hits().size();
    }
  }
  return sum;
}
