/**
   \class StPixelPileupSimMaker

   \brief Class to add PXL pile up hits
  
   This class conforms to the STAR StMaker standards.
  
   Author: A. Rose, LBL, Y. Fisyak, BNL, M. Miller, MIT, M. Mustafa
*/

#ifndef STAR_StPixelPileupSimMaker
#define STAR_StPixelPileupSimMaker
#ifndef StMaker_H
#include "StMaker.h"
#endif
#include <vector>
class StMcPixelHitCollection;

class StPixelPileupSimMaker : public StMaker 
{
 public:

  /* \brief Constructor uses standard Maker text naming convention,
     with value "PixelPileupSim"*/
  StPixelPileupSimMaker(const Char_t *name="PixelPileupSim") :StMaker(name){}

  /* Please note: The destructor is empty. Nothing is owned by this class. 
  */
  virtual ~StPixelPileupSimMaker();


  /* \brief This maker is empty.
   * 
     Returns kStOk always.
  */
  virtual Int_t  Make();

  /* \brief loads the pile hits. 
   * 
   *  Returns 1 if pileup hits were loaded successfully. 0 otherwise. 
   */
  virtual Int_t Init();

  /* \brief Documentation method. GetCVS can be called from the chain, providing a list
     of all maker versions in use.
  */
  virtual const char *GetCVS() const
  {
    static const char cvs[]="Tag $Name:  $ $Id: StPixelPileupSimMaker.h,v 1.13 2009/02/06 20:48:48 wleight Exp $ built "__DATE__" "__TIME__ ; 
    return cvs;
  }

  //..add PIXEL pileup into the collection
  void addPixPileUpHit(StMcPixelHitCollection* pixHitCol);

 private:
  //.. load pileup hits ....
  Bool_t loadPixPileUpHits();

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
  

  ClassDef(StPixelPileupSimMaker,1)   //StAF chain virtual base class for Makers
};
#endif