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
    unsigned int numberOfLadders() const;

    StMcPxlLadderHitCollection*     ladder(unsigned int);
    const StMcPxlLadderHitCollection* ladder(unsigned int) const;

protected:
    enum { kNumberOfLadders = 4 };
    StMcPxlLadderHitCollection mLadders[kNumberOfLadders];

    ClassDef(StMcPxlSectorHitCollection,1)
};

inline unsigned int StMcPxlSectorHitCollection::numberOfLadders() const {return kNumberOfLadders;}
#endif
