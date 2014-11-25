{
  myDIGMAPS2.PrintConfigurations() ;
  Bool_t boolprint=true;
  //gROOT->ForceStyle();

  //-------------------------------------------------------------------

  Char_t  ResultFileName[250];     
  //sprintf(ResultFileName,"/rawcmos7/abesson/TAF/trunk/results_ana_M28/run28581Pl3_ClCharge.root");
  // /rawcmos7/abesson/TAF/trunk2/trunk/results_ana_M28
  //TFile* ffile =new TFile(ResultFileName,"read");
  //TH1F *hnpix_c;
  //ffile->GetObject("npix_c",hnpix_c);
  const Int_t Nruns = 9;
  TPaveStats *statdigit1_1[Nruns];
  TPaveStats *statdigit1_2[Nruns];
  TPaveStats *statdigit1_3[Nruns];
  TPaveStats *statdigit1_4[Nruns];
  //  TPaveStats *statdigit2_1[Nruns];
  //  TPaveStats *statdigit2_2[Nruns];
  //  TPaveStats *statdigit2_3[Nruns];
  //  TPaveStats *statdigit2_4[Nruns];
  TPaveStats *statdata1_1[Nruns];

  Float_t Resolution_digit1[Nruns];
  Float_t Err_Resolution_digit1[Nruns];
  Float_t Resolution_digit2[Nruns];
  Float_t Err_Resolution_digit2[Nruns];
  Float_t Resolution_digit3[Nruns];
  Float_t Err_Resolution_digit3[Nruns];
  Float_t Resolution_digit4[Nruns];
  Float_t Err_Resolution_digit4[Nruns];

  Float_t Efficiency_digit1[Nruns];
  Float_t Err_Efficiency_digit1[Nruns];
  Float_t Efficiency_digit2[Nruns];
  Float_t Err_Efficiency_digit2[Nruns];
  Float_t Efficiency_digit3[Nruns];
  Float_t Err_Efficiency_digit3[Nruns];
  Float_t Efficiency_digit4[Nruns];
  Float_t Err_Efficiency_digit4[Nruns];

  Float_t Multiplicity_digit1[Nruns];
  Float_t Err_Multiplicity_digit1[Nruns];
  Float_t Multiplicity_digit2[Nruns];
  Float_t Err_Multiplicity_digit2[Nruns];
  Float_t Multiplicity_digit3[Nruns];
  Float_t Err_Multiplicity_digit3[Nruns];
  Float_t Multiplicity_digit4[Nruns];
  Float_t Err_Multiplicity_digit4[Nruns];



  Int_t RunNumber[Nruns] = {28581,28580,28579,28568,28570,28606,28567,28569,28571};//  {28567,28568,28569,28570,28571,28579,28580,28581,28606};
  Float_t Threshold[Nruns] = {4.0,4.5,5.0,5.8,7.0,8.0,9.0,10.2,11.5};//  {9.0,5.8,10.2,7.0,11.5,5.0,4.5,4.0,8.0};
  Float_t ThresholdErr[Nruns] = {0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  Int_t Plane[Nruns] = {3,3,3,3,3,3,3,3,3};

  TLegend* leg1[Nruns];
  TLegend* leg2[Nruns];
  TLegend* leg3[3];

  //hnpix_c->Draw();

  //  statdigit1_1[0] = (TPaveStats*)gPad->GetPrimitive("stats");
  //statdigit1_1[0]->SetName("digitiser");

  //-------------------------------------------------------------------
  /*  gStyle->SetOptStat("nemr");
  gStyle->SetFillStyle(0);
  gStyle->SetFillColor(1);
  gStyle->SetMarkerColor(1);
  gStyle->SetMarkerStyle(1);
  gStyle->SetMarkerSize(1);
  gStyle->SetLineColor(1);
  gStyle->SetLineStyle(1);
  gStyle->SetLineWidth(1);*/
  //MainCanvas1->UseCurrentStyle();

  const int Nconfig = 9;
  Int_t configlist[Nconfig] = {2,5,8,11,14,17,20,23,26};
  myDIGMAPS2.PlotDigitalConfiguration(1,configlist,Nconfig);
  gPad->Update();
  MainCanvas1->Update();

  Int_t plotstat = 1;
  if(plotstat!=0){
    for (Int_t i=0 ; i<Nruns ; i++){
      MainCanvas1->cd(i+1);
      TPad *subpad = gPad;
      //gPad->ls();
      statdigit1_1[i] = (TPaveStats*)subpad->GetPrimitive("stat2");
      if(statdigit1_1[i] == NULL){
	statdigit1_1[i] = (TPaveStats*)subpad->GetPrimitive("digitiser");
      }else{
	statdigit1_1[i]->SetName("digitiser1");
      } 
      statdigit1_1[i]->SetX1NDC(0.6);
      statdigit1_1[i]->SetY1NDC(0.20);
      statdigit1_1[i]->SetX2NDC(0.95);
      statdigit1_1[i]->SetY2NDC(0.34);
      statdigit1_1[i]->SetLineColor(1);
      statdigit1_1[i]->SetTextColor(1);
      statdigit1_1[i]->Draw();
      
      Char_t histoname[300];
      sprintf(histoname,"multiplicity_with_threshold_01_conf%d",configlist[i]);
      TH1F* htmp1 = 0;
      htmp1 = (TH1F*)gPad->GetPrimitive(histoname);
      Multiplicity_digit1[i] = htmp1->GetMean()-0.5;
      Err_Multiplicity_digit1[i] = htmp1->GetMeanError();
      leg1[i] = new TLegend(0.30,0.40,0.55,0.70);
      leg1[i]->SetTextSize(0.03);
      Char_t  legendsub1[150]; 
      sprintf(legendsub1,"epi = 8 um");
      leg1[i]->AddEntry(htmp1,legendsub1,"l");
      leg1[i]->SetFillStyle(0);


      MainCanvas2->cd(i+1);
      Char_t histoname2[300];
      sprintf(histoname2,"Ar_h1_ADC_LSB_conf%d",configlist[i]);
      TH1F* htmp2 = 0;
      htmp2 = (TH1F*)gPad->GetPrimitive(histoname2);
      Float_t Nevent = float(htmp2->GetEntries());

      MainCanvas3->cd(i+1);
      Char_t histoname3[300];
      sprintf(histoname3,"Ar_h1_Efficiency_ideal_conf%d",configlist[i]);
      TH1F* htmp3 = 0;
      htmp3 = (TH1F*)gPad->GetPrimitive(histoname3);
      Efficiency_digit1[i] = htmp3->GetMean();
      if(Nevent!=0.0){
	Err_Efficiency_digit1[i] = TMath::Sqrt(Efficiency_digit1[i] * (1.0-Efficiency_digit1[i]) / Nevent );
      }
   
      MainCanvas4->cd(i+1);
      Char_t histoname4[300];
      sprintf(histoname4,"Ar_h1_Resolution_ResidualX_CoG_true_conf%d",configlist[i]);
      TH1F* htmp4 = 0;
      htmp4 = (TH1F*)gPad->GetPrimitive(histoname4);
      TF1 *fitg =htmp4->GetFunction("gaus");
      fitg->SetName("gaus2");
      Resolution_digit1[i]=fitg->GetParameter(2) ;
      Err_Resolution_digit1[i]=fitg->GetParError(2);
      // cout<<" TEST SIGMA "<<Resolution_digit1[i]<<"+-"<<Err_Resolution_digit1[i]<<endl;
    }
  }



  //-------------------------------------------------------------------

  //MainCanvas1->UseCurrentStyle();

  const int Nconfig2 = 9;
  Int_t configlist2[Nconfig2] = {29,32,35,38,41,44,47,50,53}; //11  
  myDIGMAPS2.PlotDigitalConfiguration(0,configlist2,Nconfig2);
  gPad->Update();
  MainCanvas1->Update();
  if(plotstat!=0){
    for (Int_t i=0 ; i<Nruns ; i++){
      MainCanvas1->cd(i+1);
      //    TPad *subpad = (TPad*)gPad->GetPad(i+1)
      gPad->Update();
      MainCanvas1->Update();
      TPad *subpad = gPad;
      //gPad->ls();
      statdigit1_2[i] = (TPaveStats*)subpad->GetPrimitive("stat2");
      //statdigit1_2[i] = (TPaveStats*)hnpix_c->GetListOfFunctions()->FindObject("stats");
      if(statdigit1_2[i] == NULL){
	statdigit1_2[i] = (TPaveStats*)subpad->GetPrimitive("digitiser2");
      }else{
	statdigit1_2[i]->SetName("digitiser2");
      } 
      statdigit1_2[i]->SetX1NDC(0.6);
      statdigit1_2[i]->SetY1NDC(0.35);
      statdigit1_2[i]->SetX2NDC(0.95);
      statdigit1_2[i]->SetY2NDC(0.49);
      statdigit1_2[i]->SetLineColor(3); 
      statdigit1_2[i]->SetTextColor(3);
      statdigit1_2[i]->Draw();

      Char_t histoname[300];
      sprintf(histoname,"multiplicity_with_threshold_01_conf%d",configlist2[i]);
      TH1F* htmp1 = 0;
      htmp1 = (TH1F*)gPad->GetPrimitive(histoname);
      Multiplicity_digit2[i] = htmp1->GetMean()-0.5;
      Err_Multiplicity_digit2[i] = htmp1->GetMeanError();

      leg1[i]->SetTextSize(0.03);
      Char_t  legendsub1[150]; 
      sprintf(legendsub1,"epi = 9 um");
      leg1[i]->AddEntry(htmp1,legendsub1,"l");
      leg1[i]->SetFillStyle(0);

      MainCanvas2->cd(i+1);
      Char_t histoname2[300];
      sprintf(histoname2,"Ar_h1_ADC_LSB_conf%d",configlist2[i]);
      TH1F* htmp2 = 0;
      htmp2 = (TH1F*)gPad->GetPrimitive(histoname2);
      Float_t Nevent = float(htmp2->GetEntries());

      MainCanvas3->cd(i+1);
      Char_t histoname3[300];
      sprintf(histoname3,"Ar_h1_Efficiency_ideal_conf%d",configlist2[i]);
      TH1F* htmp3 = 0;
      htmp3 = (TH1F*)gPad->GetPrimitive(histoname3);
      Efficiency_digit2[i] = htmp3->GetMean();
      if(Nevent!=0.0){
	Err_Efficiency_digit2[i] = TMath::Sqrt(Efficiency_digit2[i] * (1.0-Efficiency_digit2[i]) / Nevent );
      }
 
      MainCanvas4->cd(i+1);
      Char_t histoname4[300];
      sprintf(histoname4,"Ar_h1_Resolution_ResidualX_CoG_true_conf%d",configlist2[i]);
      TH1F* htmp4 = 0;
      htmp4 = (TH1F*)gPad->GetPrimitive(histoname4);
      TF1 *fitg =htmp4->GetFunction("gaus");
      fitg->SetName("gaus2");
      Resolution_digit2[i]=fitg->GetParameter(2) ;
      Err_Resolution_digit2[i]=fitg->GetParError(2);

    }
  
  
  }

  //-------------------------------------------------------------------

  const int Nconfig3 = 9;
  Int_t configlist3[Nconfig3] = {56,59,62,65,68,71,74,77,80}; //11
  myDIGMAPS2.PlotDigitalConfiguration(0,configlist3,Nconfig3);
  gPad->Update();
  MainCanvas1->Update();
  if(plotstat!=0){
  for (Int_t i=0 ; i<Nruns ; i++){
    MainCanvas1->cd(i+1);
    //    TPad *subpad = (TPad*)gPad->GetPad(i+1)
    gPad->Update();
    MainCanvas1->Update();
    TPad *subpad = gPad;
    //gPad->ls();
    statdigit1_3[i] = (TPaveStats*)subpad->GetPrimitive("stat2");
    if(statdigit1_3[i] == NULL){
      statdigit1_3[i] = (TPaveStats*)subpad->GetPrimitive("digitiser3");
    }else{
      statdigit1_3[i]->SetName("digitiser3");
    } 
    statdigit1_3[i]->SetX1NDC(0.6);
    statdigit1_3[i]->SetY1NDC(0.50);
    statdigit1_3[i]->SetX2NDC(0.95);
    statdigit1_3[i]->SetY2NDC(0.64);
    statdigit1_3[i]->SetLineColor(4); 
    statdigit1_3[i]->SetTextColor(4);
    statdigit1_3[i]->Draw();

    Char_t histoname[300];
    sprintf(histoname,"multiplicity_with_threshold_01_conf%d",configlist3[i]);
    TH1F* htmp1 = 0;
    htmp1 = (TH1F*)gPad->GetPrimitive(histoname);
    Multiplicity_digit3[i] = htmp1->GetMean()-0.5;
    Err_Multiplicity_digit3[i] = htmp1->GetMeanError();

      leg1[i]->SetTextSize(0.03);
      Char_t  legendsub1[150]; 
      sprintf(legendsub1,"epi = 10 um");
      leg1[i]->AddEntry(htmp1,legendsub1,"l");
      leg1[i]->SetFillStyle(0);

    MainCanvas2->cd(i+1);
    Char_t histoname2[300];
    sprintf(histoname2,"Ar_h1_ADC_LSB_conf%d",configlist3[i]);
    TH1F* htmp2 = 0;
    htmp2 = (TH1F*)gPad->GetPrimitive(histoname2);
    Float_t Nevent = float(htmp2->GetEntries());

    MainCanvas3->cd(i+1);
    Char_t histoname3[300];
    sprintf(histoname3,"Ar_h1_Efficiency_ideal_conf%d",configlist3[i]);
    TH1F* htmp3 = 0;
    htmp3 = (TH1F*)gPad->GetPrimitive(histoname3);
    Efficiency_digit3[i] = htmp3->GetMean();
    if(Nevent!=0.0){
      Err_Efficiency_digit3[i] = TMath::Sqrt(Efficiency_digit3[i] * (1.0-Efficiency_digit3[i]) / Nevent );
    }

    MainCanvas4->cd(i+1);
    Char_t histoname4[300];
    sprintf(histoname4,"Ar_h1_Resolution_ResidualX_CoG_true_conf%d",configlist3[i]);
    TH1F* htmp4 = 0;
    htmp4 = (TH1F*)gPad->GetPrimitive(histoname4);
    TF1 *fitg =htmp4->GetFunction("gaus");
    fitg->SetName("gaus2");
    Resolution_digit3[i]=fitg->GetParameter(2) ;
    Err_Resolution_digit3[i]=fitg->GetParError(2);

  }
  }

  //-------------------------------------------------------------------
 
 
  //MainCanvas1->UseCurrentStyle();

  const int Nconfig4 = 9;
  Int_t configlist4[Nconfig4] = {83,86,89,92,95,98,101,104,107}; //11
  myDIGMAPS2.PlotDigitalConfiguration(0,configlist4,Nconfig4);
  gPad->Update();
  MainCanvas1->Update();
  if(plotstat!=0){
  for (Int_t i=0 ; i<Nruns ; i++){
    MainCanvas1->cd(i+1);
    //    TPad *subpad = (TPad*)gPad->GetPad(i+1)
    gPad->Update();
    MainCanvas1->Update();
    TPad *subpad = gPad;
    //gPad->ls();
    statdigit1_4[i] = (TPaveStats*)subpad->GetPrimitive("stat2");
    if(statdigit1_4[i] == NULL){
      statdigit1_4[i] = (TPaveStats*)subpad->GetPrimitive("digitiser3");
    }else{
      statdigit1_4[i]->SetName("digitiser3");
    } 
    statdigit1_4[i]->SetX1NDC(0.6);
    statdigit1_4[i]->SetY1NDC(0.65);
    statdigit1_4[i]->SetX2NDC(0.95);
    statdigit1_4[i]->SetY2NDC(0.79);
    statdigit1_4[i]->SetLineColor(6); 
    statdigit1_4[i]->SetTextColor(6);
    statdigit1_4[i]->Draw();

    Char_t histoname[300];
    sprintf(histoname,"multiplicity_with_threshold_01_conf%d",configlist4[i]);
    TH1F* htmp1 = 0;
    htmp1 = (TH1F*)gPad->GetPrimitive(histoname);
    Multiplicity_digit4[i] = htmp1->GetMean()-0.5;
    Err_Multiplicity_digit4[i] = htmp1->GetMeanError();

      leg1[i]->SetTextSize(0.03);
      Char_t  legendsub1[150]; 
      sprintf(legendsub1,"epi = 11 um");
      leg1[i]->AddEntry(htmp1,legendsub1,"l");
      leg1[i]->SetFillStyle(0);

    MainCanvas2->cd(i+1);
    Char_t histoname2[300];
    sprintf(histoname2,"Ar_h1_ADC_LSB_conf%d",configlist4[i]);
    TH1F* htmp2 = 0;
    htmp2 = (TH1F*)gPad->GetPrimitive(histoname2);
    Float_t Nevent = float(htmp2->GetEntries());

    MainCanvas3->cd(i+1);
    Char_t histoname3[300];
    sprintf(histoname3,"Ar_h1_Efficiency_ideal_conf%d",configlist4[i]);
    TH1F* htmp3 = 0;
    htmp3 = (TH1F*)gPad->GetPrimitive(histoname3);
    Efficiency_digit4[i] = htmp3->GetMean();
    if(Nevent!=0.0){
      Err_Efficiency_digit4[i] = TMath::Sqrt(Efficiency_digit4[i] * (1.0-Efficiency_digit4[i]) / Nevent );
    }

    MainCanvas4->cd(i+1);
    Char_t histoname4[300];
    sprintf(histoname4,"Ar_h1_Resolution_ResidualX_CoG_true_conf%d",configlist4[i]);
    TH1F* htmp4 = 0;
    htmp4 = (TH1F*)gPad->GetPrimitive(histoname4);
    TF1 *fitg =htmp4->GetFunction("gaus");
    fitg->SetName("gaus2");
    Resolution_digit4[i]=fitg->GetParameter(2) ;
    Err_Resolution_digit4[i]=fitg->GetParError(2);

  }
  }

  //-------------------------------------------------------------------

  for (Int_t i=0 ; i<Nruns ; i++){


    MainCanvas1->cd(i+1);
    //    TPad *subpad = (TPad*)gPad->GetPad(i+1)
    gPad->Update();
    MainCanvas1->Update();
    TPad *subpad = gPad;

    sprintf(ResultFileName,"/rawcmos7/abesson/TAF/trunk2/trunk/results_ana_M28/run%dPl%d_ClCharge.root",RunNumber[i],Plane[i]);
    TFile* ffile =new TFile(ResultFileName,"read");
    TH1F *hnpix_c;
    ffile->GetObject("npix_c",hnpix_c);    
    
    Float_t integg;
    integg = hnpix_c->Integral();
    if(integg!=0.0){hnpix_c->Scale(1/integg);}
    hnpix_c->SetLineColor(2);
    Float_t hYmax = 0.70;
    
    hnpix_c->SetAxisRange(0,hYmax,"Y");
    hnpix_c->Draw("sames");
    statdata1_1[i] = (TPaveStats*)hnpix_c->GetListOfFunctions()->FindObject("stats");
    statdata1_1[i]->SetName("data");
    statdata1_1[i]->SetLineColor(2);
    statdata1_1[i]->SetTextColor(2);
    statdata1_1[i]->SetX1NDC(0.6);
    statdata1_1[i]->SetY1NDC(0.80);
    statdata1_1[i]->SetX2NDC(0.95);
    statdata1_1[i]->SetY2NDC(0.94);
    statdata1_1[i]->Draw();
    
    TPaveText *text = new TPaveText(1.0,.5,10.,.55);
    Char_t  chartext[400];
    sprintf(chartext,"S/N >= %2.1f",Threshold[i]);
    text->AddText(chartext);
    text->SetFillColor(0);
    text->Draw("same");
    //ffile->Close();

    Char_t  legendsub1[150]; 
    sprintf(legendsub1,"data");

    //leg1->SetHeader("Prototype");
    leg1[i]->AddEntry(hnpix_c,legendsub1,"l");
    leg1[i]->SetFillStyle(0);
    leg1[i]->Draw();



  }


  //-------------------------------------------------------------------
  //canvas
  //-------------------------------------------------------------------
  TCanvas *AddCanvas1;
  AddCanvas1 = new TCanvas("AddCanvas1","AddCanvas1",750,10,1000,950);

  TCanvas *AddCanvas2;
  AddCanvas2 = new TCanvas("AddCanvas2","AddCanvas2",750,10,1000,950);
  TCanvas *AddCanvas3;
  AddCanvas3 = new TCanvas("AddCanvas3","AddCanvas3",750,10,1000,950);


  if(Nruns<=4){
    AddCanvas1->Divide(2,2);
    AddCanvas2->Divide(2,2);
    
  }else if(Nruns<=6){
    AddCanvas1->Divide(2,3);
    AddCanvas2->Divide(2,3);
    
  }else if(Nruns<=9){
    AddCanvas1->Divide(3,3);
    AddCanvas2->Divide(3,3);
    
    }else if(Nruns<=12){
    AddCanvas1->Divide(3,4);
    AddCanvas2->Divide(3,4);
    
  }else if(Nruns<=16){
    AddCanvas1->Divide(4,4);
    AddCanvas2->Divide(4,4);
    
  }else if(Nruns<=25){
    AddCanvas1->Divide(5,5);
    AddCanvas2->Divide(5,5);
 
    
  }else{
    cout<<" WARNING : Config list too big, please reduce the number of configs you want to plot"<<endl;
    AddCanvas1->Divide(5,5);
    AddCanvas2->Divide(5,5);
    
    
  }
  AddCanvas1->Update();
  AddCanvas2->Update();
  




  //-------------------------------------------------------------------
  //substration
  //-------------------------------------------------------------------
  TPaveStats *statsub_1[Nruns];
  TPaveStats *statsub_2[Nruns];
  TPaveStats *statsub_3[Nruns];
  TPaveStats *statsub_4[Nruns];
 

  for (Int_t i=0 ; i<Nruns ; i++){

    //-------GET DATA
    AddCanvas1->cd(i+1);
    sprintf(ResultFileName,"/rawcmos7/abesson/TAF/trunk2/trunk/results_ana_M28/run%dPl%d_ClCharge.root",RunNumber[i],Plane[i]);
    TFile* ffile2 =new TFile(ResultFileName,"read");
    TH1F *hnpix_c2;
    ffile2->GetObject("npix_c",hnpix_c2);    
    Float_t integg;
    integg = hnpix_c2->Integral();
    if(integg!=0.0){hnpix_c2->Scale(1/integg);}
    hnpix_c2->SetLineColor(2);
    Float_t hYmax = 0.70;    
    hnpix_c2->SetAxisRange(0,hYmax,"Y");
    hnpix_c2->Draw();
    //    Int_t configlist[Nconfig] = {2,5,8,11,14,17,20,23,26};
    //    Int_t configlist2[Nconfig2] = {29,32,35,38,41,44,47,50,53}; //11  
    //    Int_t configlist3[Nconfig3] = {56,59,62,65,68,71,74,77,80}; //11
    //    Int_t configlist4[Nconfig4] = {83,86,89,92,95,98,101,104,107}; //11

    //-------configlist 1:
    MainCanvas1->cd(i+1);
    Char_t histoname[300];
    sprintf(histoname,"multiplicity_with_threshold_01_conf%d",configlist[i]);
    TH1F* htemp1 = 0;
    htemp1 = (TH1F*)gPad->GetPrimitive(histoname);
  // TH1F* htemp = ((TH1F*)MainCanvas1_1->GetPrimitive("histoname"));
  //((TH1F*)MainCanvas1_1->GetPrimitive("histoname"))->Draw();
    AddCanvas1->cd(i+1);
    //htemp1->Draw("same");
    Char_t histonamesub[300];
    TH1F* hdata_m_digit1= new TH1F("data_m_digit1","data_m_digit1",27,0.0,27.0);
    hdata_m_digit1->Add(hnpix_c2,htemp1,1.0,-1.0);
    Int_t    ColorChosen = 1;
    hdata_m_digit1->SetFillStyle(0);
    hdata_m_digit1->SetLineColor(ColorChosen);
    hdata_m_digit1->SetMarkerSize(1);    
    hdata_m_digit1->SetMarkerStyle(2);
    hdata_m_digit1->SetMarkerColor(ColorChosen);
    hdata_m_digit1->SetAxisRange(-0.20,0.2,"Y"); 
    hdata_m_digit1->SetAxisRange(0,12,"X"); 
    hdata_m_digit1->Draw("lp");
    gPad->Update();
    statsub_1[i] = (TPaveStats*)gPad->GetPrimitive("stats");
    statsub_1[i]->SetName("statsub_1");
    statsub_1[i]->SetX1NDC(0.65);
    statsub_1[i]->SetY1NDC(0.20);
    statsub_1[i]->SetX2NDC(0.95);
    statsub_1[i]->SetY2NDC(0.35);
    statsub_1[i]->SetLineColor(ColorChosen);
    statsub_1[i]->SetTextColor(ColorChosen);
    statsub_1[i]->Draw();


    leg2[i] = new TLegend(0.42,0.65,0.59,0.80);
    leg2[i]->SetTextSize(0.03);
    Char_t  legendsub1[150]; 
    sprintf(legendsub1,"epi=8um");
    leg2[i]->AddEntry(hdata_m_digit1,legendsub1,"l");
    leg2[i]->SetFillStyle(0);

    TPaveText *text = new TPaveText(1.0,-0.15,3.,-.11);
    Char_t  chartext[400];
    sprintf(chartext,"S/N >= %2.1f",Threshold[i]);
    text->AddText(chartext);
    text->SetFillColor(0);
    text->Draw("same");
    //ffile->Close();





    //-------configlist 2:
    MainCanvas1->cd(i+1);
    Char_t histoname[300];
    sprintf(histoname,"multiplicity_with_threshold_01_conf%d",configlist2[i]);
    TH1F* htemp2 = 0;
    htemp2 = (TH1F*)gPad->GetPrimitive(histoname);
  // TH1F* htemp = ((TH1F*)MainCanvas1_1->GetPrimitive("histoname"));
  //((TH1F*)MainCanvas1_1->GetPrimitive("histoname"))->Draw();
    AddCanvas1->cd(i+1);
    //htemp2->Draw("same");
    Char_t histonamesub[300];
    TH1F* hdata_m_digit2= new TH1F("data_m_digit2","data_m_digit2",27,0.0,27.0);
    hdata_m_digit2->Add(hnpix_c2,htemp2,1.0,-1.0);
    ColorChosen = 3;
    hdata_m_digit2->SetFillStyle(0);
    hdata_m_digit2->SetLineColor(ColorChosen);
    hdata_m_digit2->SetMarkerSize(1);    
    hdata_m_digit2->SetMarkerStyle(2);
    hdata_m_digit2->SetMarkerColor(ColorChosen);
      // hdata_m_digit2->SetAxisRange(0,0.6,"Y"); 
    hdata_m_digit2->Draw("lp sames");
    gPad->Update();
    statsub_2[i] = (TPaveStats*)gPad->GetPrimitive("stats");
    statsub_2[i]->SetName("statsub_1");
    statsub_2[i]->SetX1NDC(0.65);
    statsub_2[i]->SetY1NDC(0.36);
    statsub_2[i]->SetX2NDC(0.95);
    statsub_2[i]->SetY2NDC(0.51);
    statsub_2[i]->SetLineColor(ColorChosen);
    statsub_2[i]->SetTextColor(ColorChosen);
    statsub_2[i]->Draw();

    sprintf(legendsub1,"epi=9um");
    leg2[i]->AddEntry(hdata_m_digit2,legendsub1,"l");
    leg2[i]->SetFillStyle(0);

    //-------configlist 3:
     MainCanvas1->cd(i+1);
    Char_t histoname[300];
    sprintf(histoname,"multiplicity_with_threshold_01_conf%d",configlist3[i]);
    TH1F* htemp3 = 0;
    htemp3 = (TH1F*)gPad->GetPrimitive(histoname);
  // TH1F* htemp = ((TH1F*)MainCanvas1_1->GetPrimitive("histoname"));
  //((TH1F*)MainCanvas1_1->GetPrimitive("histoname"))->Draw();
    AddCanvas1->cd(i+1);
    //htemp3->Draw("same");
    Char_t histonamesub[300];
    TH1F* hdata_m_digit3= new TH1F("data_m_digit3","data_m_digit3",27,0.0,27.0);
    hdata_m_digit3->Add(hnpix_c2,htemp3,1.0,-1.0);
    ColorChosen = 4;
    hdata_m_digit3->SetFillStyle(0);
    hdata_m_digit3->SetLineColor(ColorChosen);
    hdata_m_digit3->SetMarkerSize(1);    
    hdata_m_digit3->SetMarkerStyle(2);
    hdata_m_digit3->SetMarkerColor(ColorChosen);
      // hdata_m_digit2->SetAxisRange(0,0.6,"Y"); 
    hdata_m_digit3->Draw("lp sames");
    gPad->Update();
    statsub_3[i] = (TPaveStats*)gPad->GetPrimitive("stats");
    statsub_3[i]->SetName("statsub_1");
    statsub_3[i]->SetX1NDC(0.65);
    statsub_3[i]->SetY1NDC(0.62);
    statsub_3[i]->SetX2NDC(0.95);
    statsub_3[i]->SetY2NDC(0.77);
    statsub_3[i]->SetLineColor(ColorChosen);
    statsub_3[i]->SetTextColor(ColorChosen);
    statsub_3[i]->Draw();

    sprintf(legendsub1,"epi=10um");
    leg2[i]->AddEntry(hdata_m_digit3,legendsub1,"l");
    leg2[i]->SetFillStyle(0);

    //-------configlist 4:
    MainCanvas1->cd(i+1);
    Char_t histoname[300];
    sprintf(histoname,"multiplicity_with_threshold_01_conf%d",configlist4[i]);
    TH1F* htemp4 = 0;
    htemp4 = (TH1F*)gPad->GetPrimitive(histoname);
  // TH1F* htemp = ((TH1F*)MainCanvas1_1->GetPrimitive("histoname"));
  //((TH1F*)MainCanvas1_1->GetPrimitive("histoname"))->Draw();
    AddCanvas1->cd(i+1);
    //htemp4->Draw("same");
    Char_t histonamesub[300];
    TH1F* hdata_m_digit4= new TH1F("data_m_digit4","data_m_digit4",27,0.0,27.0);
    hdata_m_digit4->Add(hnpix_c2,htemp4,1.0,-1.0);
    ColorChosen = 6;
    hdata_m_digit4->SetFillStyle(0);
    hdata_m_digit4->SetLineColor(ColorChosen);
    hdata_m_digit4->SetMarkerSize(1);    
    hdata_m_digit4->SetMarkerStyle(2);
    hdata_m_digit4->SetMarkerColor(ColorChosen);
      // hdata_m_digit2->SetAxisRange(0,0.6,"Y"); 
    hdata_m_digit4->Draw("lp sames");
    gPad->Update();
    statsub_4[i] = (TPaveStats*)gPad->GetPrimitive("stats");
    statsub_4[i]->SetName("statsub_1");
    statsub_4[i]->SetX1NDC(0.65);
    statsub_4[i]->SetY1NDC(0.78);
    statsub_4[i]->SetX2NDC(0.95);
    statsub_4[i]->SetY2NDC(0.93);
    statsub_4[i]->SetLineColor(ColorChosen);
    statsub_4[i]->SetTextColor(ColorChosen);
    statsub_4[i]->Draw();

    sprintf(legendsub1,"epi=11um");
    leg2[i]->AddEntry(hdata_m_digit4,legendsub1,"l");
    leg2[i]->SetFillStyle(0);
    leg2[i]->Draw();
    //ffile->Close();
  }

  //-------------------------------------------------------------------
  //resolution
  //-------------------------------------------------------------------


  Float_t par0[Nruns];
  Float_t Errpar0[Nruns];
  Float_t par1[Nruns];
  Float_t Errpar1[Nruns];
  Float_t par2[Nruns];
  Float_t Errpar2[Nruns];
  Float_t dataresolution[Nruns];
  Float_t Errdataresolution[Nruns];
  Float_t trackerresolution = 1.8;
  
  Float_t TotalEff[Nruns];
  Float_t ErrTotalEff[Nruns];

  Float_t Multiplicity_data[Nruns];
  Float_t Err_Multiplicity_data[Nruns];

  for (Int_t i=0 ; i<Nruns ; i++){

    //-------GET DATA
    AddCanvas2->cd(i+1);
    sprintf(ResultFileName,"/rawcmos7/abesson/TAF/trunk2/trunk/results_ana_M28/run%dPl%d_ClCharge.root",RunNumber[i],Plane[i]);
    TFile* ffile2 =new TFile(ResultFileName,"read");
    //TH1F *hnpix_c2;
    //ffile2->GetObject("npix_c",hnpix_c2);    


    TH1F *hCG5URes_c2;
    ffile2->GetObject("hCG5URes",hCG5URes_c2);    

    hCG5URes_c2->Draw();
    TF1 *fitg =hCG5URes_c2->GetFunction("gaus");
    par0[i]=fitg->GetParameter(0);
    Errpar0[i]=fitg->GetParError(0);
    par1[i]=fitg->GetParameter(1);
    Errpar1[i]=fitg->GetParError(1);
    par2[i]=fitg->GetParameter(2);
    Errpar2[i]=fitg->GetParError(2);
   
    dataresolution[i] = TMath::Sqrt(par2[i]*par2[i]-trackerresolution*trackerresolution);
    Errdataresolution[i] = 0.1;

    cout<<" i residual resolution"<<i <<"; "<<par2[i] <<"+-"<< Errpar2[i]<<" "<<dataresolution[i]<<" um"<<endl;
    //hCG5URes   = new TH1F("hCG5URes","huCG5-tu",80,-ResRange,ResRange);
    //MyClass *obj = (Myclass*)pad->GetPrimitive(objectname);
    //       TF1 *fitgU =hM8_sub1_Residual_U_CoG[i]->GetFunction("gaus");

    TH2F *hh_htuhtv;
    ffile2->GetObject("htuhtv",hh_htuhtv);    
    Int_t ineff = hh_htuhtv->GetEntries();
    TH1F *hh_npix_c;
    ffile2->GetObject("npix_c",hh_npix_c);    
    Int_t eff = npix_c->GetEntries();

    Multiplicity_data[i]=npix_c->GetMean();
    Err_Multiplicity_data[i]=npix_c->GetMeanError();



    Float_t TotalEff[i] = 0.0;
    if((eff+ineff)!=0){
      TotalEff[i] = float(eff)/float(eff+ineff);
      ErrTotalEff[i] = TMath::Sqrt(TotalEff[i] * (1.0-TotalEff[i]) / (eff+ineff) );
    }
    
  }

  //-------------------------------------------------------------------
  //summary
  //-------------------------------------------------------------------
  AddCanvas3->Divide(1,3);

  //---------------------res

  AddCanvas3->cd(1);
  TH2F *hresFrame = new TH2F("hresFrame","resolution(um) vs threshold(/noise)",100,0,13,100,3.,5.0);
  hresFrame->SetStats(0000000);
  hresFrame->SetXTitle("Threshold (/noise)");
  hresFrame->SetYTitle("Resolution (microns)");
  
  hresFrame->Draw();
  
  hresFrame->GetYaxis()->SetLabelOffset(0.002);
  hresFrame->GetYaxis()->SetLabelSize(0.04);
  hresFrame->GetYaxis()->SetTitleOffset(1.3);
  hresFrame->GetYaxis()->SetTitleSize(0.04);
  hresFrame->GetXaxis()->SetTitleColor(1);
  hresFrame->GetXaxis()->SetTitleSize(0.05);



  TGraphErrors* grsubdata;
  grsubdata = new TGraphErrors(Nruns,Threshold,dataresolution,ThresholdErr,Errdataresolution);
  //gr->SetTitle("TGraphErrors Example");
  grsubdata->SetMarkerColor(2);
  grsubdata->SetMarkerStyle(21);
  grsubdata->SetMarkerSize(0.6);
  grsubdata->SetLineColor(2);
  grsubdata->Draw();

  TGraphErrors* grsubdigit1;
  grsubdigit1 = new TGraphErrors(Nruns,Threshold,Resolution_digit1,ThresholdErr,Err_Resolution_digit1);
  //gr->SetTitle("TGraphErrors Example");
  grsubdigit1->SetMarkerColor(1);
  grsubdigit1->SetMarkerStyle(21);
  grsubdigit1->SetMarkerSize(0.6);
  grsubdigit1->SetLineColor(1);
  grsubdigit1->Draw("same");

  TGraphErrors* grsubdigit2;
  grsubdigit2 = new TGraphErrors(Nruns,Threshold,Resolution_digit2,ThresholdErr,Err_Resolution_digit2);
  //gr->SetTitle("TGraphErrors Example");
  grsubdigit2->SetMarkerColor(3);
  grsubdigit2->SetMarkerStyle(21);
  grsubdigit2->SetMarkerSize(0.6);
  grsubdigit2->SetLineColor(3);
  grsubdigit2->Draw("same");

  TGraphErrors* grsubdigit3;
  grsubdigit3 = new TGraphErrors(Nruns,Threshold,Resolution_digit3,ThresholdErr,Err_Resolution_digit3);
  //gr->SetTitle("TGraphErrors Example");
  grsubdigit3->SetMarkerColor(4);
  grsubdigit3->SetMarkerStyle(21);
  grsubdigit3->SetMarkerSize(0.6);
  grsubdigit3->SetLineColor(4);
  grsubdigit3->Draw("same");

  TGraphErrors* grsubdigit4;
  grsubdigit4 = new TGraphErrors(Nruns,Threshold,Resolution_digit4,ThresholdErr,Err_Resolution_digit4);
  //gr->SetTitle("TGraphErrors Example");
  grsubdigit4->SetMarkerColor(6);
  grsubdigit4->SetMarkerStyle(21);
  grsubdigit4->SetMarkerSize(0.6);
  grsubdigit4->SetLineColor(6);
  grsubdigit4->Draw("same");

  leg3[0] = new TLegend(0.15,0.40,0.3,0.70);
  leg3[0]->SetTextSize(0.03);
  Char_t  legendsub1[150]; 
  sprintf(legendsub1,"epi = 8 um");
  leg3[0]->AddEntry(grsubdigit1,legendsub1,"l");
  sprintf(legendsub1,"epi = 9 um");
  leg3[0]->AddEntry(grsubdigit2,legendsub1,"l");
  sprintf(legendsub1,"epi = 10 um");
  leg3[0]->AddEntry(grsubdigit3,legendsub1,"l");
  sprintf(legendsub1,"epi = 11 um");
  leg3[0]->AddEntry(grsubdigit4,legendsub1,"l");
  sprintf(legendsub1,"data");
  leg3[0]->AddEntry(grsubdata,legendsub1,"l");
  leg3[0]->SetFillStyle(0);
  leg3[0]->Draw();

  //---------------------eff
  AddCanvas3->cd(2);
  TH2F *heffFrame = new TH2F("heffFrame","Efficiency vs threshold(/noise)",100,0,13,100,0.9,1.01);
  heffFrame->SetStats(0000000);
  heffFrame->SetXTitle("Threshold (/noise)");
  heffFrame->SetYTitle("Efficiency ");
  
  heffFrame->Draw();
  
  heffFrame->GetYaxis()->SetLabelOffset(0.002);
  heffFrame->GetYaxis()->SetLabelSize(0.04);
  heffFrame->GetYaxis()->SetTitleOffset(1.3);
  heffFrame->GetYaxis()->SetTitleSize(0.04);
  heffFrame->GetXaxis()->SetTitleColor(1);
  heffFrame->GetXaxis()->SetTitleSize(0.05);


  TGraphErrors* greffdata;
  greffdata = new TGraphErrors(Nruns,Threshold,TotalEff,ThresholdErr,ErrTotalEff);
  //gr->SetTitle("TGraphErrors Example");
  greffdata->SetMarkerColor(2);
  greffdata->SetMarkerStyle(21);
  greffdata->SetMarkerSize(0.6);
  greffdata->SetLineColor(2);
  greffdata->Draw();

  TGraphErrors* greffdigit1;
  greffdigit1 = new TGraphErrors(Nruns,Threshold,Efficiency_digit1,ThresholdErr,Err_Efficiency_digit1);
  //gr->SetTitle("TGraphErrors Example");
  greffdigit1->SetMarkerColor(1);
  greffdigit1->SetMarkerStyle(21);
  greffdigit1->SetMarkerSize(0.6);
  greffdigit1->SetLineColor(1);
  greffdigit1->Draw("");

  TGraphErrors* greffdigit2;
  greffdigit2 = new TGraphErrors(Nruns,Threshold,Efficiency_digit2,ThresholdErr,Err_Efficiency_digit2);
  //gr->SetTitle("TGraphErrors Example");
  greffdigit2->SetMarkerColor(3);
  greffdigit2->SetMarkerStyle(21);
  greffdigit2->SetMarkerSize(0.6);
  greffdigit2->SetLineColor(3);
  greffdigit2->Draw("same");

  TGraphErrors* greffdigit3;
  greffdigit3 = new TGraphErrors(Nruns,Threshold,Efficiency_digit3,ThresholdErr,Err_Efficiency_digit3);
  //gr->SetTitle("TGraphErrors Example");
  greffdigit3->SetMarkerColor(4);
  greffdigit3->SetMarkerStyle(21);
  greffdigit3->SetMarkerSize(0.6);
  greffdigit3->SetLineColor(4);
  greffdigit3->Draw("same");

  TGraphErrors* greffdigit4;
  greffdigit4 = new TGraphErrors(Nruns,Threshold,Efficiency_digit4,ThresholdErr,Err_Efficiency_digit4);
  //gr->SetTitle("TGraphErrors Example");
  greffdigit4->SetMarkerColor(6);
  greffdigit4->SetMarkerStyle(21);
  greffdigit4->SetMarkerSize(0.6);
  greffdigit4->SetLineColor(6);
  greffdigit4->Draw("same");

  leg3[1] = new TLegend(0.15,0.40,0.3,0.70);
  leg3[1]->SetTextSize(0.03);
  sprintf(legendsub1,"epi = 8 um");
  leg3[1]->AddEntry(greffdigit1,legendsub1,"l");
  sprintf(legendsub1,"epi = 9 um");
  leg3[1]->AddEntry(greffdigit2,legendsub1,"l");
  sprintf(legendsub1,"epi = 10 um");
  leg3[1]->AddEntry(greffdigit3,legendsub1,"l");
  sprintf(legendsub1,"epi = 11 um");
  leg3[1]->AddEntry(greffdigit4,legendsub1,"l");
  sprintf(legendsub1,"data");
  leg3[1]->AddEntry(greffdata,legendsub1,"l");
  leg3[1]->SetFillStyle(0);
  leg3[1]->Draw();

  /*
  //---------------------average mult.
  Float_t Multiplicity_digit1[Nruns];
  Float_t Err_Multiplicity_digit1[Nruns];
  Float_t Multiplicity_digit2[Nruns];
  Float_t Err_Multiplicity_digit2[Nruns];
  Float_t Multiplicity_digit3[Nruns];
  Float_t Err_Multiplicity_digit3[Nruns];
  Float_t Multiplicity_digit4[Nruns];
  Float_t Err_Multiplicity_digit4[Nruns];

    Multiplicity_data[i]=npix_c->GetMean();
    Err_Multiplicity_data[i]=npix_c->GetMeanError();*/

  AddCanvas3->cd(3);
  TH2F *hmulFrame = new TH2F("hmulFrame","Average multiplicit vs threshold(/noise)",100,0,13,100,1.,6.0);
  hmulFrame->SetStats(0000000);
  hmulFrame->SetXTitle("Threshold (/noise)");
  hmulFrame->SetYTitle("Average multiplicity");
  
  hmulFrame->Draw();
  
  hmulFrame->GetYaxis()->SetLabelOffset(0.002);
  hmulFrame->GetYaxis()->SetLabelSize(0.04);
  hmulFrame->GetYaxis()->SetTitleOffset(1.3);
  hmulFrame->GetYaxis()->SetTitleSize(0.04);
  hmulFrame->GetXaxis()->SetTitleColor(1);
  hmulFrame->GetXaxis()->SetTitleSize(0.05);


  TGraphErrors* grmuldata;
  grmuldata = new TGraphErrors(Nruns,Threshold,Multiplicity_data,ThresholdErr, Err_Multiplicity_data);
  //gr->SetTitle("TGraphErrors Example");
  grmuldata->SetMarkerColor(2);
  grmuldata->SetMarkerStyle(21);
  grmuldata->SetMarkerSize(0.6);
  grmuldata->SetLineColor(2);
  grmuldata->Draw();

  TGraphErrors* grmuldigit1;
  grmuldigit1 = new TGraphErrors(Nruns,Threshold,Multiplicity_digit1,ThresholdErr,Err_Multiplicity_digit1);
  //gr->SetTitle("TGraphErrors Example");
  grmuldigit1->SetMarkerColor(1);
  grmuldigit1->SetMarkerStyle(21);
  grmuldigit1->SetMarkerSize(0.6);
  grmuldigit1->SetLineColor(1);
  grmuldigit1->Draw("");

  TGraphErrors* grmuldigit2;
  grmuldigit2 = new TGraphErrors(Nruns,Threshold,Multiplicity_digit2,ThresholdErr,Err_Multiplicity_digit2);
  //gr->SetTitle("TGraphErrors Example");
  grmuldigit2->SetMarkerColor(3);
  grmuldigit2->SetMarkerStyle(21);
  grmuldigit2->SetMarkerSize(0.6);
  grmuldigit2->SetLineColor(3);
  grmuldigit2->Draw("same");

  TGraphErrors* grmuldigit3;
  grmuldigit3 = new TGraphErrors(Nruns,Threshold,Multiplicity_digit3,ThresholdErr,Err_Multiplicity_digit3);
  //gr->SetTitle("TGraphErrors Example");
  grmuldigit3->SetMarkerColor(4);
  grmuldigit3->SetMarkerStyle(21);
  grmuldigit3->SetMarkerSize(0.6);
  grmuldigit3->SetLineColor(4);
  grmuldigit3->Draw("same");

  TGraphErrors* grmuldigit4;
  grmuldigit4 = new TGraphErrors(Nruns,Threshold,Multiplicity_digit4,ThresholdErr,Err_Multiplicity_digit4);
  //gr->SetTitle("TGraphErrors Example");
  grmuldigit4->SetMarkerColor(6);
  grmuldigit4->SetMarkerStyle(21);
  grmuldigit4->SetMarkerSize(0.6);
  grmuldigit4->SetLineColor(6);
  grmuldigit4->Draw("same");

  leg3[2] = new TLegend(0.15,0.40,0.3,0.70);
  leg3[2]->SetTextSize(0.03);
  sprintf(legendsub1,"epi = 8 um");
  leg3[2]->AddEntry(grmuldigit1,legendsub1,"l");
  sprintf(legendsub1,"epi = 9 um");
  leg3[2]->AddEntry(grmuldigit2,legendsub1,"l");
  sprintf(legendsub1,"epi = 10 um");
  leg3[2]->AddEntry(grmuldigit3,legendsub1,"l");
  sprintf(legendsub1,"epi = 11 um");
  leg3[2]->AddEntry(grmuldigit4,legendsub1,"l");
  sprintf(legendsub1,"data");
  leg3[2]->AddEntry(grmuldata,legendsub1,"l");
  leg3[2]->SetFillStyle(0);
  leg3[2]->Draw();




  Char_t HeaderSave[200];
 
  if(boolprint==true){
    sprintf(HeaderSave,"Mulitiplicity1_DIG_pitch.gif");
    MainCanvas1->Print(HeaderSave,"gif");
    sprintf(HeaderSave,"Mulitiplicity1_DIG_pitch.eps");
    MainCanvas1->Print(HeaderSave,"eps");
    sprintf(HeaderSave,"Mulitiplicity2_DIG_pitch.gif");
    MainCanvas2->Print(HeaderSave,"gif");
    sprintf(HeaderSave,"Mulitiplicity2_DIG_pitch.eps");
    MainCanvas2->Print(HeaderSave,"eps");
    sprintf(HeaderSave,"Mulitiplicity3_DIG_pitch.gif");
    MainCanvas3->Print(HeaderSave,"gif");
    sprintf(HeaderSave,"Mulitiplicity3_DIG_pitch.eps");
    MainCanvas3->Print(HeaderSave,"eps");
    sprintf(HeaderSave,"Mulitiplicity4_DIG_pitch.gif");
    MainCanvas4->Print(HeaderSave,"gif");
    sprintf(HeaderSave,"Mulitiplicity4_DIG_pitch.eps");
    MainCanvas4->Print(HeaderSave,"eps");
    sprintf(HeaderSave,"AddCanvas1_DIG_pitch.gif");
    AddCanvas1->Print(HeaderSave,"gif");
    sprintf(HeaderSave,"AddCanvas1_DIG_pitch.eps");
    AddCanvas1->Print(HeaderSave,"eps");
    sprintf(HeaderSave,"AddCanvas2_DIG_pitch.gif");
    AddCanvas2->Print(HeaderSave,"gif");
    sprintf(HeaderSave,"AddCanvas2_DIG_pitch.eps");
    AddCanvas2->Print(HeaderSave,"eps");
    sprintf(HeaderSave,"AddCanvas3_DIG_pitch.gif");
    AddCanvas3->Print(HeaderSave,"gif");
    sprintf(HeaderSave,"AddCanvas3_DIG_pitch.eps");
    AddCanvas3->Print(HeaderSave,"eps");

  }


}
