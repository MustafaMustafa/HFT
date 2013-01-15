#ifndef MAPS_DIGTRANSPORT_H
#define MAPS_DIGTRANSPORT_H

#include <TNamed.h>
#include <TList.h>
#include <TGraph.h>
#include "Riostream.h"
#include "vector"

// ROOT classes
#include "TString.h"
#include "TObject.h"
#include "TVector.h"
#include "TFile.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TH1.h"
#include "TH2.h"
#include "TObjArray.h"
#include "TTree.h"
#include "TBranch.h"
#include "TClonesArray.h"
using namespace std;

class DIGInitialize;
class DIGPlane;
class DIGADC;
class DIGBeam;
class DIGTransport;
class DIGParticle;
class DIGAction;
class DIGEvent;
class DIGMAPS;
//==============================================================================
class DIGTransport : public TObject {
 public:
  DIGTransport();
  DIGTransport(Float_t myvar);
  DIGTransport(DIGTransport& adigtransport);
  virtual ~DIGTransport();
  void    Clear(const Option_t * /*option*/ = "");
  void PrintInfo();

  Float_t GetMyvar(){return fMyvar;}
  
  void SetMyvar(Float_t Myvar);

  void SetChargeModel(Int_t ChargeModel);
  void SetLorentz2DModel_Cp0(Float_t Lorentz2DModel_Cp0);
  void SetLorentz2DModel_Cp1(Float_t Lorentz2DModel_Cp1);
  void SetRangeLimit_InPitchUnit(Float_t RangeLimit_InPitchUnit);

  void SetGauss2DModel_sigma1_Cp0(Float_t Gauss2DModel_sigma1_Cp0);
  void SetGauss2DModel_sigma1_Cp1(Float_t Gauss2DModel_sigma1_Cp1);
  void SetGauss2DModel_sigma2_Cp0(Float_t Gauss2DModel_sigma2_Cp0);
  void SetGauss2DModel_sigma2_Cp1(Float_t Gauss2DModel_sigma2_Cp1);
  void SetGauss2DModel_weight(Float_t Gauss2DModel_weight);

  Int_t GetChargeModel(){return fChargeModel;}

  Float_t GetLorentz2DModel_Cp0(){return fLorentz2DModel_Cp0;}
  Float_t GetLorentz2DModel_Cp1(){return fLorentz2DModel_Cp1;}
  Float_t GetRangeLimit_InPitchUnit(){return fRangeLimit_InPitchUnit;}

  Float_t GetGauss2DModel_sigma1_Cp0(){return fGauss2DModel_sigma1_Cp0;}
  Float_t GetGauss2DModel_sigma1_Cp1(){return fGauss2DModel_sigma1_Cp1;}
  Float_t GetGauss2DModel_sigma2_Cp0(){return fGauss2DModel_sigma2_Cp0;}
  Float_t GetGauss2DModel_sigma2_Cp1(){return fGauss2DModel_sigma2_Cp1;}
  Float_t GetGauss2DModel_weight(){return fGauss2DModel_weight;}

  Float_t GetLorGaussModel_Norm1_Cp0(){return fLorGaussModel_Norm1_Cp0;}
  Float_t GetLorGaussModel_Norm1_Cp1(){return fLorGaussModel_Norm1_Cp1;}
  Float_t GetLorGaussModel_Norm1_Cp2(){return fLorGaussModel_Norm1_Cp2;}
  Float_t GetLorGaussModel_sigma_Cp0(){return fLorGaussModel_sigma_Cp0;}
  Float_t GetLorGaussModel_sigma_Cp1(){return fLorGaussModel_sigma_Cp1;}
  Float_t GetLorGaussModel_C_Cp0(){return fLorGaussModel_C_Cp0;}
  Float_t GetLorGaussModel_C_Cp1(){return fLorGaussModel_C_Cp1;}
  Float_t GetLorGaussModel_Norm_Cp0(){return fLorGaussModel_Norm_Cp0;}
  Float_t GetLorGaussModel_Norm_Cp1(){return fLorGaussModel_Norm_Cp1;}

  void SetLorGaussModel_Norm1_Cp0(Float_t LorGaussModel_Norm1_Cp0);
  void SetLorGaussModel_Norm1_Cp1(Float_t LorGaussModel_Norm1_Cp1);
  void SetLorGaussModel_Norm1_Cp2(Float_t LorGaussModel_Norm1_Cp2);
  void SetLorGaussModel_sigma_Cp0(Float_t LorGaussModel_sigma_Cp0);
  void SetLorGaussModel_sigma_Cp1(Float_t LorGaussModel_sigma_Cp1);
  void SetLorGaussModel_C_Cp0(Float_t LorGaussModel_C_Cp0);
  void SetLorGaussModel_C_Cp1(Float_t LorGaussModel_C_Cp1);
  void SetLorGaussModel_Norm_Cp0(Float_t LorGaussModel_Norm_Cp0);
  void SetLorGaussModel_Norm_Cp1(Float_t LorGaussModel_Norm_Cp1);

 protected:
  Int_t   fChargeModel;

  Float_t   fLorentz2DModel_Cp0;
  Float_t   fLorentz2DModel_Cp1;
  Float_t   fRangeLimit_InPitchUnit;

  Float_t   fGauss2DModel_sigma1_Cp0;
  Float_t   fGauss2DModel_sigma1_Cp1;
  Float_t   fGauss2DModel_sigma2_Cp0;
  Float_t   fGauss2DModel_sigma2_Cp1;
  Float_t   fGauss2DModel_weight;

  Float_t   fLorGaussModel_Norm1_Cp0;
  Float_t   fLorGaussModel_Norm1_Cp1;
  Float_t   fLorGaussModel_Norm1_Cp2;
  Float_t   fLorGaussModel_sigma_Cp0;
  Float_t   fLorGaussModel_sigma_Cp1;
  Float_t   fLorGaussModel_C_Cp0;
  Float_t   fLorGaussModel_C_Cp1;
  Float_t   fLorGaussModel_Norm_Cp0;
  Float_t   fLorGaussModel_Norm_Cp1;

  Float_t fMyvar;

  ClassDef(DIGTransport,1);
};



//==============================================================================

#endif
