#ifndef ST_MCANALYSISMAKER_H
#define ST_MCANALYSISMAKER_H

class TFile;
class TNtuple;

class StMcTrack;
class StTrack;
class StGlobalTrack;
class StAssociationMaker;
class StMcEvent;

#include "StMaker.h"


class StMcAnalysisMaker : public StMaker
{
  private:
    char* outfile;
    TFile* mFile;

    TNtuple* mTracks; //.. RC is a subset of MC

    StAssociationMaker* mAssoc;
    const StTrack* findPartner(StMcTrack*, int&);
    const StMcTrack* findPartner(StGlobalTrack*, int&);

    int fillTracks(StMcEvent*);

  public:
    StMcAnalysisMaker(char* in);

    int Init();
    int Make();
    int Finish();

  ClassDef(StMcAnalysisMaker, 1)
};

#endif
