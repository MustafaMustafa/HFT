/***************************************************************************
 *
 * $Id: $
 * $Log: $
 *
 * Author: Manuel Calderon de la Barca Sanchez
 *
 *  ***************************************************************************
 *
 * Description: Monte Carlo PXL Hit Collection class
 *
 *  ***************************************************************************
 * 
 **************************************************************************/
#include "StMcPxlHitCollection.hh"
#include "StMcPxlHit.hh"

static const char rcsid[] = "$Id: $";

ClassImp(StMcPxlHitCollection)

StMcPxlHitCollection::StMcPxlHitCollection() { /* noop */ }

StMcPxlHitCollection::~StMcPxlHitCollection() { /* noop */ }
    
bool
StMcPxlHitCollection::addHit(StMcPxlHit* hit)
{
    unsigned int p;
    if (hit && (p = hit->sector()-1) < mNumberOfSectors) {
      mSectors[p].hits().push_back(hit);
      return true;
    }
    else
      return false;
}

unsigned int
StMcPxlHitCollection::numberOfSectors() const { return mNumberOfSectors; }

unsigned long
StMcPxlHitCollection::numberOfHits() const
{
    unsigned long sum = 0;
    for (int i=0; i<mNumberOfSectors; i++)
      sum += mSectors[i].numberOfHits();

    return sum;
}

StMcPxlSectorHitCollection*
StMcPxlHitCollection::sector(unsigned int i)
{
    if (i < mNumberOfSectors)
        return &(mSectors[i]);
    else
        return 0;
}

const StMcPxlSectorHitCollection*
StMcPxlHitCollection::sector(unsigned int i) const
{
    if (i < mNumberOfSectors)
        return &(mSectors[i]);
    else
        return 0;
}

/***************************************************************************
 *
 * $Id: StMcPixelHitCollection.cc,v 2.2 2005/07/06 21:47:45 calderon Exp $
 *
 * Author: Manuel Calderon de la Barca Sanchez, Oct 1999
 ***************************************************************************
 *
 * Description: Monte Carlo Pixel Hit Collection class
 *
 ***************************************************************************
 *
 * $Log: StMcPixelHitCollection.cc,v $
 * Revision 2.2  2005/07/06 21:47:45  calderon
 * remove old ifdef, now all classes are persistent.
 *
 * Revision 2.1  2003/08/20 18:50:21  calderon
 * Addition of Tof classes and Pixel classes.  Modified track, event, and
 * container code to reflect this.
 * Fix bug in StMcVertex and in clearing of some hit collections.
 *
 * Revision 2.1  1999/12/14 07:04:49  calderon
 * Numbering scheme as per SVT request.
 *
 * Revision 2.0  1999/11/17 02:00:59  calderon
 * Completely revised for new StEvent
 *
 *
 **************************************************************************/