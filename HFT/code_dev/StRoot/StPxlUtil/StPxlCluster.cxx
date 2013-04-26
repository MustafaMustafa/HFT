#include "StPxlCluster.h"
#include <iostream>
using namespace std;

ClassImp(StPxlCluster)

StPxlCluster::StPxlCluster(){
    nRawHits = 0;
}

StPxlCluster::~StPxlCluster() {}

void StPxlCluster::AddRawHit(int columnAdd, int rowAdd){
    if(nRawHits >= maxNRawHits)
        {
            cout<<"StPxlCluster::AddRawHit(): cluster full."<<endl;
            return;
        }
    column[nRawHits] = columnAdd;
    row[nRawHits] = rowAdd;
    nRawHits++;
}

void StPxlCluster::Centering(){
    float columnSum=0;
    float rowSum=0;
    for(int i=0;i<nRawHits;i++){
        columnSum += column[i];
        rowSum += row[i];
    }
    columnCenter = columnSum/float(nRawHits);
    rowCenter = rowSum/float(nRawHits);
}

void StPxlCluster::Clear(){
    nRawHits=0;
}


