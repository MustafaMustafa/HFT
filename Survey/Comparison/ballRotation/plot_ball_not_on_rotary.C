/*
 * File:   plot_ball_not_on_rotary.C
 * Author: mustafa
 *
 * Created on September 19, 2012, 8:36 PM
 */
#include <iostream>
#include <fstream>
#include <string>

#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraph2D.h"
#include "TAxis.h"
#include "TString.h"
#include "TNtuple.h"
#include "TVector3.h"
#include "TVectorD.h"
#include "TMatrixD.h"
#include "TMatrixDSym.h"
#include "TMinuit.h"
#include "TMath.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TLegend.h"

using namespace std;

Int_t markerColor[6] = {2,4,6,8,9,1};
// if size becomes an issue you can modify this to create the arrays on the heap
UInt_t arrayIndex = 0;
UInt_t nMeasurementsPerBall = 7;
TFile* outFile;
Double_t dataX[200];
Double_t dataY[200];
Double_t dataZ[200];
Double_t dR[200];
Double_t dTheta[200];
Double_t dX[200];

// assuming 10 circles max
Double_t minStat[10][6]; // minimization statistics
Double_t center[10][3];
Double_t centerErr[10][3];
Double_t axisVec[10][3];
Double_t axisVecErr[10][3];
TGraph2D* gr2Circles[10];
TGraph2D* gr2AxisLine;
TGraph* grDR[10];
TGraph* grDTheta[10];
TGraph* grDX[10];
TGraphErrors* grY0X0;
TGraphErrors* grZ0X0;
TGraphErrors* grDY0X0; // difference between the y0 and the fit function
TGraphErrors* grDZ0X0;
TF1* fY0X0;
TF1* fZ0X0;
Bool_t axisFitExists;

TNtuple* ntData;

void fit_all(UInt_t nBalls,TF1* fYX=0,TF1* fZX=0);
void fit_data(UInt_t ballIndx,TF1* fYX=0,TF1* fZX=0);
void find_YZ_circle_center(TVectorD& centVec,Double_t& R0);
void fit_axis(UInt_t nBalls); // numberOfBalls
void fcn(Int_t& npar,Double_t* gin,Double_t& f,Double_t* par,Int_t iflag);
UInt_t read_file(TString inputFile); // returns number of balls after reading data into data* arrays.
void book_graphs(UInt_t ballIndx);
void draw(TString inFileName,UInt_t nBalls,Bool_t drawAxisFit=false);
void write_graphs(TString dirName,UInt_t nBalls,Bool_t axisFitGraphs=false);

