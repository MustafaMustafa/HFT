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

#include "TObjectSet.h"
#include "StPxlDbMaker/StPxlDb.h"


StPxlPileupAdder::~StPxlPileupAdder()
{
	if(mPxlDb) delete mPxlDb;
}
//____________________________________________________________
Int_t StPxlPileupAdder::init(TString pileupFileName,const TObjectSet* pxlDbDataSet)
{
   // run is not used in the current implementation, but might be necessary in the future.
   LOG_INFO << "StPxlPileupAdder::init()" << endm;

   if(pxlDbDataSet != 0)
   {
	   mPxlDb = (StPxlDb *)pxlDbDataSet->GetObject();
	   if (!mPxlDb)
	   {
		   LOG_ERROR << "StPxlFastSim - E - mPxlDb is not available" << endm;
		   return kStErr;
	   }
	   else
	   {
		   LOG_INFO << "StPxlFastSim - Using geometry from pxlDB" <<endm;
	   }
   }
   else
   {
	   LOG_INFO << "StPxlPileupAdder - PxlDb is not available this will potentially mess up your transformations for vid==0 hits" <<endm;
   }

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

		//Long64_t volume_id = vid[i] !=0 ? vid[i] : get_vid(i);
		//Long64_t volume_id = get_vid(i);
		//if(volume_id) mcPxlHitCol.addHit(new StMcPxlHit(hit_x,hit_p,de[i],ds[i],0,key[i],volume_id));
	
		mcPxlHitCol.addHit(new StMcPxlHit(hit_x,hit_p,de[i],ds[i],0,key[i],vid[i]));
	}

	cout<<"Number of hits after adding..."<<mcPxlHitCol.numberOfHits()<<endl;

   return kStOK;
}
//____________________________________________________________
Long64_t StPxlPileupAdder::get_vid(Int_t i)
{

	const Double_t globalPos[3] = {x[i],y[i],z[i]};
	bool found = false;
	UInt_t sec,lad,sen;

	Float_t min[3] = {0.1,0.1,0.1};

	for(UInt_t iSec=0; iSec < 10; iSec++)
	{
		for(UInt_t iLad=0; iLad< 4; iLad++)
		{
			for(UInt_t iSen=0; iSen<10; iSen++)
			{
				Double_t localPos[3] = {0.,0.,0.};

				TGeoHMatrix* combP = (TGeoHMatrix*)mPxlDb->geoHMatrixSensorOnGlobal(iSec+1,iLad+1,iSen+1);
				combP->MasterToLocal(globalPos,localPos);

				if(fabs(xLoc[i]-localPos[0])< min[0]
				&& fabs(yLoc[i]-localPos[1])< min[1]
				&& fabs(zLoc[i]-localPos[2])< min[2])
				{
					sec = iSec+1;
					lad = iLad+1;
					sen = iSen+1;
					min[0] = fabs(xLoc[i]-localPos[0]);
					min[1] = fabs(yLoc[i]-localPos[1]);
					min[2] = fabs(zLoc[i]-localPos[2]);
					
					found = true;
					//break;
				}
			}

			//if(found) break;
		}
		
		//if(found) break;
	}

	 //UChar_t sector() const {return mVolumeId/1000000;}
	 //UChar_t ladder() const {return  (mVolumeId%1000000)/10000;} 
	 //UChar_t sensor() const {return  (mVolumeId - sector()*1000000 - ladder()*10000)/100;} 

	 Long64_t volume_id = 0;
	 
	 if(found)
	 {
		 volume_id = sec*1000000;
		 volume_id += lad*10000;
		 volume_id += sen*100;
	 }

	// cout<<globalPos[0]<<" "<<globalPos[1]<<" "<<globalPos[2]<<endl;
	 cout<<found<<" "<<vid[i]<<" "<<volume_id<<" "<<sec<<" "<<lad<<" "<<sen<<" "<<min[0]<<" "<<min[1]<<" "<<min[2]<<endl;
	 return volume_id;
}
