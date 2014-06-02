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

#include "StPxlISim.h"

class StPxlPileupAdder: public StPxlISim
{
 public:

  /*! \brief Constructor */ 
  StPxlPileupAdder(const Char_t *name="pxlPileupAdder"): StPxlISim(name) {}

  /*! \brief This class does not own any hit containers.
  */
  ~StPxlPileupAdder();


  Int_t initRun();
  Int_t addPxlHits(StMcPxlHitCollection&);

  /*! \brief Documentation method. GetCVS can be called from the chain, providing a list
   *  of all maker versions in use.
  */

 virtual const char *GetCVS() const
  {static const char cvs[]=""__DATE__" "__TIME__ ; return cvs;}

 private:
};
#endif
