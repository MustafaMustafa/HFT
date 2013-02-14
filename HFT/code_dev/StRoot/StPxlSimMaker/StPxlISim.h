/**
   \class StPxlISim

   \brief An abstract class (interface) for all PXL simulation algorithms. 

   Author: M. Mustafa
*/

#ifndef STAR_STPXLISIM_H
#define	STAR_STPXLISIM_H

#include "StMessMgr.h" 
#include "TNamed.h"

class TDataSet;
class StMcPixelHitCollection;
class StPxlHitCollection;
class StPxlRawHitCollection;

class StPxlISim : public TNamed
{
public:
    StPxlISim(const Char_t *name): TNamed(name,name){}
    virtual Int_t initRun(const TDataSet& calib_db,const Int_t run) = 0;
    virtual Int_t addPxlHits(const StMcPixelHitCollection& in, StPxlHitCollection& out){LOG_INFO<<"StPxlISim::addPxlHits is not implemented in daughter class."<<endm; return 1;}
    virtual Int_t addPxlRawHits(const StMcPixelHitCollection& in, StPxlRawHitCollection& out){LOG_INFO<<"StPxlISim::addPxlRawHits is not implemented in daughter class."<<endm; return 1;}
};
#endif	/* STPXLISIM_H */
