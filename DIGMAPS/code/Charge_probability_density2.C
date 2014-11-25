#include "TF2.h"
#include "TProfile2D.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TMultiGraph.h"
#include "vector"
#include "TMinuit.h"
//.x macros/Charge_probability_density2.C++


vector< Float_t > vecX;
vector< Float_t > vecY;
vector< Float_t > vecZ;
vector< Float_t > vecNentries;

vector< Float_t > vecChargeError;
vector< Float_t > vecZAverage;
Double_t   pitchX;
Double_t   pitchY;


//_______________________________________________________________________________________
//
  Double_t Gaus2D(Double_t *x, Double_t *par){
  if(par[2]!=0 && par[4] !=0){
    double rx = (x[0]-par[1])/par[2];
    double ry = (x[1]-par[3])/par[4];
    return par[0]*TMath::Exp(-(rx*rx+ry*ry)/2.0);
  }else{
    return 0;
  }
}
//_______________________________________________________________________________________
//
  Double_t SumGaus2D(Double_t *x, Double_t *par){
    //par[0] Norm_1
    //par[1] x0_1
    //par[2] sigma_x_1
    //par[3] y0_1
    //par[4] sigma_y_1
    //par[5] Norm_2
    //par[6] x0_2
    //par[7] sigma_x_2
    //par[8] y0_2
    //par[9] sigma_y_2

  if(par[2]!=0 && par[4] !=0 && par[7]!=0 && par[9]!=0){
    double rx = (x[0]-par[1])/par[2];
    double ry = (x[1]-par[3])/par[4];
    double rx2 = (x[0]-par[6])/par[7];
    double ry2 = (x[1]-par[8])/par[9];

    return par[0]*( TMath::Exp(-(rx*rx+ry*ry)/2.0)+par[5]*TMath::Exp(-(rx2*rx2+ry2*ry2)/2.0) ) ;
  }else{
    return 0;
  }
}
//_______________________________________________________________________________________
//
  Double_t Lorentz2D(Double_t *x, Double_t *par){

    //x[0] = x
    //x[1] = y
    // par[0] = Gamma
    // par[1] = x0
    // par[2] = y0
    // par[3] = norm
  if(par[0]>0){
    Double_t Pi = 3.141592653;
    return par[3]*par[0]/Pi/((x[0]-par[1])*(x[0]-par[1])+(x[1]-par[2])*(x[1]-par[2])+par[0]*par[0]) ; 
  }else{
    return 0;
  }
}
//_______________________________________________________________________________________
//
  Double_t poly2D(Double_t *x, Double_t *par){

    //x[0] = x
    //x[1] = y
    // par[0] = Gamma
    // par[1] = x0
    // par[2] = y0

  Double_t Result;
  Result = par[0]*(par[1]*x[0]*x[0]*x[0]+par[2]*x[0]*x[0]+par[3]*x[0]+par[4] )
    *(par[5]*x[1]*x[1]*x[1]+par[6]*x[1]*x[1]+par[7]*x[1]+par[8] );

  return Result;
}
//_______________________________________________________________________________________
//



