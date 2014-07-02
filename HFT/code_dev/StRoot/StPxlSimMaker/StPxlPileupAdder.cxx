/*
 *
 * Author: M. Mustafa
 */

#include <stdio.h>

#include "StMessMgr.h"
#include "Stypes.h"
#include "Stiostream.h"
#include "StPxlPileupAdder.h"
#include "StMcEvent/StMcPxlHitCollection.hh"
#include "StMcEvent/StMcPxlHit.hh"
#include "StThreeVectorF.hh"

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"


StPxlPileupAdder::~StPxlPileupAdder()
{
}
//____________________________________________________________
Int_t StPxlPileupAdder::init(TString pileupFileName)
{
   // run is not used in the current implementation, but might be necessary in the future.
   LOG_INFO << "StPxlPileupAdder::init()" << endm;

   mPileupFile = new TFile(pileupFileName.Data());
   if(!mPileupFile)
   {
	   LOG_ERROR << "StPxlPileupAdder: pileup file not found." << endm;
	   return kStErr;
   }

   // set tree addresses
   mPileupTree = (TTree*)mPileupFile->Get("pileup_tree");
   mPileupTree->SetBranchAddress("nhits", &nhits, &b_nhits);
   mPileupTree->SetBranchAddress("x", x, &b_x);
   mPileupTree->SetBranchAddress("y", y, &b_y);
   mPileupTree->SetBranchAddress("z", z, &b_z);
   mPileupTree->SetBranchAddress("xLoc", xLoc, &b_xLoc);
   mPileupTree->SetBranchAddress("yLoc", yLoc, &b_yLoc);
   mPileupTree->SetBranchAddress("zLoc", zLoc, &b_zLoc);
   mPileupTree->SetBranchAddress("px", px, &b_px);
   mPileupTree->SetBranchAddress("py", py, &b_py);
   mPileupTree->SetBranchAddress("pz", pz, &b_pz);
   mPileupTree->SetBranchAddress("de", de, &b_de);
   mPileupTree->SetBranchAddress("ds", ds, &b_ds);
   mPileupTree->SetBranchAddress("key", key, &b_key);
   mPileupTree->SetBranchAddress("vid", vid, &b_vid);
   mPileupTree->SetBranchAddress("layer", layer, &b_layer);

   return kStOk;
}
//____________________________________________________________
Int_t StPxlPileupAdder::addPxlHits(StMcPxlHitCollection& mcPxlHitCol)
{

	// tree has one event
	mPileupTree->GetEntry(0);

	LOG_INFO<<"StPxlPileupAdder: adding "<<nhits<<" pileup hits."<<endm;

	cout<<"Number of hits before adding..."<<mcPxlHitCol.numberOfHits()<<endl;

	for(int i=0;i<nhits;i++)
	{
		StThreeVectorF hit_x(xLoc[i],yLoc[i],zLoc[i]);
		StThreeVectorF hit_p(px[i],py[i],pz[i]);

		mcPxlHitCol.addHit(new StMcPxlHit(hit_x,hit_p,de[i],ds[i],0,key[i],vid[i]));
	}

	cout<<"Number of hits after adding..."<<mcPxlHitCol.numberOfHits()<<endl;

   return kStOK;
}
