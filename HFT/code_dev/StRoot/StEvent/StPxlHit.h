/*!
 * \class StPxlHit 
 * \authors S. MArgetis, J. Bouchet, Jan 2013
 * \Initial Revision.
 *
 **************************************************************************/
#ifndef StPxlHit_hh
#define StPxlHit_hh
#include "StHit.h"
#include "StMemoryPool.hh"
#include "StEnumerations.h"

class StPxlHit : public StHit
{
public:
    StPxlHit();
    StPxlHit(const StThreeVectorF& position,
	     const StThreeVectorF& error,
	     unsigned int hwPosition, float charge, 
	     unsigned char trackRefCount = 0);
    ~StPxlHit();

    StDetectorId detector() const;
    
    UChar_t sector() const;
    UChar_t ladder() const;
    UChar_t sensor() const;
    Float_t meanRow() const;
    Float_t meanColumn() const;
    UChar_t nRawHits() const;
    UChar_t layer() const ;
    
    Float_t localPosition(unsigned int) const;
    void    setLocalPosition(float, float, float);
    
    void setSector(unsigned char);
    void setLadder(unsigned char);
    void setSensor(unsigned char);
    void setDetectorId(StDetectorId);
    void setMeanRow(float);
    void setMeanColumn(float);
    void setNRawHits(unsigned char);

    virtual Bool_t IsSortable() const { return kTRUE; }

    void* operator new(size_t sz,void *p)     { return p;}
    void* operator new(size_t)     { return mPool.alloc(); }
    void  operator delete(void* p) { mPool.free(p); }
    
    friend ostream& operator<<(ostream& os, const StPxlHit& h);
    
protected:
				UChar_t mSector; //Sector : 1-10
				UChar_t mLadder; //Ladder : 1-4 
				UChar_t mSensor; //Sensor : 1-10
				Float_t mMeanRow; // mean row : mean row of the pxl cluster
				Float_t mMeanColumn; // mean column : mean column of the pxl cluster
				UChar_t mNRawHits; // nRawHits
				//local position of hit inside the wafer 
				// 3D : u,v,TPS
				Float_t mLocalPosition[3];

				// this has to go once the playing and testing is over.
				// should be hard wired in member function.
				StDetectorId mDetectorId;
				
				static StMemoryPool mPool;  //!
				
				ClassDef(StPxlHit,1)        
				  };

inline UChar_t StPxlHit::sector() const {return mSector;}
inline UChar_t StPxlHit::ladder() const {return mLadder;}
inline UChar_t StPxlHit::sensor() const {return mSensor;}
inline Float_t StPxlHit::meanRow() const {return mMeanRow;}
inline Float_t StPxlHit::meanColumn()  const {return mMeanColumn;}
inline UChar_t StPxlHit::nRawHits() const {return mNRawHits;}
inline UChar_t StPxlHit::layer() const {return (mLadder==4)?1:2;}


inline void StPxlHit::setSector(UChar_t v) {mSector = v;}
inline void StPxlHit::setLadder(UChar_t v) {mLadder = v;}
inline void StPxlHit::setSensor(UChar_t v) {mSensor = v;}
inline void StPxlHit::setMeanRow(Float_t v) {mMeanRow = v;}
inline void StPxlHit::setMeanColumn(Float_t v) {mMeanColumn = v;}
inline void StPxlHit::setNRawHits(UChar_t v) {mNRawHits = v;}

#endif