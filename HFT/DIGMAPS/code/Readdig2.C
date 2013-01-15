{
  gROOT->ProcessLine(".L digresult.cxx+");
  gROOT->ProcessLine(".L digaction.cxx+");
  gROOT->ProcessLine(".L digadc.cxx+");
  gROOT->ProcessLine(".L digbeam.cxx+");
  gROOT->ProcessLine(".L digplane.cxx+");
  gROOT->ProcessLine(".L digtransport.cxx+");
  gROOT->ProcessLine(".L digparticle.cxx+"); 
  gROOT->ProcessLine(".L digreadoutmap.cxx+");
  gROOT->ProcessLine(".L digcluster.cxx+");
  gROOT->ProcessLine(".L digevent.cxx+"); 
  gROOT->ProcessLine(".L diginitialize.cxx+"); 
  gROOT->ProcessLine(".L  dighistograms.cxx+");
  gROOT->ProcessLine(".L digmaps.cxx+");
  //  gROOT->ProcessLine(".L digproto.cxx+");

  //  DIGMAPS myDIGMAPS("nameDIGMAPS","titleDIGMAPS","/home/abesson/work/ILC/DIGITISEUR/code/","input.txt","/home/abesson/work/ILC/DIGITISEUR/code/","output.txt");
  // DIGMAPS myDIGMAPS("nameDIGMAPS","titleDIGMAPS","/var/autofs/nfs/rawcmos7/abesson/ILCSOFT/DIGITISEUR/code/","input.txt","/var/autofs/nfs/rawcmos7/abesson/ILCSOFT/DIGITISEUR/code/","output.txt");
  //DIGMAPS myDIGMAPS2("nameDIGMAPS","titleDIGMAPS","/var/autofs/nfs/rawcmos7/abesson/ILCSOFT/DIGITISEUR/code/","inputplot.txt","/var/autofs/nfs/rawcmos7/abesson/ILCSOFT/DIGITISEUR/code/","outputtree.txt","plot");
  //  DIGMAPS myDIGMAPS2("nameDIGMAPS","titleDIGMAPS","/var/autofs/nfs/rawcmos7/abesson/ILCSOFT/DIGITISEUR/code/","input.txt","/var/autofs/nfs/rawcmos7/abesson/ILCSOFT/DIGITISEUR/code/","outputtree.txt","plot");
  DIGMAPS myDIGMAPS2("nameDIGMAPS","titleDIGMAPS","./","inputdig2.txt","./","outputtreedig.txt","plot");




}


/*

  myDIGMAPS2.PrintConfigurations() ;
  myDIGMAPS2.PlotAConfiguration(3,1);

  Char_t  ResultFileName[150];

  sprintf(ResultFileName,"/rawcmos7/abesson/ILCSOFT/DIGITISEUR/data/run%dPl%d_ClCharge.root",9552,9);

  ffile = new TFile(ResultFileName,"READ");

  //ffile->GetObject("ProfhGOODCharge_Charge_DiodePosition",hprof2i);

  TH1F *hmult_SN_1;
  TH1F *hmult_SN_2;
  TH1F *hmult_SN_3;
  TH1F *hmult_SN_4;
  TH1F *hmult_SN_5;
  TH1F *hmult_SN_6;
  TH1F *hGOODCharge_Seed_over_total ;
  TH1F *hGOODCharge_Crown1_over_total ;
  TH1F *hGOODCharge_Crown2_over_total ;
  TH1F *hGOODCharge_total ;
  TH1F *hGOODCharge_4neighbours_over_total ;
  TH1F *hqc1;
  TH1F *hqc9;
  TH1F *hqc25;
  TH1F *hqcn1_adc;
  TH1F *hqcn9_adc;
  TH1F *hqcn25_adc;


  ffile->GetObject("hmult_SN_1",hmult_SN_1);
  ffile->GetObject("hmult_SN_2",hmult_SN_2);
  ffile->GetObject("hmult_SN_3",hmult_SN_3);
  ffile->GetObject("hmult_SN_4",hmult_SN_4);
  ffile->GetObject("hmult_SN_5",hmult_SN_5);
  ffile->GetObject("hmult_SN_6",hmult_SN_6);
  ffile->GetObject("hGOODCharge_Seed_over_total",hGOODCharge_Seed_over_total);
  ffile->GetObject("hGOODCharge_Crown1_over_total",hGOODCharge_Crown1_over_total);
  ffile->GetObject("hGOODCharge_Crown2_over_total",hGOODCharge_Crown2_over_total);
  ffile->GetObject("hGOODCharge_total",hGOODCharge_total);
  ffile->GetObject("hGOODCharge_4neighbours_over_total",hGOODCharge_4neighbours_over_total ); 
  ffile->GetObject("hqc1",hqc1);
  ffile->GetObject("hqc9",hqc9);
  ffile->GetObject("hqc25",hqc25);
*/
