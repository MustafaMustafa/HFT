/**
   \class StPixelSlowSimMaker

   \brief This class is an interface to DIGMAPS

   This class conforms to the STAR StMaker standards.
 
   Author: M. Mustafa
*/

#ifndef STAR_StPixelSlowSimMaker
#define STAR_StPixelSlowSimMaker

#ifndef StMaker_H
#include "StMaker.h"
#endif

#include <vector>
class StRandom;
class StMcPixelHitCollection;

class StPixelSlowSimMaker : public StMaker 
{
public:

  /* \brief Constructor uses standard Maker text naming convention,
     with value "PixelSlowSim"*/
  StPixelSlowSimMaker(const Char_t *name="PixelSlowSim") :StMaker(name){}

  /* Please note: The destructor is empty. StEvent will own any hits
     created by this maker, and is responsible for cleanup.
  */
  virtual  ~StPixelSlowSimMaker();


  /* \brief This is called every event, and contains all the activity
     of making StHit objects.

   // needs to be updated for the slow simulator -- Mustafa
     Make() creates an StPxlHit object for every MChit, and fills the
     hit container. Hit container is passed to StEvent.

     Returns kStOk always.
  */
  virtual Int_t Make();

  /* \brief Init */
  virtual Int_t Init();

 /* \brief InitRun method is not currently used. */
  virtual Int_t InitRun(Int_t);
  
  /* \brief Documentation method. GetCVS can be called from the chain, providing a list
     of all maker versions in use.
  */
  virtual const char *GetCVS() const
  {
    static const char cvs[]="Tag $Name:  $ $Id: St_TLA_Maker.h,v 1.15 2003/09/10 19:47:43 perev Exp $ built "__DATE__" "__TIME__ ; 
    return cvs;
  }


protected:

    StRandom* mRandom;

  ClassDef(StPixelSlowSimMaker,1)   //StAF chain virtual base class for Makers
};

#endif



