{

  Int_t myconfig = 1; 

  //myDIGMAPS2.PlotAConfiguration(1,2) 
  //  Bool_t boolprint=false;
  Bool_t boolprint=true;
  myDIGMAPS2.PrintConfigurations() ;
    myDIGMAPS2.PlotAConfiguration(myconfig,1);
  //myDIGMAPS2.PlotAConfiguration(myconfig,2);

  Char_t  ResultFileName[150];

  const Int_t NRuns = 3;
  Int_t Runs[NRuns] = {22765,22786,22787};
  Int_t Planes[NRuns] = {9,9,9};

  TH1F *hmult_SN_1;
  TH1F *hmult_SN_2;
  TH1F *hmult_SN_3;
  TH1F *hmult_SN_4;
  TH1F *hmult_SN_5;
  TH1F *hmult_SN_6;
  TH1F *hmult_ADC_1;
  TH1F *hmult_ADC_2;
  TH1F *hmult_ADC_3;
  TH1F *hmult_ADC_4;
  TH1F *hmult_ADC_5;
  TH1F *hmult_ADC_6;
  TH1F *hmult_ADC_7;
  TH1F *hmult_ADC_8;
  TH1F *hmult_ADC_9;
  TH1F *hmult_ADC_10;
  TH1F *hmult_ADC_15;
  TH1F *hmult_ADC_20;
  TH1F *hmult_ADC_25;
  TH1F *hmult_ADC_30;
  TH1F *hmult_ADC_40;

  TH1F *hGOODCharge_Seed_over_total ;
  TH1F *hGOODCharge_Crown1_over_total ;
  TH1F *hGOODCharge_Crown2_over_total ;
  TH1F *hGOODCharge_total ;
  TH1F *hGOODCharge_4neighbours_over_total ;
  TH1F *hqc1;
  TH1F *hqc9;
  TH1F *hqc25;
  TH1F *hqcn_adc1;
  TH1F *hqcn_adc9;
  TH1F *hqcn_adc25;

  TH1F *hmult_SN_1_sum;
  TH1F *hmult_SN_2_sum;
  TH1F *hmult_SN_3_sum;
  TH1F *hmult_SN_4_sum;
  TH1F *hmult_SN_5_sum;
  TH1F *hmult_SN_6_sum;
  TH1F *hmult_ADC_1_sum;
  TH1F *hmult_ADC_2_sum;
  TH1F *hmult_ADC_3_sum;
  TH1F *hmult_ADC_4_sum;
  TH1F *hmult_ADC_5_sum;
  TH1F *hmult_ADC_6_sum;
  TH1F *hmult_ADC_7_sum;
  TH1F *hmult_ADC_8_sum;
  TH1F *hmult_ADC_9_sum;
  TH1F *hmult_ADC_10_sum;
  TH1F *hmult_ADC_15_sum;
  TH1F *hmult_ADC_20_sum;
  TH1F *hmult_ADC_25_sum;
  TH1F *hmult_ADC_30_sum;
  TH1F *hmult_ADC_40_sum;

  TH1F *hGOODCharge_Seed_over_total_sum;
  TH1F *hGOODCharge_Crown1_over_total_sum;
  TH1F *hGOODCharge_Crown2_over_total_sum;
  TH1F *hGOODCharge_total_sum;
  TH1F *hGOODCharge_4neighbours_over_total_sum;
  TH1F *hqc1_sum;
  TH1F *hqc9_sum;
  TH1F *hqc25_sum;
  TH1F *hqcn_adc1_sum;
  TH1F *hqcn_adc9_sum;
  TH1F *hqcn_adc25_sum;


  for (Int_t i=0 ; i<NRuns ; i++){
    sprintf(ResultFileName,"/rawcmos9/abesson/maf/results_ana_M22/run%dPl%d_ClCharge.root",Runs[i], Planes[i]);
    ffile = new TFile(ResultFileName,"READ");


    ffile->GetObject("hmult_SN_1",hmult_SN_1);
    ffile->GetObject("hmult_SN_2",hmult_SN_2);
    ffile->GetObject("hmult_SN_3",hmult_SN_3);
    ffile->GetObject("hmult_SN_4",hmult_SN_4);
    ffile->GetObject("hmult_SN_5",hmult_SN_5);
    ffile->GetObject("hmult_SN_6",hmult_SN_6);

    ffile->GetObject("hmult_ADC_1",hmult_ADC_1);
    ffile->GetObject("hmult_ADC_2",hmult_ADC_2);
    ffile->GetObject("hmult_ADC_3",hmult_ADC_3);
    ffile->GetObject("hmult_ADC_4",hmult_ADC_4);
    ffile->GetObject("hmult_ADC_5",hmult_ADC_5);
    ffile->GetObject("hmult_ADC_6",hmult_ADC_6);
    ffile->GetObject("hmult_ADC_7",hmult_ADC_7);
    ffile->GetObject("hmult_ADC_8",hmult_ADC_8);
    ffile->GetObject("hmult_ADC_9",hmult_ADC_9);
    ffile->GetObject("hmult_ADC_10",hmult_ADC_10);
    ffile->GetObject("hmult_ADC_15",hmult_ADC_15);
    ffile->GetObject("hmult_ADC_20",hmult_ADC_20);
    ffile->GetObject("hmult_ADC_25",hmult_ADC_25);
    ffile->GetObject("hmult_ADC_30",hmult_ADC_30);
    ffile->GetObject("hmult_ADC_40",hmult_ADC_40);



    ffile->GetObject("hGOODCharge_Seed_over_total",hGOODCharge_Seed_over_total);
    ffile->GetObject("hGOODCharge_Crown1_over_total",hGOODCharge_Crown1_over_total);
    ffile->GetObject("hGOODCharge_Crown2_over_total",hGOODCharge_Crown2_over_total);
    ffile->GetObject("hGOODCharge_total",hGOODCharge_total);
    ffile->GetObject("hGOODCharge_4neighbours_over_total",hGOODCharge_4neighbours_over_total ); 

    ffile->GetObject("hqc1",hqc1);
    ffile->GetObject("hqc9",hqc9);
    ffile->GetObject("hqc25",hqc25);
    ffile->GetObject("hqcn_adc1",hqcn_adc1);
    ffile->GetObject("hqcn_adc9",hqcn_adc9);
    ffile->GetObject("hqcn_adc25",hqcn_adc25);

    TProfile *hprof2i;
    ffile->GetObject("ProfhGOODCharge_Charge_DiodeDistance",hprof2i);

    TH2F *hGOODCharge_Charge_DiodeDistance;
    ffile->GetObject("hGOODCharge_Charge_DiodeDistance",hGOODCharge_Charge_DiodeDistance);

    Float_t integg;

    if(i==0){
      // hGOODCharge_Charge_DiodePositionSum->Sumw2();
      hmult_SN_1_sum = (TH1F*)hmult_SN_1->Clone("hmult_SN_1");
      hmult_SN_2_sum = (TH1F*)hmult_SN_2->Clone("hmult_SN_2");
      hmult_SN_3_sum = (TH1F*)hmult_SN_3->Clone("hmult_SN_3");
      hmult_SN_4_sum = (TH1F*)hmult_SN_4->Clone("hmult_SN_4");
      hmult_SN_5_sum = (TH1F*)hmult_SN_5->Clone("hmult_SN_5");
      hmult_SN_6_sum = (TH1F*)hmult_SN_6->Clone("hmult_SN_6");
      hmult_ADC_1_sum = (TH1F*)hmult_ADC_1->Clone("hmult_ADC_1");
      hmult_ADC_2_sum = (TH1F*)hmult_ADC_2->Clone("hmult_ADC_2");
      hmult_ADC_3_sum = (TH1F*)hmult_ADC_3->Clone("hmult_ADC_3");
      hmult_ADC_4_sum = (TH1F*)hmult_ADC_4->Clone("hmult_ADC_4");
      hmult_ADC_5_sum = (TH1F*)hmult_ADC_5->Clone("hmult_ADC_5");
      hmult_ADC_6_sum = (TH1F*)hmult_ADC_6->Clone("hmult_ADC_6");
      hmult_ADC_7_sum = (TH1F*)hmult_ADC_7->Clone("hmult_ADC_7");
      hmult_ADC_8_sum = (TH1F*)hmult_ADC_8->Clone("hmult_ADC_8");
      hmult_ADC_9_sum = (TH1F*)hmult_ADC_9->Clone("hmult_ADC_9");
      hmult_ADC_10_sum = (TH1F*)hmult_ADC_10->Clone("hmult_ADC_10");
      hmult_ADC_15_sum = (TH1F*)hmult_ADC_15->Clone("hmult_ADC_15");
      hmult_ADC_20_sum = (TH1F*)hmult_ADC_20->Clone("hmult_ADC_20");
      hmult_ADC_25_sum = (TH1F*)hmult_ADC_25->Clone("hmult_ADC_25");
      hmult_ADC_30_sum = (TH1F*)hmult_ADC_30->Clone("hmult_ADC_30");
      hmult_ADC_40_sum = (TH1F*)hmult_ADC_40->Clone("hmult_ADC_40");

      hGOODCharge_Seed_over_total_sum = (TH1F*)hGOODCharge_Seed_over_total->Clone("hGOODCharge_Seed_over_total");
      hGOODCharge_Crown1_over_total_sum = (TH1F*)hGOODCharge_Crown1_over_total->Clone("hGOODCharge_Crown1_over_total");
      hGOODCharge_Crown2_over_total_sum = (TH1F*)hGOODCharge_Crown2_over_total->Clone("hGOODCharge_Crown2_over_total");
      hGOODCharge_total_sum = (TH1F*)hGOODCharge_total->Clone("hGOODCharge_total");
      hGOODCharge_4neighbours_over_total_sum = (TH1F*)hGOODCharge_4neighbours_over_total->Clone("hGOODCharge_4neighbours_over_total");
      hqc1_sum = (TH1F*)hqc1->Clone("hqc1");
      hqc9_sum = (TH1F*)hqc9->Clone("hqc9");
      hqc25_sum = (TH1F*)hqc25->Clone("hqc25");
      hqcn_adc1_sum = (TH1F*)hqcn_adc1->Clone("hqcn_adc1");
      hqcn_adc9_sum = (TH1F*)hqcn_adc9->Clone("hqcn_adc9");
      hqcn_adc25_sum = (TH1F*)hqcn_adc25->Clone("hqcn_adc25");
    }else{
      hmult_SN_1_sum->Sumw2();
      hmult_SN_2_sum->Sumw2();
      hmult_SN_3_sum->Sumw2();
      hmult_SN_4_sum->Sumw2();
      hmult_SN_5_sum->Sumw2();
      hmult_SN_6_sum->Sumw2();
      hmult_ADC_1_sum->Sumw2();
      hmult_ADC_2_sum->Sumw2();
      hmult_ADC_3_sum->Sumw2();
      hmult_ADC_4_sum->Sumw2();
      hmult_ADC_5_sum->Sumw2();
      hmult_ADC_6_sum->Sumw2();
      hmult_ADC_7_sum->Sumw2();
      hmult_ADC_8_sum->Sumw2();
      hmult_ADC_9_sum->Sumw2();
      hmult_ADC_10_sum->Sumw2();
      hmult_ADC_15_sum->Sumw2();
      hmult_ADC_20_sum->Sumw2();
      hmult_ADC_25_sum->Sumw2();
      hmult_ADC_30_sum->Sumw2();
      hmult_ADC_40_sum->Sumw2();
      hGOODCharge_Seed_over_total_sum->Sumw2();
      hGOODCharge_Crown1_over_total_sum->Sumw2();
      hGOODCharge_Crown2_over_total_sum->Sumw2();
      hGOODCharge_total_sum->Sumw2();
      hGOODCharge_4neighbours_over_total_sum->Sumw2();
      hqc1_sum->Sumw2();
      hqc9_sum->Sumw2();
      hqc25_sum->Sumw2();
      hqcn_adc1_sum->Sumw2();
      hqcn_adc9_sum->Sumw2();
      hqcn_adc25_sum->Sumw2();

      hmult_SN_1_sum->Add(hmult_SN_1,1);
      hmult_SN_2_sum->Add(hmult_SN_2,1);
      hmult_SN_3_sum->Add(hmult_SN_3,1);
      hmult_SN_4_sum->Add(hmult_SN_4,1);
      hmult_SN_5_sum->Add(hmult_SN_5,1);
      hmult_SN_6_sum->Add(hmult_SN_6,1);
      hmult_ADC_1_sum->Add(hmult_ADC_1,1);
      hmult_ADC_2_sum->Add(hmult_ADC_2,1);
      hmult_ADC_3_sum->Add(hmult_ADC_3,1);
      hmult_ADC_4_sum->Add(hmult_ADC_4,1);
      hmult_ADC_5_sum->Add(hmult_ADC_5,1);
      hmult_ADC_6_sum->Add(hmult_ADC_6,1);
      hmult_ADC_7_sum->Add(hmult_ADC_7,1);
      hmult_ADC_8_sum->Add(hmult_ADC_8,1);
      hmult_ADC_9_sum->Add(hmult_ADC_9,1);
      hmult_ADC_10_sum->Add(hmult_ADC_10,1);
      hmult_ADC_15_sum->Add(hmult_ADC_15,1);
      hmult_ADC_20_sum->Add(hmult_ADC_20,1);
      hmult_ADC_25_sum->Add(hmult_ADC_25,1);
      hmult_ADC_30_sum->Add(hmult_ADC_30,1);
      hmult_ADC_40_sum->Add(hmult_ADC_40,1);
      hGOODCharge_Seed_over_total_sum->Add(hGOODCharge_Seed_over_total,1);
      hGOODCharge_Crown1_over_total_sum->Add(hGOODCharge_Crown1_over_total,1);
      hGOODCharge_Crown2_over_total_sum->Add(hGOODCharge_Crown2_over_total,1);
      hGOODCharge_total_sum->Add(hGOODCharge_total,1);
      hGOODCharge_4neighbours_over_total_sum->Add(hGOODCharge_4neighbours_over_total,1);
      hqc1_sum->Add(hqc1,1);
      hqc9_sum->Add(hqc9,1);
      hqc25_sum->Add(hqc25,1);
      hqcn_adc1_sum->Add(hqcn_adc1,1);
      hqcn_adc9_sum->Add(hqcn_adc9,1);
      hqcn_adc25_sum->Add(hqcn_adc25,1);
    }





  }


  //ffile->GetObject("ProfhGOODCharge_Charge_DiodePosition",hprof2i);



  //-----------------------------------------
 
  Float_t hYmax = 0.40;
  MainCanvas1->cd(1);
  integg = hmult_ADC_1_sum->Integral();
  if(integg!=0.0){hmult_ADC_1_sum->Scale(1/integg);}
  hmult_ADC_1_sum->SetLineColor(2);
  TPaveStats *statdigit1_1 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_1 == NULL){
    statdigit1_1 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_1->SetName("digitiser");
  }
  statdigit1_1->SetX1NDC(0.6);
  statdigit1_1->SetY1NDC(0.20);
  statdigit1_1->SetX2NDC(0.95);
  statdigit1_1->SetY2NDC(0.58);
  statdigit1_1->SetLineColor(1);
  hmult_ADC_1_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_1_sum->Draw("sames");
  MainCanvas1_1->Update();
  TPaveStats *statdata1_1 = (TPaveStats*)hmult_ADC_1_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_1->SetLineColor(2);
  statdata1_1->SetTextColor(2);
  statdata1_1->SetX1NDC(0.6);
  statdata1_1->SetY1NDC(0.60);
  statdata1_1->SetX2NDC(0.95);
  statdata1_1->SetY2NDC(0.98);
  statdata1_1->Draw();

  MainCanvas1->cd(2);
  integg = hmult_ADC_2_sum->Integral();
  if(integg!=0.0){hmult_ADC_2_sum->Scale(1/integg);}
  hmult_ADC_2_sum->SetLineColor(2);
  TPaveStats *statdigit1_2 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_2 == NULL){
    statdigit1_2 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_2->SetName("digitiser");
  }
  statdigit1_2->SetX1NDC(0.6);
  statdigit1_2->SetY1NDC(0.20);
  statdigit1_2->SetX2NDC(0.95);
  statdigit1_2->SetY2NDC(0.58);
  statdigit1_2->SetLineColor(1);
  hmult_ADC_2_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_2_sum->Draw("sames");
  MainCanvas1_2->Update();
  TPaveStats *statdata1_2 = (TPaveStats*)hmult_ADC_2_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_2->SetLineColor(2);
  statdata1_2->SetTextColor(2);
  statdata1_2->SetX1NDC(0.6);
  statdata1_2->SetY1NDC(0.60);
  statdata1_2->SetX2NDC(0.95);
  statdata1_2->SetY2NDC(0.98);
  statdata1_2->Draw();

  MainCanvas1->cd(3);
  integg = hmult_ADC_3_sum->Integral();
  if(integg!=0.0){hmult_ADC_3_sum->Scale(1/integg);}
  hmult_ADC_3_sum->SetLineColor(2);
  TPaveStats *statdigit1_3 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_3 == NULL){
    statdigit1_3 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_3->SetName("digitiser");
  }
  statdigit1_3->SetX1NDC(0.6);
  statdigit1_3->SetY1NDC(0.20);
  statdigit1_3->SetX2NDC(0.95);
  statdigit1_3->SetY2NDC(0.58);
  statdigit1_3->SetLineColor(1);
  hmult_ADC_3_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_3_sum->Draw("sames");
  MainCanvas1_3->Update();
  TPaveStats *statdata1_3 = (TPaveStats*)hmult_ADC_3_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_3->SetLineColor(2);
  statdata1_3->SetTextColor(2);
  statdata1_3->SetX1NDC(0.6);
  statdata1_3->SetY1NDC(0.60);
  statdata1_3->SetX2NDC(0.95);
  statdata1_3->SetY2NDC(0.98);
  statdata1_3->Draw();

  MainCanvas1->cd(4);
  integg = hmult_ADC_4_sum->Integral();
  if(integg!=0.0){hmult_ADC_4_sum->Scale(1/integg);}
  hmult_ADC_4_sum->SetLineColor(2);
  TPaveStats *statdigit1_4 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_4 == NULL){
    statdigit1_4 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_4->SetName("digitiser");
  }
  statdigit1_4->SetX1NDC(0.6);
  statdigit1_4->SetY1NDC(0.20);
  statdigit1_4->SetX2NDC(0.95);
  statdigit1_4->SetY2NDC(0.58);
  statdigit1_4->SetLineColor(1);
  hmult_ADC_4_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_4_sum->Draw("sames");
  MainCanvas1_4->Update();
  TPaveStats *statdata1_4 = (TPaveStats*)hmult_ADC_4_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_4->SetLineColor(2);
  statdata1_4->SetTextColor(2);
  statdata1_4->SetX1NDC(0.6);
  statdata1_4->SetY1NDC(0.60);
  statdata1_4->SetX2NDC(0.95);
  statdata1_4->SetY2NDC(0.98);
  statdata1_4->Draw();

  MainCanvas1->cd(5);
  integg = hmult_ADC_5_sum->Integral();
  if(integg!=0.0){hmult_ADC_5_sum->Scale(1/integg);}
  hmult_ADC_5_sum->SetLineColor(2);
  TPaveStats *statdigit1_5 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_5 == NULL){
    statdigit1_5 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_5->SetName("digitiser");
  }
  statdigit1_5->SetX1NDC(0.6);
  statdigit1_5->SetY1NDC(0.20);
  statdigit1_5->SetX2NDC(0.95);
  statdigit1_5->SetY2NDC(0.58);
  statdigit1_5->SetLineColor(1);
  hmult_ADC_5_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_5_sum->Draw("sames");
  MainCanvas1_5->Update();
  TPaveStats *statdata1_5 = (TPaveStats*)hmult_ADC_5_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_5->SetLineColor(2);
  statdata1_5->SetTextColor(2);
  statdata1_5->SetX1NDC(0.6);
  statdata1_5->SetY1NDC(0.60);
  statdata1_5->SetX2NDC(0.95);
  statdata1_5->SetY2NDC(0.98);
  statdata1_5->Draw();

  MainCanvas1->cd(6);
  integg = hmult_ADC_6_sum->Integral();
  if(integg!=0.0){hmult_ADC_6_sum->Scale(1/integg);}
  hmult_ADC_6_sum->SetLineColor(2);
  TPaveStats *statdigit1_6 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_6 == NULL){
    statdigit1_6 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_6->SetName("digitiser");
  }
  statdigit1_6->SetX1NDC(0.6);
  statdigit1_6->SetY1NDC(0.20);
  statdigit1_6->SetX2NDC(0.95);
  statdigit1_6->SetY2NDC(0.58);
  statdigit1_6->SetLineColor(1);
  hmult_ADC_6_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_6_sum->Draw("sames");
  MainCanvas1_6->Update();
  TPaveStats *statdata1_6 = (TPaveStats*)hmult_ADC_6_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_6->SetLineColor(2);
  statdata1_6->SetTextColor(2);
  statdata1_6->SetX1NDC(0.6);
  statdata1_6->SetY1NDC(0.60);
  statdata1_6->SetX2NDC(0.95);
  statdata1_6->SetY2NDC(0.98);
  statdata1_6->Draw();

  MainCanvas1->cd(7);
  integg = hmult_ADC_7_sum->Integral();
  if(integg!=0.0){hmult_ADC_7_sum->Scale(1/integg);}
  hmult_ADC_7_sum->SetLineColor(2);
  TPaveStats *statdigit1_7 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_7 == NULL){
    statdigit1_7 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_7->SetName("digitiser");
  }
  statdigit1_7->SetX1NDC(0.6);
  statdigit1_7->SetY1NDC(0.20);
  statdigit1_7->SetX2NDC(0.95);
  statdigit1_7->SetY2NDC(0.58);
  statdigit1_7->SetLineColor(1);
  hmult_ADC_7_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_7_sum->Draw("sames");
  MainCanvas1_7->Update();
  TPaveStats *statdata1_7 = (TPaveStats*)hmult_ADC_7_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_7->SetLineColor(2);
  statdata1_7->SetTextColor(2);
  statdata1_7->SetX1NDC(0.6);
  statdata1_7->SetY1NDC(0.60);
  statdata1_7->SetX2NDC(0.95);
  statdata1_7->SetY2NDC(0.98);
  statdata1_7->Draw();

  MainCanvas1->cd(8);
  integg = hmult_ADC_8_sum->Integral();
  if(integg!=0.0){hmult_ADC_8_sum->Scale(1/integg);}
  hmult_ADC_8_sum->SetLineColor(2);
  TPaveStats *statdigit1_8 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_8 == NULL){
    statdigit1_8 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_8->SetName("digitiser");
  }
  statdigit1_8->SetX1NDC(0.6);
  statdigit1_8->SetY1NDC(0.20);
  statdigit1_8->SetX2NDC(0.95);
  statdigit1_8->SetY2NDC(0.58);
  statdigit1_8->SetLineColor(1);
  hmult_ADC_8_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_8_sum->Draw("sames");
  MainCanvas1_8->Update();
  TPaveStats *statdata1_8 = (TPaveStats*)hmult_ADC_8_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_8->SetLineColor(2);
  statdata1_8->SetTextColor(2);
  statdata1_8->SetX1NDC(0.6);
  statdata1_8->SetY1NDC(0.60);
  statdata1_8->SetX2NDC(0.95);
  statdata1_8->SetY2NDC(0.98);
  statdata1_8->Draw();

  MainCanvas1->cd(9);
  integg = hmult_ADC_9_sum->Integral();
  if(integg!=0.0){hmult_ADC_9_sum->Scale(1/integg);}
  hmult_ADC_9_sum->SetLineColor(2);
  TPaveStats *statdigit1_9 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_9 == NULL){
    statdigit1_9 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_9->SetName("digitiser");
  }
  statdigit1_9->SetX1NDC(0.6);
  statdigit1_9->SetY1NDC(0.20);
  statdigit1_9->SetX2NDC(0.95);
  statdigit1_9->SetY2NDC(0.58);
  statdigit1_9->SetLineColor(1);
  hmult_ADC_9_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_9_sum->Draw("sames");
  MainCanvas1_9->Update();
  TPaveStats *statdata1_9 = (TPaveStats*)hmult_ADC_9_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_9->SetLineColor(2);
  statdata1_9->SetTextColor(2);
  statdata1_9->SetX1NDC(0.6);
  statdata1_9->SetY1NDC(0.60);
  statdata1_9->SetX2NDC(0.95);
  statdata1_9->SetY2NDC(0.98);
  statdata1_9->Draw();

  MainCanvas1->cd(10);
  integg = hmult_ADC_10_sum->Integral();
  if(integg!=0.0){hmult_ADC_10_sum->Scale(1/integg);}
  hmult_ADC_10_sum->SetLineColor(2);
  TPaveStats *statdigit1_10 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_10 == NULL){
    statdigit1_10 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_10->SetName("digitiser");
  }
  statdigit1_10->SetX1NDC(0.6);
  statdigit1_10->SetY1NDC(0.20);
  statdigit1_10->SetX2NDC(0.95);
  statdigit1_10->SetY2NDC(0.58);
  statdigit1_10->SetLineColor(1);
  hmult_ADC_10_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_10_sum->Draw("sames");
  MainCanvas1_10->Update();
  TPaveStats *statdata1_10 = (TPaveStats*)hmult_ADC_10_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_10->SetLineColor(2);
  statdata1_10->SetTextColor(2);
  statdata1_10->SetX1NDC(0.6);
  statdata1_10->SetY1NDC(0.60);
  statdata1_10->SetX2NDC(0.95);
  statdata1_10->SetY2NDC(0.98);
  statdata1_10->Draw();

  MainCanvas1->cd(11);
  integg = hmult_ADC_15_sum->Integral();
  if(integg!=0.0){hmult_ADC_15_sum->Scale(1/integg);}
  hmult_ADC_15_sum->SetLineColor(2);
  TPaveStats *statdigit1_15 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_15 == NULL){
    statdigit1_15 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_15->SetName("digitiser");
  }
  statdigit1_15->SetX1NDC(0.6);
  statdigit1_15->SetY1NDC(0.20);
  statdigit1_15->SetX2NDC(0.95);
  statdigit1_15->SetY2NDC(0.58);
  statdigit1_15->SetLineColor(1);
  hmult_ADC_15_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_15_sum->Draw("sames");
  MainCanvas1_11->Update();
  TPaveStats *statdata1_15 = (TPaveStats*)hmult_ADC_15_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_15->SetLineColor(2);
  statdata1_15->SetTextColor(2);
  statdata1_15->SetX1NDC(0.6);
  statdata1_15->SetY1NDC(0.60);
  statdata1_15->SetX2NDC(0.95);
  statdata1_15->SetY2NDC(0.98);
  statdata1_15->Draw();

  MainCanvas1->cd(12);
  integg = hmult_ADC_20_sum->Integral();
  if(integg!=0.0){hmult_ADC_20_sum->Scale(1/integg);}
  hmult_ADC_20_sum->SetLineColor(2);
  TPaveStats *statdigit1_20 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_20 == NULL){
    statdigit1_20 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_20->SetName("digitiser");
  }
  statdigit1_20->SetX1NDC(0.6);
  statdigit1_20->SetY1NDC(0.20);
  statdigit1_20->SetX2NDC(0.95);
  statdigit1_20->SetY2NDC(0.58);
  statdigit1_20->SetLineColor(1);
  hmult_ADC_20_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_20_sum->Draw("sames");
  MainCanvas1_12->Update();
  TPaveStats *statdata1_20 = (TPaveStats*)hmult_ADC_20_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_20->SetLineColor(2);
  statdata1_20->SetTextColor(2);
  statdata1_20->SetX1NDC(0.6);
  statdata1_20->SetY1NDC(0.60);
  statdata1_20->SetX2NDC(0.95);
  statdata1_20->SetY2NDC(0.98);
  statdata1_20->Draw();

  MainCanvas1->cd(13);
  integg = hmult_ADC_25_sum->Integral();
  if(integg!=0.0){hmult_ADC_25_sum->Scale(1/integg);}
  hmult_ADC_25_sum->SetLineColor(2);
  TPaveStats *statdigit1_25 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_25 == NULL){
    statdigit1_25 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_25->SetName("digitiser");
  }
  statdigit1_25->SetX1NDC(0.6);
  statdigit1_25->SetY1NDC(0.20);
  statdigit1_25->SetX2NDC(0.95);
  statdigit1_25->SetY2NDC(0.58);
  statdigit1_25->SetLineColor(1);
  hmult_ADC_25_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_25_sum->Draw("sames");
  MainCanvas1_13->Update();
  TPaveStats *statdata1_25 = (TPaveStats*)hmult_ADC_25_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_25->SetLineColor(2);
  statdata1_25->SetTextColor(2);
  statdata1_25->SetX1NDC(0.6);
  statdata1_25->SetY1NDC(0.60);
  statdata1_25->SetX2NDC(0.95);
  statdata1_25->SetY2NDC(0.98);
  statdata1_25->Draw();

  MainCanvas1->cd(14);
  integg = hmult_ADC_30_sum->Integral();
  if(integg!=0.0){hmult_ADC_30_sum->Scale(1/integg);}
  hmult_ADC_30_sum->SetLineColor(2);
  TPaveStats *statdigit1_30 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_30 == NULL){
    statdigit1_30 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_30->SetName("digitiser");
  }
  statdigit1_30->SetX1NDC(0.6);
  statdigit1_30->SetY1NDC(0.20);
  statdigit1_30->SetX2NDC(0.95);
  statdigit1_30->SetY2NDC(0.58);
  statdigit1_30->SetLineColor(1);
  hmult_ADC_30_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_30_sum->Draw("sames");
  MainCanvas1_14->Update();
  TPaveStats *statdata1_30 = (TPaveStats*)hmult_ADC_30_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_30->SetLineColor(2);
  statdata1_30->SetTextColor(2);
  statdata1_30->SetX1NDC(0.6);
  statdata1_30->SetY1NDC(0.60);
  statdata1_30->SetX2NDC(0.95);
  statdata1_30->SetY2NDC(0.98);
  statdata1_30->Draw();

  MainCanvas1->cd(15);
  integg = hmult_ADC_40_sum->Integral();
  if(integg!=0.0){hmult_ADC_40_sum->Scale(1/integg);}
  hmult_ADC_40_sum->SetLineColor(2);
  TPaveStats *statdigit1_40 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit1_40 == NULL){
    statdigit1_40 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit1_40->SetName("digitiser");
  }
  statdigit1_40->SetX1NDC(0.6);
  statdigit1_40->SetY1NDC(0.20);
  statdigit1_40->SetX2NDC(0.95);
  statdigit1_40->SetY2NDC(0.58);
  statdigit1_40->SetLineColor(1);
  hmult_ADC_40_sum->SetAxisRange(0,hYmax,"Y");
  hmult_ADC_40_sum->Draw("sames");
  MainCanvas1_15->Update();
  TPaveStats *statdata1_40 = (TPaveStats*)hmult_ADC_40_sum->GetListOfFunctions()->FindObject("stats");
  statdata1_40->SetLineColor(2);
  statdata1_40->SetTextColor(2);
  statdata1_40->SetX1NDC(0.6);
  statdata1_40->SetY1NDC(0.60);
  statdata1_40->SetX2NDC(0.95);
  statdata1_40->SetY2NDC(0.98);
  statdata1_40->Draw();


  //-----------------------------------------
  MainCanvas2->cd(1);
  hqcn_adc1_sum->Sumw2();
  Float_t integ1 = hqcn_adc1_sum->Integral();
  if(integ1!=0.0){hqcn_adc1_sum->Scale(1/integ1);}
  hqcn_adc1_sum->SetLineColor(2);
  MainCanvas2->cd(1);
  TPaveStats *statdigit = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit == NULL){
    statdigit = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit->SetName("digitiser");
  }
  //digit->SetTitle("digitiser");
  statdigit->SetX1NDC(0.5);
  statdigit->SetY1NDC(0.20);
  statdigit->SetX2NDC(0.95);
  statdigit->SetY2NDC(0.58);
  statdigit->SetLineColor(1);

  hqcn_adc1_sum->Draw("sames");
  hqcn_adc1_sum->Fit("landau","","same");
  hqcn_adc1_sum->GetFunction("landau")->SetLineColor(2);
  hqcn_adc1_sum->GetFunction("landau")->SetLineStyle(2);
  MainCanvas2_1->Update();
  TPaveStats *statdata = (TPaveStats*)hqcn_adc1_sum->GetListOfFunctions()->FindObject("stats");

  /*  
      if(statdata == NULL){
      statdata = (TPaveStats*)hqcn_adc1->GetListOfFunctions()->FindObject("data");
      cout<<" statdat is == null "<<endl;
      }else{
      statdata->SetName("data");
      cout<<" statdat is not null "<<endl;
      }
  */
  statdata->SetLineColor(2);
  statdata->SetTextColor(2);
  statdata->SetX1NDC(0.5);
  statdata->SetY1NDC(0.60);
  statdata->SetX2NDC(0.95);
  statdata->SetY2NDC(0.98);
  statdata->Draw();

  //   TPaveStats *ptstats = new TPaveStats(0.5736991,0.2606809,0.9774417,0.6285014,"brNDC");
  //   ptstats = new TPaveStats(0.5769034,0.6567952,0.9774417,0.9963218,"brNDC");
  //TPaveText TPaveText(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Option_t* option = "br")
  //PaveStats TPaveStats(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Option_t* option = "br")

  //hqcn_adc1->GetFunction("landau")->Draw("same");



  //-----------------------------------------

  MainCanvas2->cd(2);
  hqcn_adc25_sum->Sumw2();
  Float_t integ2 = hqcn_adc25_sum->Integral();
  if(integ2!=0.0){hqcn_adc25_sum->Scale(1/integ2);}
  hqcn_adc25_sum->SetLineColor(2);
  MainCanvas2->cd(2);
  
  TPaveStats *statdigit2 = (TPaveStats*)gPad->GetPrimitive("stats");
  if(statdigit2 == NULL){
    statdigit2 = (TPaveStats*)gPad->GetPrimitive("digitiser");
  }else{
    statdigit2->SetName("digitiser");
  }
  statdigit2->SetX1NDC(0.5);
  statdigit2->SetY1NDC(0.20);
  statdigit2->SetX2NDC(0.95);
  statdigit2->SetY2NDC(0.58);
  statdigit2->SetLineColor(1);

  /// Float_t integ2 = hqcn_adc25->Integral();
    // if(integ2!=0.0){hqcn_adc25->Scale(1/integ2);}
    //  hqcn_adc25->SetLineColor(2);
    // MainCanvas2->cd(2);

    hqcn_adc25_sum->Draw("sames");
    hqcn_adc25_sum->Fit("landau","","same");
    hqcn_adc25_sum->GetFunction("landau")->SetLineColor(2);
    hqcn_adc25_sum->GetFunction("landau")->SetLineStyle(2);
    MainCanvas2_2->Update();
    //hqcn_adc25->GetFunction("landau")->Draw("same");
    TPaveStats *statdata2 = (TPaveStats*)hqcn_adc25_sum->GetListOfFunctions()->FindObject("stats");
    statdata2->SetLineColor(2);
    statdata2->SetTextColor(2);
    statdata2->SetX1NDC(0.5);
    statdata2->SetY1NDC(0.60);
    statdata2->SetX2NDC(0.95);
    statdata2->SetY2NDC(0.98);
    statdata2->Draw();

 

    //-----------------------------------------
    MainCanvas3->cd(5);
    integg = hGOODCharge_Seed_over_total_sum->Integral();
    if(integg!=0.0){hGOODCharge_Seed_over_total_sum->Scale(1/integg);}
    hGOODCharge_Seed_over_total_sum->SetLineColor(2);
    TPaveStats *statdigit3_1 = (TPaveStats*)gPad->GetPrimitive("stats");
    if(statdigit3_1 == NULL){
      statdigit3_1 = (TPaveStats*)gPad->GetPrimitive("digitiser");
    }else{
      statdigit3_1->SetName("digitiser");
    }
    statdigit3_1->SetX1NDC(0.6);
    statdigit3_1->SetY1NDC(0.20);
    statdigit3_1->SetX2NDC(0.95);
    statdigit3_1->SetY2NDC(0.58);
    statdigit3_1->SetLineColor(1);
    hGOODCharge_Seed_over_total_sum->SetAxisRange(0,0.3,"Y");
    hGOODCharge_Seed_over_total_sum->Draw("sames");
    MainCanvas3_1->Update();
    TPaveStats *statdata3_1 = (TPaveStats*)hGOODCharge_Seed_over_total_sum->GetListOfFunctions()->FindObject("stats");
    statdata3_1->SetLineColor(2);
    statdata3_1->SetTextColor(2);
    statdata3_1->SetX1NDC(0.6);
    statdata3_1->SetY1NDC(0.60);
    statdata3_1->SetX2NDC(0.95);
    statdata3_1->SetY2NDC(0.98);
    statdata3_1->Draw();

    MainCanvas3->cd(6);
    integg = hGOODCharge_Crown1_over_total_sum->Integral();
    if(integg!=0.0){hGOODCharge_Crown1_over_total_sum->Scale(1/integg);}
    hGOODCharge_Crown1_over_total_sum->SetLineColor(2);
    TPaveStats *statdigit3_2 = (TPaveStats*)gPad->GetPrimitive("stats");
    if(statdigit3_2 == NULL){
      statdigit3_2 = (TPaveStats*)gPad->GetPrimitive("digitiser");
    }else{
      statdigit3_2->SetName("digitiser");
    }
    statdigit3_2->SetX1NDC(0.6);
    statdigit3_2->SetY1NDC(0.20);
    statdigit3_2->SetX2NDC(0.95);
    statdigit3_2->SetY2NDC(0.58);
    statdigit3_2->SetLineColor(1);
    hGOODCharge_Crown1_over_total_sum->SetAxisRange(0,0.3,"Y");
    hGOODCharge_Crown1_over_total_sum->Draw("sames");
    MainCanvas3_2->Update();
    TPaveStats *statdata3_2 = (TPaveStats*)hGOODCharge_Crown1_over_total_sum->GetListOfFunctions()->FindObject("stats");
    statdata3_2->SetLineColor(2);
    statdata3_2->SetTextColor(2);
    statdata3_2->SetX1NDC(0.6);
    statdata3_2->SetY1NDC(0.60);
    statdata3_2->SetX2NDC(0.95);
    statdata3_2->SetY2NDC(0.98);
    statdata3_2->Draw();

    MainCanvas3->cd(7);
    integg = hGOODCharge_Crown2_over_total_sum->Integral();
    if(integg!=0.0){hGOODCharge_Crown2_over_total_sum->Scale(1/integg);}
    hGOODCharge_Crown2_over_total_sum->SetLineColor(2);
    TPaveStats *statdigit3_3 = (TPaveStats*)gPad->GetPrimitive("stats");
    if(statdigit3_3 == NULL){
      statdigit3_3 = (TPaveStats*)gPad->GetPrimitive("digitiser");
    }else{
      statdigit3_3->SetName("digitiser");
    }
    statdigit3_3->SetX1NDC(0.6);
    statdigit3_3->SetY1NDC(0.20);
    statdigit3_3->SetX2NDC(0.95);
    statdigit3_3->SetY2NDC(0.58);
    statdigit3_3->SetLineColor(1);
    hGOODCharge_Crown2_over_total_sum->SetAxisRange(0,0.3,"Y");
    hGOODCharge_Crown2_over_total_sum->Draw("sames");
    MainCanvas3_3->Update();
    TPaveStats *statdata3_3 = (TPaveStats*)hGOODCharge_Crown2_over_total_sum->GetListOfFunctions()->FindObject("stats");
    statdata3_3->SetLineColor(2);
    statdata3_3->SetTextColor(2);
    statdata3_3->SetX1NDC(0.6);
    statdata3_3->SetY1NDC(0.60);
    statdata3_3->SetX2NDC(0.95);
    statdata3_3->SetY2NDC(0.98);
    statdata3_3->Draw();

    MainCanvas3->cd(8);
    integg = hGOODCharge_4neighbours_over_total_sum->Integral();
    if(integg!=0.0){hGOODCharge_4neighbours_over_total_sum->Scale(1/integg);}
    hGOODCharge_4neighbours_over_total_sum->SetLineColor(2);
    TPaveStats *statdigit3_4 = (TPaveStats*)gPad->GetPrimitive("stats");
    if(statdigit3_4 == NULL){
      statdigit3_4 = (TPaveStats*)gPad->GetPrimitive("digitiser");
    }else{
      statdigit3_4->SetName("digitiser");
    }
    statdigit3_4->SetX1NDC(0.6);
    statdigit3_4->SetY1NDC(0.20);
    statdigit3_4->SetX2NDC(0.95);
    statdigit3_4->SetY2NDC(0.58);
    statdigit3_4->SetLineColor(1);
    hGOODCharge_4neighbours_over_total_sum->SetAxisRange(0,0.3,"Y");
    hGOODCharge_4neighbours_over_total_sum->Draw("sames");
    MainCanvas3_4->Update();
    TPaveStats *statdata3_4 = (TPaveStats*)hGOODCharge_4neighbours_over_total_sum->GetListOfFunctions()->FindObject("stats");
    statdata3_4->SetLineColor(2);
    statdata3_4->SetTextColor(2);
    statdata3_4->SetX1NDC(0.6);
    statdata3_4->SetY1NDC(0.60);
    statdata3_4->SetX2NDC(0.95);
    statdata3_4->SetY2NDC(0.98);
    statdata3_4->Draw();

  
    MainCanvas3->cd(4);
    TPaveStats *statdigit3_5 = (TPaveStats*)gPad->GetPrimitive("stats");
    if(statdigit3_5 == NULL){
      statdigit3_5 = (TPaveStats*)gPad->GetPrimitive("digitiser");
    }else{
      statdigit3_5->SetName("digitiser");
    }
    statdigit3_5->SetX1NDC(0.6);
    statdigit3_5->SetY1NDC(0.20);
    statdigit3_5->SetX2NDC(0.95);
    statdigit3_5->SetY2NDC(0.58);
    statdigit3_5->SetLineColor(1);
    //hGOODCharge_4neighbours_over_total->SetAxisRange(0,0.3,"Y");
    hprof2i->SetMarkerColor(2);
    hprof2i->SetLineColor(2);
    hprof2i->Draw("sames");
    MainCanvas3_5->Update();
    TPaveStats *statdata3_5 = (TPaveStats*)hprof2i->GetListOfFunctions()->FindObject("stats");
    statdata3_5->SetLineColor(2);
    statdata3_5->SetTextColor(2);
    statdata3_5->SetX1NDC(0.6);
    statdata3_5->SetY1NDC(0.60);
    statdata3_5->SetX2NDC(0.95);
    statdata3_5->SetY2NDC(0.98);
    statdata3_5->Draw();

    MainCanvas3->cd(3);
    hGOODCharge_Charge_DiodeDistance->SetMarkerStyle(1);
    hGOODCharge_Charge_DiodeDistance->SetMarkerColor(2);
    hGOODCharge_Charge_DiodeDistance->SetLineColor(2);
    hGOODCharge_Charge_DiodeDistance->Draw("sames");





    Char_t HeaderSave[200];
 



    //----MimosaResolution
    //sprintf(HeaderSave,"resolution_%d_%d.gif",RunNumber,ThePlaneNumber);
    if(boolprint==true){
      sprintf(HeaderSave,"Mulitiplicity1_M22_pitch.gif");
      MainCanvas1->Print(HeaderSave,"gif");
      sprintf(HeaderSave,"Mulitiplicity1_M22_pitch.eps");
      MainCanvas1->Print(HeaderSave,"eps");
      sprintf(HeaderSave,"Mulitiplicity2_M22_pitch.gif");
      MainCanvas2->Print(HeaderSave,"gif");
      sprintf(HeaderSave,"Mulitiplicity2_M22_pitch.eps");
      MainCanvas2->Print(HeaderSave,"eps");
      sprintf(HeaderSave,"Mulitiplicity3_M22_pitch.gif");
      MainCanvas3->Print(HeaderSave,"gif");
      sprintf(HeaderSave,"Mulitiplicity3_M22_pitch.eps");
      MainCanvas3->Print(HeaderSave,"eps");
      sprintf(HeaderSave,"Mulitiplicity4_M22_pitch.gif");
      MainCanvas4->Print(HeaderSave,"gif");
      sprintf(HeaderSave,"Mulitiplicity4_M22_pitch.eps");
      MainCanvas4->Print(HeaderSave,"eps");
    }


}

/*
  TH1F *hGOODCharge_Seed_over_total;
  TH1F *hGOODCharge_Crown1_over_total;
  TH1F *hGOODCharge_Crown2_over_total;
  TH1F *hGOODCharge_4neighbours_over_total;
  TH1F *hGOODCharge_4highestneighbours_over_total;
*/
  
/*

MainCanvas2->cd(1);
Float_t integ1 = hqcn_adc1->Integral();
if(integ1!=0.0){hqcn_adc1->Scale(1/integ1);}
hqcn_adc1->SetLineColor(2);
//gStyle->SetLineColor(2);
//gStyle->SetLineStyle(2);
//hqcn_adc1->Draw();
//hqcn_adc1->Fit("landau","R+","same");
MainCanvas2->cd(1);
hqcn_adc1->Draw("sames");
hqcn_adc1->Fit("landau","","same");
hqcn_adc1->GetFunction("landau")->SetLineColor(2);
hqcn_adc1->GetFunction("landau")->SetLineStyle(2);
//hqcn_adc1->GetFunction("landau")->Draw("same");
*/

