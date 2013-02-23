/***************************************************************************
 *
 * $Id: StPxlSensorHitCollection.cxx,v 1.3 2013/01/31 01:13:03 qiuh Exp $
 *
 * Author: Thomas Ullrich, Jan 2006
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StPxlSensorHitCollection.cxx,v $
 *
 **************************************************************************/
#include "StPxlSensorHitCollection.h"
#include "StPxlHit.h"

ClassImp(StPxlSensorHitCollection)

StPxlSensorHitCollection::StPxlSensorHitCollection() { /* noop */ }

StPxlSensorHitCollection::~StPxlSensorHitCollection() 
{
    //
    // Usually this wouldn't be necessary but mHits
    // is a polymorphic container and StPxlHit
    // provides its own new/delete operator.
    //
    for (unsigned int i=0; i<mHits.size(); i++) {
        delete mHits[i];
        mHits[i] = 0;
    }
}

const StSPtrVecPxlHit&
StPxlSensorHitCollection::hits() const { return mHits; }

StSPtrVecPxlHit&
StPxlSensorHitCollection::hits() { return mHits; }
