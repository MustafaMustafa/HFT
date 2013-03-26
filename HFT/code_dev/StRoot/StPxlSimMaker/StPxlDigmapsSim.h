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
class StRandom;

//! coordinates of PXL sensor active area to restrict smeared hits to active area
//! see doc/PXL_ultimate_sensor_flemming.pdf
const Double_t PXL_ACTIVE_X_LENGTH = 1.921;
const Double_t PXL_ACTIVE_Y_LENGTH = 1.9872;


class StPxlFastSim: public StPxlISim
{
 public:

  /*! \brief Constructor */ 
  StPxlFastSim(const Char_t *name="pxlFastSim"): StPxlISim(name){mRandom=0;}

  /*! \brief This class does not own any hit containers.
   *        mRandom is deleted here. 
  */
  virtual ~StPxlFastSim();


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
  virtual Int_t addPxlHits(const StMcPixelHitCollection&, StPxlHitCollection&);

  /*! \brief Documentation method. GetCVS can be called from the chain, providing a list
   *  of all maker versions in use.
  */
 virtual const char *GetCVS() const
  {static const char cvs[]="Tag $Name$ $Id$ built "__DATE__" "__TIME__ ; return cvs;}

 private:
  //Routine to smear hit by resolution with gaussian, mean zero and width res.
  Double_t distortHit(Double_t x, Double_t res, Double_t constraint);

 private:
  StRandom* mRandom;

  Double_t mResXPix;
  Double_t mResYPix;
  Double_t mResZPix;
};
#endif
