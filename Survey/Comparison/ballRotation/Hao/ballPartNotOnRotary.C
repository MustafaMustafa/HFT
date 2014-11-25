double x[7];
double y[7];
double z[7];

void fcn (int &npar, double *gin, double &f, double *par, int iflag)
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
  for(int i=0; i<7; i++)
    {
      TVector3 xyz(x[i],y[i],z[i]);
      TVector3 tempVec = (xyz-xyz0).Unit().Cross(axisR);
      TVector3 xyzOnCircle = axis.Cross(tempVec);
      xyzOnCircle += xyz0;
      //      cout<<(xyz-xyzOnCircle).Mag()<<endl;
      chi2 += (xyz-xyzOnCircle).Mag2();
    }
  f = chi2;
  cout<<x0<<", "<<y0<<", "<<z0<<", "<<axisRx<<", "<<axisRy<<", "<<axisRz<<"     chi2: "<<chi2<<endl;
}

void ballPartNotOnRotary()
{
  TCanvas* c1 = new TCanvas();

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
  //return;


  double x0 = 0;
  double y0 = 38.11;
  double z0 = -2.08;
  double R = 38.139;
  double axisRx = R;
  double axisRy = 0;
  double axisRz = 0;

  double dR[7];
  double dTheta[7];
  double dX[7];

  //3D circle TMinuitFit
  Double_t arglist[10];
  int ierflag = 0;
  TMinuit *gMinuit = new TMinuit(6);
  gMinuit->SetMaxIterations(50000);
  gMinuit->SetFCN(fcn);
  gMinuit->mnparm(0,"x0", x0, 0.1, x0-5, x0+5, ierflag);
  gMinuit->mnparm(1,"y0", y0, 0.1, y0-5, y0+5, ierflag);
  gMinuit->mnparm(2,"z0", z0, 0.1, z0-5, z0+5, ierflag);
  gMinuit->mnparm(3,"axisRx", R, 0.1, R-5, R+5, ierflag);
  gMinuit->mnparm(4,"axisRy", 0., 0.01, -1, 1, ierflag);
  gMinuit->mnparm(5,"axisRz", 0., 0.01, -1, 1, ierflag);

  arglist[0] = 1;
  gMinuit->mnexcm("SET PRINT", arglist, 1, ierflag);

  arglist[0] = 1000;
  gMinuit->mnexcm("HESSE", arglist, 1, ierflag);


  arglist[0] = 5000;
  arglist[1] = 0.0001;
  gMinuit->mnexcm("MIGRAD", arglist, 2, ierflag);

  Double_t amin, edm, errdef;
  int nvpar, nparx, icstat;
  Double_t x0Error, y0Error, z0Error, axisRxError, axisRyError, axisRzError;
  gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
  gMinuit->GetParameter(0, x0, x0Error);
  gMinuit->GetParameter(1, y0, y0Error);
  gMinuit->GetParameter(2, z0, z0Error);
  gMinuit->GetParameter(3, axisRx, axisRxError);
  gMinuit->GetParameter(4, axisRy, axisRyError);
  gMinuit->GetParameter(5, axisRz, axisRzError);

  TVector3 xyz0(x0, y0, z0);
  TVector3 axisR(axisRx, axisRy, axisRz);
  TVector3 axis = axisR.Unit();
  R = axisR.Mag();
  TVector3 xyz1(x[0],y[0],z[0]);
  TVector3 zeroDegree = axis.Cross((xyz1-xyz0).Cross(axis));

  TGraph* grDR = new TGraph();
  TGraph* grDTheta = new TGraph();
  TGraph* grDX = new TGraph();

  for(int i=0; i<7; i++)
    {
      TVector3 xyz(x[i],y[i],z[i]);
      TVector3 tempVec = (xyz-xyz0).Unit().Cross(axisR);
      TVector3 xyzOnCircle = axis.Cross(tempVec);
      double theta = xyzOnCircle.Angle(zeroDegree);
      xyzOnCircle += xyz0;
      dTheta[i] = theta - TMath::Pi()*(i/6.);
      dR[i] = (xyz-xyzOnCircle).Dot((xyzOnCircle-xyz0).Unit());
      dX[i] = (xyz-xyzOnCircle).Dot(axis);
      grDR->SetPoint(i, TMath::Pi()*(i/6.), dR[i]);
      grDTheta->SetPoint(i, TMath::Pi()*(i/6.), dTheta[i]);
      grDX->SetPoint(i, TMath::Pi()*(i/6.), dX[i]);
    }
  grDR->SetMarkerStyle(20);
  grDR->GetYaxis()->SetTitleOffset(1.4);
  grDR->GetXaxis()->SetTitle("#theta");
  grDR->GetYaxis()->SetTitle("#DeltaR");
  grDR->Draw("ap");
  c1->SaveAs("dR.gif");
  //  return;

  grDTheta->SetMarkerStyle(20);
  grDTheta->GetYaxis()->SetTitleOffset(1.4);
  grDTheta->GetXaxis()->SetTitle("#theta");
  grDTheta->GetYaxis()->SetTitle("#Delta#theta");
  grDTheta->Draw("ap");
  c1->SaveAs("dTheta.gif");

  grDX->SetMarkerStyle(20);
  grDX->GetYaxis()->SetTitleOffset(1.4);
  grDX->GetXaxis()->SetTitle("#theta");
  grDX->GetYaxis()->SetTitle("#Deltax");
  grDX->Draw("ap");
  c1->SaveAs("dX.gif");

  TFile f("ballPartNotOnRotary.root","RECREATE");
  ntp->Write();
  f.Close();
}
