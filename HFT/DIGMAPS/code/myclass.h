//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon May 30 14:12:27 2011 by ROOT version 5.28/00
// from TTree mytree/DIGMAPS tree
// found on file: tree.root
//////////////////////////////////////////////////////////

#ifndef myclass_h
#define myclass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
   const Int_t kMaxfDIGParticleArray = 57;

class myclass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //DIGBeam         *beam_branch;
   Int_t           fBeamOption;
   Int_t           fRunNumber;
   Int_t           fNumberOfEvents;
   Float_t         fParticleDensity;
   Float_t         fThetaIncidentDeg;
   Float_t         fPhiIncidentDeg;
 //DIGPlane        *plane_branch;
   Float_t         fPitchX;
   Float_t         fPitchY;
   Float_t         fXdimension;
   Float_t         fYdimension;
   Float_t         fZdimension;
   Int_t           fNpixelsX;
   Int_t           fNpixelsY;
   Float_t         fNoiseElectrons;
   Float_t         fTemperature;
   Float_t         fIonizationEnergy;
   Float_t         fSegmentSize;
   Float_t         fMaximumSegmentSize;
   Float_t         fMaximumChargePerSegment;
   Float_t         fDiffusionMaximumRangeInX;
   Float_t         fDiffusionMaximumRangeInY;
   Float_t         fReflexionCoefficient;
   Float_t         fBasicModel_SigmaTenMicrons;
   Float_t         fLorentz2DModel_Cp0;
   Float_t         fLorentz2DModel_Cp1;
   Float_t         fLorentz2DModel_RangeLimit_InPitchUnit;
 //DIGADC          *adc_branch;
   Int_t           fNbits;
   Int_t           fNThresholds;
   Bool_t          fADC_linear;
   Float_t         fLSB;
   Float_t         fElectron_Conversion;
   Float_t         fADC_thresholds[4096];
 //DIGEvent        *event_branch;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           fNParticles;
   Int_t           fDIGParticleArray_;
   UInt_t          fDIGParticleArray_fUniqueID[kMaxfDIGParticleArray];   //[fDIGParticleArray_]
   UInt_t          fDIGParticleArray_fBits[kMaxfDIGParticleArray];   //[fDIGParticleArray_]
   Float_t         fDIGParticleArray_fEntryX[kMaxfDIGParticleArray];   //[fDIGParticleArray_]
   Float_t         fDIGParticleArray_fEntryY[kMaxfDIGParticleArray];   //[fDIGParticleArray_]
   Float_t         fDIGParticleArray_fEntryZ[kMaxfDIGParticleArray];   //[fDIGParticleArray_]
   Float_t         fDIGParticleArray_fExitX[kMaxfDIGParticleArray];   //[fDIGParticleArray_]
   Float_t         fDIGParticleArray_fExitY[kMaxfDIGParticleArray];   //[fDIGParticleArray_]
   Float_t         fDIGParticleArray_fExitZ[kMaxfDIGParticleArray];   //[fDIGParticleArray_]
   Float_t         fDIGParticleArray_fEnergy_deposited[kMaxfDIGParticleArray];   //[fDIGParticleArray_]
   Int_t           fDIGParticleArray_fNSegment[kMaxfDIGParticleArray];   //[fDIGParticleArray_]
   vector<Float_t> fDIGParticleArray_fSegmentX[kMaxfDIGParticleArray];
   vector<Float_t> fDIGParticleArray_fSegmentY[kMaxfDIGParticleArray];
   vector<Float_t> fDIGParticleArray_fSegmentZ[kMaxfDIGParticleArray];
   vector<Float_t> fDIGParticleArray_fSegmentCharge[kMaxfDIGParticleArray];
   Int_t           fDIGParticleArray_fNpixels[kMaxfDIGParticleArray];   //[fDIGParticleArray_]
   vector<Int_t>   fDIGParticleArray_fPixelMap[kMaxfDIGParticleArray];
   vector<Float_t> fDIGParticleArray_fAnalogChargeMap[kMaxfDIGParticleArray];
   vector<Float_t> fDIGParticleArray_fDigitalChargeMap[kMaxfDIGParticleArray];

   // List of branches
   TBranch        *b_beam_branch_fBeamOption;   //!
   TBranch        *b_beam_branch_fRunNumber;   //!
   TBranch        *b_beam_branch_fNumberOfEvents;   //!
   TBranch        *b_beam_branch_fParticleDensity;   //!
   TBranch        *b_beam_branch_fThetaIncidentDeg;   //!
   TBranch        *b_beam_branch_fPhiIncidentDeg;   //!
   TBranch        *b_plane_branch_fPitchX;   //!
   TBranch        *b_plane_branch_fPitchY;   //!
   TBranch        *b_plane_branch_fXdimension;   //!
   TBranch        *b_plane_branch_fYdimension;   //!
   TBranch        *b_plane_branch_fZdimension;   //!
   TBranch        *b_plane_branch_fNpixelsX;   //!
   TBranch        *b_plane_branch_fNpixelsY;   //!
   TBranch        *b_plane_branch_fNoiseElectrons;   //!
   TBranch        *b_plane_branch_fTemperature;   //!
   TBranch        *b_plane_branch_fIonizationEnergy;   //!
   TBranch        *b_plane_branch_fSegmentSize;   //!
   TBranch        *b_plane_branch_fMaximumSegmentSize;   //!
   TBranch        *b_plane_branch_fMaximumChargePerSegment;   //!
   TBranch        *b_plane_branch_fDiffusionMaximumRangeInX;   //!
   TBranch        *b_plane_branch_fDiffusionMaximumRangeInY;   //!
   TBranch        *b_plane_branch_fReflexionCoefficient;   //!
   TBranch        *b_plane_branch_fBasicModel_SigmaTenMicrons;   //!
   TBranch        *b_plane_branch_fLorentz2DModel_Cp0;   //!
   TBranch        *b_plane_branch_fLorentz2DModel_Cp1;   //!
   TBranch        *b_plane_branch_fLorentz2DModel_RangeLimit_InPitchUnit;   //!
   TBranch        *b_adc_branch_fNbits;   //!
   TBranch        *b_adc_branch_fNThresholds;   //!
   TBranch        *b_adc_branch_fADC_linear;   //!
   TBranch        *b_adc_branch_fLSB;   //!
   TBranch        *b_adc_branch_fElectron_Conversion;   //!
   TBranch        *b_adc_branch_fADC_thresholds;   //!
   TBranch        *b_event_branch_fUniqueID;   //!
   TBranch        *b_event_branch_fBits;   //!
   TBranch        *b_event_branch_fNParticles;   //!
   TBranch        *b_event_branch_fDIGParticleArray_;   //!
   TBranch        *b_fDIGParticleArray_fUniqueID;   //!
   TBranch        *b_fDIGParticleArray_fBits;   //!
   TBranch        *b_fDIGParticleArray_fEntryX;   //!
   TBranch        *b_fDIGParticleArray_fEntryY;   //!
   TBranch        *b_fDIGParticleArray_fEntryZ;   //!
   TBranch        *b_fDIGParticleArray_fExitX;   //!
   TBranch        *b_fDIGParticleArray_fExitY;   //!
   TBranch        *b_fDIGParticleArray_fExitZ;   //!
   TBranch        *b_fDIGParticleArray_fEnergy_deposited;   //!
   TBranch        *b_fDIGParticleArray_fNSegment;   //!
   TBranch        *b_fDIGParticleArray_fSegmentX;   //!
   TBranch        *b_fDIGParticleArray_fSegmentY;   //!
   TBranch        *b_fDIGParticleArray_fSegmentZ;   //!
   TBranch        *b_fDIGParticleArray_fSegmentCharge;   //!
   TBranch        *b_fDIGParticleArray_fNpixels;   //!
   TBranch        *b_fDIGParticleArray_fPixelMap;   //!
   TBranch        *b_fDIGParticleArray_fAnalogChargeMap;   //!
   TBranch        *b_fDIGParticleArray_fDigitalChargeMap;   //!

   myclass(TTree *tree=0);
   virtual ~myclass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef myclass_cxx
