/**
   \class StPxlISim

   \brief An abstract class (interface) for all PXL simulation algorithms. 

   Author: M. Mustafa
*/

#ifndef STAR_STPXLISIM_H
#define	STAR_STPXLISIM_H

class TNamed;
class TDataset;
class StMcPixelHitCollection;
class StPxlHitCollection;
class StPxlRawHitCollection;
class g2t_pix_hit_st; // temp

class StPxlISim : public TNamed
{
public:
    virtual Int_t init(const TDataSet& calib_db) = 0;
    virtual Int_t addPxlHits(const StMcPixelHitCollection&, StPxlHitCollection&, const g2t_pix_hit_st&);
    virtual Int_t addPxlRawHits(const StMcPixelHitCollection&, StPxlRawHitCollection& );
};

#endif	/* STPXLISIM_H */

