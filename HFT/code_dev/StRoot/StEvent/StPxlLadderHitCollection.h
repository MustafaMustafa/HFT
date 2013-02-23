/*!
 * \class StPxlLadderHitCollection 
 * \author Thomas Ullrich, Jan 2006
 */
/***************************************************************************
 *
 * $Id: StPxlLadderHitCollection.h,v 1.3 2013/01/31 01:14:04 qiuh Exp $
 *
 * Author: Thomas Ullrich, Jan 2006
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 **************************************************************************/
#ifndef StPxlLadderHitCollection_hh
#define StPxlLadderHitCollection_hh

#include "StObject.h"
#include "StPxlSensorHitCollection.h"

class StPxlLadderHitCollection : public StObject {
public:
    StPxlLadderHitCollection();
    ~StPxlLadderHitCollection();

    unsigned int numberOfHits() const;
    unsigned int numberOfSensors() const { return mNumberOfSensors; }
        
    StPxlSensorHitCollection*       sensor(unsigned int);
    const StPxlSensorHitCollection* sensor(unsigned int) const;
    
private:
    enum { mNumberOfSensors = 10 };
    StPxlSensorHitCollection mSensors[mNumberOfSensors];
    
    ClassDef(StPxlLadderHitCollection,1)
};
#endif
