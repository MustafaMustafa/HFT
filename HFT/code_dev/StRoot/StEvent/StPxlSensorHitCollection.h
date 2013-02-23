/*!
 * \class StPxlSensorHitCollection 
 * \author Thomas Ullrich, Jan 2006
 */
/***************************************************************************
 *
 * $Id: StPxlSensorHitCollection.h,v 1.3 2013/01/31 01:14:04 qiuh Exp $
 *
 * Author: Thomas Ullrich, Jan 2006
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 **************************************************************************/
#ifndef StPxlSensorHitCollection_hh
#define StPxlSensorHitCollection_hh

#include "StObject.h"
#include "StContainers.h"

class StPxlHit;

class StPxlSensorHitCollection : public StObject {
public:
    StPxlSensorHitCollection();
    ~StPxlSensorHitCollection();

    StSPtrVecPxlHit&       hits();
    const StSPtrVecPxlHit& hits() const;
    
private:
    StSPtrVecPxlHit mHits;
    
    ClassDef(StPxlSensorHitCollection,1)
};
#endif
