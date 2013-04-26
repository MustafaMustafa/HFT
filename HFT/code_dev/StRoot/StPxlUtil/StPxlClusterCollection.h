/*!
 * \class StPxlClusterCollection 
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
#ifndef StPxlClusterCollection_hh
#define StPxlClusterCollection_hh

#include "StObject.h"
#include "StPxlCluster.h"
#include "StPxlConstants.h"

const int maxNClustersPerSensor = 1000;

class StPxlClusterCollection : public StObject {
public:
    StPxlClusterCollection();
    ~StPxlClusterCollection();
    
    StPxlCluster clusters[nPxlSectors][nPxlLaddersPerSector][nPxlSensorsPerLadder][maxNClustersPerSensor];
    unsigned int nClusters[nPxlSectors][nPxlLaddersPerSector][nPxlSensorsPerLadder];

    StPxlCluster* newCluster(int sector, int ladder, int sensor); //access to a new cluster, 0-9, 0-3, 0-9
    
    ClassDef(StPxlClusterCollection,1)
};

#endif
