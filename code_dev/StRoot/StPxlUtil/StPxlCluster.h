//  2008 09 30 by Xiangming Sun
#ifndef StPxlCluster_hh
#define StPxlCluster_hh

#include "Rtypes.h"
#include "TObject.h"
const int maxNRawHits = 20;

class StPxlCluster: public TObject{
public:
    StPxlCluster();
    ~StPxlCluster();
    int nRawHits;
    int column[maxNRawHits]; 
    int row[maxNRawHits]; 
    float columnCenter;
    float rowCenter;
    void AddRawHit(int column, int row);
    void Centering();
    void Clear();
    ClassDef(StPxlCluster,1)
};

#endif 
