/*
 * $Id: $
 *
 * Author: M. Mustafa
 *
 * 
 **********************************************************
 * $Log: $
 *
 */

/**
   \class StPxlPileupAdder

   \brief Class to add pile up hits to StMcPxlHitCollection

   THIS IS A HACK THAT IS NOT IN THE OFFICIAL STAR VERSION

   This class conforms to the STAR StMaker standards.
*/

#ifndef STAR_StPxlPileupAdder
#define STAR_StPxlPileupAdder

class TString;
class TBranch;
class TFile;
class TTree;
class StMcPxlHitCollection;
class TObjectSet;
class StPxlDb;

const int MAXHIT = 200000;

class StPxlPileupAdder
{
 public:

  /*! \brief Constructor */ 
  StPxlPileupAdder(){}

  /*! \brief This class does not own any hit containers.
  */
  ~StPxlPileupAdder();


  Int_t init(TString pileupFileName,const TObjectSet*);
  Int_t addPxlHits(StMcPxlHitCollection&);

  /*! \brief Documentation method. GetCVS can be called from the chain, providing a list
   *  of all maker versions in use.
  */

 virtual const char *GetCVS() const
  {static const char cvs[]=""__DATE__" "__TIME__ ; return cvs;}

 private:
 StPxlDb* mPxlDb;
 TFile* mPileupFile;
 TTree* mPileupTree;

 // pileup tree 
   Float_t x[MAXHIT], y[MAXHIT], z[MAXHIT], xLoc[MAXHIT], yLoc[MAXHIT], zLoc[MAXHIT],
	 px[MAXHIT], py[MAXHIT], pz[MAXHIT], de[MAXHIT], ds[MAXHIT];
   Long64_t key[MAXHIT], vid[MAXHIT];
   Int_t layer[MAXHIT], nhits;

   TBranch  *b_nhits;   //! 
   TBranch  *b_x;   //! 
   TBranch  *b_y;   //! 
   TBranch  *b_z;   //! 
   TBranch  *b_xLoc;   //! 
   TBranch  *b_yLoc;   //! 
   TBranch  *b_zLoc;   //! 
   TBranch  *b_px;   //! 
   TBranch  *b_py;   //! 
   TBranch  *b_pz;   //! 
   TBranch  *b_de;   //! 
   TBranch  *b_ds;   //! 
   TBranch  *b_key;   //! 
   TBranch  *b_vid;   //! 
   TBranch  *b_layer;   //! 

   Long64_t get_vid(Int_t);
 
};
#endif
