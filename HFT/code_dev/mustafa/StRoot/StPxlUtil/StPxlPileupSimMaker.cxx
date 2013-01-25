/*
 *
 * Author: A. Rose, LBL, Y. Fisyak, BNL, M. Miller, MIT, M. Mustafa
 *
 * 
 **********************************************************
 */

#include "StPxlPileupSimMaker.h"
#include "StMcPixelHit.hh"
#include "StMcEventTypes.hh"
#include <stdio.h>
#include "TFile.h"
#include "TTree.h"
#include "StThreeVectorF.hh"
#include "StThreeVectorD.hh"

ClassImp(StPxlPileupSimMaker)

  
using namespace std;

StPxlPileupSimMaker::~StPxlPileupSimMaker(){ /*noop*/ }

Int_t StPxlPileupSimMaker::Init()
{
  LOG_INFO<<"StPxlPileupSimMaker::Init()"<<endm;
  
  loadPxlPileupHits();

  return StMaker::Init();
}
//___________________________
void StPxlPileupSimMaker::loadPxlPileupHits()
{
  LOG_INFO<<"+++ loading the PXL pileup files +++"<<endm;

  mPileupHitsAvailable = kTRUE;

  TFile f_pileup("pileup.root");
  
  if (f_pileup.IsZombie()) 
  {
    mPileupHitsAvailable = kFALSE;
    LOG_INFO << "no PXL pileup file found. Will run with regular setup" << endm;
    return;
  }

  LOG_INFO<<"+++ Loaded pileup.root for PXL pileup simulation +++"<<endm;

  TTree* pileup_tree = (TTree*)f_pileup.Get("pileup_tree");

  const Int_t maxhit = 200000;
  Float_t x[maxhit], y[maxhit], z[maxhit], px[maxhit], py[maxhit], pz[maxhit], de[maxhit], ds[maxhit];
  Long_t key[maxhit], vid[maxhit];
  Int_t layer[maxhit], nhits;

  TBranch *b_x = pileup_tree->GetBranch("x");
  TBranch *b_y = pileup_tree->GetBranch("y");
  TBranch *b_z = pileup_tree->GetBranch("z");
  TBranch *b_px = pileup_tree->GetBranch("px");
  TBranch *b_py = pileup_tree->GetBranch("py");
  TBranch *b_pz = pileup_tree->GetBranch("pz");
  TBranch *b_de = pileup_tree->GetBranch("de");
  TBranch *b_ds = pileup_tree->GetBranch("ds");
  TBranch *b_key = pileup_tree->GetBranch("key");
  TBranch *b_vid = pileup_tree->GetBranch("vid");
  TBranch *b_layer = pileup_tree->GetBranch("layer");
  TBranch *b_nhits = pileup_tree->GetBranch("nhits");
  b_x->SetAddress(x);
  b_y->SetAddress(y);
  b_z->SetAddress(z);
  b_px->SetAddress(px);
  b_py->SetAddress(py);
  b_pz->SetAddress(pz);
  b_de->SetAddress(de);
  b_ds->SetAddress(de);
  b_key->SetAddress(key);
  b_vid->SetAddress(vid);
  b_layer->SetAddress(layer);
  b_nhits->SetAddress(&nhits);

  pileup_tree->GetEntry(0); //.. just one events

  for(Int_t ihit = 0; ihit<nhits; ihit++) 
  {
    mPxlPileup_x.push_back(x[ihit]);
    mPxlPileup_y.push_back(y[ihit]);
    mPxlPileup_z.push_back(z[ihit]);

    mPxlPileup_px.push_back(px[ihit]);
    mPxlPileup_py.push_back(py[ihit]);
    mPxlPileup_pz.push_back(pz[ihit]);

    mPxlPileup_key.push_back(key[ihit]);
    mPxlPileup_vid.push_back(vid[ihit]);

    mPxlPileup_de.push_back(de[ihit]);
    mPxlPileup_ds.push_back(ds[ihit]);
  }

  mPileupHitsAvailable = kTRUE;
}
//____________________________________________________________
void StPxlPileupSimMaker::addPxlPileupHit(StMcPixelHitCollection* mcPxlHitCol)
{
  for(UInt_t i = 0; i<mPxlPileup_x.size(); i++) 
  {
    StThreeVectorD pos(mPxlPileup_x[i], mPxlPileup_y[i], mPxlPileup_z[i]);
    StThreeVectorF mom(mPxlPileup_px[i], mPxlPileup_py[i], mPxlPileup_pz[i]);

    Float_t de = mPxlPileup_de[i]; 
    Float_t ds = mPxlPileup_ds[i];

    Int_t key = mPxlPileup_key[i];
    Int_t vid = mPxlPileup_vid[i];

    StMcPixelHit* pxlhit = new StMcPixelHit(pos, mom, de, ds, key, vid, 0);
    mcPxlHitCol->addHit(pxlhit);
  }

  LOG_DEBUG<<"pilup hits added."<<endm;
}
//____________________________________________________________

Int_t StPxlPileupSimMaker::Make()
{
  LOG_INFO<<"StPxlPileupSimMaker::Make()"<<endm;

  return kStOK;
}
