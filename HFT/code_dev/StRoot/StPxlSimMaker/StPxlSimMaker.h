/*
 * $Id: StPxlSimMaker.h,v 1.1 2013/05/12 21:43:33 jeromel Exp $
 *
 * Author: M. Mustafa
 *
 * 
 **********************************************************
 * $Log: StPxlSimMaker.h,v $
 * Revision 1.1  2013/05/12 21:43:33  jeromel
 * Initial revision, code peer review closed 2013/05/06
 *
 * Revision 1.4  2013/05/03 15:08:19  mstftsm
 *
 */

/**
   \class StPxlSimMaker

   \brief maker for all PXL simulators

   This maker should be called for all PXL simulators.
   The simulation algorithm depends on the StPxlISim used. 
   The default algorithm is StPxlFastSim.
   Options for other alogrithms should be set using SetAttr method.

   This class conforms to the STAR StMaker standards.
*/

#ifndef STAR_StPxlSimMaker
#define STAR_StPxlSimMaker

#ifndef StMaker_H
#include "StMaker.h"
#endif

class StPxlISim;

class StPxlSimMaker : public StMaker 
{
 public:

  /*! \brief Constructor uses standard Maker text naming convention,
   *  with value "pxlSimMaker"*/
  StPxlSimMaker(const Char_t *name="pxlSimMaker");

  /*! \brief StEvent will own any hits created by this maker, and is responsible for cleanup.
  */
  virtual ~StPxlSimMaker();


  /*! \brief calls the StPxlISim methods.
   * 
   *  Returns kStOk always.
  */
  virtual Int_t  Make();

  /*! \brief checks if other simulators have been requested and initializes StPxlISim accordingly.
   */
  virtual Int_t Init();

 /*! \brief gets the DB and initializes StPxlISim for this run.
  */
  virtual Int_t InitRun(Int_t);

  void useDIGMAPSSim() {SetAttr("useDIGMAPSSim",kTRUE);}
  /*! \brief Documentation method. GetCVS can be called from the chain, providing a list
   *  of all maker versions in use.
  */
  virtual const char *GetCVS() const
  {static const char cvs[]="Tag $Name:  $ $Id: StPxlSimMaker.h,v 1.1 2013/05/12 21:43:33 jeromel Exp $ built "__DATE__" "__TIME__ ; return cvs;}

private:
    StPxlISim* mPxlSimulator;

    Bool_t mUseFastSim;
    Bool_t mUseDIGMAPSSim;


  ClassDef(StPxlSimMaker,1)   //StAF chain virtual base class for Makers
};
#endif

/*
 * $Id: StPxlSimMaker.h,v 1.1 2013/05/12 21:43:33 jeromel Exp $
 *
 * 
 **********************************************************
 * $Log: StPxlSimMaker.h,v $
 * Revision 1.1  2013/05/12 21:43:33  jeromel
 * Initial revision, code peer review closed 2013/05/06
 *
 * Revision 1.4  2013/05/03 15:08:19  mstftsm
 *
 */

