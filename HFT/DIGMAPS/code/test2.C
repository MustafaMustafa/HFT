{
  myDIGMAPS2.PrintConfigurations() ;
  Bool_t boolprint=true;
  Char_t  ResultFileName[250];     
  sprintf(ResultFileName,"/rawcmos7/abesson/TAF/trunk/results_ana_M28/run28581Pl3_ClCharge.root");
  TFile* ffile =new TFile(ResultFileName,"read");
  TH1F *hnpix_c;
  ffile->GetObject("npix_c",hnpix_c);
  const Int_t Nruns = 9;
  TPaveStats *statdigit1_1[Nruns];
  TPaveStats *statdigit1_2[Nruns];
  TPaveStats *statdigit1_3[Nruns];
  TPaveStats *statdata1_1[Nruns];



  Int_t RunNumber[Nruns] = {28581,28580,28579,28568,28570,28606,28567,28569,28571};//  {28567,28568,28569,28570,28571,28579,28580,28581,28606};
  Float_t Threshold[Nruns] = {4.0,4.5,5.0,5.8,7.0,8.0,9.0,10.2,11.5};//  {9.0,5.8,10.2,7.0,11.5,5.0,4.5,4.0,8.0};
  Int_t Plane[Nruns] = {3,3,3,3,3,3,3,3,3};

  //hnpix_c->Draw();

  //  statdigit1_1[0] = (TPaveStats*)gPad->GetPrimitive("stats");
  //statdigit1_1[0]->SetName("digitiser");


  gStyle->SetOptStat("nemr");

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
    statdigit1_1[i]->SetY2NDC(0.38);
    statdigit1_1[i]->SetLineColor(1);
    statdigit1_1[i]->SetTextColor(1);
    statdigit1_1[i]->Draw();
  }
  }
  const int Nconfig2 = 9;
  Int_t configlist2[Nconfig2] = {56,59,62,65,68,71,74,77,80}; //11  
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
    statdigit1_2[i]->SetY1NDC(0.40);
    statdigit1_2[i]->SetX2NDC(0.95);
    statdigit1_2[i]->SetY2NDC(0.58);
    statdigit1_2[i]->SetLineColor(3); 
    statdigit1_2[i]->SetTextColor(3);
    statdigit1_2[i]->Draw();
  }
  }


  const int Nconfig3 = 9;
  Int_t configlist3[Nconfig3] = {83,86,89,92,95,98,101,104,107}; //11
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
    statdigit1_3[i]->SetY1NDC(0.60);
    statdigit1_3[i]->SetX2NDC(0.95);
    statdigit1_3[i]->SetY2NDC(0.78);
    statdigit1_3[i]->SetLineColor(4); 
    statdigit1_3[i]->SetTextColor(4);
    statdigit1_3[i]->Draw();
  }
  }


  for (Int_t i=0 ; i<Nruns ; i++){


    MainCanvas1->cd(i+1);
    //    TPad *subpad = (TPad*)gPad->GetPad(i+1)
    gPad->Update();
    MainCanvas1->Update();
    TPad *subpad = gPad;

    sprintf(ResultFileName,"/rawcmos7/abesson/TAF/trunk/results_ana_M28/run%dPl%d_ClCharge.root",RunNumber[i],Plane[i]);
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
    statdata1_1[i]->SetY2NDC(0.98);
    statdata1_1[i]->Draw();
    


  }





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
  }


}
