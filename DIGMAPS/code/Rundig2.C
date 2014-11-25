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
  //DIGMAPS myDIGMAPS2("nameDIGMAPS","titleDIGMAPS","/var/autofs/nfs/rawcmos7/abesson/ILCSOFT/DIGITISEUR/code/","inputplot.txt","/var/autofs/nfs/rawcmos7/abesson/ILCSOFT/DIGITISEUR/code/","output.txt");
  
  //  DIGMAPS myDIGMAPS("nameDIGMAPS","titleDIGMAPS","/var/autofs/nfs/rawcmos7/abesson/ILCSOFT/DIGITISEUR/code/","input.txt","/var/autofs/nfs/rawcmos7/abesson/ILCSOFT/DIGITISEUR/code/","output.txt","foresee");
  DIGMAPS myDIGMAPS("nameDIGMAPS","titleDIGMAPS","./","inputdig2.txt","./","outputdig.txt","foresee");


}
