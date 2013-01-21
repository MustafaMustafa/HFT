/*!
 * \class StPxlHit 
 * \authors S. MArgetis, J. Bouchet, Jan 2013
 * \Initial Revision.
 *
 **************************************************************************/
#include "StPxlHit.h"

ClassImp(StPxlHit)

StMemoryPool StPxlHit::mPool(sizeof(StPxlHit));
  
StPxlHit::~StPxlHit() { /* noop */ }

StPxlHit::StPxlHit()
{
  mSector = mLadder = mSensor = -1;
    mDetectorId = kUnknownId;
}

StPxlHit::StPxlHit(const StThreeVectorF& p,
                   const StThreeVectorF& e,
                   unsigned int hw, float q, unsigned char c)
    : StHit(p, e, hw, q, c)
{ 
  mSector = mLadder = mSensor = -1;
  mDetectorId = kUnknownId;
}

StDetectorId StPxlHit::detector() const {return mDetectorId;}

void StPxlHit::setDetectorId(StDetectorId id) {mDetectorId = id;}

Float_t StPxlHit::localPosition(unsigned int i) const
{
	if (i<3)
		return mLocalPosition[i];
	else
      return 0;
}
 
void
StPxlHit::setLocalPosition(float u, float v, float w)
{
	mLocalPosition[0] = u;	
	mLocalPosition[1] = v;
	mLocalPosition[2] = w;
}

ostream& operator<<(ostream& os, const StPxlHit& hit)
{
    return os << "HFT Hit -I- \tSector:"<<hit.mSector<<" ladder: "<<hit.mLadder
	      << " sensor: "<< hit.mSensor <<" localPosition[0]/localPosition[1]/localPosition[2] : " <<hit.localPosition(0)
	      <<"/"<<hit.localPosition(1)<<"/"<<hit.localPosition(2)
	      <<" kDetectorId : " <<hit.detector()<<"\n\t\t"<<((StHit)hit)
	      <<endl;
}
