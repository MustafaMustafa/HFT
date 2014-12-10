#include "TFile.h"
#include "TNtuple.h"

#include "StParticleDefinition.hh"
#include "StTrack.h"
#include "StPrimaryTrack.h"
#include "StTrackGeometry.h"
#include "StMcEvent/StMcEventTypes.hh"
#include "StMcEvent/StMcContainers.hh"
#include "SystemOfUnits.h"
#include "StEvent.h"
#include "StTrackNode.h"
#include "StGlobalTrack.h"
#include "StEvent/StTpcHit.h"

#include "StMcEvent.hh"
#include "StAssociationMaker/StAssociationMaker.h"
#include "StAssociationMaker/StTrackPairInfo.hh"
#include "StMcEvent/StMcTpcHit.hh"
#include "StMcAnalysisMaker.h"
#include "StMcTpcHitCollection.hh"

#include "StEvent/StEventTypes.h"
#include "StEventUtilities/StuRefMult.hh"
#include "StEvent/StEventSummary.h"
#include "StEvent/StBTofCollection.h"
#include "StEvent/StBTofHeader.h"
#include "StEvent/StEnumerations.h"
#include "StEvent/StTpcDedxPidAlgorithm.h"
#include "StarClassLibrary/StParticleTypes.hh"

#include "StDetectorDbMaker/StDetectorDbTriggerID.h"

ClassImp(StMcAnalysisMaker);

StMcAnalysisMaker::StMcAnalysisMaker(char* in)
{
    outfile = in;
    
    cout<<"StMcAnalysisMaker::StMcAnalysisMaker - DONE"<<endl;
}
//__________________________________
int StMcAnalysisMaker::Init()
{

    mFile = new TFile(outfile, "recreate");
    assert(mFile && !mFile->IsZombie());
        
    const char* varlist = "geantId:p:pt:svx:svy:svz:pgeantId:pp:ppt:phi:y:eta:peta:label:"
    "rp:rpt:reta:rphi:nfit:ncom:nmax:"
    "nDedxPts:dedx:dedx_2:nSigPi:nSigK:nSigP:nSigE:"
    "vx:vy:vz:";

    mTracks= new TNtuple("tracks", "tracks", varlist);

    mAssoc = (StAssociationMaker*)GetMaker("StAssociationMaker");

    cout<<"StMcAnalysisMaker::Init - DONE"<<endl;
    return StMaker::Init();
}

//__________________________________
int StMcAnalysisMaker::Make()
{
    cout<<"StMcAnalysisMaker::Make() - call"<<endl;
    StMcEvent* mcEvent = (StMcEvent*)GetDataSet("StMcEvent");
    
    if (!mcEvent) 
    {
        LOG_WARN << "No StMcEvent" << endm;
        return kStWarn;
    }

    StEvent* event = (StEvent*)GetDataSet("StEvent");
    if (!event) {
        LOG_WARN << "No StEvent" << endm;
        return kStWarn;
    }
    
    cout<<"StMcAnalysisMaker::Make() : event: "<<event->id()<<endl;


    for(rcTpcHitMapIter iter = mAssoc->rcTpcHitMap()->begin(); iter!=mAssoc->rcTpcHitMap()->end(); iter++)
    {
      // pair<const StTpcHit*, const StMcTpcHit*>& p = dynamic_cast< pair<const StTpcHit*,const StMcTpcHit*> >(*iter);
      cout<<(*iter).first->qaTruth()<<endl;
    }
    

    // fillTracks(mcEvent);

    return kStOk;
}
//____________________________________
int StMcAnalysisMaker::fillTracks(StMcEvent* mcEvent)
{
    StSPtrVecMcTrack& trks = mcEvent->tracks();
    cout<<"Filling "<<trks.size()<<" mcTracks..."<<endl;   
    
    for (unsigned int i = 0;  i<trks.size(); i++) 
    {
        StMcTrack* mcTrack = trks[i];
        // if(mcTrack->geantId()!=2 && mcTrack->geantId()!=3) continue;

        int ncommonhits = 0;
        const StTrack* rcTrack = findPartner(mcTrack, ncommonhits);
        if(!rcTrack) continue;

        StPtrVecHit rcTpcHits = rcTrack->detectorInfo()->hits(kTpcId);
        const StPtrVecMcHit* mcTpcHits = mcTrack->Hits(kTpcId);
        
        cout<<"ncommonhits "<<ncommonhits<<endl;
        cout<<"Rc track hits"<<endl;
        for(size_t ih = 0; ih <rcTpcHits.size(); ih++)
        {
          StTpcHit* rcHit = dynamic_cast<StTpcHit*>(rcTpcHits[ih]);
          if(!rcHit) continue;
          cout<<rcHit->qaTruth()<<endl;
        }

        cout<<"MC track hits"<<endl;
        for(size_t ih = 0; ih <mcTpcHits->size(); ih++)
        {
          StMcTpcHit* mcHit = dynamic_cast<StMcTpcHit*>((*mcTpcHits)[ih]);
          if(!mcHit) continue;
          cout<<mcHit->key()<<endl;
        }


    }

    return kStOk;
}


//________________________________________________
const StTrack* StMcAnalysisMaker::findPartner(StMcTrack* mcTrack, int& maxCommonTpcHits) 
{//..StMcTrack find partner from the StTracks
    if(!mAssoc) {
        cout<<" empty StAssociateMaker, stop!!"<<endl;
        exit(1);
    }
    pair<mcTrackMapIter, mcTrackMapIter> p = mAssoc->mcTrackMap()->equal_range(mcTrack);

    const StTrack* maxTrack = 0;
    maxCommonTpcHits = 0;
    for (mcTrackMapIter k = p.first; k != p.second; ++k) {
        int commonTpcHits = k->second->commonTpcHits();
        const StTrack* track = k->second->partnerTrack()->node()->track(global);//should be global
        if (track && commonTpcHits > maxCommonTpcHits) {
            maxTrack = track;
            maxCommonTpcHits = commonTpcHits;
        }
    }
    return maxTrack;
}


//________________________________________________
const StMcTrack* StMcAnalysisMaker::findPartner(StGlobalTrack* rcTrack, int& maxCommonTpcHits) 
{//.. StGlobalTracks find partner from StMcTracks. 
    //.. See example from StRoot/StMcAnalysisMaker

    if(!mAssoc) {
        cout<<" empty StAssociateMaker, stop!!"<<endl;
        exit(1);
    }

    pair<rcTrackMapIter,rcTrackMapIter> p = mAssoc->rcTrackMap()->equal_range(rcTrack);

    const StMcTrack* maxTrack = 0;
    maxCommonTpcHits = 0;
    for (rcTrackMapIter k = p.first; k != p.second; ++k) {
        int commonTpcHits = k->second->commonTpcHits();

        const StMcTrack* track = k->second->partnerMcTrack();

        if (track && commonTpcHits > maxCommonTpcHits) {
            maxTrack = track;
            maxCommonTpcHits = commonTpcHits;
        }
    }
    return maxTrack;
}
//______________________________________________________
int StMcAnalysisMaker::Finish()
{
    mFile->Write();
    mFile->Close();
    return kStOk;
}
