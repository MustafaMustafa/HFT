/*!
 * \class StRnDHitCollection 
 * \author Thomas Ullrich, Jan 2006
 */
/***************************************************************************
 *
 * $Id: StPxlHitCollection.h,v 1.3 2013/01/31 01:14:04 qiuh Exp $
 *
 * Author: Thomas Ullrich, Jan 2006
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StPxlHitCollection.h,v $
 * Revision 1.3  2013/01/31 01:14:04  qiuh
 * *** empty log message ***
 *
 * Revision 2.1  2006/01/19 21:42:06  ullrich
 * Initial Revision.
 *
 **************************************************************************/
#ifndef StPxlHitCollection_hh
#define StPxlHitCollection_hh

#include "StObject.h"
#include "StPxlSectorHitCollection.h"

class StPxlHit;

class StPxlHitCollection : public StObject {
public:
    StPxlHitCollection();
    ~StPxlHitCollection();
    
    bool          addHit(StPxlHit*);
    unsigned int  numberOfHits() const;
    unsigned int  numberOfSectors() const { return mNumberOfSectors; }
    
    StPxlSectorHitCollection*       sector(unsigned int);
    const StPxlSectorHitCollection* sector(unsigned int) const;
    
private:
    enum { mNumberOfSectors = 10 };
    StPxlSectorHitCollection mSectors[mNumberOfSectors];
    
    ClassDef(StPxlHitCollection,1)
};
#endif
