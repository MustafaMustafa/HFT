/*!
 * \class StPxlRawHitCollection 
 * \author Qiu Hao, March 2013
 */
/***************************************************************************
 *
 * $Id$
 *
 * Author: Qiu Hao, March 2013
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log$
 *
 **************************************************************************/
#ifndef StPxlRawHitCollection_hh
#define StPxlRawHitCollection_hh

#include "StObject.h"
#include "StPxlRawHit.h"
#include "StPxlConstants.h"

const int maxNRawHitsPerSensor = 1000;

class StPxlRawHitCollection : public StObject {
public:
    StPxlRawHitCollection();
    ~StPxlRawHitCollection();
    
    StPxlRawHit rawHits[nPxlSectors][nPxlLaddersPerSector][nPxlSensorsPerLadder][maxNRawHitsPerSensor];
    unsigned int nRawHits[nPxlSectors][nPxlLaddersPerSector][nPxlSensorsPerLadder];
    
    StPxlRawHit* newRawHit(int sector, int ladder, int sensor); //access to a new rawHit, 0-9, 0-3, 0-9

    ClassDef(StPxlRawHitCollection,1)
};

#endif
