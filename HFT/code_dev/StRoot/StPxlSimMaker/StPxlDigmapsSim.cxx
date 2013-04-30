/*
 *
 * Author: M. Mustafa
 *
 *
 **********************************************************
 * $Log:  $
 */

#include <stdio.h>

#include "StMessMgr.h"
#include "Stypes.h"
#include "Stiostream.h"
#include "StPxlDigmapsSim.h"
#include "StMcEvent/StMcPxlHit.hh"
#include "StMcEvent/StMcPxlHitCollection.hh"
#include "StPxlUtil/StPxlRawHitCollection.h"
#include "StPxlUtil/StPxlRawHit.h"
#include "StPxlUtil/StPxlConstants.h"
#include "tables/St_HitError_Table.h"
#include "StarClassLibrary/StRandom.hh"
#include "StThreeVectorF.hh"

#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TDataSet.h"
#include "TMath.h"
#include "TRandom3.h"

#include "DIGMAPS/digplane.h"
#include "DIGMAPS/digadc.h"
#include "DIGMAPS/digtransport.h"
#include "DIGMAPS/digparticle.h"
#include "DIGMAPS/digevent.h"

StPxlDigmapsSim::~StPxlDigmapsSim()
{
   delete mDigAdc;
   delete mDigPlane;
   delete mDigTransport;
}
//____________________________________________________________
Int_t StPxlDigmapsSim::initRun(const TDataSet& calib_db, const Int_t run)
{
   // run is not used in the current implementation, but might be necessary in the future.

   LOG_INFO << "StPxlDigmapsSim::init()" << endm;

   // temporary setup, need to utilize a DB

   // set ADC threshold(s)
   Int_t nAdcBits = 1;
   Int_t nAdcThresholds = int(TMath::Power(2.0, nAdcBits) - 1);
   Bool_t adcLinear = 0;
   Float_t adcElectronConversion = -999;
   Float_t adcThresholds[] = {4.0}; // one threshold only
   Float_t adcLsb = adcThresholds[0];

   if (!mDigAdc) mDigAdc = new DIGADC();
   cout<<mDigAdc<<endl;
   mDigAdc->SetNbits(nAdcBits);
   mDigAdc->SetNThresholds(nAdcThresholds);
   mDigAdc->SetADC_linear(adcLinear);
   mDigAdc->SetLSB(adcLsb);
   mDigAdc->SetElectron_Conversion(adcElectronConversion);
   mDigAdc->SetADC_thresholds(adcThresholds, nAdcThresholds);

   // set transport
   Int_t transportChargeModel = 5;
   Float_t transportRangeLimit_InPitchUnit = 2.5;
   Float_t   transport_l1dimgauslor_Norm_g_1st = 0.458955;
   Float_t   transport_l1dimgauslor_x0_g_1st = -3.98149;
   Float_t   transport_l1dimgauslor_sigma_g_1st = 13.1559;
   Float_t   transport_l1dimgauslor_Gamma_lor_1st = 3.98673;
   Float_t   transport_l1dimgauslor_x0_lor_1st = 1.79712;
   Float_t   transport_l1dimgauslor_norm_lor_1st = 6.4533;
   Float_t   transport_l1dimgauslor_Norm_g_2nd = 0.116703;
   Float_t   transport_l1dimgauslor_x0_g_2nd = -1.0688;
   Float_t   transport_l1dimgauslor_sigma_g_2nd = 17.4533;
   Float_t   transport_l1dimgauslor_Gamma_lor_2nd = 47.0837;
   Float_t   transport_l1dimgauslor_x0_lor_2nd = -4.63879;
   Float_t   transport_l1dimgauslor_norm_lor_2nd = 3.71411;

   if (!mDigTransport) mDigTransport = new DIGTransport();
   mDigTransport->SetChargeModel(transportChargeModel);
   mDigTransport->SetRangeLimit_InPitchUnit(transportRangeLimit_InPitchUnit);
   mDigTransport->Setf1dimgauslor_Norm_g_1st(transport_l1dimgauslor_Norm_g_1st);
   mDigTransport->Setf1dimgauslor_x0_g_1st(transport_l1dimgauslor_x0_g_1st);
   mDigTransport->Setf1dimgauslor_sigma_g_1st(transport_l1dimgauslor_sigma_g_1st);
   mDigTransport->Setf1dimgauslor_Gamma_lor_1st(transport_l1dimgauslor_Gamma_lor_1st);
   mDigTransport->Setf1dimgauslor_x0_lor_1st(transport_l1dimgauslor_x0_lor_1st);
   mDigTransport->Setf1dimgauslor_norm_lor_1st(transport_l1dimgauslor_norm_lor_1st);
   mDigTransport->Setf1dimgauslor_Norm_g_2nd(transport_l1dimgauslor_Norm_g_2nd);
   mDigTransport->Setf1dimgauslor_x0_g_2nd(transport_l1dimgauslor_x0_g_2nd);
   mDigTransport->Setf1dimgauslor_sigma_g_2nd(transport_l1dimgauslor_sigma_g_2nd);
   mDigTransport->Setf1dimgauslor_Gamma_lor_2nd(transport_l1dimgauslor_Gamma_lor_2nd);
   mDigTransport->Setf1dimgauslor_x0_lor_2nd(transport_l1dimgauslor_x0_lor_2nd);
   mDigTransport->Setf1dimgauslor_norm_lor_2nd(transport_l1dimgauslor_norm_lor_2nd);

   // set plane
   Float_t planePitchX = 20.7;
   Float_t planePitchY = 20.7;
   Float_t planeEpitaxialThickness = 9.0;
   Float_t planeNoiseElectrons = 13.7;
   Int_t planeNpixelsX = nPxlColumnsOnSensor;
   Int_t planeNpixelsY = nPxlRowsOnSensor;
   Float_t planeTemprature = 10.0;
   Float_t planeIonizationEnergy = 3.6;
   Float_t planeSegmentSize = 0.1;
   Float_t planeMaximumSegmentSize = 1.0;
   Float_t planeMaximumChargePerSegment = 1.0;
   Float_t planeDiffusionMaximumRangeInX = 2.5;
   Float_t planeDiffusionMaximumRangeInY = 2.5;
   Float_t planeReflexionCoefficient = 1.0;
   Float_t planeBasicModel_SigmaTenMicrons = 10.0;

   if (!mDigPlane) mDigPlane = new DIGPlane();
   mDigPlane->SetPitch(planePitchX, planePitchY);
   mDigPlane->SetNpixels(planeNpixelsX, planeNpixelsY);
   mDigPlane->SetDimensions(planePitchX * planeNpixelsX, planePitchY * planeNpixelsY, planeEpitaxialThickness);
   mDigPlane->SetNoiseElectrons(planeNoiseElectrons);
   mDigPlane->SetTemperature(planeTemprature);
   mDigPlane->SetIonizationEnergy(planeIonizationEnergy);
   mDigPlane->SetSegmentSize(planeSegmentSize);
   mDigPlane->SetMaximumSegmentSize(planeMaximumSegmentSize);
   mDigPlane->SetMaximumChargePerSegment(planeMaximumChargePerSegment);
   mDigPlane->SetDiffusionMaximumRange(planeDiffusionMaximumRangeInX, planeDiffusionMaximumRangeInY);
   mDigPlane->SetReflexionCoefficient(planeReflexionCoefficient);
   mDigPlane->SetBasicModel_SigmaTenMicrons(planeBasicModel_SigmaTenMicrons);

   return kStOk;
}
//____________________________________________________________
Int_t StPxlDigmapsSim::addPxlRawHits(const StMcPxlHitCollection& mcPxlHitCol,
                                     StPxlRawHitCollection& pxlRawHitCol)
{

   // Loop over sectors
   for (UInt_t iSec = 0; iSec < mcPxlHitCol.numberOfSectors(); iSec++)
   {
      const StMcPxlSectorHitCollection* mcPxlSectorHitCol = mcPxlHitCol.sector(iSec);
      if (!mcPxlSectorHitCol) continue;

      for (UInt_t iLad = 0; iLad < mcPxlSectorHitCol->numberOfLadders(); iLad++)
      {
         const StMcPxlLadderHitCollection* mcPxlLadderHitCol = mcPxlSectorHitCol->ladder(iLad);
         if (!mcPxlLadderHitCol) continue;

         for (UInt_t iSen = 0; iSen < mcPxlLadderHitCol->numberOfSensors(); iSen++)
         {
            const StMcPxlSensorHitCollection* mcPxlSensorHitCol = mcPxlLadderHitCol->sensor(iSen);
            if (!mcPxlSensorHitCol) continue;

            UInt_t nSenHits = mcPxlSensorHitCol->hits().size();
            LOG_DEBUG << "Sector/Ladder/Sensor = " << iSec << "/" << iLad << "/" << iSen << ". Number of sensor hits = " << nSenHits << endm;

	    DIGEvent* fdigevent = new DIGEvent();
            // Loop over hits in the sensor
            for (UInt_t iHit = 0; iHit < nSenHits; iHit++)
            {
               StMcPxlHit* mcPix = mcPxlSensorHitCol->hits()[iHit];

               Long_t volId = mcPix->volumeId();
               Int_t sector = mcPix->sector();
               Int_t ladder = mcPix->ladder();
               Int_t sensor = mcPix->sensor();

               TString Path("");
               LOG_DEBUG << endm;
               Path = Form("/HALL_1/CAVE_1/IDSM_1/PXMO_1/PXLA_%i/LADR_%i/PXSI_%i/PLAC_1", sector, ladder, sensor);
               LOG_DEBUG << "PATH: " << Path << endm;
               LOG_DEBUG << "pxl hit volId/sector/ladder/sensor is " << volId << "/" << sector << "/" << ladder << "/" << sensor << endm;

               gGeoManager->RestoreMasterVolume();
               gGeoManager->CdTop();
               gGeoManager->cd(Path);

               Double_t globalPixHitPos[3] = {mcPix->position().x(), mcPix->position().y(), mcPix->position().z()};
               Double_t localPixHitPos[3]  = {0, 0, 0};
               gGeoManager->GetCurrentMatrix()->MasterToLocal(globalPixHitPos, localPixHitPos);

	       // convert to um
	       localPixHitPos[0] *= 10000.0;
	       localPixHitPos[1] *= 10000.0;
	       localPixHitPos[2] *= 10000.0;

               LOG_DEBUG << "globalPixHitPos = " << globalPixHitPos[0] << " " << globalPixHitPos[1] << " " << globalPixHitPos[2] << endm;
               LOG_DEBUG << "localPixHitPos = " << localPixHitPos[0] << " " << localPixHitPos[1] << " " << localPixHitPos[2] << endm;

               Float_t lXpos = localPixHitPos[0] + mDigPlane->GetXdimension()/2.0;
               Float_t lYpos = localPixHitPos[2] + mDigPlane->GetYdimension()/2.0;
               Float_t lZpos = 0.0;
               LOG_DEBUG << "digHitPos = " << lXpos << " " << lYpos << " " << lZpos << endm;
               Float_t thetapos = 0; //temporary
               Float_t phipos = 0; // temporary
               Float_t thetaposrad = thetapos * TMath::Pi() / 180.0;
               Float_t phiposrad = phipos * TMath::Pi() / 180.0;
               //compute exit position given the incident angle:
               Float_t totalXlength = (mDigPlane->GetZdimension()) * TMath::Tan(thetaposrad) * TMath::Cos(phiposrad);
               Float_t totalYlength = (mDigPlane->GetZdimension()) * TMath::Tan(thetaposrad) * TMath::Sin(phiposrad);
               Float_t outputXpos = lXpos + totalXlength;
               Float_t outputYpos = lYpos + totalYlength;
               Float_t outputZpos = lZpos + mDigPlane->GetZdimension();

               // calculate deposited energy - need to move to a separate function
               Float_t mtotallentgh = (mDigPlane->GetZdimension()) / TMath::Cos(thetaposrad);
               Float_t EnergyMPV = 800.0 * mtotallentgh / 10.0;
               Float_t EnergySIGMA = 180.0 * mtotallentgh / 10.0;
               Float_t Energy = LandauLaw(EnergyMPV, EnergySIGMA);

               while (Energy > 20000)
               {
                  cout << "Energy too high -> Energy regenerated" << Energy << endl;
                  Energy = LandauLaw(EnergyMPV, EnergySIGMA);
               }

               DIGParticle* fdigparticle = new DIGParticle(lXpos, lYpos, lZpos, outputXpos, outputYpos, outputZpos, Energy);
               //---------charge generation
               fdigparticle->ComputeChargeDeposition(mDigPlane->GetSegmentSize(),
                                                     mDigPlane->GetMaximumSegmentSize(),
                                                     mDigPlane->GetMaximumChargePerSegment());
               //---------charge transport
               fdigparticle->ComputeChargeTransport(mDigPlane, mDigTransport);
               //---------random noise (should be removed if one wants to avoid double noise on double hit pixels)
               fdigparticle->AddRandomNoise(mDigPlane);
               //---------ADC (stored only for reference)
               //fdigparticle->AnalogToDigitalconversion(mDigAdc,mDigPlane);

               fdigevent->AddParticle(*fdigparticle);
               std::vector<Float_t> chargevector;
               std::vector<Int_t> pixmapvector;
               chargevector = fdigparticle->GetAnalogCharge();
               pixmapvector = fdigparticle->GetPixelMap();

               for (Int_t ipix = 0 ; ipix < fdigparticle->GetNpixels() ; ipix++)
               {
                  (fdigevent->GetReadoutmap())->UpdatePixel(chargevector[ipix], pixmapvector[ipix]);
               }
               delete fdigparticle;
            }

            // .... done with simulating hits on this sensor

            //---------Build readout map:
            (fdigevent->GetReadoutmap())->AnalogToDigitalconversion(mDigAdc, mDigPlane);
            //---------Build clusters (ideal clusters):
            //fdigevent->BuildTrueClusters(GetPlane(PlaneNumber));

            if (fdigevent->GetReadoutmap()->GetNpixels() > 0)
            {
               for (Int_t iy = 0 ; iy < mDigPlane->GetNpixelsY() ; iy++)
               {
                  for (Int_t ix = 0 ; ix < mDigPlane->GetNpixelsX() ; ix++)
                  {
                     //search pixel:
                     Int_t Npixel = ix + mDigPlane->GetNpixelsX() * iy;
                     Bool_t found = false;
                     Int_t j = 0;
                     while ((!found) && (j < fdigevent->GetReadoutmap()->GetNpixels()))
                     {
                        if (Npixel == fdigevent->GetReadoutmap()->GetPixelMap()[j])
                        {
                           found = true;
			   StPxlRawHit *pxlRawHit = pxlRawHitCol.newRawHit(iSec,iLad ,iSen);
			   if(!pxlRawHit) continue;
    
			   pxlRawHit->setSector(iSec+1);
			   pxlRawHit->setLadder(iLad+1);
			   pxlRawHit->setSensor(iSen+1);
			   pxlRawHit->setRow(iy);
			   pxlRawHit->setColumn(ix);
    
			   pxlRawHitCol.nRawHits[iSec][iLad][iSen]++;
                        }
                        else
                        {
                           j++;
                        }
                     }
                  }
               }
            }

	    delete fdigevent;
         }
      }
   }
   return kStOK;
}
//______________________________________________________________________________
Double_t  StPxlDigmapsSim::LandauLaw(Double_t mean, Double_t sigma)
{
   Double_t x;
   Int_t seed = time(NULL);
   // need to create one global TRandom3 and change the seed only
   TRandom3 *r3 = new TRandom3(seed);

   x = r3->Landau(mean, sigma);

   delete r3;
   return x;
}
