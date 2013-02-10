/*
 * $Id: StPxlFastSimMaker.h,v 1.13 2009/02/06 20:48:48 wleight Exp $
 *
 * Author: A. Rose, LBL, Y. Fisyak, BNL, M. Miller, MIT, M. Mustafa
 *
 * 
 **********************************************************
 * $Log: StPixelFastSimMaker.h,v $
 * Revision 1.13  2009/02/06 20:48:48  wleight
 * UPGR15 Update
 *
 * Revision 1.12  2009/01/26 14:50:46  fisyak
 * Clean up
 *
 * Revision 1.11  2007/11/06 16:20:07  wleight
 * Digitized Pixel, removed all hit smearing, and implemented idTruth
 *
 * Revision 1.10  2007/10/18 14:25:13  didenko
 * updates for pile-up events
 *
 * Revision 1.9  2007/09/09 17:00:33  fisyak
 * Fix bug 1056
 *
 * Revision 1.8  2007/04/23 18:11:48  andrewar
 * Removed references to Hpd (includes were obsolete)
 *
 * Revision 1.7  2007/04/16 19:10:52  wleight
 * Added IST simulation (digitization but no clustering)
 *
 * Revision 1.6  2007/04/06 14:55:33  andrewar
 * Shift of HFT to face of ladder.
 *
 * Revision 1.5  2006/12/15 02:17:20  wleight
 * Ist now gets hit smearing parameters from the database
 *
 * Revision 1.4  2006/12/14 23:52:52  andrewar
 * Added Sevil's hit error db loader.
 *
 * Revision 1.3  2006/11/29 21:42:20  andrewar
 * Update with Pixel resolution smearing.
 *
 * Revision 1.2  2006/11/28 21:29:13  wleight
 * Added smearing for Hpd and Ist and a switch to turn it on and off
 *
 * Revision 1.1  2006/02/03 20:11:57  fisyak
 * The initial revision
 *
 *
 */

/**
   \class StPxlFastSim

   \brief Class to simulate Pixel hits from Monte Carlo.

   This class has the responsibility to create StPxlHit objects and store them in
   StPxlHitCollection.

   StPxlHit is a Gaussian smeared StMcPixelHit. 

   This class conforms to the STAR StMaker standards.
*/

#ifndef STAR_StPxlFastSim
#define STAR_StPxlFastSim

#include "StPxlISim.h"
#include "StThreeVectorF.hh"
#include "StThreeVectorD.hh"
#include <vector>
class StRandom;

//! coordinates of PXL sensor active area to restrict smeared hits to active area
//! see doc/PXL_ultimate_sensor_flemming.pdf
const Double_t PXL_MAX_X_CORD = 2.0220;
const Double_t PXL_MAX_Y_CORD = 2.2710;


class StPxlFastSim: public StPxlISim
{
 public:

  /*! \brief Constructor */ 
  StPxlFastSim(const Char_t *name="pxlFastSim"): TNamed(name){}

  /*! \brief This class does not own any hit containers.
   *        mRandom is deleted here. 
  */
  virtual ~StPxlFastSim();


  /*! \brief A random seed is passed to mRandom 
   * and mPixelPileupSimMaker is created and initiated here.
   * PXL smearing resolutions (PixelHitError) are fetched from calib_db.
   * 
   * returns KkStOk if resolutions have been fetched successfully. kStErr otherwise.
   */
  virtual Int_t init(const TDataSet& calib_db);

   /*! \brief creates an StPxlHit object for every StMcPixelHit, and fills the
   *  hit StPxlHitCollection container. 
   * 
   *  Returns kStOk always (for now).
  */
  virtual Int_t addPxlHits(const StMcPixelHitCollection&, StPxlHitCollection& ,const g2t_pix_hit_st&);

  /*! \brief Documentation method. GetCVS can be called from the chain, providing a list
   *  of all maker versions in use.
  */
 virtual const char *GetCVS() const
  {static const char cvs[]="Tag $Name$ $Id$ built "__DATE__" "__TIME__ ; return cvs;}

 private:
  //Routine to smear hit by resolution with gaussian, mean zero and width res
  Double_t distortHit(Double_t x, Double_t res, Double_t sensorLenght);

 private:
  StRandom* mRandom;

  Double_t mResZPix;
  Double_t mResXPix;
};
#endif
