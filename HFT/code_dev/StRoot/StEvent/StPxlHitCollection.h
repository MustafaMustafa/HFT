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
#ifndef StPxlHitCollection_hh
#define StPxlHitCollection_hh

#include "StObject.h"
#include "StContainers.h"

class StPxlHit;

class StPxlHitCollection : public StObject {
public:
    StPxlHitCollection();
    ~StPxlHitCollection();
    // StPxlHitCollection(const StPxlHitCollection&); use default
    // const StPxlHitCollection&
    // operator=(const StPxlHitCollection&);           use default
    
    StSPtrVecPxlHit&       hits();
    const StSPtrVecPxlHit& hits() const;

    bool          addHit(StPxlHit*);
    unsigned int  numberOfHits() const;
    
private:
    StSPtrVecPxlHit mHits;
    
    ClassDef(StPxlHitCollection,1)
};

//inline const StSPtrVecPixelHit& StPxlHitCollection::hits() const { return mHits; }
//inline StSPtrVecPixelHit& StPxlHitCollection::hits() { return mHits; }
inline unsigned int StPxlHitCollection::numberOfHits() const {return mHits.size();}

#endif
