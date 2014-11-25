#include <iostream>
#include <string>
//#include "Tps.h"

class Tps;
using namespace std;

const int nMaxMeasurements = 10000;
double xMeasurement[nMaxMeasurements];
double yMeasurement[nMaxMeasurements];
double zMeasurement[nMaxMeasurements];

Tps* tps[10];

void compareLadder(char* input = "ladder_08_28.txt")
//void compareLadder(char* input = "ladder_8chips.txt")
{
  gSystem->CompileMacro("Tps.C");
  ifstream ifs(input);
  int nMeasurements = 0;
  string line;
  string valueStr;

  while(!ifs.eof())
    {
      getline(ifs,line);
      valueStr = line;
      int found = line.find(" ");
      if(found == string::npos) continue;
      valueStr.replace(found, line.length()-found, "");
      double value = atof(valueStr.data());
      if(value == 0) continue;
      xMeasurement[nMeasurements] = value;
      line.replace(0, found+1, "");

      valueStr = line;
      found = line.find(" ");
      valueStr.replace(found, line.length()-found, "");
      value = atof(valueStr.data());
      yMeasurement[nMeasurements] = value;
      line.replace(0, found+1, "");

      valueStr = line;
      value = atof(valueStr.data());
      zMeasurement[nMeasurements] = value;
      //      cout<<xMeasurement[nMeasurements]<<", "<<yMeasurement[nMeasurements]<<", "<<zMeasurement[nMeasurements]<<endl;

      nMeasurements++;
    }

  cout<<nMeasurements<<endl;

  double xVision[10][132];
  double yVision[10][132];
  double zVision[10][132];
  double xStylus[10][132];
  double yStylus[10][132];
  double zStylus[10][132];

  for(int i=0; i<10; i++)
    for(int j=0; j<132; j++)
      {
	xVision[i][j] = xMeasurement[i*132*2+j]+i*26;
	yVision[i][j] = yMeasurement[i*132*2+j];
	zVision[i][j] = zMeasurement[i*132*2+j];
	xStylus[i][j] = xMeasurement[i*132*2+132+j]+i*26;
	yStylus[i][j] = yMeasurement[i*132*2+132+j];
	zStylus[i][j] = zMeasurement[i*132*2+132+j];
      }

  TCanvas* c1 = new TCanvas("can", "can", 1000, 300);
  c1->SetRightMargin(0.14);

  TGraph2D* grVision = new TGraph2D(1320, xVision[0], yVision[0], zVision[0]);
  //  TGraph2D* grVision = new TGraph2D(660, xVision[0], yVision[0], zVision[0]);
  //  TGraph2D* grVision = new TGraph2D(396, xVision[5], yVision[5], zVision[5]);
  grVision->SetTitle("vision");
  grVision->SetMarkerStyle(20);
  grVision->Draw("pcol");
  //  return;

  TGraph2D* grStylus = new TGraph2D(1320, xStylus[0], yStylus[0], zStylus[0]);
  //  TGraph2D* grStylus = new TGraph2D(660, xStylus[0], yStylus[0], zStylus[0]);
  //  TGraph2D* grStylus = new TGraph2D(396, xStylus[5], yStylus[5], zStylus[5]);
  grStylus->SetTitle("stylus");
  grStylus->SetMarkerStyle(20);
  grStylus->Draw("pcol");

  //  return;

  for(int i=0; i<10; i++)
    {
      tps[i] = new Tps();
      tps[i]->Fit(132, xVision[i], yVision[i], zVision[i], 0);
    }

  double zDiff[10][132];
  TH1D* hDiff = new TH1D("hDiff", "hDiff", 200, -0.02, 0.02);
  double zDiffFit[10][132];
  TH1D* hDiffFit = new TH1D("hDiffFit", "hDiffFit", 200, -0.02, 0.02);
  double yDiff[10][132];
  for(int i=0; i<10; i++)
    for(int j=0; j<132; j++)
      {
	if(fabs(xVision[i][j] - xStylus[i][j]) > 0.005)
	  cout<<"large x difference: "<<xVision[i][j] - xStylus[i][j]<<endl;
	if(fabs(yVision[i][j] - yStylus[i][j]) > 0.005)
	  cout<<"large y difference: "<<yVision[i][j] - yStylus[i][j]<<endl;
	zDiff[i][j] = zVision[i][j] - zStylus[i][j];
	yDiff[i][j] = yVision[i][j] - yStylus[i][j];
	zDiffFit[i][j] = tps[i]->Z(xStylus[i][j], yStylus[i][j]) - zStylus[i][j];
	hDiff->Fill(zDiff[i][j]);
	hDiffFit->Fill(zDiffFit[i][j]);
      }
  TGraph2D* grZDiff = new TGraph2D(1320, xVision[0], yVision[0], zDiff[0]);
  grZDiff->SetTitle("zDiff");
  grZDiff->SetMarkerStyle(20);
  grZDiff->Draw("pcol");
  //  c1->SaveAs("stylusZDiff.gif");
  //  return;

  TGraph2D* grZDiffFit = new TGraph2D(1320, xVision[0], yVision[0], zDiffFit[0]);
  grZDiffFit->SetTitle("zDiffFit");
  grZDiffFit->SetMarkerStyle(20);
  grZDiffFit->Draw("pcol");
  return;

  TGraph2D* grYDiff = new TGraph2D(660, xVision[0], yVision[0], yDiff[0]);
  grYDiff->SetTitle("yDiff");
  grYDiff->SetMarkerStyle(20);
  grYDiff->Draw("pcol");

  TGraph* grYZDiff = new TGraph(132, zDiff[0], yDiff[0]);
  grYZDiff->SetMarkerStyle(20);
  grYZDiff->Draw("Ap");
  return;

  hDiff->Draw();
  hDiff->SetTitle("ladderZDiff1D");
  hDiff->Fit("gaus", "l");
  c1->SaveAs("ladderZDiff1D.gif");
  return;

  TF2* plane = new TF2("plane", "[0]+[1]*x+[2]*y", 0,21,0,23);
  plane->SetTitle("stylusZDiffPlane");
  grZDiff->Fit(plane);
  plane->Draw("cont4z");
  c1->SaveAs("stylusZDiffPlane.gif");

  TH1D* hDiff1 = new TH1D("hDiff1", "hDiff1", 200, -0.01, 0.01);
  for(int i=0; i<132; i++)
    {
      zDiff[i] -= plane->Eval(xMeasurement[i], yMeasurement[i]);
      hDiff1->Fill(zDiff[i]);
    }
  TGraph2D* grZDiff2 = new TGraph2D(132, xMeasurement, yMeasurement, zDiff);
  grZDiff2->SetTitle("stylusZDiffSubtractPlane");
  grZDiff2->Draw("cont4z");
  c1->SaveAs("stylusZDiffSubtractPlane.gif");

  hDiff1->SetTitle("stylusZDiffSubtractPlane1D");
  hDiff1->Draw();
  hDiff1->Fit("gaus", "l");
  c1->SaveAs("stylusZDiffSubtractPlane1D.gif");

  gSystem->CleanCompiledMacros();
}


