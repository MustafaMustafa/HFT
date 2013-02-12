/**
   \class StPxlISim

   \brief An abstract class (interface) for all PXL simulation algorithms. 

   Author: M. Mustafa
*/

#ifndef STAR_STPXLISIM_H
#define	STAR_STPXLISIM_H

#include "TNamed.h"

class TDataSet;
class StMcPixelHitCollection;
class StPxlHitCollection;
class StPxlRawHitCollection;
class g2t_pix_hit_st; // temp

class StPxlISim : public TNamed
{
public:
    StPxlISim(const Char_t *name): TNamed(name,name){}
    virtual Int_t initRun(const TDataSet& calib_db,const Int_t run) = 0;
    virtual Int_t addPxlHits(const StMcPixelHitCollection&, StPxlHitCollection& ){return 0;};
    //virtual Int_t addPxlRawHits(const StMcPixelHitCollection&, StPxlRawHitCollection& );
};

#endif	/* STPXLISIM_H */

