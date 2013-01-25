/**
   \class StPxlPileupSimMaker

   \brief A utility class to add PXL pile up hits. 

   This class is to be used by any PXL simulator (e.g. StPxlFastSimMaker) to add pileup hits
  
   This class conforms to the STAR StMaker standards.
  
   Author: A. Rose, LBL, Y. Fisyak, BNL, M. Miller, MIT, M. Mustafa
*/

#ifndef STAR_StPxlPileupSimMaker
#define STAR_StPxlPileupSimMaker
#ifndef StMaker_H
#include "StMaker.h"
#endif
#include <vector>
class StMcPixelHitCollection;

class StPxlPileupSimMaker : public StMaker 
{
 public:

  /*! \brief Constructor uses standard Maker text naming convention,
   *  with value "pxlPileupSim"*/
  StPxlPileupSimMaker(const Char_t *name="pxlPileupSimMaker") :StMaker(name){}

  /*! \brief The destructor is empty. Nothing is owned by this class. */ 
  virtual ~StPxlPileupSimMaker();


  /*! \brief This maker is empty.
   * 
   *  Returns kStOk always.
  */
  virtual Int_t  Make();

  /*! \brief loads the pile hits. 
   */
  virtual Int_t Init();

  /*! \brief Documentation method. GetCVS can be called from the chain, providing a list
   *  of all maker versions in use.
  */
  virtual const char *GetCVS() const
  {
    static const char cvs[]="Tag $Name:  $ $Id: StPxlPileupSimMaker.h,v 1.13 2009/02/06 20:48:48 wleight Exp $ built "__DATE__" "__TIME__ ; 
    return cvs;
  }

  /*! \brief This adds PXL pileup hits into the collection */
  void addPxlPileupHit(StMcPixelHitCollection* mcPxlHitCol);

  /*! \brief returns kTRUE if pilehits were loaded successfully, kFALSE otherwise */
  inline Bool_t pileupHitsAvailable(){return mPileupHitsAvailable;}
 

private:
  //! .. load pileup hits ....
  void loadPxlPileupHits();

private:
  Bool_t mPileupHitsAvailable;
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

  ClassDef(StPxlPileupSimMaker,1)   //StAF chain virtual base class for Makers
};
#endif
