/*!
 * \class StRnDHitCollection 
 * \author Thomas Ullrich, Jan 2006
 */
/***************************************************************************
 *
 * $Id: StRnDHitCollection.h,v 2.1 2006/01/19 21:42:06 ullrich Exp $
 *
 * Author: Thomas Ullrich, Jan 2006
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StRnDHitCollection.h,v $
 * Revision 2.1  2006/01/19 21:42:06  ullrich
 * Initial Revision.
 *
 **************************************************************************/
#ifndef StIstHitCollection_hh
#define StIstHitCollection_hh

#include "StObject.h"
#include "StContainers.h"

class StIstHit;

class StIstHitCollection : public StObject {
public:
    StIstHitCollection();
    ~StIstHitCollection();
    // StIstHitCollection(const StIstHitCollection&); use default
    // const StIstHitCollection&
    // operator=(const StIstHitCollection&);           use default
    
    StSPtrVecIstHit&       hits();
    const StSPtrVecIstHit& hits() const;

    bool          addHit(StIstHit*);
    unsigned int  numberOfHits() const;
    
private:
    StSPtrVecIstHit mHits;
    
    ClassDef(StIstHitCollection,1)
};

inline const StSPtrVecIstHit& StIstHitCollection::hits() const { return mHits; }
inline StSPtrVecIstHit& StIstHitCollection::hits() { return mHits; }
inline unsigned int StIstHitCollection::numberOfHits() const {return mHits.size();}

#endif
