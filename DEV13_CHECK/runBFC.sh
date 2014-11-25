#!/bin/sh
starver dev
#dev13, slow TPC, pixel tracking only
root4star -b -q 'bfc.C(1,5,"dev13,AgML,ITTF,Sti,tpcI,TpcRS,TpxRaw,TpxClu,pixFastSim,-ssdfast,VFMCE,McEvent,geant,IdTruth,fzin,StiRnd,PixelIT,IstIT,NoSvtIt,NoSsdIt,StiPulls,analysis,tags,clearmem,evout,McEvOut,MiniMcMk,McAna,MakeEvent","test_dev13_v2.fz") > log_slow' 

#dev13 , fast TPC, pixel tracking only
#root4star -b -q 'bfc.C(1,5,"dev13,AgML,ITTF,Sti,tpcI,TpcFastSim,pixFastSim,-ssdfast,VFMCE,McEvent,geant,IdTruth,fzin,StiRnd,PixelIT,IstIT,NoSvtIt,NoSsdIt,StiPulls,analysis,tags,clearmem,evout,McEvOut,MiniMcMk,McAna,MakeEvent","test_dev13_v2.fz") > log_fast '

