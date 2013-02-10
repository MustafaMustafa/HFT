/*
 *
 * Author: A. Rose, LBL, Y. Fisyak, BNL, M. Miller, MIT, M. Mustafa
 *
 * 
 **********************************************************
 * $Log: StPixelFastSimMaker.cxx,v $
 * Revision 1.44  2012/12/18 18:46:59  margetis
 * update for DEV13 geometry
 *
 * Revision 1.43  2010/09/01 20:31:47  fisyak
 * clean up unused varaibles
 *
 * Revision 1.42  2009/02/06 20:48:48  wleight
 * UPGR15 Update
 *
 * Revision 1.41  2009/01/26 14:50:46  fisyak
 * Clean up
 *
 * Revision 1.40  2007/12/03 20:42:43  wleight
 * Replaced couts with LOG_DEBUGs
 *
 * Revision 1.37  2007/11/13 19:09:51  wleight
 * Corrected bug causing pixel fast simulator to crash when there were no pixel and/or ist hits in the event
 *
 * Revision 1.36  2007/11/06 16:20:06  wleight
 * Digitized Pixel, removed all hit smearing, and implemented idTruth
 *
 * Revision 1.34  2007/10/18 16:31:44  fisyak
 * Add pile-up from weixie
 *
 * Revision 1.33  2007/10/18 14:25:13  didenko
 * updates for pile-up events
 * 
 * Revision 1.32  2007/10/16 19:53:08  fisyak
 * rename Hft => Pxl, remove Hpd, Igt and Fst
 *
 * Revision 1.31  2007/10/16 19:50:46  fisyak
 * rename Hft => Pxl, remove Hpd, Igt and Fst
 *
 * Revision 1.30  2007/09/09 17:00:32  fisyak
 * Fix bug 1056
 *
 * Revision 1.29  2007/09/08 00:33:05  andrewar
 * Modifications for pileup hit read in.
 *
 * Revision 1.28  2007/05/17 13:18:52  andrewar
 * Removed cout in shiftHit.
 *
 * Revision 1.27  2007/05/16 15:06:55  andrewar
 * Switched cout's to LOG_INFO.
 *
 * Revision 1.26  2007/04/28 17:56:36  perev
 * Redundant StChain.h removed
 *
 * Revision 1.25  2007/04/27 18:41:29  wleight
 * Removed smearing of the coordinate not controlled by the strips in the 17cm layer
 *
 * Revision 1.24  2007/04/27 14:59:10  wleight
 * Corrected another error in the creation of new hits
 *
 * Revision 1.23  2007/04/26 04:08:41  perev
 * Remove StBFChain dependency
 *
 * Revision 1.22  2007/04/25 17:44:59  wleight
 * Corrected error in assignment of reconstructed IST hits
 *
 * Revision 1.21  2007/04/23 18:11:30  andrewar
 * Removed references to Hpd (includes were obsolete)
 *
 * Revision 1.19  2007/04/23 16:32:47  wleight
 * Added explicit casting for Double_t to int in calculating strip number
 *
 * Revision 1.18  2007/04/22 22:57:23  wleight
 * The two hits in the 17 cm layer are no longer combined into 1
 *
 * Revision 1.17  2007/04/16 19:10:52  wleight
 * Added IST simulation (digitization but no clustering)
 *
 * Revision 1.16  2007/04/13 19:17:15  andrewar
 * Removed misleading errors. Changed cout and printf to gMessMgr.
 *
 * Revision 1.15  2007/04/06 21:46:36  andrewar
 * Removed some debug messages.
 *
 * Revision 1.14  2007/04/06 14:55:11  andrewar
 * Shift of HFT hit to face of ladder.
 *
 * Revision 1.13  2007/03/28 13:33:45  mmiller
 * Removed cout/printf's.
 *
 * Revision 1.12  2006/12/21 18:11:59  wleight
 * Fixed UPGR09 compatibility so it works with all versions
 *
 * Revision 1.11  2006/12/20 16:50:21  wleight
 * Added fix for UPGR09 problem with layer number mismatch
 *
 * Revision 1.10  2006/12/15 02:17:20  wleight
 * Ist now gets hit smearing parameters from the database
 *
 * Revision 1.9  2006/12/14 23:52:51  andrewar
 * Added Sevil's hit error db loader.
 *
 * Revision 1.7  2006/11/29 21:42:07  andrewar
 * Update with Pixel resolution smearing.
 *
 * Revision 1.6  2006/11/28 22:37:42  wleight
 * Fixed minor smearing bug
 *
 * Revision 1.4  2006/10/13 20:15:45  fisyak
 * Add Hpd fast simulation (Sevil)
 *
 * Revision 1.3  2006/02/17 21:44:29  andrewar
 * Remover streaming of each Pixel hit.
 *
 * Revision 1.2  2006/02/08 20:57:33  fisyak
 * Set proper Detector Id
 *
 * Revision 1.1  2006/02/03 20:11:56  fisyak
 * The initial revision
 *
 *
 */

