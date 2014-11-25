float x[7];
float y[7];
float z[7];

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
      chi2 += (xyz-xyzOnCircle).Mag2();
    }
  f = chi2;
}

void ballPartNotOnRotary()
{
  ifstream ifs("ballPartNotOnRotary.txt");
  float x[7];
  float y[7];
  float z[7];
  float r[7];
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

  float p0 = plane->GetParameter(0);
  float p1 = plane->GetParameter(1);
  float p2 = plane->GetParameter(2);
  float y_[7];
  float z_[7];
  TGraph* grXDiffY = new TGraph();
  TGraph* grZY_ = new TGraph();
  for(int i=0; i<7; i++)
    {
      grXDiffY->SetPoint(i, y[i], x[i]-p0-p1*y[i]-p2*z[i]);
      y_[i] = (y[i]+p1*p0+p1*p2*z[i]-p2*p2*y[i]-x[i]*p1)/(1-p1*p1-p2*p2);
      z_[i] = (z[i]+p2*p0+p1*p2*y[i]-p1*p1*z[i]-x[i]*p2)/(1-p1*p1-p2*p2);
      grZY_->SetPoint(i, y_[i], z_[i]);
    }
  grXDiffY->SetMarkerStyle(20);
  grXDiffY->Draw("ap");
  c1->SaveAs("dX.gif");

  grZY_->SetMarkerStyle(20);
  grZY_->Draw("ap");

  //2D circle fit
  TF1* circle = new TF1("circle", "[1]+sqrt([2]*[2]-(x-[0])*(x-[0]))");
  circle->SetParameters(38, 0, 38);
  grZY_->Fit(circle);

  float x0 = p0;
  float y0 = circle->GetParameter(0);
  float z0 = circle->GetParameter(1);
  float R = circle->GetParameter(2);
  cout<<y0<<" "<<z0<<" "<<R<<endl;
  float axisRx = R;
  float axisRy = 0;
  float axisRz = 0;

  //draw some 2D circle fit results
  float dR[7];
  float dTheta[7];
  TGraph* grDR = new TGraph();
  TGraph* grDTheta = new TGraph();
  for(int i=0; i<7; i++)
    {
      float theta = atan2(z_[i]-z0, y_[i]-y0);
      dTheta[i] = theta + TMath::Pi()*(i/6.-1);
      dR[i] = sqrt(pow(z_[i]-z0,2)+pow(y_[i]-y0,2)) - R;
      grDR->SetPoint(i, theta, dR[i]);
      grDTheta->SetPoint(i, theta, dTheta[i]);
    }
  grDR->SetMarkerStyle(20);
  grDR->Draw("ap");
  c1->SaveAs("dR_2DcircleFit.gif");
  //  return;

  grDTheta->SetMarkerStyle(20);
  grDTheta->Draw("ap");
  c1->SaveAs("dTheta_2DcircleFit.gif");

  //3D circle TMinuitFit
  Double_t arglist[10];
  int ierflag = 0;
  TMinuit *gMinuit = new TMinuit(2);
  gMinuit->SetMaxIterations(50000);
  gMinuit->SetFCN(fcn);
  gMinuit->mnparm(0,"x0", x0, 0.0001, x0-10, x0+10, ierflag);
  gMinuit->mnparm(1,"y0", y0, 0.0001, y0-10, y0+10, ierflag);
  gMinuit->mnparm(2,"z0", z0, 0.0001, z0-10, z0+10, ierflag);
  gMinuit->mnparm(3,"axisRx", R, 0.0001, R-10, R+10, ierflag);
  gMinuit->mnparm(4,"axisRy", 0, 0.0001, -10, 10, ierflag);
  gMinuit->mnparm(5,"axisRz", 0, 0.0001, -10, 10, ierflag);

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

  grDR = new TGraph();
  grDTheta = new TGraph();
  
  for(int i=0; i<7; i++)
    {
      TVector3 xyz(x[i],y[i],z[i]);
      TVector3 tempVec = (xyz-xyz0).Unit().Cross(axisR);
      TVector3 xyzOnCircle = axis.Cross(tempVec);
      xyzOnCircle += xyz0;
      float theta = atan2(z_[i]-z0, y_[i]-y0);
      dTheta[i] = theta + TMath::Pi()*(i/6.-1);
      dR[i] = (xyz-xyzOnCircle).Dot(xyzOnCircle.Unit());
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
