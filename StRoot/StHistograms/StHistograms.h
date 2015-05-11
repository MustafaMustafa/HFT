#ifndef StHistograms__h
#define StHistograms__h

/* **************************************************
 *
 *  Authors: Mustafa Mustafa (mmustafa@lbl.gov)
 *
 * **************************************************
 */
#include <vector>
#include "TObject.h"

class TH1F;
class TH2F;
class TFile;
class TString;
class StEvent;
class StMcEvent;
class StMcHit;

class StHistograms: public TObject
{
  public:
   StHistograms(TString fileBaseName);
   virtual ~StHistograms();

   enum Layer{kPxl1=0,kPxl2=1,kIst};
   void addEvent(StMcEvent const *);
   void addEvent(StEvent const *);
   void addHits(Layer layer,StMcHit const* hit1,StMcHit const* hit2);
   void closeFile();

  private:
   StHistograms(){}
   StHistograms(StHistograms const &){}

   TFile* mOutFile;

   struct hists
   {
     TH1F* h1Hit1Pt;
     TH1F* h1Hit2Pt;
     TH2F* h2XDiffVsPt;
     TH2F* h2YDiffVsPt;
     TH2F* h2ZDiffVsPt;
     hists(TString layerName,TString hit1Name,TString hit2Name);
     void write(TFile*);
   };

   TH1F* mhVz;
   std::vector<hists> mHists;

   // ClassDef(StHistograms, 1)
};
#endif
