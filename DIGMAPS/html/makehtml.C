{
  // clean
  //.x makehtml.C
  gROOT->ProcessLine(".L ../code/digaction.cxx+");
  gROOT->ProcessLine(".L ../code/digadc.cxx+");
  gROOT->ProcessLine(".L ../code/digbeam.cxx+");
  gROOT->ProcessLine(".L ../code/digplane.cxx+");
  gROOT->ProcessLine(".L ../code/digtransport.cxx+");
  gROOT->ProcessLine(".L ../code/digparticle.cxx+"); 
  gROOT->ProcessLine(".L ../code/digreadoutmap.cxx+");
  gROOT->ProcessLine(".L ../code/digcluster.cxx+");
  gROOT->ProcessLine(".L ../code/digevent.cxx+"); 
  gROOT->ProcessLine(".L ../code/diginitialize.cxx+");
  gROOT->ProcessLine(".L ../code/dighistograms.cxx+");
  //gROOT->ProcessLine(".L ../code/digproto.cxx+");
  gROOT->ProcessLine(".L ../code/digmaps.cxx+");
  THtml html;
  //  html.SetOutputDir( "/rawcmos7/abesson/ILCSOFT/DIGITISEUR/html/" );
  //  html.SetSourceDir( "/rawcmos7/abesson/ILCSOFT/DIGITISEUR/code/" );
  html.SetOutputDir( "." );
  html.SetSourceDir( "../code/" );
  html.MakeIndex();
  html.MakeClass("DIGMAPS");
  html.MakeClass("DIGInitialize");
  html.MakeClass("DIGPlane");
  html.MakeClass("DIGADC");
  html.MakeClass("DIGBeam");
  html.MakeClass("DIGParticle");
  html.MakeClass("DIGAction");
  html.MakeClass("DIGEvent");
  html.MakeClass("DIGHistograms");
  html.MakeClass("DIGTransport");
  html.MakeClass("DIGMAPS");
  html.MakeClass("DIGReadoutmap");
  html.MakeClass("DIGCluster");
  //  html.MakeClass("DIGProto");


  //  html.MakeAll( kTRUE );


}

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

