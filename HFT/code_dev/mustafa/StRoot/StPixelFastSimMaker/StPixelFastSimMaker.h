/*
 * $Id: StPixelFastSimMaker.h,v 1.13 2009/02/06 20:48:48 wleight Exp $
 *
 * Author: A. Rose, LBL, Y. Fisyak, BNL, M. Miller, MIT
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
   \class StPixelFastSimMaker

   \brief Class to simulate Pixel and Ist hits from Monte Carlo.

   The HFT and IST hits slow simulator will evolve over time. This class
   has responsibility for creating StHit objects and storing them in the
   appropriate container. The created container is then added to the
   reconstructed event.

   Currently (Jan, 2006), we simply store the perfect Monte Carlo position
   for each hit. This will change as the simulations become more complex.
   In particular, for the HFT gaussian smearing will be introduced as a
   first approximation. For the IST, a more complicated simulator is needed
   to account for ambiguities in hit recconstruction. That is not the
   purpose of this maker.

   This class conforms to the STAR StMaker standards.
*/

#ifndef STAR_StPixelFastSimMaker
#define STAR_StPixelFastSimMaker
#ifndef StMaker_H
#include "StMaker.h"
#endif
#include "StThreeVectorF.hh"
#include "StThreeVectorD.hh"
#include <vector>
class StRandom;
class StMcPixelHitCollection;

class StPixelFastSimMaker : public StMaker {
 public:

  /* \brief Constructor uses standard Maker text naming convention,
     with value "PixelFastSim"*/
  StPixelFastSimMaker(const Char_t *name="PixelFastSim") :StMaker(name){}

  /* Please note: The destructor is empty. StEvent will own any hits
     created by this maker, and is responsible for cleanup.
  */
  virtual       ~StPixelFastSimMaker();


  /* \brief This is called every event, and contains all the activity
     of making StHit objects.

     Make() creates an StPxlHit object for every MChit, and fills the
     hit container. Hit container is passed to StEvent.

     Returns kStOk always.
  */
  virtual Int_t  Make();

  /* \brief A random seed is passed to mRandom */
  virtual Int_t Init();

 /* \brief Smearing resolutions for PXL and IST are fetched here. */
  virtual Int_t InitRun(Int_t);
  
  /* \brief Documentation method. GetCVS can be called from the chain, providing a list
     of all maker versions in use.
  */
  virtual const char *GetCVS() const
  {
    static const char cvs[]="Tag $Name:  $ $Id: StPixelFastSimMaker.h,v 1.13 2009/02/06 20:48:48 wleight Exp $ built "__DATE__" "__TIME__ ; 
    return cvs;
  }

 private:
  //.. load pileup hits ....
  void loadPixPileUpHits();

  //..add PIXEL pileup into the collection
  void addPixPileUpHit(StMcPixelHitCollection* pixHitCol);

  //Routine to smear hit by resolution with gaussian, mean zero and width res
  Double_t distortHit(Double_t x, Double_t res, Double_t detLength);


 protected:
  StRandom* mRandom;

  Double_t mResXIst1;
  Double_t mResZIst1;
  Double_t mResXIst2;
  Double_t mResZIst2;
  Double_t mResXIst3;
  Double_t mResZIst3;
  Double_t mResZPix;
  Double_t mResXPix;
  Int_t mSmear; //to turn smearing on and off

 protected:
  vector<Double_t> mPxlPileup_x; 
  vector<Double_t> mPxlPileup_y; 
  vector<Double_t> mPxlPileup_z; 
			
  vector<Float_t> mPxlPileup_px;
  vector<Float_t> mPxlPileup_py;
  vector<Float_t> mPxlPileup_pz;

  vector<Int_t> mPxlPileup_key;
  vector<Int_t> mPxlPileup_vid;

  vector<Float_t> mPxlPileup_de;
  vector<Float_t> mPxlPileup_ds;
  
  Bool_t mPxlPileup_on;  //.. true: there's a pile file on the disk and will do
		   //.. pileup simulation. 
		   //.. false: there's no pile up file on the disk and will 
		   //.. do regular production


  ClassDef(StPixelFastSimMaker,1)   //StAF chain virtual base class for Makers
};
#endif