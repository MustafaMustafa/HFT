/*
 * Author: M. Mustafa
 * 
 */
/**
   \class StPxlDigmapsSim

   \brief STAR wrapper for DIGMAPS package.

   This class conforms to the STAR StMaker standards.
*/

#ifndef STAR_StPxlDigmapsSim
#define STAR_StPxlDigmapsSim

#include "StPxlISim.h"


class DIGPlane;
class DIGADC;
class DIGTransport;

class StPxlDigmapsSim: public StPxlISim
{
 public:

  /*! \brief Constructor */ 
  StPxlDigmapsSim(const Char_t *name="pxlDigmapsSim"): StPxlISim(name){mDigAdc=0;mDigPlane=0;mDigTransport=0;}

  /*! \brief This class does not own any hit containers.
   *        mRandom is deleted here. 
  */
  virtual ~StPxlDigmapsSim();


  /*! \brief A random seed is passed to mRandom 
   * PXL smearing resolutions (PixelHitError) are fetched from calib_db.
   * 
   * returns kStOk if resolutions have been fetched successfully. kStErr otherwise.
   */
  virtual Int_t initRun(const TDataSet& calib_db, const Int_t run);

   /*! \brief creates an StPxlHit object for every StMcPixelHit, and fills the
   *  hit StPxlHitCollection container. 
   * 
   *  Returns:
   *  kStOk: if hits have been loaded to StPxlHitCollection successfully.
  */
virtual Int_t addPxlRawHits(const StMcPxlHitCollection& in, StPxlRawHitCollection& out);

  /*! \brief Documentation method. GetCVS can be called from the chain, providing a list
   *  of all maker versions in use.
  */
 virtual const char *GetCVS() const
  {static const char cvs[]="Tag $Name$ $Id$ built "__DATE__" "__TIME__ ; return cvs;}

private: 
    Double_t         LandauLaw(Double_t mean, Double_t sigma);

private:
    DIGPlane* mDigPlane;
    DIGADC* mDigAdc;
    DIGTransport* mDigTransport;
};
#endif
