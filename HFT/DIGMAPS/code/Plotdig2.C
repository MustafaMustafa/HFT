{

  myDIGMAPS2.PrintConfigurations() ;
  Bool_t boolprint=true;
  Char_t  ResultFileName[250];     

  const Int_t Nruns = 16;
  TPaveStats *statdigit1_1[Nruns];
  TPaveStats *statdigit1_2[Nruns];
  TPaveStats *statdigit1_3[Nruns];
  TPaveStats *statdigit1_4[Nruns];
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

  /*

  RUN       THRESHOLD   ANGLE
  28581,    4           0
  28579,    5           0
  28568,    6           0
  28606,    8           0
  
  xxxxx,    4           -
  28602,    5           30
  28603,    6           30
  28604,    8           30
  
  28584,    4           45
  xxxxx,    5           -
  28582,    6           45
  28583,    8           45
  
  xxxxx,    4           -
  28586,    5           60
  28587,    6           60
  28588,    8           60


  */


  ///home/abesson/SAVE/ILCSOFT/DIGITISEUR/data
    ///home/senyukov/Beamtests/Mimosa28/Plots
    ///rawcmos7/abesson/TAF/trunk2/trunk/results_ana_M28/
  ///rawcmos16c/senyukov/soft/taf/trunk/results_ana_M28/run28*
  //  Int_t RunNumber[Nruns] = {28584,28000,28000,28582,28000,28583,28000,28000,28000};//  {28567,28568,28569,28570,28571,28579,28580,28581,28606};
  //  Float_t Threshold[Nruns] = {4.0,4.5,5.0,6.0,7.0,8.0,9.0,10.2,11.5};//  {9.0,5.8,10.2,7.0,11.5,5.0,4.5,4.0,8.0};
    Int_t RunNumber[Nruns] = {28581,28579,28568,28606, 28000,28602,28603,28604, 28584,28000,28582,28583, 28000,28586,28587,28588};
    Float_t Threshold[Nruns] = {4.0,5.0,6.0,8.0, 4.0,5.0,6.0,8.0, 4.0,5.0,6.0,8.0, 4.0,5.0,6.0,8.0};
    Float_t ThresholdErr[Nruns] = {0.1,0.1,0.1,0.1, 0.1,0.1,0.1,0.1, 0.1,0.1,0.1,0.1, 0.1,0.1,0.1,0.1};
  Int_t Plane[Nruns] = {3,3,3,3, 3,3,3,3, 3,3,3,3, 3,3,3,3};
  Int_t Exist[Nruns] = {1,1,1,1, 0,1,1,1, 1,0,1,1, 0,1,1,1};
  Float_t Angle[Nruns] = {0.0,0.0,0.0,0.0,  30.0,30.0,30.0,30.0, 45.0,45.0,45.0,45.0, 60.0,60.0,60.0,60.0};
// /rawcmos7/abesson/ILCSOFT/DIGITISEUR/data/run28582Pl3_ClCharge.root
// /rawcmos7/abesson/ILCSOFT/DIGITISEUR/data/run28583Pl3_ClCharge.root
// /rawcmos7/abesson/ILCSOFT/DIGITISEUR/data/run28584Pl3_ClCharge.root

  TPaveText *text1[Nruns];
  TPaveText *text2[Nruns];

  //-------------------------------------------------------------------
  /*
  const int Nconfig = 9;
  Int_t configlist[Nconfig] = {0,1,2,3,4,5,6,7,8};
  myDIGMAPS2.PlotDigitalConfiguration(1,configlist,Nconfig);
  gPad->Update();
  MainCanvas1->Update();
  */
  //-------------------------------------------------------------------
  /*
  const int Nconfig2 = 9;
  Int_t configlist2[Nconfig2] = {9,10,11,12,13,14,15,16,17}; //11  
  myDIGMAPS2.PlotDigitalConfiguration(0,configlist2,Nconfig2);
  gPad->Update();
  MainCanvas1->Update();
  */
  //-------------------------------------------------------------------
  //   Float_t Threshold[Nruns] = {5.0,6.0,8.0,4.0,6.0,8.0,5.0,6.0,8.0};
  //  Float_t Angle[Nruns] = {30.0,30.0,30.0,45.0,45.0,45.0,60.0,60.0,60.0};
  const int Nconfig3 = 16;
  //  Int_t configlist3[Nconfig3] = {18,19,20,21,22,23,24,25,26}; //11  
  Int_t configlist3[Nconfig3] = {0,2,3,5,  9,11,12,14, 18,20,21,23, 27,29,30,32};
  myDIGMAPS2.PlotDigitalConfiguration(1,configlist3,Nconfig3);
  gPad->Update();
  MainCanvas1->Update();

  Int_t plotstat = 1;
  if(plotstat!=0){
    for (Int_t i=0 ; i<Nruns ; i++){
      
      
      MainCanvas1->cd(i+1);

      text1[i] = new TPaveText(10.0,.1,25.,.3);
      //text1[i]->SetTextSize(1.5);
      Char_t  chartext[400];
      sprintf(chartext,"Thres = %2.0f mV",Threshold[i]);
      text1[i]->AddText(chartext);
      sprintf(chartext,"Angle = %4.0f deg",Angle[i]);
      text1[i]->AddText(chartext);
      text1[i]->SetFillColor(0);
      text1[i]->Draw("same");
      //cout<<" TEXT "<<text1[i]->GetTextSize()<<endl;
      TPad *subpad = gPad;
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
      statdigit1_3[i]->SetY1NDC(0.65);
      statdigit1_3[i]->SetX2NDC(0.95);
      statdigit1_3[i]->SetY2NDC(0.79);
      statdigit1_3[i]->SetLineColor(1); 
      statdigit1_3[i]->SetTextColor(1);
      statdigit1_3[i]->Draw();
      
      Char_t histoname[300];
      sprintf(histoname,"multiplicity_with_threshold_01_conf%d",configlist3[i]);
      TH1F* htmp1 = 0;
      htmp1 = (TH1F*)gPad->GetPrimitive(histoname);
      Multiplicity_digit4[i] = htmp1->GetMean()-0.5;
      Err_Multiplicity_digit4[i] = htmp1->GetMeanError();
      
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
      Efficiency_digit4[i] = htmp3->GetMean();
      if(Nevent!=0.0){
	Err_Efficiency_digit4[i] = TMath::Sqrt(Efficiency_digit4[i] * (1.0-Efficiency_digit4[i]) / Nevent );
      }

      MainCanvas4->cd(i+1);
      Char_t histoname4[300];
      sprintf(histoname4,"Ar_h1_Resolution_ResidualX_CoG_true_conf%d",configlist3[i]);
      TH1F* htmp4 = 0;
      htmp4 = (TH1F*)gPad->GetPrimitive(histoname4);
      TF1 *fitg =htmp4->GetFunction("gaus");
      fitg->SetName("gaus2");
      Resolution_digit4[i]=fitg->GetParameter(2) ;
      Err_Resolution_digit4[i]=fitg->GetParError(2);
    }
    
  }
  
  //-------------------------------------------------------------------
  /*
  const int Nconfig4 = 9;
  Int_t configlist4[Nconfig4] = {27,28,29,30,31,32,33,34,35}; //11  
  myDIGMAPS2.PlotDigitalConfiguration(0,configlist4,Nconfig4);
  gPad->Update();
  MainCanvas1->Update();
  */

  //-------------------------------------------------------------------

  for (Int_t i=0 ; i<Nruns ; i++){

    if(Exist[i]==1){
      MainCanvas1->cd(i+1);
      //    TPad *subpad = (TPad*)gPad->GetPad(i+1)
      gPad->Update();
      MainCanvas1->Update();
      TPad *subpad = gPad;

      sprintf(ResultFileName,"/rawcmos7/abesson/ILCSOFT/DIGITISEUR/data/run%dPl%d_ClCharge.root",RunNumber[i],Plane[i]);
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
    
      //ffile->Close();

    }
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
  //summary
  //-------------------------------------------------------------------

  //-------------------------------------------------------------------
  //substration
  //-------------------------------------------------------------------
  TPaveStats *statsub_1[Nruns];
  //  TPaveStats *statsub_2[Nruns];
  //  TPaveStats *statsub_3[Nruns];
  //  TPaveStats *statsub_4[Nruns];
  for (Int_t i=0 ; i<Nruns ; i++){

    //-------GET DATA
    AddCanvas1->cd(i+1);
    if(Exist[i]==1){  
      sprintf(ResultFileName,"/rawcmos7/abesson/ILCSOFT/DIGITISEUR/data/run%dPl%d_ClCharge.root",RunNumber[i],Plane[i]);
      
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
      sprintf(histoname,"multiplicity_with_threshold_01_conf%d",configlist3[i]);
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
      statsub_1[i]->SetX1NDC(0.6);
      statsub_1[i]->SetY1NDC(0.20);
      statsub_1[i]->SetX2NDC(0.95);
      statsub_1[i]->SetY2NDC(0.35);
      statsub_1[i]->SetLineColor(ColorChosen);
      statsub_1[i]->SetTextColor(ColorChosen);
      statsub_1[i]->Draw();

      text2[i] = new TPaveText(6.0,.1,12.,.19);
      //text1[i]->SetTextSize(1.5);
      Char_t  chartext[400];
      sprintf(chartext,"Thres = %2.0f mV",Threshold[i]);
      text2[i]->AddText(chartext);
      sprintf(chartext,"Angle = %4.0f deg",Angle[i]);
      text2[i]->AddText(chartext);
      text2[i]->SetFillColor(0);
      text2[i]->Draw("same");
  
    }
    AddCanvas1->Update();
  }


  Char_t HeaderSave[200];
 
  if(boolprint==true){
    sprintf(HeaderSave,"Mulitiplicity1_DIGAngle_pitch.gif");
    MainCanvas1->Print(HeaderSave,"gif");
    sprintf(HeaderSave,"Mulitiplicity1_DIGAngle_pitch.eps");
    MainCanvas1->Print(HeaderSave,"eps");
    sprintf(HeaderSave,"Mulitiplicity2_DIGAngle_pitch.gif");
    MainCanvas2->Print(HeaderSave,"gif");
    sprintf(HeaderSave,"Mulitiplicity2_DIGAngle_pitch.eps");
    MainCanvas2->Print(HeaderSave,"eps");
    sprintf(HeaderSave,"Mulitiplicity3_DIGAngle_pitch.gif");
    MainCanvas3->Print(HeaderSave,"gif");
    sprintf(HeaderSave,"Mulitiplicity3_DIGAngle_pitch.eps");
    MainCanvas3->Print(HeaderSave,"eps");
    sprintf(HeaderSave,"Mulitiplicity4_DIGAngle_pitch.gif");
    MainCanvas4->Print(HeaderSave,"gif");
    sprintf(HeaderSave,"Mulitiplicity4_DIGAngle_pitch.eps");
    MainCanvas4->Print(HeaderSave,"eps");
    sprintf(HeaderSave,"AddCanvas1_DIGAngle_pitch.gif");
    AddCanvas1->Print(HeaderSave,"gif");
    sprintf(HeaderSave,"AddCanvas1_DIGAngle_pitch.eps");
    AddCanvas1->Print(HeaderSave,"eps");
    sprintf(HeaderSave,"AddCanvas2_DIGAngle_pitch.gif");
    AddCanvas2->Print(HeaderSave,"gif");
    sprintf(HeaderSave,"AddCanvas2_DIGAngle_pitch.eps");
    AddCanvas2->Print(HeaderSave,"eps");
    sprintf(HeaderSave,"AddCanvas3_DIGAngle_pitch.gif");
    AddCanvas3->Print(HeaderSave,"gif");
    sprintf(HeaderSave,"AddCanvas3_DIGAngle_pitch.eps");
    AddCanvas3->Print(HeaderSave,"eps");

  }



}

