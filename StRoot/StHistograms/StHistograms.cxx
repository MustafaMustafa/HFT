#include <cmath>
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TString.h"
#include "StEvent.h"
#include "StMcEvent.hh"
#include "StMcEvent/StMcHit.hh"

#include "StHistograms.h"

// ClassImp(StHistograms)

StHistograms::StHistograms(TString fileBaseName) : mOutFile(NULL), mhVz(NULL)
{
  mOutFile = new TFile(Form("%s.hists.root",fileBaseName.Data()),"RECREATE");

  mhVz = new TH1F("hVz","hVz;V_{z}(cm)",100,-10,10);

  // the order here should be consistent with the enum Layer in the header file
  mHists.push_back(hists("Pxl1","Mc","McProj"));
  mHists.push_back(hists("Pxl2","Mc","McProj"));
  mHists.push_back(hists("Ist","Mc","McProj"));

}
StHistograms::~StHistograms()
{
}
void StHistograms::addEvent(StMcEvent const* const mcEvent)
{
}
void StHistograms::addEvent(StEvent const* const mcEvent)
{
}

void StHistograms::addHits(Layer layer,StMcHit const* hit1,StMcHit const* hit2)
{
  if(hit1) mHists[layer].h1Hit1Pt->Fill(hit1->localMomentum().perp());
  if(hit2) mHists[layer].h1Hit1Pt->Fill(hit2->localMomentum().perp());

  if(hit1 && hit2)
  {
    mHists[layer].h2XDiffVsPt->Fill(hit1->position().x()-hit2->position().x(),hit1->localMomentum().perp());
    mHists[layer].h2YDiffVsPt->Fill(hit1->position().y()-hit2->position().y(),hit1->localMomentum().perp());
    mHists[layer].h2ZDiffVsPt->Fill(hit1->position().z()-hit2->position().z(),hit1->localMomentum().perp());
  }
}

void StHistograms::closeFile()
{
  mOutFile->cd();
  mhVz->Write();

  for(size_t i=0;i<mHists.size();++i)
  {
    mHists[i].write(mOutFile);
  }
}
StHistograms::hists::hists(TString layerName,TString hit1Name,TString hit2Name)
  : h1Hit1Pt(NULL), h1Hit2Pt(NULL), h2XDiffVsPt(NULL), h2YDiffVsPt(NULL), h2ZDiffVsPt(NULL)
{
  h1Hit1Pt = new TH1F(Form("h%s%sPt",layerName.Data(),hit1Name.Data()),";p_{T}(GeV/c)",50,0,5);
  h1Hit2Pt = new TH1F(Form("h%s%sPt",layerName.Data(),hit2Name.Data()),";p_{T}(GeV/c)",50,0,5);
  h2XDiffVsPt = new TH2F(Form("h2%s%s%sXDiffVsPt",layerName.Data(),hit1Name.Data(), hit2Name.Data()),";p_{T}(GeV/c);#DeltaX(cm)",50,0,5,4000,-0.2,0.2);
  h2YDiffVsPt = new TH2F(Form("h2%s%s%sYDiffVsPt",layerName.Data(),hit1Name.Data(), hit2Name.Data()),";p_{T}(GeV/c);#DeltaY(cm)",50,0,5,4000,-0.2,0.2);
  h2ZDiffVsPt = new TH2F(Form("h2%s%s%sZDiffVsPt",layerName.Data(),hit1Name.Data(), hit2Name.Data()),";p_{T}(GeV/c);#DeltaZ(cm)",50,0,5,4000,-0.2,0.2);
}
void StHistograms::hists::write(TFile* outFile)
{
  outFile->cd();
  h1Hit1Pt->Write();
  h1Hit2Pt->Write();
  h2XDiffVsPt->Write();
  h2YDiffVsPt->Write();
  h2ZDiffVsPt->Write();
}