myclass::myclass(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("tree.root");
      if (!f) {
         f = new TFile("tree.root");
      }
      tree = (TTree*)gDirectory->Get("mytree");

   }
   Init(tree);
}

myclass::~myclass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t myclass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t myclass::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void myclass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fBeamOption", &fBeamOption, &b_beam_branch_fBeamOption);
   fChain->SetBranchAddress("fRunNumber", &fRunNumber, &b_beam_branch_fRunNumber);
   fChain->SetBranchAddress("fNumberOfEvents", &fNumberOfEvents, &b_beam_branch_fNumberOfEvents);
   fChain->SetBranchAddress("fParticleDensity", &fParticleDensity, &b_beam_branch_fParticleDensity);
   fChain->SetBranchAddress("fThetaIncidentDeg", &fThetaIncidentDeg, &b_beam_branch_fThetaIncidentDeg);
   fChain->SetBranchAddress("fPhiIncidentDeg", &fPhiIncidentDeg, &b_beam_branch_fPhiIncidentDeg);
   fChain->SetBranchAddress("fPitchX", &fPitchX, &b_plane_branch_fPitchX);
   fChain->SetBranchAddress("fPitchY", &fPitchY, &b_plane_branch_fPitchY);
   fChain->SetBranchAddress("fXdimension", &fXdimension, &b_plane_branch_fXdimension);
   fChain->SetBranchAddress("fYdimension", &fYdimension, &b_plane_branch_fYdimension);
   fChain->SetBranchAddress("fZdimension", &fZdimension, &b_plane_branch_fZdimension);
   fChain->SetBranchAddress("fNpixelsX", &fNpixelsX, &b_plane_branch_fNpixelsX);
   fChain->SetBranchAddress("fNpixelsY", &fNpixelsY, &b_plane_branch_fNpixelsY);
   fChain->SetBranchAddress("fNoiseElectrons", &fNoiseElectrons, &b_plane_branch_fNoiseElectrons);
   fChain->SetBranchAddress("fTemperature", &fTemperature, &b_plane_branch_fTemperature);
   fChain->SetBranchAddress("fIonizationEnergy", &fIonizationEnergy, &b_plane_branch_fIonizationEnergy);
   fChain->SetBranchAddress("fSegmentSize", &fSegmentSize, &b_plane_branch_fSegmentSize);
   fChain->SetBranchAddress("fMaximumSegmentSize", &fMaximumSegmentSize, &b_plane_branch_fMaximumSegmentSize);
   fChain->SetBranchAddress("fMaximumChargePerSegment", &fMaximumChargePerSegment, &b_plane_branch_fMaximumChargePerSegment);
   fChain->SetBranchAddress("fDiffusionMaximumRangeInX", &fDiffusionMaximumRangeInX, &b_plane_branch_fDiffusionMaximumRangeInX);
   fChain->SetBranchAddress("fDiffusionMaximumRangeInY", &fDiffusionMaximumRangeInY, &b_plane_branch_fDiffusionMaximumRangeInY);
   fChain->SetBranchAddress("fReflexionCoefficient", &fReflexionCoefficient, &b_plane_branch_fReflexionCoefficient);
   fChain->SetBranchAddress("fBasicModel_SigmaTenMicrons", &fBasicModel_SigmaTenMicrons, &b_plane_branch_fBasicModel_SigmaTenMicrons);
   fChain->SetBranchAddress("fLorentz2DModel_Cp0", &fLorentz2DModel_Cp0, &b_plane_branch_fLorentz2DModel_Cp0);
   fChain->SetBranchAddress("fLorentz2DModel_Cp1", &fLorentz2DModel_Cp1, &b_plane_branch_fLorentz2DModel_Cp1);
   fChain->SetBranchAddress("fLorentz2DModel_RangeLimit_InPitchUnit", &fLorentz2DModel_RangeLimit_InPitchUnit, &b_plane_branch_fLorentz2DModel_RangeLimit_InPitchUnit);
   fChain->SetBranchAddress("fNbits", &fNbits, &b_adc_branch_fNbits);
   fChain->SetBranchAddress("fNThresholds", &fNThresholds, &b_adc_branch_fNThresholds);
   fChain->SetBranchAddress("fADC_linear", &fADC_linear, &b_adc_branch_fADC_linear);
   fChain->SetBranchAddress("fLSB", &fLSB, &b_adc_branch_fLSB);
   fChain->SetBranchAddress("fElectron_Conversion", &fElectron_Conversion, &b_adc_branch_fElectron_Conversion);
   fChain->SetBranchAddress("fADC_thresholds[4096]", fADC_thresholds, &b_adc_branch_fADC_thresholds);
   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_event_branch_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_event_branch_fBits);
   fChain->SetBranchAddress("fNParticles", &fNParticles, &b_event_branch_fNParticles);
   fChain->SetBranchAddress("fDIGParticleArray", &fDIGParticleArray_, &b_event_branch_fDIGParticleArray_);
   fChain->SetBranchAddress("fDIGParticleArray.fUniqueID", fDIGParticleArray_fUniqueID, &b_fDIGParticleArray_fUniqueID);
   fChain->SetBranchAddress("fDIGParticleArray.fBits", fDIGParticleArray_fBits, &b_fDIGParticleArray_fBits);
   fChain->SetBranchAddress("fDIGParticleArray.fEntryX", fDIGParticleArray_fEntryX, &b_fDIGParticleArray_fEntryX);
   fChain->SetBranchAddress("fDIGParticleArray.fEntryY", fDIGParticleArray_fEntryY, &b_fDIGParticleArray_fEntryY);
   fChain->SetBranchAddress("fDIGParticleArray.fEntryZ", fDIGParticleArray_fEntryZ, &b_fDIGParticleArray_fEntryZ);
   fChain->SetBranchAddress("fDIGParticleArray.fExitX", fDIGParticleArray_fExitX, &b_fDIGParticleArray_fExitX);
   fChain->SetBranchAddress("fDIGParticleArray.fExitY", fDIGParticleArray_fExitY, &b_fDIGParticleArray_fExitY);
   fChain->SetBranchAddress("fDIGParticleArray.fExitZ", fDIGParticleArray_fExitZ, &b_fDIGParticleArray_fExitZ);
   fChain->SetBranchAddress("fDIGParticleArray.fEnergy_deposited", fDIGParticleArray_fEnergy_deposited, &b_fDIGParticleArray_fEnergy_deposited);
   fChain->SetBranchAddress("fDIGParticleArray.fNSegment", fDIGParticleArray_fNSegment, &b_fDIGParticleArray_fNSegment);
   fChain->SetBranchAddress("fDIGParticleArray.fSegmentX", fDIGParticleArray_fSegmentX, &b_fDIGParticleArray_fSegmentX);
   fChain->SetBranchAddress("fDIGParticleArray.fSegmentY", fDIGParticleArray_fSegmentY, &b_fDIGParticleArray_fSegmentY);
   fChain->SetBranchAddress("fDIGParticleArray.fSegmentZ", fDIGParticleArray_fSegmentZ, &b_fDIGParticleArray_fSegmentZ);
   fChain->SetBranchAddress("fDIGParticleArray.fSegmentCharge", fDIGParticleArray_fSegmentCharge, &b_fDIGParticleArray_fSegmentCharge);
   fChain->SetBranchAddress("fDIGParticleArray.fNpixels", fDIGParticleArray_fNpixels, &b_fDIGParticleArray_fNpixels);
   fChain->SetBranchAddress("fDIGParticleArray.fPixelMap", fDIGParticleArray_fPixelMap, &b_fDIGParticleArray_fPixelMap);
   fChain->SetBranchAddress("fDIGParticleArray.fAnalogChargeMap", fDIGParticleArray_fAnalogChargeMap, &b_fDIGParticleArray_fAnalogChargeMap);
   fChain->SetBranchAddress("fDIGParticleArray.fDigitalChargeMap", fDIGParticleArray_fDigitalChargeMap, &b_fDIGParticleArray_fDigitalChargeMap);
   Notify();
}

Bool_t myclass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void myclass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t myclass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef myclass_cxx
