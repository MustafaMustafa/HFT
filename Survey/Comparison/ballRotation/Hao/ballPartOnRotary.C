void ballPartOnRotary()
{
  ifstream ifs("ballPartOnRotary.txt");
  float x[7];
  float y[7];
  float z[7];
  float r[7];
  string tempstring;
  TNtuple* ntp = new TNtuple("ball", "ball", "x:y:z:r:theta");
  for(int i=0; i<7; i++)
    {
      ifs>>tempstring>>tempstring>>x[i]>>y[i]>>z[i]>>r[i];
      float theta = i*TMath::Pi()/6;
      ntp->Fill(x[i], y[i], z[i], r[i], theta);
    }
  ntp->SetMarkerStyle(20);
  ntp->Draw("x");
  c1->SaveAs("xBallPartOnRotary.gif");
  ntp->Draw("y");
  c1->SaveAs("yBallPartOnRotary.gif");
  ntp->Draw("z");
  c1->SaveAs("zBallPartOnRotary.gif");
  ntp->Draw("r");
  c1->SaveAs("rBallPartOnRotary.gif");
  
  ntp->Draw("x:theta");
  c1->SaveAs("xThetaBallPartOnRotary.gif");
  ntp->Draw("y:theta");
  c1->SaveAs("yThetaBallPartOnRotary.gif");
  ntp->Draw("z:theta");
  c1->SaveAs("zThetaBallPartOnRotary.gif");
  
}
