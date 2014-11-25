/*
 * File:   quick_zDiff_check.C
 * Author: mustafa
 *
 * Created on September 14, 2012, 4:09 PM
 */
#include <iostream>

using namespace std;

/*
 *
 */
void quick_zDiff_check(TString file1="ladderGrid0910_vision.dat",TString file2="ladderGrid0910_stylus.dat")
{
    TGraph2D* gr1 = new TGraph2D(file1.Data());
    gr1->SetName("gr1");
    TGraph2D* gr2 = new TGraph2D(file2.Data());
    gr1->SetName("gr2");

    Double_t zDiff[3000];
    Double_t* z1 = gr1->GetZ();
    Double_t* z2 = gr2->GetZ();
    TH1D* hZDiff = new TH1D("hDiff", "hDiff", 200, -0.02, 0.02);

    for(UInt_t i=0;i<gr1->GetN();i++)
    {
	zDiff[i] = z1[i] - z2[i];
	hZDiff->Fill(zDiff[i]);
    }

    TCanvas* c1 = new TCanvas();
    hZDiff->Draw();
    c1->SaveAs("qk_hZDiff.gif");
}

