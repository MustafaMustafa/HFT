/***************************************************************************
 *
 * $Id: $
 * $Log: $
 *
 * Author: Fabrice Retiere/Kai Schweda,  Aug 2003
 * 
 ***************************************************************************
 *
 * Description: 
 *
 *
 ***************************************************************************
 *
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

/***************************************************************************
 *
 * $Id: StMcPixelLayerHitCollection.hh,v 2.5 2012/03/22 00:46:36 perev Exp $
 *
 * Author: Fabrice Retiere/Kai Schweda, Aug 2003
 ***************************************************************************
 *
 * Description: Monte Carlo Pixel Layer Hit Collection class from Kai
 *
 * The pixel detector hits are stored here.
 *
 ***************************************************************************
 *
 * $Log: StMcPixelLayerHitCollection.hh,v $
 * Revision 2.5  2012/03/22 00:46:36  perev
 * private => protected
 *
 * Revision 2.4  2012/03/01 16:48:29  perev
 * method Browse() added
 *
 * Revision 2.3  2009/07/24 19:08:08  perev
 * Cleanup + Btof added (Geurts)
 *
 * Revision 2.2  2005/01/27 23:40:47  calderon
 * Adding persistency to StMcEvent as a step for Virtual MonteCarlo.
 *
 * Revision 2.1  2003/08/20 18:50:21  calderon
 * Addition of Tof classes and Pixel classes.  Modified track, event, and
 * container code to reflect this.
 * Fix bug in StMcVertex and in clearing of some hit collections.
 *
 *
 *
 **************************************************************************/
