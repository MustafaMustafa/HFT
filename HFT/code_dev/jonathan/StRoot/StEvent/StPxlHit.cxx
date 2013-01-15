/*!
 * \class StRnDHit 
 * \author Mike Miller and Andrew Rose, Jan 2006
 */
/***************************************************************************
 *
 * $Id: StRnDHit.cxx,v 2.1 2006/01/19 21:42:06 ullrich Exp $
 *
 * Author: Mike Miller and Andrew Rose, Jan 2006
 ***************************************************************************
 *
 * Description:  This is an experimental class and not final yet
 *
 ***************************************************************************
 *
 * $Log: StRnDHit.cxx,v $
 * Revision 2.1  2006/01/19 21:42:06  ullrich
 * Initial Revision.
 *
 **************************************************************************/
#include "StPxlHit.h"

ClassImp(StPxlHit)

StMemoryPool StPxlHit::mPool(sizeof(StPxlHit));
  
StPxlHit::~StPxlHit() { /* noop */ }

StPxlHit::StPxlHit()
{
    mSector = mLadder = mWafer = -1;
    mExtraByte1 = mExtraByte0 = 0;
    mKey = mVolumeId = -1;
    mDouble0 = mDouble1 = mDouble2 = mDouble3 = mDouble4 = 0.;
    mDetectorId = kUnknownId;
}

StPxlHit::StPxlHit(const StThreeVectorF& p,
                   const StThreeVectorF& e,
                   unsigned int hw, float q, unsigned char c,
	         unsigned short idTruth,  unsigned short quality,
	         unsigned short id, StDetectorId dId)
    : StHit(p, e, hw, q, c, idTruth, quality, id)
{ 
    mSector = mLadder = mWafer = -1;
    mExtraByte0 = mExtraByte1 = 0;
    
    mKey = mVolumeId = -1;
    
    mDouble0 = mDouble1 = mDouble2 = mDouble3 = mDouble4 = 0.;
    mDetectorId = dId;
}

StDetectorId StPxlHit::detector() const {return mDetectorId;}

void StPxlHit::setDetectorId(StDetectorId id) {mDetectorId = id;}

double StPxlHit::localPosition(unsigned int i) const
{
	if (i<2)
		return mLocalPosition[i];
	else
      return 0;
}
 
void
StPxlHit::setLocalPosition(double u, double v)
{
	mLocalPosition[0] = u;
	mLocalPosition[1] = v;
}

ostream& operator<<(ostream& os, const StPxlHit& hit)
{
    return os << "HFT Hit -I- \tSector:"<<hit.mSector<<" ladder: "<<hit.mLadder
	    << " wafer: "<< hit.mWafer<<"\n\t\t"<<((StHit)hit)
	    <<" \n\t\tExtraByte0: "<<hit.mExtraByte0<<" ExtraByte1: "<<hit.mExtraByte1
	    <<"\n\t\tDoubles: "<< hit.mDouble0<< " "<<hit.mDouble1<<" "<<hit.mDouble2
	    << hit.mDouble3 << " " << hit.mDouble4<<endl;
}
