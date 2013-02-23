/*!
 * \class StPxlSectorHitCollection 
 * \author Thomas Ullrich, Jan 2006
 */
/***************************************************************************
 *
 * $Id: StPxlSectorHitCollection.h,v 1.3 2013/01/31 01:14:04 qiuh Exp $
 *
 * Author: Thomas Ullrich, Jan 2006
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 **************************************************************************/
#ifndef StPxlSectorHitCollection_hh
#define StPxlSectorHitCollection_hh

#include "StObject.h"
#include "StPxlLadderHitCollection.h"

class StPxlSectorHitCollection : public StObject {
public:
    StPxlSectorHitCollection();
    ~StPxlSectorHitCollection();

    unsigned int numberOfHits() const;
    unsigned int numberOfLadders() const { return mNumberOfLadders; }
        
    StPxlLadderHitCollection*       ladder(unsigned int);
    const StPxlLadderHitCollection* ladder(unsigned int) const;
    
private:
    enum { mNumberOfLadders = 4 };
    StPxlLadderHitCollection mLadders[mNumberOfLadders];
    
    ClassDef(StPxlSectorHitCollection,1)
};
#endif
