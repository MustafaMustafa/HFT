/***************************************************************************
 * $Id: $
 * $Log: $
 *
 *
 **************************************************************************/
#ifndef StMcPxlSensorHitCollection_hh
#define StMcPxlSensorHitCollection_hh

#include "StObject.h"
#include "StMcContainers.hh"

class StMcPxlHit;

class StMcPxlSensorHitCollection : public StObject {
public:
    StMcPxlSensorHitCollection();
    ~StMcPxlSensorHitCollection();

    StSPtrVecMcPxlHit&       hits();
    const StSPtrVecMcPxlHit& hits() const;
    
private:
    StSPtrVecMcPxlHit mHits;
    
    ClassDef(StMcPxlSensorHitCollection,1)
};
#endif
