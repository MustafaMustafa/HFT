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
#include "StPxlRawHitCollection.h"
#include <iostream>
using namespace std;

ClassImp(StPxlRawHitCollection)

StPxlRawHitCollection::StPxlRawHitCollection()
{
    for (int i=0; i<nPxlSectors; i++)                                                                        
        for(int j=0; j<nPxlLaddersPerSector; j++)                                                            
            for(int k=0; k<nPxlSensorsPerLadder; k++)                                                        
                nRawHits[i][j][k] = 0;
}

StPxlRawHitCollection::~StPxlRawHitCollection() {}

StPxlRawHit* StPxlRawHitCollection::newRawHit(int sector, int ladder, int sensor)
{
    if(sector < 0 || sector >= nPxlSectors)
        {
            cout<<"StPxlRawHitCollection::newRawHit() : wrong sector: "<<sector<<endl;
            return 0;
        }
    if(ladder < 0 || ladder >= nPxlLaddersPerSector)
        {
            cout<<"StPxlRawHitCollection::newRawHit() : wrong ladder: "<<ladder<<endl;
            return 0;
        }
    if(sensor < 0 || sensor >= nPxlSensorsPerLadder)
        {
            cout<<"StPxlRawHitCollection::newRawHit() : wrong sensor: "<<sensor<<endl;
            return 0;
        }
    int nRawHitsInSensor = nRawHits[sector][ladder][sensor];
    if(nRawHitsInSensor >= maxNRawHitsPerSensor-1)
        {
            cout<<"StPxlRawHitCollection::newRawHit() : sensor array full: "<<sector<<" "<<ladder<<" "<<sensor<<endl;
            return 0;
        }
    return &rawHits[sector][ladder][sensor][nRawHitsInSensor];


}
