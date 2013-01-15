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
#ifndef StIstHit_hh
#define StIstHit_hh
#include "StHit.h"
#include "StMemoryPool.hh"
#include "StEnumerations.h"

class StIstHit : public StHit
{
public:
    StIstHit();
    StIstHit(const StThreeVectorF& position,
	   const StThreeVectorF& error,
	   unsigned int hwPosition, float charge, unsigned char trackRefCount = 0,
	   unsigned short idTruth=0,  unsigned short quality=0,  unsigned short id =0,
	   StDetectorId = kUnknownId);
    ~StIstHit();

    StDetectorId detector() const;
    
    short  layer() const;
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
    
    void setLayer(short);
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

    void* operator new(size_t sz,void *p)     { return p;}
    void* operator new(size_t)     { return mPool.alloc(); }
    void  operator delete(void* p) { mPool.free(p); }
    
    friend ostream& operator<<(ostream& os, const StIstHit& h);
    
protected:
    Short_t mLayer; ///Layer
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

    // this has to go once the playing and testing is over.
    // should be hard wired in member function.
    StDetectorId mDetectorId;
    
    static StMemoryPool mPool;  //!
    
    ClassDef(StIstHit,1)        
};

inline short  StIstHit::layer() const {return mLayer;}
inline short  StIstHit::ladder() const {return mLadder;}
inline short  StIstHit::wafer() const {return mWafer;}
inline int    StIstHit::extraByte0() const {return mExtraByte0;}
inline int    StIstHit::extraByte1() const {return mExtraByte1;}
inline int    StIstHit::key() const {return mKey;}
inline int    StIstHit::volumeId() const {return mVolumeId;}
inline double StIstHit::double0() const {return mDouble0;}
inline double StIstHit::double1() const {return mDouble1;}
inline double StIstHit::double2() const {return mDouble2;}
inline double StIstHit::double3() const {return mDouble3;}
inline double StIstHit::double4() const {return mDouble4;}
    
inline void StIstHit::setLayer(short v) {mLayer = v;}
inline void StIstHit::setLadder(short v) {mLadder = v;}
inline void StIstHit::setWafer(short v) {mWafer = v;}
inline void StIstHit::setExtraByte0(int v) {mExtraByte0=v;}
inline void StIstHit::setExtraByte1(int v) {mExtraByte1=v;}
inline void StIstHit::setKey(int v) {mKey = v;}
inline void StIstHit::setVolumeId(int v) {mVolumeId=v;}
inline void StIstHit::setDouble0(double val) {mDouble0 = val;}
inline void StIstHit::setDouble1(double val) {mDouble1 = val;}
inline void StIstHit::setDouble2(double val) {mDouble2 = val;}
inline void StIstHit::setDouble3(double val) {mDouble3 = val;}
inline void StIstHit::setDouble4(double val) {mDouble4 = val;}

#endif
