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
   \class StPxlFastSimMaker

   \brief Class to simulate Pixel hits from Monte Carlo.

   This class has the responsibility for creating StPxlHit objects and storing them in
   StPxlHitCollection which is later added to StEvent.

   StPxlHit is a Gaussian smeared StMcPixelHit. 

   This class conforms to the STAR StMaker standards.
*/

#ifndef STAR_StPxlFastSimMaker
#define STAR_StPxlFastSimMaker
#ifndef StMaker_H
#include "StMaker.h"
#endif
#include "StThreeVectorF.hh"
#include "StThreeVectorD.hh"
#include <vector>
class StRandom;
class StMcPixelHitCollection;

class StPxlFastSimMaker : public StMaker 
{
 public:

  /*! \brief Constructor uses standard Maker text naming convention,
   *  with value "PxlFastSim"*/
  StPxlFastSimMaker(const Char_t *name="PxlFastSim") :StMaker(name){}

  /*! \brief StEvent will own any hits created by this maker, and is responsible for cleanup.
   *        mRandom is deleted here. 
  */
  virtual ~StPxlFastSimMaker();


  /*! \brief This is called every event, and contains all the activity
   *  of making StPxlHit objects.
   * 
   *  Make() creates an StPxlHit object for every StMcPixelHit, and fills the
   *  hit StPxlHitCollection container. StPxlHitCollection container is passed to StEvent at the end.
   * 
   *  Returns kStOk always.
  */
  virtual Int_t  Make();

  /*! \brief A random seed is passed to mRandom 
   *        and mPixelPileupSimMaker is created and initiated here.
   */
  virtual Int_t Init();

 /*! \brief Smearing resolutions for PXL are fetched here. 
  * 
  *  PXL smearing resolutions (PixelHitError) are fetched from Calibrations/tracker DB.
  */
  virtual Int_t InitRun(Int_t);
  
  /*! \brief Documentation method. GetCVS can be called from the chain, providing a list
   *  of all maker versions in use.
  */
  virtual const char *GetCVS() const
  {
    static const char cvs[]="Tag $Name:  $ $Id: StPxlFastSimMaker.h,v 1.13 2009/02/06 20:48:48 wleight Exp $ built "__DATE__" "__TIME__ ; 
    return cvs;
  }

 private:
  //Routine to smear hit by resolution with gaussian, mean zero and width res
  Double_t distortHit(Double_t x, Double_t res, Double_t detLength);


 private:
  StRandom* mRandom;

  Double_t mResZPix;
  Double_t mResXPix;
  Int_t mSmear; //to turn smearing on and off

  Bool_t mPxlPileup_on;  //.. true: if mPxlPilupSimMaker has been initiated successfully. mFALSE otherwise


  ClassDef(StPxlFastSimMaker,1)   //StAF chain virtual base class for Makers
};
#endif