void plot_ball_not_on_rotary(TString inputFile="shaftSector0917.txt",UInt_t measurementsPerBall=7)
{
    axisFitExists = false;

    // define ntuples and get data
    nMeasurementsPerBall = measurementsPerBall;
    ntData = new TNtuple("ntData","ntData","x:y:z:r");
    UInt_t nBalls = read_file(inputFile);

    // open outFile and write data
    inputFile.ReplaceAll(".txt","\0");
    outFile = new TFile(Form("%s.root",inputFile.Data()),"RECREATE");
    outFile->cd();
    ntData->SetMarkerStyle(20);
    ntData->SetMarkerSize(1.4);
    ntData->Write();

    // Fit data
    fit_all(nBalls,0,0);
    if(nBalls>1) fit_axis(nBalls);
    draw(inputFile,nBalls,true);
    write_graphs("no_constraint",nBalls,true);

    if(nBalls>1)
    {
        // Constrain Y0
        fit_all(nBalls, fY0X0, 0);
        draw(Form("%s_const_Y0", inputFile.Data()), nBalls);
        write_graphs("const_Y0", nBalls);

        // Constrain Z0
        fit_all(nBalls, 0, fZ0X0);
        draw(Form("%s_const_Z0", inputFile.Data()), nBalls);
        write_graphs("const_Z0", nBalls);

        // Constrain Y0 and Z0
        fit_all(nBalls, fY0X0, fZ0X0);
        draw(Form("%s_const_Y0Z0", inputFile.Data()), nBalls);
        write_graphs("const_Y0Z0", nBalls);
    }

    // Report
    cout<<"\n\n";
    cout << "Minimization done and data stored. ";
    cout << "Lines below should be used to judge fits quality." << endl;

    for(UInt_t iBall=0;iBall<nBalls;iBall++)
    {
	cout<<iBall+1<<" ";
	cout<<minStat[iBall][0]<<" ";
	cout<<minStat[iBall][1]<<" ";
	cout<<minStat[iBall][2]<<" ";
	cout<<minStat[iBall][3]<<" ";
	cout<<minStat[iBall][4]<<" ";
	cout<<minStat[iBall][5]<<" ";
	cout<<"\n";
    }

    outFile->Close();
}
//_____________________
void fit_all(UInt_t nBalls, TF1* fYX, TF1* fZX)
{
    static Bool_t firstCall = true;

    for (UInt_t iBall = 0; iBall < nBalls; iBall++)
    {
        arrayIndex = iBall * nMeasurementsPerBall;

	if(firstCall) book_graphs(iBall);

        cout << "Ball number: " << iBall + 1 << endl;

        for (UInt_t i = 0; i < nMeasurementsPerBall; i++)
	{
            cout << i + arrayIndex << " " << dataX[i + arrayIndex] << " "
                    "" << dataY[i + arrayIndex] << " " << dataZ[i + arrayIndex] << endl;
        }

        fit_data(iBall, fYX, fZX);
        cout << "__________________________________" << endl;
        cout << "__________________________________" << endl;
    }

    firstCall = false;
}
//_____________________
void fit_data(UInt_t bIndx,TF1* fYX,TF1* fZX)
{
    // Get the initial center of the circle in YZ-plane
    Double_t x0,y0,z0,axisRx,axisRy,axisRz,R;
    TVectorD centVec0(2); // centVec0 is in YZ-plane
    Double_t R0 = 0;
    find_YZ_circle_center(centVec0,R0);

    x0 = dataX[arrayIndex];
    y0 = centVec0[0];
    z0 = centVec0[1];
    R = R0;
    axisRx = R0;
    axisRy = 0;
    axisRz = 0;

    Double_t yStep = 0.1;
    Double_t zStep = 0.1;

    // if fYX or fYZ provided, constrain the fit
    if(fYX)
    {
        y0 = fYX->Eval(x0);
        yStep = 0;
    }

    if(fZX)
    {
        z0 = fZX->Eval(x0);
        zStep = 0;
    }

    //3D circle TMinuitFit
    Double_t arglist[10];
    int ierflag = 0;
    TMinuit *gMinuit = new TMinuit(6);
    gMinuit->SetMaxIterations(50000);
    gMinuit->SetFCN(fcn);
    gMinuit->mnparm(0, "x0", x0, 0.1, x0 - 5, x0 + 5, ierflag);
    gMinuit->mnparm(1, "y0", y0, yStep, y0 - 5, y0 + 5, ierflag);
    gMinuit->mnparm(2, "z0", z0, zStep, z0 - 5, z0 + 5, ierflag);
    gMinuit->mnparm(3, "axisRx", R, 0.1, R - 5, R + 5, ierflag);
    gMinuit->mnparm(4, "axisRy", 0., 0.01, -1, 1, ierflag);
    gMinuit->mnparm(5, "axisRz", 0., 0.01, -1, 1, ierflag);

    // printout
    arglist[0] = 1;
    gMinuit->mnexcm("SET PRINT", arglist, 1, ierflag);

    // minimize
    arglist[0] = 1000;
    gMinuit->mnexcm("HESSE", arglist, 1, ierflag);
    arglist[0] = 5000;
    arglist[1] = 0.0001;
    gMinuit->mnexcm("MIGRAD", arglist, 2, ierflag);

    // Get minimization statistics
    Double_t amin, edm, errdef;
    Int_t nvpar, nparx, icstat;
    gMinuit->mnstat(amin, edm, errdef, nvpar, nparx, icstat);
    minStat[bIndx][0] = amin;
    minStat[bIndx][1] = edm;
    minStat[bIndx][2] = errdef;
    minStat[bIndx][3] = nvpar;
    minStat[bIndx][4] = nparx;
    minStat[bIndx][5] = icstat;

    // Get fit parameters
    Double_t x0Error, y0Error, z0Error, axisRxError, axisRyError, axisRzError;
    gMinuit->GetParameter(0, x0, x0Error);
    gMinuit->GetParameter(1, y0, y0Error);
    gMinuit->GetParameter(2, z0, z0Error);
    gMinuit->GetParameter(3, axisRx, axisRxError);
    gMinuit->GetParameter(4, axisRy, axisRyError);
    gMinuit->GetParameter(5, axisRz, axisRzError);

    // fill arrays
    center[bIndx][0] = x0;
    center[bIndx][1] = y0;
    center[bIndx][2] = z0;
    centerErr[bIndx][0] = x0Error;
    centerErr[bIndx][1] = y0Error;
    centerErr[bIndx][2] = z0Error;
    axisVec[bIndx][0] = axisRx;
    axisVec[bIndx][1] = axisRy;
    axisVec[bIndx][2] = axisRz;
    axisVecErr[bIndx][0] = axisRxError;
    axisVecErr[bIndx][1] = axisRyError;
    axisVecErr[bIndx][2] = axisRzError;

    // Calculate deviations
    TVector3 xyz0(x0, y0, z0);
    TVector3 axisR(axisRx, axisRy, axisRz);
    TVector3 axis = axisR.Unit();
    R = axisR.Mag();
    TVector3 xyz1(dataX[arrayIndex], dataY[arrayIndex], dataZ[arrayIndex]);
    TVector3 zeroDegree = axis.Cross((xyz1 - xyz0).Cross(axis));

    for (UInt_t i = 0; i < nMeasurementsPerBall; i++)
    {
        TVector3 xyz(dataX[i+arrayIndex], dataY[i+arrayIndex], dataZ[i+arrayIndex]);
        TVector3 tempVec = (xyz - xyz0).Unit().Cross(axisR);
        TVector3 xyzOnCircle = axis.Cross(tempVec);
        double theta = xyzOnCircle.Angle(zeroDegree);
        xyzOnCircle += xyz0;

	// temporary
	Double_t theta0 = TMath::Pi()*(i/6.0);
	if(i>3) theta0 = TMath::Pi()*((i-3)/6.0);

        dTheta[i+arrayIndex] = theta - theta0;
        dR[i+arrayIndex] = (xyz - xyzOnCircle).Dot((xyzOnCircle - xyz0).Unit());
        dX[i+arrayIndex] = (xyz - xyzOnCircle).Dot(axis);

	// Fill graphs
	grDR[bIndx]->SetPoint(i, TMath::Pi()*(i / 6.), dR[i+arrayIndex]);
        grDTheta[bIndx]->SetPoint(i, TMath::Pi()*(i / 6.), dTheta[i+arrayIndex]);
        grDX[bIndx]->SetPoint(i, TMath::Pi()*(i / 6.), dX[i+arrayIndex]);
	//Fill ntuple
	// Fill gr2Circles
	gr2Circles[bIndx]->SetPoint(i,dataX[i+arrayIndex],dataY[i+arrayIndex],dataZ[i+arrayIndex]);
    }

    delete gMinuit;
}
//_____________________
void find_YZ_circle_center(TVectorD& centVec, Double_t& R0)
{
    // See http://www.dtcenter.org/met/users/docs/write_ups/circle_fit.pdf
    TVectorD yVec(nMeasurementsPerBall);
    TVectorD zVec(nMeasurementsPerBall);

    for (UInt_t i = 0; i < nMeasurementsPerBall; i++)
    {
        yVec(i) = dataY[i+arrayIndex];
        zVec(i) = dataZ[i+arrayIndex];
    }

    Double_t yavg = yVec.Sum()/yVec.GetNoElements();
    Double_t zavg = zVec.Sum()/zVec.GetNoElements();

    yVec -= yavg;
    zVec -= zavg;

    Double_t Suu = 0;
    Double_t Svv = 0;
    Double_t Suv = 0;
    Double_t Suuu = 0;
    Double_t Svvv = 0;
    Double_t Suvv = 0;
    Double_t Svuu = 0;

    for(UInt_t i=0; i<nMeasurementsPerBall;i++)
    {
        Suu += yVec[i]*yVec[i];
        Svv += zVec[i]*zVec[i];
        Suv += yVec[i]*zVec[i];
        Suuu += yVec[i]*yVec[i]*yVec[i];
        Svvv += zVec[i]*zVec[i]*zVec[i];
        Suvv += yVec[i]*zVec[i]*zVec[i];
        Svuu += zVec[i]*yVec[i]*yVec[i];
    }

    TMatrixD SMatrix(2,2);
    TVectorD hVec(2);
    SMatrix(0,0) = Suu; SMatrix(0,1) = Suv;
    SMatrix(1,0) = Suv; SMatrix(1,1) = Svv;
    hVec(0) = (1/2.)*(Suuu+Suvv);
    hVec(1) = (1/2.)*(Svvv+Svuu);
    SMatrix.Invert();
    centVec = SMatrix * hVec;

    R0 = sqrt(centVec[0]*centVec[0]+centVec[1]*centVec[1]+(Suu+Svv)/yVec.GetNoElements());
    centVec[0] += yavg;
    centVec[1] += zavg;
}
//_____________________
void fit_axis(UInt_t nBalls)
{
    Double_t x[nBalls];
    Double_t y[nBalls];
    Double_t z[nBalls];
    Double_t xErr[nBalls];
    Double_t yErr[nBalls];
    Double_t zErr[nBalls];

    for(UInt_t iBall=0;iBall<nBalls;iBall++)
    {
	x[iBall] = center[iBall][0];
	y[iBall] = center[iBall][1];
	z[iBall] = center[iBall][2];
	xErr[iBall] = 0;//centerErr[iBall][0];
	yErr[iBall] = 0;//centerErr[iBall][1];
	zErr[iBall] = 0;//centerErr[iBall][2];
    }

    // Fill graphs
    grY0X0 = new TGraphErrors(nBalls,x,y,xErr,yErr);
    grZ0X0 = new TGraphErrors(nBalls,x,z,xErr,zErr);
    grY0X0->SetName("grY0X0");
    grZ0X0->SetName("grZ0X0");
    grY0X0->SetTitle("grY0X0;x0(mm);y0(mm)");
    grZ0X0->SetTitle("grZ0X0;x0(mm);z0(mm)");
    grY0X0->GetYaxis()->SetTitleOffset(1.4);
    grZ0X0->GetYaxis()->SetTitleOffset(1.4);
    grY0X0->SetMarkerStyle(20);
    grY0X0->SetMarkerSize(1.4);
    grY0X0->SetMarkerColor(2);
    grY0X0->SetLineColor(2);
    grZ0X0->SetMarkerStyle(20);
    grZ0X0->SetMarkerSize(1.4);
    grZ0X0->SetMarkerColor(2);
    grZ0X0->SetLineColor(2);

    //Fit Graphs
    grY0X0->Fit("pol1","EQ");
    grZ0X0->Fit("pol1","EQ");
    fY0X0 = grY0X0->GetFunction("pol1");
    fZ0X0 = grZ0X0->GetFunction("pol1");
    fY0X0->SetName("fitY0X0");
    fZ0X0->SetName("fitZ0X0");
    fY0X0->SetTitle("fitY0X0");
    fZ0X0->SetTitle("fitZ0X0");

    // get the difference of the fits and the data points
    grDY0X0 = (TGraphErrors*)grY0X0->Clone("grDY0X0");
    grDZ0X0 = (TGraphErrors*)grZ0X0->Clone("grDZ0X0");
    grDY0X0->SetName("grDY0X0");
    grDZ0X0->SetName("grDZ0X0");
    grDY0X0->SetTitle("fit-y0;x0(mm);#Deltay(mm)");
    grDZ0X0->SetTitle("fit-z0;x0(mm);#Deltaz(mm)");
    grDY0X0->GetYaxis()->SetTitleOffset(1.7);
    grDZ0X0->GetYaxis()->SetTitleOffset(1.7);
    grDY0X0->Apply(fY0X0);
    grDZ0X0->Apply(fZ0X0);

    gr2AxisLine = new TGraph2D();
    gr2AxisLine->SetName("gr2AxisLine");
    gr2AxisLine->SetTitle("gr2AxisLine");
    gr2AxisLine->SetMarkerStyle(20);
    gr2AxisLine->SetMarkerSize(1.4);
    gr2AxisLine->SetMarkerColor(1);
    gr2AxisLine->SetLineColor(1);
    gr2AxisLine->SetLineWidth(2);

    // there should be a function to add graphs somewhere or maybe use TH1
    // anyway, no time to do that here
    Double_t* y0x0 = grY0X0->GetY();
    Double_t* z0x0 = grZ0X0->GetY();
    Double_t* dy0x0 = grDY0X0->GetY();
    Double_t* dz0x0 = grDZ0X0->GetY();
    for(UInt_t iBall=0;iBall<nBalls;iBall++)
    {
	gr2AxisLine->SetPoint(iBall,x[iBall],dy0x0[iBall],dz0x0[iBall]);
	dy0x0[iBall] = dy0x0[iBall] - y0x0[iBall];
	dz0x0[iBall] = dz0x0[iBall] - z0x0[iBall];
    }

    axisFitExists = true;
}
//__________________________
void fcn(Int_t& npar,Double_t* gin,Double_t& f,Double_t* par,Int_t iflag)
{
    Double_t x0 = par[0];
    Double_t y0 = par[1];
    Double_t z0 = par[2];
    Double_t axisRx = par[3];
    Double_t axisRy = par[4];
    Double_t axisRz = par[5];
    TVector3 xyz0(x0, y0, z0);
    TVector3 axisR(axisRx, axisRy, axisRz);
    TVector3 axis = axisR.Unit();
    Double_t chi2 = 0;

    for (UInt_t i = 0; i < nMeasurementsPerBall; i++)
    {
        TVector3 xyz(dataX[i+arrayIndex], dataY[i+arrayIndex], dataZ[i+arrayIndex]);
        TVector3 tempVec = (xyz - xyz0).Unit().Cross(axisR);
        TVector3 xyzOnCircle = axis.Cross(tempVec);
        xyzOnCircle += xyz0;
        chi2 += (xyz - xyzOnCircle).Mag2();
    }
    f = chi2;

    cout << x0 << ", " << y0 << ", " << z0 << ", " << axisRx << ", " << axisRy << ", " << axisRz << "     chi2: " << chi2 << endl;
}
//_____________________
UInt_t read_file(TString inputFile)
{
    ifstream ifs(inputFile.Data());
    string tempstring;
    Double_t x,y,z,r;

    UInt_t counter = 0;
    UInt_t mpb = nMeasurementsPerBall - 1;

    while(ifs >> tempstring >> tempstring >> x >> y >> z >> r)
    {
	ntData->Fill(x,y,z,r);

//	if(dataSequential)
//	{
//	    dataX[counter] = x;
//	    dataY[counter] = y;
//	    dataZ[counter] = z;
//	    ++counter;
//
//	    continue;
//	}

	UInt_t idx = counter/mpb + (counter%mpb) * (mpb+1);
	++counter;
	dataX[idx] = x;
	dataY[idx] = y;
	dataZ[idx] = z;
    }

    return counter/nMeasurementsPerBall;
}
//__________________
void book_graphs(UInt_t ballIndx)
{
    grDR[ballIndx] = new TGraph();
    grDTheta[ballIndx] = new TGraph();
    grDX[ballIndx]= new TGraph();
    gr2Circles[ballIndx] = new TGraph2D();

    grDR[ballIndx]->SetName(Form("dR_ball_%d",ballIndx));
    grDR[ballIndx]->SetTitle(Form("#DeltaR_ball_%d;#theta;#DeltaR",ballIndx));
    grDR[ballIndx]->SetMarkerStyle(20);
    grDR[ballIndx]->SetMarkerSize(1.4);
    grDR[ballIndx]->SetMarkerColor(markerColor[ballIndx%6]);
    grDR[ballIndx]->SetLineColor(markerColor[ballIndx%6]);
    grDR[ballIndx]->GetYaxis()->SetTitleOffset(1.7);

    grDTheta[ballIndx]->SetName(Form("dTheta_ball_%d",ballIndx));
    grDTheta[ballIndx]->SetTitle(Form("#DeltaTheta_ball_%d;#theta;#Delta#theta",ballIndx));
    grDTheta[ballIndx]->SetMarkerStyle(20);
    grDTheta[ballIndx]->SetMarkerSize(1.4);
    grDTheta[ballIndx]->SetMarkerColor(markerColor[ballIndx%6]);
    grDTheta[ballIndx]->SetLineColor(markerColor[ballIndx%6]);
    grDTheta[ballIndx]->GetYaxis()->SetTitleOffset(1.7);

    grDX[ballIndx]->SetName(Form("dX_ball_%d",ballIndx));
    grDX[ballIndx]->SetTitle(Form("#DeltaX_ball_%d;#theta;#Deltax",ballIndx));
    grDX[ballIndx]->SetMarkerStyle(20);
    grDX[ballIndx]->SetMarkerSize(1.4);
    grDX[ballIndx]->SetMarkerColor(markerColor[ballIndx%6]);
    grDX[ballIndx]->SetLineColor(markerColor[ballIndx%6]);
    grDX[ballIndx]->GetYaxis()->SetTitleOffset(1.7);

    gr2Circles[ballIndx]->SetName(Form("data_ball_%d",ballIndx));
    gr2Circles[ballIndx]->SetTitle("\0;x(mm);y(mm);z(mm)");
    gr2Circles[ballIndx]->SetMarkerStyle(20);
    gr2Circles[ballIndx]->SetMarkerSize(1.4);
    gr2Circles[ballIndx]->SetMarkerColor(markerColor[ballIndx%6]);
    gr2Circles[ballIndx]->SetLineColor(markerColor[ballIndx%6]);
    gr2Circles[ballIndx]->SetFillColor(markerColor[ballIndx%6]);
}
//__________________
void draw(TString inFileName,UInt_t nBalls,Bool_t drawAxisFit)
{
    // draw dR and dX
    TCanvas* cDR = new TCanvas("cDR", "cDR");
    TCanvas* cDX = new TCanvas("cDX","cDX");
    TLegend* leg = new TLegend(0.85,0.72,0.99,0.95);
    leg->SetFillColor(0);
    leg->SetBorderSize(0);

    cDR->cd();
    grDR[0]->SetMinimum(-0.009);
    grDR[0]->SetMaximum(0.009);
    grDR[0]->SetTitle("dR");
    grDR[0]->Draw("AP");
    cDX->cd();
    grDX[0]->SetMinimum(-0.005);
    grDX[0]->SetMaximum(0.005);
    grDX[0]->SetTitle("dX");
    grDX[0]->Draw("AP");
    for(UInt_t iBall=0;iBall<nBalls;iBall++)
    {
	cDR->cd();
	grDR[iBall]->Draw("P:SAME");
	cDX->cd();
	grDX[iBall]->Draw("P:SAME");

	// legend
	leg->AddEntry(grDR[iBall],Form("Ball %d",iBall+1),"P");
    }
    cDR->cd();
    leg->Draw();
    cDR->SaveAs(Form("%s_dR_theta.gif",inFileName.Data()));
    cDX->cd();
    leg->Draw();
    cDX->SaveAs(Form("%s_dX_theta.gif",inFileName.Data()));
    grDR[0]->SetTitle("dR_ball_0");
    grDX[0]->SetTitle("dX_ball_0");

    delete cDR;
    delete cDX;

    if(!drawAxisFit || !axisFitExists) return;

    // draw Y0X0 and Z0X0
    gStyle->SetOptFit(111);
    TCanvas* c1 = new TCanvas("c1", "c1");

    c1->cd();
    grY0X0->Draw("AP");
    c1->SaveAs(Form("%s_y0x0.gif",inFileName.Data()));

    c1->cd();
    grZ0X0->Draw("AP");
    c1->SaveAs(Form("%s_z0x0.gif",inFileName.Data()));

    c1->cd();
    grDY0X0->Draw("AP");
    c1->SaveAs(Form("%s_dy0x0.gif",inFileName.Data()));

    c1->cd();
    grDZ0X0->Draw("AP");
    c1->SaveAs(Form("%s_dz0x0.gif",inFileName.Data()));

    // draw data in 3D
    c1->cd();
    ntData->Draw("z:y:x");

    for(Int_t iBall=nBalls-1;iBall>=0;--iBall)
    {
	gr2Circles[iBall]->Draw("PTRI:SAME");
    }
    gr2AxisLine->Draw("PLine:SAME");
    c1->SetName("data3D");
    c1->SaveAs(Form("%s_data_3d.root",inFileName.Data()));

    delete c1;
}
//______________________
void write_graphs(TString dirName,UInt_t nBalls,Bool_t axisFitGraphs)
{
    outFile->cd();
    if(axisFitGraphs && axisFitExists)
    {
        grY0X0->Write();
        grZ0X0->Write();
        grDY0X0->Write();
        grDZ0X0->Write();
        fY0X0->Write();
        fZ0X0->Write();
        gr2AxisLine->Write();
    }

    TDirectory* dir = (TDirectory*) outFile->mkdir(dirName.Data());
    dir->cd();

    for(UInt_t iBall=0;iBall<nBalls;iBall++)
    {
	grDR[iBall]->Write();
	grDTheta[iBall]->Write();
	grDX[iBall]->Write();
	gr2Circles[iBall]->Write();
    }
}