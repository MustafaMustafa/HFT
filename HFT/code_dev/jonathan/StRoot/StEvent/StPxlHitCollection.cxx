/***************************************************************************
 *
 * $Id: StRnDHitCollection.cxx,v 2.1 2006/01/19 21:42:06 ullrich Exp $
 *
 * Author: Thomas Ullrich, Jan 2006
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StRnDHitCollection.cxx,v $
 * Revision 2.1  2006/01/19 21:42:06  ullrich
 * Initial Revision.
 *
 **************************************************************************/
#include "StPxlHitCollection.h"
#include "StPxlHit.h"

ClassImp(StPxlHitCollection)

StPxlHitCollection::StPxlHitCollection() { /* noop */ }

StPxlHitCollection::~StPxlHitCollection()
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

bool
StPxlHitCollection::addHit(StPxlHit* hit)
{
    if (hit) {
        mHits.push_back(hit);
        return true;
    }
    else
        return false;
}
const StSPtrVecPxlHit&
StPxlHitCollection::hits() const { return mHits; }

StSPtrVecPxlHit&
StPxlHitCollection::hits() { return mHits; }

