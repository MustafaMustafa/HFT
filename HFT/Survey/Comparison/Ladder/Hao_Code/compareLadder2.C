#include <iostream>
#include <string>
#include "Tps.h"
using namespace std;

const int nMaxMeasurements = 10000;
double xMeasurement[nMaxMeasurements];                                                     
double yMeasurement[nMaxMeasurements];                                                     
double zMeasurement[nMaxMeasurements];

Tps* tps[10];

void compareLadder2()
{
  gSystem->Load("Tps.C");
  ifstream ifs("ladder_8chips.txt");
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

  double xVision1[10][132];
  double yVision1[10][132];
  double zVision1[10][132];
  double xStylus1[10][132];
  double yStylus1[10][132];
  double zStylus1[10][132];

  for(int i=0; i<5; i++)
    for(int j=0; j<132; j++)
      {
	xVision1[i][j] = xMeasurement[i*132*2+j]+i*26;
	yVision1[i][j] = yMeasurement[i*132*2+j];
	zVision1[i][j] = zMeasurement[i*132*2+j];
	xStylus1[i][j] = xMeasurement[i*132*2+132+j]+i*26;
	yStylus1[i][j] = yMeasurement[i*132*2+132+j];
	zStylus1[i][j] = zMeasurement[i*132*2+132+j];
      }

  ifs.close();
  ifs.open("ladder_08_28.txt");
  nMeasurements = 0;

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


  double xVision2[10][132];
  double yVision2[10][132];
  double zVision2[10][132];
  double xStylus2[10][132];
  double yStylus2[10][132];
  double zStylus2[10][132];

  for(int i=0; i<5; i++)
    for(int j=0; j<132; j++)
      {
	xVision2[i][j] = xMeasurement[i*132*2+j]+i*26;
	yVision2[i][j] = yMeasurement[i*132*2+j];
	zVision2[i][j] = zMeasurement[i*132*2+j];
	xStylus2[i][j] = xMeasurement[i*132*2+132+j]+i*26;
	yStylus2[i][j] = yMeasurement[i*132*2+132+j];
	zStylus2[i][j] = zMeasurement[i*132*2+132+j];
      }
  
  cout<<xVision1[3][0]<<endl;
  cout<<xVision2[3][0]<<endl;
  cout<<xVision2[2][131]<<endl;
  cout<<xMeasurement[3*132*2+132]<<", "<<yMeasurement[3*132*2+132]<<endl;

  TCanvas* c1 = new TCanvas("can", "can", 1000, 300);
  c1->SetRightMargin(0.14);

  TGraph2D* grZDiff = new TGraph2D(660, xStylus2[0], yStylus2[0], zStylus2[0]);
  grZDiff->SetMarkerStyle(20);
  grZDiff->Draw("pcol");
  //  return;

  for(int i=0; i<5; i++)
    {
      tps[i] = new Tps();
      tps[i]->Fit(132, xVision1[i], yVision1[i], zVision1[i], 0);
    }

  double zDiff[10][132];
  TH1D* hDiff = new TH1D("hDiff", "hDiff", 200, -0.02, 0.02);
  double zDiffFit[10][132];
  TH1D* hDiffFit = new TH1D("hDiffFit", "hDiffFit", 200, -0.02, 0.02);
  double yDiff[10][132];
  for(int i=0; i<5; i++)
    for(int j=0; j<132; j++)
      {
	if(fabs(xVision2[i][j] - xVision1[i][j]) > 0.005) 
	  cout<<"large x difference: "<<xVision2[i][j] - xVision1[i][j]<<endl;
	if(fabs(yVision2[i][j] - yVision1[i][j]) > 0.005) 
	  cout<<"large y difference: "<<yVision2[i][j] - yVision1[i][j]<<endl;
	zDiff[i][j] = zVision2[i][j] - zVision1[i][j];
	yDiff[i][j] = yVision2[i][j] - yVision1[i][j];
	zDiffFit[i][j] = tps[i]->Z(xVision1[i][j], yVision1[i][j]) - zVision2[i][j];
	hDiff->Fill(zDiff[i][j]);
	hDiffFit->Fill(zDiffFit[i][j]);
      }
  TGraph2D* grZDiff = new TGraph2D(660, xStylus2[0], yStylus2[0], zDiff[0]);
  grZDiff->SetTitle("zDiff");
  grZDiff->SetMarkerStyle(20);
  grZDiff->Draw("pcol");
  //  c1->SaveAs("stylusZDiff.gif");
  //  return;

  TGraph2D* grZDiffFit = new TGraph2D(132, xVision1[0], yVision1[0], zDiffFit[0]);
  grZDiffFit->SetTitle("zDiffFit");
  grZDiffFit->SetMarkerStyle(20);
  grZDiffFit->Draw("pcol");
  return;

  TGraph2D* grYDiff = new TGraph2D(660, xVision1[0], yVision1[0], yDiff[0]);
  grYDiff->SetTitle("yDiff");
  grYDiff->SetMarkerStyle(20);
  grYDiff->Draw("pcol");

  TGraph* grYZDiff = new TGraph(132, zDiff[0], yDiff[0]);
  grYZDiff->SetMarkerStyle(20);
  grYZDiff->Draw("Ap");
  //  return;

  hDiff->Draw();
  hDiff->SetTitle("ladderZDiff1D");
  hDiff->Fit("gaus", "l");
  //  c1->SaveAs("ladderZDiff1D.gif");

  hDiffFit->Draw();
  hDiffFit->SetTitle("ladderZDiff1D");
  hDiffFit->Fit("gaus", "l");

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

}


