/*!
 * \class StRnDHitCollection 
 * \author Thomas Ullrich, Jan 2006
 */
/***************************************************************************
 *
 * $Id: StPxlRawHitCollection.h,v 1.3 2013/01/31 01:14:04 qiuh Exp $
 *
 * Author: Thomas Ullrich, Jan 2006
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StPxlRawHitCollection.h,v $
 * Revision 1.3  2013/01/31 01:14:04  qiuh
 * *** empty log message ***
 *
 * Revision 2.1  2006/01/19 21:42:06  ullrich
 * Initial Revision.
 *
 **************************************************************************/
#ifndef StPxlRawHitCollection_hh
#define StPxlRawHitCollection_hh

#include "StObject.h"
#include "StContainers.h"

class StPxlRawHit;

class StPxlRawHitCollection : public StObject {
public:
    StPxlRawHitCollection();
    ~StPxlRawHitCollection();
    // StPxlRawHitCollection(const StPxlRawHitCollection&); use default
    // const StPxlRawHitCollection&
    // operator=(const StPxlRawHitCollection&);           use default
    
    StSPtrVecPxlRawHit&       hits();
    const StSPtrVecPxlRawHit& hits() const;

    bool          addHit(StPxlRawHit*);
    unsigned int  numberOfHits() const;
    
private:
    StSPtrVecPxlRawHit mHits;
    
    ClassDef(StPxlRawHitCollection,1)
};

//inline const StSPtrVecPixelHit& StPxlRawHitCollection::hits() const { return mHits; }
//inline StSPtrVecPixelHit& StPxlRawHitCollection::hits() { return mHits; }
inline unsigned int StPxlRawHitCollection::numberOfHits() const {return mHits.size();}

#endif
