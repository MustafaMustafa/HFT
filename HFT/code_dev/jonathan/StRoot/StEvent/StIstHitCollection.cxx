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
#include "StIstHitCollection.h"
#include "StIstHit.h"

ClassImp(StIstHitCollection)

StIstHitCollection::StIstHitCollection() { /* noop */ }

StIstHitCollection::~StIstHitCollection()
{
    //
    // Usually this wouldn't be necessary but mHits
    // is a polymorphic container and StIstHit
    // provides its own new/delete operator.
    //
    for (unsigned int i=0; i<mHits.size(); i++) {
        delete mHits[i];
        mHits[i] = 0;
    }
}

bool
StIstHitCollection::addHit(StIstHit* hit)
{
    if (hit) {
        mHits.push_back(hit);
        return true;
    }
    else
        return false;
}