#include "StPxlFastSim.h"
#include "StHit.h"
#include "StPxlHit.h"
#include "StMcPixelHit.hh"
#include <stdio.h>
#include "tables/St_g2t_pix_hit_Table.h"
#include "StarClassLibrary/StRandom.hh"

  
StPxlFastSim::~StPxlFastSim()
{
    if(mRandom) delete mRandom;
}    
//____________________________________________________________
Int_t StPxlFastSim::init(const TDataset& calib_db)
{
  LOG_INFO<<"StPxlFastSim::init()"<<endm;

  Int_t seed=time(NULL);
  mRandom=new StRandom();
  mRandom->setSeed(seed);

  St_HitError *pixelTableSet = (St_HitError*)calib_db.Find("PixelHitError");
  
  HitError_st* pixelHitError = pixelTableSet->GetTable();
  mResXPix = sqrt(pixelHitError->coeff[0]);
  mResZPix = sqrt(pixelHitError->coeff[3]);

  return kStOk;
}
//____________________________________________________________
Int_t StPxlFastSim::addPxlHits(const StMcPixelHitCollection& mcPxlHitCol, StPxlHitCollection& pxlHitCol, const g2t_pix_hit_st& g2tPix)
{
  Float_t smearedX=0,smearedY=0,smearedZ=0;

    Int_t nMcHits = mcPxlHitCol->numberOfHits();
    LOG_DEBUG<<"There are "<<nMcHits<<" mc pixel hits"<<endm;
    
    if (nMcHits)
    {
      for(UInt_t iSec=0; iSec<mcPxlHitCol->numberOfLayers(); iSec++) // As of 1/25/2013, layer of StMcPixelHitCollection is actually a sector
      {
	if (mcPxlHitCol->layer(iSec))
        {
	  LOG_DEBUG<<"Sector "<<iSec+1<<endm;
	  //simple simulator for perfect hits that just converts StMcPixelHit to StPxlHit
	  //as of 11/21/08, hits are now smeared with resolution taken from hit error table
	  UInt_t nSecHits = mcPxlHitCol->layer(iSec)->hits().size();
	  LOG_DEBUG << " Number of hits in sector "<< iSec+1 <<" =" << nSecHits << endm;

	  for (UInt_t iHit = 0; iHit < nSecHits; iHit++)
	  {
	    StMcHit *mcH    = mcPxlHitCol->layer(iSec)->hits()[iHit];
	    StMcPixelHit* mcPix=dynamic_cast<StMcPixelHit*>(mcH);
	    
	    Long_t volId     = mcPix->volumeId();
	    Int_t sector     = mcPix->layer();
	    Int_t ladder    = mcPix->ladder();

	    TString Path("");
	    Path= Form("/HALL_1/CAVE_1/IDSM_1/PXMO_1/PXLA_%i/LADR_%i/PLAC_1",layer,ladder);
	    LOG_DEBUG <<"PATH: " << Path << endm;
	    LOG_DEBUG<<"pixel hit sector/ladder is "<<sector<<"/"<<ladder<<" and volume id "<<volId<<endm;

	    gGeoManager->RestoreMasterVolume();
	    gGeoManager->CdTop();
	    gGeoManager->cd(Path);

	    Double_t globalPixHitPos[3] = {mcPix->position().x(),mcPix->position().y(),mcPix->position().z()};
	    Double_t localPixHitPos[3]  = {0,0,0};
	    gGeoManager->GetCurrentMatrix()->MasterToLocal(globalPixHitPos,localPixHitPos);

            LOG_DEBUG<<endm;
            LOG_DEBUG<<"globalPixHitPos = "<<globalPixHitPos[0]<<" "<<globalPixHitPos[1]<<" "<<globalPixHitPos[2]<<endm;
            LOG_DEBUG<<"localPixHitPos = "<<localPixHitPos[0]<<" "<<localPixHitPos[1]<<" "<<localPixHitPos[2]<<endm;
	    smearedX=distortHit(localPixHitPos[0],mResXPix,PXL_MAX_X_CORD);
	    smearedY=distortHit(localPixHitPos[1],mResXPix,PXL_MAX_Y_CORD);
	    smearedZ=distortHit(localPixHitPos[2],mResZPix,0.5); // Not properly constrained yet
	    localPixHitPos[0]=smearedX;
	    localPixHitPos[1]=smearedY;
	    localPixHitPos[2]=smearedZ;
            LOG_DEBUG<<"smearedlocal = "<<localPixHitPos[0]<<" "<<localPixHitPos[1]<<" "<<localPixHitPos[2]<<endm;
            LOG_DEBUG<<endm;
	    Double_t smearedGlobalPixHitPos[3]={0,0,0};
	    gGeoManager->GetCurrentMatrix()->LocalToMaster(localPixHitPos,smearedGlobalPixHitPos);

	    StThreeVectorF gpixpos(smearedGlobalPixHitPos);
	    StThreeVectorD mRndHitError(0.,0.,0.);

	    UInt_t hw = sector*10 + ladder;
	    StPxlHit* tempHit = new StPxlHit(gpixpos, mRndHitError, hw,mcPix->dE() ,0);
	    tempHit->setSector(iSec+1);
	    tempHit->setLadder(mcPix->ladder());
	    //tempHit->setSensor(mcPix->ladder());
	    //to be set later with new geom

	    tempHit->setLocalPosition(localPixHitPos[0],localPixHitPos[1],localPixHitPos[2]); 
	    Int_t truth =0;
	    truth = g2tPix[mcPix->key()-1].track_p;
	    tempHit->setIdTruth(truth,100);

	    LOG_DEBUG<<"key() : "<< mcPix->key()-1 << " idTruth: "<< truth <<endm;
	    LOG_DEBUG <<"from g2t : x= " << g2tPix[iHit].x[0] <<"  y= " << g2tPix[iHit].x[1] <<"  z= " << g2tPix[iHit].x[2] << endm;
	    LOG_DEBUG<<"pixel rnd hit location x: "<<tempHit->position().x()<<"; y: "<<tempHit->position().y()<<"; z: "<<tempHit->position().z()<<endm;
	    
	    pxlHitCol->addHit(tempHit);
	    LOG_DEBUG << *tempHit<<endm;
	  }
	}
      }
    }

  return kStOK;
}

//____________________________________________________________
Double_t StPxlFastSimMaker::distortHit(Double_t x, Double_t res, Double_t sensorLenght)
{
  Double_t test;

  if(mSmear)
  {
    test = x + mRandom->gauss(0,res);

    while( test <0 || test > sensorLenght)
    {
      test = x + mRandom->gauss(0,res);
    }

    return test;
  }
  else return x;
}