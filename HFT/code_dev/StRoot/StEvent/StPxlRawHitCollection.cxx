/***************************************************************************
 *
 * $Id: StPxlRawHitCollection.cxx,v 1.3 2013/01/31 01:13:03 qiuh Exp $
 *
 * Author: Thomas Ullrich, Jan 2006
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StPxlRawHitCollection.cxx,v $
 * Revision 1.3  2013/01/31 01:13:03  qiuh
 * *** empty log message ***
 *
 * Revision 2.1  2006/01/19 21:42:06  ullrich
 * Initial Revision.
 *
 **************************************************************************/
#include "StPxlRawHitCollection.h"
#include "StPxlRawHit.h"

ClassImp(StPxlRawHitCollection)

StPxlRawHitCollection::StPxlRawHitCollection() { /* noop */ }

StPxlRawHitCollection::~StPxlRawHitCollection()
{
    //
    // Usually this wouldn't be necessary but mHits
    // is a polymorphic container and StPxlRawHit
    // provides its own new/delete operator.
    //
    for (unsigned int i=0; i<mHits.size(); i++) {
        delete mHits[i];
        mHits[i] = 0;
    }
}

bool
StPxlRawHitCollection::addHit(StPxlRawHit* hit)
{
    if (hit) {
        mHits.push_back(hit);
        return true;
    }
    else
        return false;
}
const StSPtrVecPxlRawHit&
StPxlRawHitCollection::hits() const { return mHits; }

StSPtrVecPxlRawHit&
StPxlRawHitCollection::hits() { return mHits; }

