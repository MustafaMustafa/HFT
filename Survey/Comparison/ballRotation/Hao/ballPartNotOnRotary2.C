double x[7];
double y[7];
double z[7];
double axisX;
double axisY;
double axisZ;
double R;

void fcn (int &npar, double *gin, double &f, double *par, int iflag)
{
  Double_t x0 = par[0];
  Double_t y0 = par[1];
  Double_t z0 = par[2];
  //  Double_t R = par[3];
  Double_t axisRx = R*axisX;
  Double_t axisRy = R*axisY;
  Double_t axisRz = R*axisZ;
  TVector3 xyz0(x0, y0, z0);
  TVector3 axisR(axisRx, axisRy, axisRz);
  TVector3 axis = axisR.Unit();
  Double_t chi2 = 0;
  for(int i=0; i<7; i++)
    {
      TVector3 xyz(x[i],y[i],z[i]);
      TVector3 tempVec = (xyz-xyz0).Unit().Cross(axisR);
      TVector3 xyzOnCircle = axis.Cross(tempVec);
      xyzOnCircle += xyz0;
      cout<<x[i]<<endl;
      chi2 += pow(((xyz-xyzOnCircle).Dot((xyzOnCircle-xyz0).Unit())),2);
    }
  f = chi2;
  cout<<x0<<", "<<y0<<", "<<z0<<"     chi2: "<<chi2<<endl;
}

void ballPartNotOnRotary()
{
  ifstream ifs("ballPartNotOnRotary.txt");
  double r[7];
  string tempstring;
  TNtuple* ntp = new TNtuple("ball", "ball", "x:y:z:r");
  for(int i=0; i<7; i++)
    {
      ifs>>tempstring>>tempstring>>x[i]>>y[i]>>z[i]>>r[i];
      ntp->Fill(x[i], y[i], z[i], r[i]);
    }
  ntp->SetMarkerStyle(20);
  //  ntp->Draw("y:x");
  //  c1->SaveAs("xyBallPartNotOnRotary.gif");
  //  return;
  ntp->Draw("z:y:x");

  TGraph2D* grX = new TGraph2D(7, y, z, x);
  grX->SetMarkerStyle(20);

  grX->Draw("colz");
  TF2* plane = new TF2("plane", "[0]+[1]*x+[2]*y", 0,21,0,23);
  grX->Fit(plane);
  plane->Draw("colz");

  double p0 = plane->GetParameter(0);
  double p1 = plane->GetParameter(1);
  double p2 = plane->GetParameter(2);

  axisX = 1./sqrt(1+p1*p1+p2*p2);
  axisY = p1/sqrt(1+p1*p1+p2*p2);
  axisZ = p2/sqrt(1+p1*p1+p2*p2);

  double x0 = 0;
  double y0 = 38.11;
  double z0 = -2.08;
  R = 38.139;

  double dR[7];
  double dTheta[7];

  
  //3D circle TMinuitFit
  Double_t arglist[10];
  int ierflag = 0;
  TMinuit *gMinuit = new TMinuit(2);
  gMinuit->SetMaxIterations(50000);
  gMinuit->SetFCN(fcn);
  gMinuit->mnparm(0,"x0", x0, 0.001, x0-5, x0+5, ierflag);
  gMinuit->mnparm(1,"y0", y0, 0.001, y0-5, y0+5, ierflag);
  gMinuit->mnparm(2,"z0", z0, 0.001, z0-5, z0+5, ierflag);
  //  gMinuit->mnparm(3,"R", R, 0.1, R-5, R+5, ierflag);

  arglist[0] = 1;
  gMinuit->mnexcm("SET PRINT", arglist, 1, ierflag);
  
  arglist[0] = 1000;
  gMinuit->mnexcm("HESSE", arglist, 1, ierflag);
  

  arglist[0] = 5000;
  arglist[1] = 0.0001;
  gMinuit->mnexcm("MIGRAD", arglist, 2, ierflag);
  
  Double_t amin, edm, errdef;  
  int nvpar, nparx, icstat;
  Double_t x0Error, y0Error, z0Error, RError;
  gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat); 
  gMinuit->GetParameter(0, x0, x0Error);
  gMinuit->GetParameter(1, y0, y0Error);
  gMinuit->GetParameter(2, z0, z0Error);
  //  gMinuit->GetParameter(3, R, RError);


  Double_t axisRx = R*axisX;
  Double_t axisRy = R*axisY;
  Double_t axisRz = R*axisZ;
  TVector3 xyz0(x0, y0, z0);
  TVector3 axisR(axisRx, axisRy, axisRz);
  TVector3 axis = axisR.Unit();
  R = axisR.Mag();

  TGraph* grDR = new TGraph();
  TGraph* grDTheta = new TGraph();
  
  for(int i=0; i<7; i++)
    {
      TVector3 xyz(x[i],y[i],z[i]);
      TVector3 tempVec = (xyz-xyz0).Unit().Cross(axisR);
      TVector3 xyzOnCircle = axis.Cross(tempVec);
      xyzOnCircle += xyz0;
      double theta = atan2(z[i]-z0, y[i]-y0);
      dTheta[i] = theta + TMath::Pi()*(i/6.-1);
      dR[i] = (xyz-xyzOnCircle).Dot((xyzOnCircle-xyz0).Unit());
      grDR->SetPoint(i, theta, dR[i]);
      grDTheta->SetPoint(i, theta, dTheta[i]);
    }
  grDR->SetMarkerStyle(20);
  grDR->Draw("ap");
  c1->SaveAs("dR.gif");
  return;

  grDTheta->SetMarkerStyle(20);
  grDTheta->Draw("ap");

  return;
  c1->SaveAs("xyzBallPartOnRotary.gif");
  ntp->Draw("z");
  c1->SaveAs("zBallPartOnRotary.gif");
  ntp->Draw("r");
  c1->SaveAs("rBallPartOnRotary.gif");
  
}
