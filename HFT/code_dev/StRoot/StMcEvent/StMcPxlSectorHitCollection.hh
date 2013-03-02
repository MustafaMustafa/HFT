/***************************************************************************
 *
 * $Id: $
 * $Log: $
 *
 **************************************************************************/
#ifndef StMcPxlSectorHitCollection_hh
#define StMcPxlSectorHitCollection_hh

#include "StObject.h"
#include "StMcPxlLadderHitCollection.hh"


class StMcPxlSectorHitCollection : public StObject
{
public:
    StMcPxlSectorHitCollection();
    virtual ~StMcPxlSectorHitCollection();
    
    unsigned int numberOfHits() const;
    unsigned int numberOfLadders() const {return mNumberOfLadders;}

    StMcPxlLadderHitCollection*     ladder(unsigned int);
    const StMcPxlLadderHitCollection* ladder(unsigned int) const;

protected:
    enum { mNumberOfLadders = 4 };
    StMcPxlLadderHitCollection mLadders[mNumberOfLadders];

    ClassDef(StMcPxlSectorHitCollection,1)
};
#endif