//______________________________________________________________________________
void fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{


  //digreadoutmap.cxx:    std::cout<<" size vectors "<<  fPixelMap.size()<<" "<<fAnalogChargeMap.size()<<" "<<fDigitalChargeMap.size()<<endl;
  /*
    vector<Float_t> vecX; //x pos pour tous les Z possibles
    vector<Float_t> vecY; //y pos pour tous les Z possibles
    vector<Float_t> vecZ; // tous les bins en Z par bin en x et y
    vector<Float_t> vecNentries; // Nombre d'entrees par bin en x y z
    vector<Float_t> vecZAverage; // valeur moyenne en Z par bin en x y
    vector<Float_t> vecChargeError;
  */


   const Int_t nbins =   vecX.size();

   Int_t i;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;

   //Lorentz2DModel_Cp0: 0.6607
   //Lorentz2DModel_Cp1: 0.40  //0.400664
   //Lorentz2DModel_RangeLimit_InPitchUnit: 2.5

   Double_t lorentz2Dmodel_rangelimit_inpitchunit = 2.5;

   TF2 *mylorentz2D;
   mylorentz2D = new TF2("funlor2d",Lorentz2D,-lorentz2Dmodel_rangelimit_inpitchunit*pitchX,lorentz2Dmodel_rangelimit_inpitchunit*pitchX,
			 -lorentz2Dmodel_rangelimit_inpitchunit*pitchY,lorentz2Dmodel_rangelimit_inpitchunit*pitchY,4);
   mylorentz2D->SetParNames("C","X_{0}","Y_{0}","Norm");

   //   Double_t params1[] = {Cvalue,0.,0.,1.0};
   Double_t params1[] = {par[0],par[1],par[2],par[3]};
   mylorentz2D->SetParameters(params1);
//mylorentz2D->SetRange(-float(PixelSize*pitchrange),-float(PixelSize*pitchrange),float(PixelSize*pitchrange),float(PixelSize*pitchrange));
//cout<<" lorentz2D evaluation "<<mylorentz2D->Eval(0.0,0.0)<<endl;

   for (i=0;i<nbins; i++) {
     Double_t functionvalue = mylorentz2D->Eval(vecX[i],vecY[i]);
     // delta  = (vecZAverage[i]-func(vecX[i],vecY[i],par))/vecChargeError[i];
     delta  = (vecZAverage[i]-functionvalue)/vecChargeError[i];

     chisq += delta*delta;

   }

   f = chisq;
}

//______________________________________________________________________________
Double_t func(float x,float y,Double_t *par)
{
 Double_t value=( (par[0]*par[0])/(x*x)-1)/ ( par[1]+par[2]*y-par[3]*y*y);
 return value;
}



//_______________________________________________________________________________________
//

//  .x macros/Charge_probability_density.C++

