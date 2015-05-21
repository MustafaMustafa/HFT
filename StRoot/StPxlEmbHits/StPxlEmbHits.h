#ifndef StPxlEmbHits_hh
#define StPxlEmbHits_hh

#include "StMaker.h"

class StMcEvent;
class StPxlDb;
class StMcTrack;
class StMcPxlHitCollection;
class StHistograms;

class StPxlEmbHits : public StMaker
{
  public:

   StPxlEmbHits(const Char_t *name = "pxlEmbHits");
   ~StPxlEmbHits() {}

   virtual Int_t  Init();
   virtual Int_t  InitRun(Int_t runNumber);
   virtual Int_t  Make();
   virtual Int_t  Finish();

   bool IsOnSensor(Double_t LocalPosition[3]);
   void   McTrk2RealGeo(StMcPxlHitCollection&);

  private:

   float    mBField;
   StMcEvent* mMcEvent;
   StPxlDb*   mPxlDb;
   StHistograms* mPionsHists;
   StHistograms* mKaonsHists;
   StHistograms* mProtonsHists;

   ClassDef(StPxlEmbHits, 1)
};
#endif
