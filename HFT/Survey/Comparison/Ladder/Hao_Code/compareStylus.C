#include <iostream>
#include <string>
using namespace std;

const int nMaxMeasurements = 10000;
double xMeasurement[nMaxMeasurements];                                                     
double yMeasurement[nMaxMeasurements];                                                     
double zMeasurement[nMaxMeasurements];

void compareStylus(char* input = "stylus_08_16.txt")
{
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

  TCanvas* c1 = new TCanvas();
  c1->SetRightMargin(0.14);

  //  TGraph2D* grMeasurement = new TGraph2D(nMeasurements, xMeasurement, yMeasurement, zMeasurement);
  TGraph2D* grMeasurement = new TGraph2D(132, xMeasurement, yMeasurement, zMeasurement);
  grMeasurement->SetTitle("stylus");
  grMeasurement->Draw("surf1");
  grMeasurement->Draw("cont4z");
  c1->SaveAs("stylus.gif");
  
  double zDiff[132];
  TH1D* hDiff = new TH1D("hDiff", "hDiff", 200, -0.01, 0.01);
  for(int i=0; i<132; i++)
    {
      if(fabs(xMeasurement[i] - xMeasurement[i+132]) > 0.002) 
	cout<<"large x difference: "<<xMeasurement[i] - xMeasurement[i+132]<<endl;
      if(fabs(yMeasurement[i] - yMeasurement[i+132]) > 0.002) 
	cout<<"large y difference: "<<yMeasurement[i] - yMeasurement[i+132]<<endl;
      zDiff[i] = zMeasurement[i] - zMeasurement[i+132];
      hDiff->Fill(zDiff[i]);
    }
  TGraph2D* grZDiff = new TGraph2D(132, xMeasurement, yMeasurement, zDiff);
  grZDiff->SetTitle("stylusZDiff");
  grZDiff->Draw("cont4z");
  c1->SaveAs("stylusZDiff.gif");

  hDiff->Draw();
  hDiff->SetTitle("stylusZDiff1D");
  hDiff->Fit("gaus", "l");
  c1->SaveAs("stylusZDiff1D.gif");

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


