/***************************************************************************
 *
 * $Id: $
 * $Log: $
 *
 **************************************************************************/
#ifndef StMcPxlHitCollection_hh
#define StMcPxlHitCollection_hh

#include "StMcPxlSectorHitCollection.hh"
class StMcPxlHit;

class StMcPxlHitCollection : public StObject {
public:

    StMcPxlHitCollection();
    virtual ~StMcPxlHitCollection();
    
    bool addHit(StMcPxlHit*);
    unsigned int numberOfHits() const;
    unsigned int  numberOfSectors() const;
    
    StMcPxlSectorHitCollection*       sector(unsigned int);
    const StMcPxlSectorHitCollection* sector(unsigned int) const;
protected:
    enum { mNumberOfSectors = 10 };
    StMcPxlSectorHitCollection mSectors[mNumberOfSectors];
    ClassDef(StMcPxlHitCollection,1)
};

inline unsigned int StMcPxlHitCollection::numberOfSectors() const {return mNumberOfSectors;}
#endif
