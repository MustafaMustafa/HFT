/*!
 * \class StRnDHit 
 * \author Mike Miller and Andrew Rose, Jan 2006
 */
/*
 ***************************************************************************
 * $Id: StRnDHit.h,v 2.2 2006/09/27 18:31:43 ullrich Exp $
 *
 * Author: Mike Miller and Andrew Rose, Jan 2006
 ***************************************************************************
 *
 * Description:  This is an experimental class and not final yet
 *
 ***************************************************************************
 *
 * $Log: StRnDHit.h,v $
 * Revision 2.2  2006/09/27 18:31:43  ullrich
 * Fixed setDouble() interface. Was sooo wrong.
 *
 * Revision 2.1  2006/01/19 21:42:06  ullrich
 * Initial Revision.
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
	   unsigned int hwPosition, float charge, unsigned char trackRefCount = 0,
	   unsigned short idTruth=0,  unsigned short quality=0,  unsigned short id =0,
	   StDetectorId = kUnknownId);
    ~StPxlHit();

    StDetectorId detector() const;
    
    short  sector() const;
    short  ladder() const;
    short  wafer() const;
    
    int    extraByte0() const;
    int    extraByte1() const;
    
    int    key() const;
    int    volumeId() const;
    
    double double0() const;
    double double1() const;
    double double2() const;
    double double3() const;
    double double4() const;
	
	 double localPosition(unsigned int) const;
	 void  setLocalPosition(double, double);
    
    void setSector(short);
    void setLadder(short);
    void setWafer(short);
    void setExtraByte0(int);
    void setExtraByte1(int);
    void setDetectorId(StDetectorId);
    
    void setKey(int);
    void setVolumeId(int);
    
    void setDouble0(double);
    void setDouble1(double);
    void setDouble2(double);
    void setDouble3(double);
    void setDouble4(double);

    virtual Bool_t IsSortable() const { return kTRUE; }

    void* operator new(size_t sz,void *p)     { return p;}
    void* operator new(size_t)     { return mPool.alloc(); }
    void  operator delete(void* p) { mPool.free(p); }
    
    friend ostream& operator<<(ostream& os, const StPxlHit& h);
    
protected:
				Short_t mSector; ///Sector
				Short_t mLadder; ///Ladder
				Short_t mWafer; ///Wafer
				
				//Extras
				Int_t mExtraByte0;
				Int_t mExtraByte1;
				
				//info to get back to StMcHit pointer:
				Int_t mKey; ///key from StMcHit
				Int_t mVolumeId; ///VolumeId from StMcHit
				
				//and 5 overflow doubles
				Double_t mDouble0;
				Double_t mDouble1;
				Double_t mDouble2;
				Double_t mDouble3;
				Double_t mDouble4;

				//local position of hit inside the wafer
				Double_t mLocalPosition[2];

				// this has to go once the playing and testing is over.
				// should be hard wired in member function.
				StDetectorId mDetectorId;
				
				static StMemoryPool mPool;  //!
				
				ClassDef(StPxlHit,1)        
		  };

		  inline short  StPxlHit::sector() const {return mSector;}
		  inline short  StPxlHit::ladder() const {return mLadder;}
		  inline short  StPxlHit::wafer() const {return mWafer;}
		  inline int    StPxlHit::extraByte0() const {return mExtraByte0;}
		  inline int    StPxlHit::extraByte1() const {return mExtraByte1;}
		  inline int    StPxlHit::key() const {return mKey;}
		  inline int    StPxlHit::volumeId() const {return mVolumeId;}
		  inline double StPxlHit::double0() const {return mDouble0;}
		  inline double StPxlHit::double1() const {return mDouble1;}
		  inline double StPxlHit::double2() const {return mDouble2;}
		  inline double StPxlHit::double3() const {return mDouble3;}
		  inline double StPxlHit::double4() const {return mDouble4;}
				
inline void StPxlHit::setSector(short v) {mSector = v;}
inline void StPxlHit::setLadder(short v) {mLadder = v;}
inline void StPxlHit::setWafer(short v) {mWafer = v;}
inline void StPxlHit::setExtraByte0(int v) {mExtraByte0=v;}
inline void StPxlHit::setExtraByte1(int v) {mExtraByte1=v;}
inline void StPxlHit::setKey(int v) {mKey = v;}
inline void StPxlHit::setVolumeId(int v) {mVolumeId=v;}
inline void StPxlHit::setDouble0(double val) {mDouble0 = val;}
inline void StPxlHit::setDouble1(double val) {mDouble1 = val;}
inline void StPxlHit::setDouble2(double val) {mDouble2 = val;}
inline void StPxlHit::setDouble3(double val) {mDouble3 = val;}
inline void StPxlHit::setDouble4(double val) {mDouble4 = val;}

#endif