void Charge_probability_density2(){

  cout<<" --------------------------------- Charge_probability_density2 : START 1"<<endl;
  const Int_t Nruns = 4;
  Int_t ChipArray[Nruns] = {18,9,9,9};
  Int_t RunArray[Nruns] = {18524,9552,9553,9552};
  Int_t PlaneArray[Nruns] = {9,9,10,10};
  Char_t  ResultFileName[200];
  Float_t Pitch[Nruns] = {10.,20.,30.,40.};
  Float_t PitchError[Nruns] = {0.,0.,0.,0.};

  TFile *ffile;
  TProfile2D *hprof2i;
  TProfile2D *hprof1[Nruns];
  TProfile2D *hprof2[Nruns];
  TProfile2D *hprof3[Nruns];
  TProfile2D *hprof4[Nruns];
  TH3F  *hGOODCharge_Charge_DiodePosition;
  TH3F  *hGOODCharge_Charge_DiodePosition1[Nruns];
  TH2 *hError[Nruns];
  TH2 *hchi2[Nruns];
  TF2 *funlor2d[Nruns];
  TCanvas *c1[Nruns];
  TCanvas *c2[1];
  cout<<" --------------------------------- Charge_probability_density2 : START 2"<<endl;

  for (Int_t i=0 ; i<Nruns ; i++){
    //   sprintf(ResultFileName,
    //	    "/rawcmos9/abesson/maf/results_ana_M%d/run%dPl%d_ClCharge.root",
    sprintf(ResultFileName,
	    "/home/abesson/work/ILC/DIGITISEUR/data/run%dPl%d_ClCharge.root",
	    RunArray[i],PlaneArray[i]);
    // cout<<" --------------------------------- Charge_probability_density2 : START 2 0 Run = "<<i<<endl;
    // open file:
    ffile = new TFile(ResultFileName,"READ");
    //  TH2F *h2;
    // hprof2 = 
    //cout<<" --------------------------------- Charge_probability_density2 : START 2 1"<<endl;
    ffile->GetObject("ProfhGOODCharge_Charge_DiodePosition",hprof2i);
    //cout<<" --------------------------------- Charge_probability_density2 : START 2 2"<<endl;
    ffile->GetObject("hGOODCharge_Charge_DiodePosition",hGOODCharge_Charge_DiodePosition);
    // cout<<" --------------------------------- Charge_probability_density2 : START 2 3"<<endl;

    hGOODCharge_Charge_DiodePosition1[i] = (TH3F*)hGOODCharge_Charge_DiodePosition->Clone("hGOODCharge_Charge_DiodePosition1");
    //cout<<" --------------------------------- Charge_probability_density2 : START 3"<<endl;

    hprof1[i] = (TProfile2D*)hprof2i->Clone("hprof1");
    hprof2[i] = (TProfile2D*)hprof2i->Clone("hprof2");
    hprof3[i] = (TProfile2D*)hprof2i->Clone("hprof3");
    hprof4[i] = (TProfile2D*)hprof2i->Clone("hprof4");
    hprof1[i]->Sumw2();
    hprof1[i]->Approximate(kTRUE);
    hprof2[i]->Sumw2();
    hprof2[i]->Approximate(kTRUE);
    hprof3[i]->Sumw2();
    hprof3[i]->Approximate(kTRUE);
    hprof4[i]->Sumw2();
    hprof4[i]->Approximate(kTRUE);
    //Float_t Integ_hprof1 = hprof1[i]->Integral();     

    Float_t PixelSize = Pitch[i];
    Float_t pitchrange = 1.5;
    Int_t nbinx = hprof2[i]->GetNbinsX();
    Int_t nbiny = hprof2[i]->GetNbinsY();
    //cout<<" --------------------------------- Charge_probability_density2 : START 4"<<endl;

    //TArrayD & binsumw2 = *(hprof1[i]->GetBinSumw2());


    //hGOODCharge_Charge_DiodePosition = new TH3F("hGOODCharge_Charge_DiodePosition",
    //					    "All Pixel Charge vs impact position",100,-float(PixelSize*2.),float(PixelSize*2.),100,
    //-float(PixelSize*2.),float(PixelSize*2.),110,-100.,1000.);
    cout<<" INFORMATIONS ON TH3F "<<    hGOODCharge_Charge_DiodePosition1[i]->GetEntries()<<endl;
    Int_t Nentries = int(hGOODCharge_Charge_DiodePosition1[i]->GetEntries());
    Int_t NbinsX = hGOODCharge_Charge_DiodePosition1[i]->GetNbinsX();
    Int_t NbinsY = hGOODCharge_Charge_DiodePosition1[i]->GetNbinsY();
    Int_t NbinsZ = hGOODCharge_Charge_DiodePosition1[i]->GetNbinsZ();
    Int_t nxy=0; //counter in the x/y plane
    Int_t nxyz=0; //counter in the x/y/z volume
    for (Int_t nx=0 ; nx<NbinsX ; nx++){
      for (Int_t ny=0 ; ny<NbinsY ; ny++){
	vecX.push_back(hGOODCharge_Charge_DiodePosition1[i]->GetXaxis()->GetBinCenter(nx));
	vecY.push_back(hGOODCharge_Charge_DiodePosition1[i]->GetYaxis()->GetBinCenter(ny));

	vecZAverage.push_back(0.0);
	Int_t nentriesz =0;
	for (Int_t nz=0 ; nz<NbinsZ ; nz++){
	  vecZ.push_back(hGOODCharge_Charge_DiodePosition1[i]->GetZaxis()->GetBinCenter(nz));
	  vecNentries.push_back(hGOODCharge_Charge_DiodePosition1[i]->GetBinContent(nx,ny,nz));
	  //cout<<"nx ny nz / NbinsX NbinsY NbinsZ " <<nx <<" "<<ny <<" "<<nz <<" / "<<NbinsX <<" "<< NbinsY<<" "<<NbinsZ <<endl;
	  vecZAverage[nxy]+=vecZ[nxyz]*vecNentries[nz];
	  nentriesz+=int(vecNentries[nz]);
	  nxyz++;
	}
	if(0!=nentriesz){
	  vecZAverage[nxy]/=float(nentriesz);  
	}
	//compute RMS:
	Float_t ChargeError = 0.0;
	if(nentriesz>1){
	  for (Int_t nz=0 ; nz<NbinsZ ; nz++){
	    ChargeError += vecNentries[nz]* (vecZ[nz] - vecZAverage[nxy])*(vecZ[nz] - vecZAverage[nxy]);
	    ChargeError/=nentriesz;
	  }
	}else if(nentriesz==1){
	  ChargeError = TMath::Sqrt(TMath::Abs(vecZAverage[nxy]));
	}
	vecChargeError.push_back(ChargeError);


	nxy++;
      }
    }
    // ----------------------now fit:
    pitchX = Pitch[i];
    pitchY = Pitch[i];
    Double_t lorentz2Dmodel_Cp0 =  0.6607;
    Double_t lorentz2Dmodel_Cp1 = 0.40;
    Float_t Cvalue=  lorentz2Dmodel_Cp0 + pitchX * lorentz2Dmodel_Cp1 ;
    //  Double_t params1[] = {Cvalue,0.,0.,1.0};

    TMinuit *gMinuit = new TMinuit(4);  //initialize TMinuit with a maximum of 5 params
    gMinuit->SetFCN(fcn);

    Double_t arglist[10];
    Int_t ierflg = 0;

    arglist[0] = 1;
    gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

// Set starting values and step sizes for parameters "C","X_{0}","Y_{0}","Norm"
   Double_t vstart[4] = {Cvalue,0.,0.,1.0};
   Double_t step[4] = {0.01 , 0.1 , 0.01 , 0.001};
   gMinuit->mnparm(0, "C", vstart[0], step[0], 0,0,ierflg);
   gMinuit->mnparm(1, "X_{0}", vstart[1], step[1], 0,0,ierflg);
   gMinuit->mnparm(2, "Y_{0}", vstart[2], step[2], 0,0,ierflg);
   gMinuit->mnparm(3, "Norm", vstart[3], step[3], 0,0,ierflg);

// Now ready for minimization step
   arglist[0] = 500;
   arglist[1] = 1.;
   gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

// Print results
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
   gMinuit->mnprin(3,amin);






    /*

vector<Float_t> vecX; //x pos pour tous les Z possibles
vector<Float_t> vecY; //y pos pour tous les Z possibles
vector<Float_t> vecZ; // tous les bins en Z par bin en x et y
vector<Float_t> vecNentries; // Nombre d'entrees par bin en x y z
vector<Float_t> vecZAverage; // valeur moyenne en Z par bin en x y


vector<Float_t> vecChargeError;


hGOODCharge_Charge_DiodePosition->GetNbinsX()

Double_t GetBinContent(Int_t bin) const
Double_t GetBinContent(Int_t bin, Int_t) const
Double_t GetBinContent(Int_t binx, Int_t biny, Int_t binz) const
void GetBinXYZ(Int_t binglobal, Int_t& binx, Int_t& biny, Int_t& binz) const
GetNdivisions
GetNbinsX
GetNbinsY
GetNbinsZ
hGOODCharge_Charge_DiodePosition->GetBinError    
Int_t GetBin(Int_t binx, Int_t biny = 0, Int_t binz = 0) const  = return global bin number

GetBinCenter

  fSegmentX.resize(fNSegment);
fAnalogChargeMap.push_back(AnalogCharge);

vector<Float_t> vecX;
vector<Float_t> vecY;
vector<Float_t> vecZ;
vector<Float_t> vecNentries;
vector<Float_t> vecChargeError;


GetXaxis()->GetBinCenter()


    */
  }




  cout<<" ------------- end ------"<<endl;
}
