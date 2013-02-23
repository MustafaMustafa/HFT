/***************************************************************************
 *
 * $Id: $
 * $Log: $
 *
 * Author: Fabrice Retiere/Kai Schweda,  Aug 2003
 * 
 ***************************************************************************
 *
 * Description: 
 *
 *
 ***************************************************************************
 *
 *
 **************************************************************************/
#ifndef StMcPxlLadderHitCollection_hh
#define StMcPxlLadderHitCollection_hh

#include "StObject.h"
#include "StMcPxlSensorHitCollection.hh"


class StMcPxlLadderHitCollection : public StObject
{
public:
    StMcPxlLadderHitCollection();
    virtual ~StMcPxlLadderHitCollection();
    
    unsigned int numberOfHits() const;
    unsigned int numberOfSensors() const {return mNumberOfSensors;}

    StMcPxlSensorHitCollection*     sensor(unsigned int);
    const StMcPxlSensorHitCollection* sensor(unsigned int) const;

protected:
    enum { mNumberOfSensors = 10 };
    StMcPxlSensorHitCollection mSensors[mNumberOfSensors];

    ClassDef(StMcPxlLadderHitCollection,1)
};
#endif
