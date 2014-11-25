/*
 * File:   plot_comp.C
 * Author: mustafa
 *
 * Created on September 14, 2012, 3:15 AM
 *
 * You can use this macro to compare ladder surveys.
 * file1 and file2 can be measurements using the same probe
 * or vision and stylus.
 */
#include <iostream>

#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TGraph2D.h"
//#include "Tps.h"
#include "LadderSurvey.h"

using namespace std;


void plot_ladder_comp(TString visionFile="ladderGrid0910_vision.dat",TString stylusFile="ladderGrid0910_stylus.dat",UInt_t points=132)
{
    gSystem->CompileMacro("Tps.C");

    TString baseName = visionFile;
    baseName.ReplaceAll(".txt","_");
    baseName = baseName + stylusFile;
    baseName.ReplaceAll(".txt","\0");

    LadderSurvey vision(visionFile,points);
    LadderSurvey stylus(stylusFile,points);

    if(vision.mNChips != stylus.mNChips ||
	    vision.mNPoints != stylus.mNPoints)
    {
	cout<<"Either number of chips or number of measurement points are not "
		"equal in the input files. Exiting..."<<endl;
	exit(0);
    }


    // Make the difference histograms

    UInt_t nChips = vision.mNChips;
    UInt_t nPoints = vision.mNPoints;

    Double_t* zDiff = new Double_t[nChips*nPoints];
    Double_t* zDiffFit = new Double_t[nChips*nPoints];

    TH1D* hZDiff = new TH1D("hDiff", "hDiff", 200, -0.02, 0.02);
    TH1D* hZDiffFit = new TH1D("hDiffFit", "hDiffFit", 200, -0.02, 0.02);
    vision.GenerateTps();

    for (UInt_t iChip = 0; iChip < nChips; iChip++)
    {
        for (UInt_t iPoint = 0; iPoint < nPoints; iPoint++)
	{
	    zDiff[iChip*nPoints+iPoint] =
		    vision.GetZ(iChip,iPoint) - stylus.GetZ(iChip,iPoint);

	    Double_t x = stylus.GetX(iChip,iPoint);
	    Double_t y = stylus.GetY(iChip,iPoint);

	    zDiffFit[iChip*nPoints+iPoint] =
		    vision.GetZFit(iChip,x,y) - stylus.GetZ(iChip,iPoint);

	    // Fill histograms
	    hZDiff->Fill(zDiff[iChip*nPoints+iPoint]);
	    hZDiffFit->Fill(zDiffFit[iChip*nPoints+iPoint]);
        }
    }

    TCanvas* c1 = new TCanvas("can1", "can1");
    c1->SetRightMargin(0.14);

    hZDiff->Draw();
    c1->SaveAs(Form("%s_hZDiff.gif",baseName.Data()));
    hZDiffFit->Draw();
    c1->SaveAs(Form("%s_hZDiffFit.gif",baseName.Data()));

    TCanvas* c2 = new TCanvas("can2", "can2", 1000, 300);
    c2->SetRightMargin(0.14);

    TGraph2D* grZDiff = new TGraph2D(nChips*nPoints,vision.grandX,vision.grandY,zDiff);
    grZDiff->SetName("zDiff");
    grZDiff->SetTitle("zDiff");
    grZDiff->SetMarkerStyle(20);
    grZDiff->Draw("pcol");
    c2->SaveAs(Form("%s_zDiff2D.gif",baseName.Data()));

    TGraph2D* grZDiffFit = new TGraph2D(nChips*nPoints,vision.grandX,vision.grandY,zDiffFit);
    grZDiffFit->SetName("zDiffFit");
    grZDiffFit->SetTitle("zDiffFit");
    grZDiffFit->SetMarkerStyle(20);
    grZDiffFit->Draw("pcol");
    c2->SaveAs(Form("%s_zDiffFit2D.gif",baseName.Data()));

    TFile* outFile = new TFile(Form("%s_comp.root",baseName.Data()),"RECREATE");
    outFile->cd();
    hZDiff->Write();
    hZDiffFit->Write();
    grZDiff->Write();
    grZDiffFit->Write();
    outFile->Close();

    gSystem->CleanCompiledMacros();
}

