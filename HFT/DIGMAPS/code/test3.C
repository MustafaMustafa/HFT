//_______________________________________________________________________________________
//
Double_t SumGausLorentz1D(Double_t *x, Double_t *par){

  //par[0] Norm_g
  //par[1] x0_g
  //par[2] sigma_g
  // par[3] = Gamma_lor
  // par[4] = x0_lor
  // par[5] = norm_lor



  /*   for (int j=0;j<10; j++) {
       cout<<"par " <<j<<" "<<par[j]<<endl;
       }
  */
  Double_t Pi = 3.141592653;
  if((par[2]!=0.0) ){
    Double_t rx = (x[0]-par[1])/par[2];
    Double_t tempoutput;
    tempoutput= par[0]*( TMath::Exp(-(rx*rx)/2.0)
		    +par[5]*par[3]/Pi/ ((x[0]-par[4])*(x[0]-par[4]) +par[3]*par[3])
    		    );
    //  cout<<"SumGausLorentz1D " <<tempoutput<<endl;
    return tempoutput;
   
  }else{
    return 0;
  }
}
void test3()
{

  TF1 *mymodel1D_1st=0;
  TF1 *mymodel1D_2nd=0;
  Double_t Norm_g_1st     =  0.458955;
  Double_t x0_g_1st       = -3.98149 ;
  Double_t sigma_g_1st    = 13.1559     ;    
  Double_t Gamma_lor_1st  = 3.98673  ;
  Double_t x0_lor_1st     = 1.79712  ;
  Double_t norm_lor_1st   = 6.4533	  ;
  Double_t Norm_g_2nd     = 0.116703 ;
  Double_t x0_g_2nd       = -1.0688  ;
  Double_t sigma_g_2nd    = 17.4823     ;    
  Double_t Gamma_lor_2nd  = 47.0837  ;
  Double_t x0_lor_2nd     = -4.63879 ;
  Double_t norm_lor_2nd   = 3.71411  ;
 
  Float_t pitchX =   20.7;
 

  mymodel1D_1st = new TF1("namemodel1D_1st",SumGausLorentz1D,0,sqrt(2)*pitchX,6);
  // mymodel1D_1st = new TF1("namemodel1D_1st",SumGausLorentz1D,0,1.41*pitchX,6);
  mymodel1D_2nd = new TF1("namemodel1D_2nd",SumGausLorentz1D,pitchX,sqrt(2)*3.0*pitchX,6);
  mymodel1D_1st->SetParNames("Norm_g","x0_g","sigma_g","Gamma_lor","x0_lor","norm_lor");
  mymodel1D_2nd->SetParNames("Norm_g","x0_g","sigma_g","Gamma_lor","x0_lor","norm_lor");
  Double_t params1[] = {Norm_g_1st,x0_g_1st,sigma_g_1st, Gamma_lor_1st,x0_lor_1st,norm_lor_1st};
  Double_t params2[] = {Norm_g_2nd,x0_g_2nd,sigma_g_2nd, Gamma_lor_2nd,x0_lor_2nd,norm_lor_2nd};
  mymodel1D_1st->SetParameters(params1);
  mymodel1D_2nd->SetParameters(params2);
 
  // mymodel1D_1st->SetAxisRange(0,80,"X");





TH2F *hFrame = new TH2F("hFrame","Probability density functions",100,0,87.82,100,0,0.8);
hFrame->SetStats(0000000);
hFrame->SetXTitle("Distance (#mum)");
hFrame->SetYTitle("Probability (#mum)");
hFrame->Draw();

hFrame->GetXaxis()->SetLabelOffset(0.011);
  hFrame->GetYaxis()->SetLabelOffset(0.011);
  hFrame->GetYaxis()->SetLabelSize(0.04);


  // Float_t rightmax = 3.5;
  // Float_t rightmin = 1.0;
  // TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),gPad->GetUxmax(), gPad->GetUymax(),rightmin,rightmax,510,"+LU");
  // // axis->SetLineColor(kRed);
  // // axis->SetLabelColor(kRed);
  // axis->Draw();
  // TGaxis *axisx = new TGaxis(gPad->GetUxmin(),gPad->GetUymax(),gPad->GetUxmax(), gPad->GetUymax(),rightmin,rightmax,510,"-U");
  // axisx->Draw();







  mymodel1D_1st->Draw("same");
  mymodel1D_1st->SetLineColor(2);
  mymodel1D_2nd->Draw("same");



}
