#include <cmath>
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TString.h"
#include "StEvent.h"
#include "StEvent/StPrimaryVertex.h"
#include "StMcEvent.hh"
#include "StMcEvent/StMcVertex.hh"
#include "StMcEvent/StMcHit.hh"
#include "StMcEvent/StMcPxlHit.hh"
#include "StMessMgr.h"

#include "StHistograms.h"

// ClassImp(StHistograms)

StHistograms::StHistograms(TString fileBaseName) : mOutFile(NULL), mhVz(NULL), mhNHits(NULL)
{
  mOutFile = new TFile(Form("%s.hists.root",fileBaseName.Data()),"RECREATE");

  mhVz = new TH1F("hVz","hVz;V_{z}(cm)",100,-10,10);

  mhNHits = new TH1F("mhNHits","mhNHits;nHits",20,0,20);

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
  mhVz->Fill(mcEvent->primaryVertex()->position().z());
}
void StHistograms::addEvent(StEvent const* const event)
{
  mhVz->Fill(event->primaryVertex()->position().z());
}

void StHistograms::addHits(Layer layer,StMcHit const* hit1,StMcHit const* hit2)
{
  if(hit1) mHists[layer].h1Hit1Pt->Fill(hit1->localMomentum().perp());
  if(hit2) mHists[layer].h1Hit2Pt->Fill(hit2->localMomentum().perp());

  if(hit1 && hit2)
  {
    mHists[layer].h2XDiffVsPt->Fill(hit1->localMomentum().perp(),hit1->position().x()-hit2->position().x());
    mHists[layer].h2YDiffVsPt->Fill(hit1->localMomentum().perp(),hit1->position().y()-hit2->position().y());
    mHists[layer].h2ZDiffVsPt->Fill(hit1->localMomentum().perp(),hit1->position().z()-hit2->position().z());
  }
}

void StHistograms::addHits(StPtrVecMcPxlHit const & hits1, StPtrVecMcPxlHit const & hits2)
{
  LOG_INFO <<" --------------------------------- "<<endm;

  mhNHits->Fill(hits1.size());

  if(hits1.size() != hits2.size())
  {
    LOG_INFO <<" ----------Different Sizes---------- "<<endm;
  }
  
  LOG_INFO <<" ----------hits1------------ "<<endm;

  for(size_t iHit1 = 0; iHit1 < hits1.size(); ++iHit1)
  {
    StMcPxlHit const* hit1 = static_cast<StMcPxlHit*>(hits1[iHit1]);
    LOG_INFO << "volId/sector/ladder/sensor: " << (int)hit1->sector() <<"/"<<(int)hit1->ladder()<<"/"<<(int)hit1->sensor()<<endm;
    hit1->Print();
  }

  LOG_INFO <<" ----------hits2------------ "<<endm;
  for(size_t iHit2 = 0; iHit2 < hits2.size(); ++iHit2)
  {
    StMcPxlHit const* hit2 = static_cast<StMcPxlHit*>(hits2[iHit2]);
    LOG_INFO << "volId/sector/ladder/sensor: " << (int)hit2->sector() <<"/"<<(int)hit2->ladder()<<"/"<<(int)hit2->sensor()<<endm;
    hit2->Print();
  }

  if(hits1.size() >= hits2.size())
  {
    for(size_t iHit1 = 0; iHit1 < hits1.size(); ++iHit1)
    {
      StMcPxlHit const* hit1 = static_cast<StMcPxlHit*>(hits1[iHit1]);
      StMcPxlHit* hit2 = NULL;

      for(size_t iHit2 = 0; iHit2 < hits2.size(); ++iHit2)
      {
        if((hits2[iHit2]->volumeId() == hit1->volumeId()) ||
            ((hits2[iHit2]->position() - hit1->position()).mag() < 0.2))
        {
          hit2 = static_cast<StMcPxlHit*>(hits2[iHit2]);
          break;
        }
      }

      Layer layer = (int)hit1->ladder() == 1? kPxl1 : kPxl2;
      addHits(layer,hit1,hit2);
    }
  }
  else
  {
    for(size_t iHit2 = 0; iHit2 < hits2.size(); ++iHit2)
    {
      StMcPxlHit const* hit2 = static_cast<StMcPxlHit*>(hits2[iHit2]);
      StMcPxlHit* hit1 = NULL;

      for(size_t iHit1 = 0; iHit1 < hits1.size(); ++iHit1)
      {
        if((hits1[iHit1]->volumeId() == hit2->volumeId()) ||
            ((hits1[iHit1]->position() - hit2->position()).mag() < 0.2))
        {
          hit1 = static_cast<StMcPxlHit*>(hits1[iHit1]);
          break;
        }
      }

      Layer layer = (int)hit2->ladder() == 1? kPxl1 : kPxl2;
      addHits(layer,hit1,hit2);
    }
  }
}

void StHistograms::closeFile()
{
  mOutFile->cd();
  mhVz->Write();
  mhNHits->Write();

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
  h2XDiffVsPt = new TH2F(Form("h2%s%s%sXDiffVsPt",layerName.Data(),hit1Name.Data(), hit2Name.Data()),";p_{T}(GeV/c);#DeltaX(cm)",50,0,5,4000,-0.4,0.4);
  h2YDiffVsPt = new TH2F(Form("h2%s%s%sYDiffVsPt",layerName.Data(),hit1Name.Data(), hit2Name.Data()),";p_{T}(GeV/c);#DeltaY(cm)",50,0,5,4000,-0.4,0.4);
  h2ZDiffVsPt = new TH2F(Form("h2%s%s%sZDiffVsPt",layerName.Data(),hit1Name.Data(), hit2Name.Data()),";p_{T}(GeV/c);#DeltaZ(cm)",50,0,5,4000,-0.4,0.4);
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
