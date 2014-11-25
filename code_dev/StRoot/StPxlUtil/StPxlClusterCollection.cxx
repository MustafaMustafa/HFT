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
#include "StPxlClusterCollection.h"
#include <iostream>
using namespace std;

ClassImp(StPxlClusterCollection)

StPxlClusterCollection::StPxlClusterCollection()
{
    for (int i=0; i<nPxlSectors; i++)
        for(int j=0; j<nPxlLaddersPerSector; j++)
            for(int k=0; k<nPxlSensorsPerLadder; k++)
                nClusters[i][j][k] = 0;
}

StPxlClusterCollection::~StPxlClusterCollection() {}

StPxlCluster* StPxlClusterCollection::newCluster(int sector, int ladder, int sensor)
{
    if(sector < 0 || sector >= nPxlSectors)
        {
            cout<<"StPxlClusterCollection::newCluster() : wrong sector: "<<sector<<endl;
            return 0;
        }
    if(ladder < 0 || ladder >= nPxlLaddersPerSector)
        {
            cout<<"StPxlClusterCollection::newCluster() : wrong ladder: "<<ladder<<endl;
            return 0;
        }
    if(sensor < 0 || sensor >= nPxlSensorsPerLadder)
        {
            cout<<"StPxlClusterCollection::newCluster() : wrong sensor: "<<sensor<<endl;
            return 0;
        }
    int nClustersInSensor = nClusters[sector][ladder][sensor];
    if(nClustersInSensor >= maxNClustersPerSensor-1)
        {
            cout<<"StPxlClusterCollection::newCluster() : sensor array full: "<<sector<<" "<<ladder<<" "<<sensor<<endl;
            return 0;
        }
    return &clusters[sector][ladder][sensor][nClustersInSensor];

}

