/*!
 * \class StTrack 
 * \author Thomas Ullrich, Sep 1999
 */
/***************************************************************************
 *
 * $Id: StTrack.h,v 2.29 2012/09/16 21:36:09 fisyak Exp $
 *
 * Author: Thomas Ullrich, Sep 1999
 ***************************************************************************
 *
 * Description:
 *
 * Note the following: with the arrival of ITTF it is now possible to
 * store the numberOfPossiblePoints for every detector individually. Before
 * that and because of the way the tables were defined TPC and FTPC were
 * one and the same. This caused confusion. However, since we have to
 * stay backwards compatible the "old way" is still working.
 *    mNumberOfPossiblePoints ==>  seedQuality 
 *    mNumberOfPossiblePointsTpc
 *    mNumberOfPossiblePointsFtpcWest 
 *    mNumberOfPossiblePointsFtpcEast 
 *    mNumberOfPossiblePointsSvt 
 *    mNumberOfPossiblePointsSsd 
 *    are the ones that count
  * --------------------------------------------------------------------------
 *  The track flag (mFlag accessed via flag() method) definitions with ITTF 
 *  (flag definition in EGR era can be found at
 *   http://www.star.bnl.gov/STAR/html/all_l/html/dst_track_flags.html)
 *
 *  mFlag= zxyy, where  z = 1 for pile up track in TPC (otherwise 0) 
 *                      x indicates the detectors included in the fit and 
 *                     yy indicates the status of the fit. 
 *  Positive mFlag values are good fits, negative values are bad fits. 
 *
 *  The first digit indicates which detectors were used in the refit: 
 *
 *      x=1 -> TPC only 
 *      x=3 -> TPC       + primary vertex 
 *      x=5 -> SVT + TPC 
 *      x=6 -> SVT + TPC + primary vertex 
 *      x=7 -> FTPC only 
 *      x=8 -> FTPC      + primary 
 *      x=9 -> TPC beam background tracks            
 *
 *  The last two digits indicate the status of the refit: 
 *       = +x01 -> good track 
 *
 *      = -x01 -> Bad fit, outlier removal eliminated too many points 
 *      = -x02 -> Bad fit, not enough points to fit 
 *      = -x03 -> Bad fit, too many fit iterations 
 *      = -x04 -> Bad Fit, too many outlier removal iterations 
 *      = -x06 -> Bad fit, outlier could not be identified 
 *      = -x10 -> Bad fit, not enough points to start 
 *
 *      = +x11 -> Short track pointing to EEMC
 *
 ***************************************************************************
 *
 * $Log: StTrack.h,v $
 * Revision 2.29  2012/09/16 21:36:09  fisyak
 * Handlers for Tpc Only West and Only East bits
 *
 * Revision 2.28  2012/05/07 14:42:58  fisyak
 * Add handilings for Track to Fast Detectors Matching
 *
 * Revision 2.27  2011/10/13 21:25:27  perev
 * setting IdTruth from the hits is added
 *
 * Revision 2.26  2011/04/26 21:41:29  fisyak
 * Make mKey Int_t instead of UShort_t (no. of tracks might be more that 64k)
 *
 * Revision 2.25  2011/03/31 19:29:01  fisyak
 * Add IdTruth information for tracks and vertices
 *
 * Revision 2.24  2010/08/31 20:00:09  fisyak
 * Clean up, add mSeedQuality
 *
 * Revision 2.23  2009/11/23 16:34:07  fisyak
 * Cleanup, remove dependence on dst tables, clean up software monitors
 *
 * Revision 2.22  2008/08/26 12:47:38  fisyak
 * add track pule up flag description
 *
 * Revision 2.21  2007/10/11 21:51:40  ullrich
 * Added member to handle number of possible points fpr PXL and IST.
 *
 * Revision 2.20  2006/08/28 17:03:54  fisyak
 * Add track flag definitions from EGR (we suppose that this will be primary information from now)
 *
 * Revision 2.19  2004/08/05 22:24:51  ullrich
 * Changes to the handling of numberOfPoints() to allow ITTF more flexibility.
 *
 * Revision 2.18  2004/07/15 16:36:26  ullrich
 * Removed all clone() declerations and definitions. Use StObject::clone() only.
 *
 * Revision 2.17  2003/10/31 16:00:04  ullrich
 * Added setKey() method.
 *
 * Revision 2.16  2003/10/30 20:07:32  perev
 * Check of quality added
 *
 * Revision 2.15  2002/03/14 17:42:15  ullrich
 * Added method to set mNumberOfPossiblePoints.
 *
 * Revision 2.14  2002/02/22 22:56:52  jeromel
 * Doxygen basic documentation in all header files. None of this is required
 * for QM production.
 *
 * Revision 2.13  2001/09/28 22:20:50  ullrich
 * Added helix geometry at last point.
 *
 * Revision 2.12  2001/05/30 17:45:55  perev
 * StEvent branching
 *
 * Revision 2.11  2001/04/05 04:00:45  ullrich
 * Replaced all (U)Long_t by (U)Int_t and all redundant ROOT typedefs.
 *
 * Revision 2.10  2001/03/24 03:34:59  perev
 * clone() -> clone() const
 *
 * Revision 2.9  2001/03/16 20:56:46  ullrich
 * Added non-const version of fitTraits().
 *
 * Revision 2.8  1999/12/01 15:58:10  ullrich
 * New decoding for dst_track::method. New enum added.
 *
 * Revision 2.7  1999/11/30 23:20:32  didenko
 * temporary solution to get library compiled
 *
 * Revision 2.6  1999/11/29 17:32:45  ullrich
 * Added non-const method pidTraits().
 *
 * Revision 2.5  1999/11/15 18:48:22  ullrich
 * Adapted new enums for dedx and track reco methods.
 *
 * Revision 2.4  1999/11/05 15:27:07  ullrich
 * Added non-const versions of several methods
 *
 * Revision 2.3  1999/11/04 13:32:03  ullrich
 * Added non-const versions of some methods
 *
 * Revision 2.2  1999/11/01 12:45:06  ullrich
 * Modified unpacking of point counter
 *
 * Revision 2.1  1999/10/28 22:27:24  ullrich
 * Adapted new StArray version. First version to compile on Linux and Sun.
 *
 * Revision 2.0  1999/10/12 18:42:56  ullrich
 * Completely Revised for New Version
 *
 * 
 **************************************************************************/
#ifndef StTrack_hh
#define StTrack_hh
#include "StObject.h"
#include "StContainers.h"
#include "StEnumerations.h"
#include "StTrackTopologyMap.h"
#include "StFunctional.h"
#include "StTrackFitTraits.h"

class StParticleDefinition;
class StVertex;
class StTrackGeometry;
class StTrackDetectorInfo;
class StTrackPidTraits;
class StTrackNode;

class StTrack : public StObject {
public:
    StTrack();
    StTrack(const StTrack&);
    StTrack & operator=(const StTrack&);
    virtual ~StTrack();

    virtual StTrackType            type() const = 0;
    virtual const StVertex*        vertex() const = 0;
    virtual Int_t                  key() const { return mKey; }
    Short_t                        flag() const;
    UInt_t                         flagExtension() const { return mFlagExtension; }
    UShort_t                       encodedMethod() const;
    bool                           finderMethod(StTrackFinderMethod) const;
    StTrackFittingMethod           fittingMethod() const;
    Float_t                        impactParameter() const;
    Float_t                        length() const;
    UShort_t                       numberOfPossiblePoints() const;
    UShort_t                       numberOfPossiblePoints(StDetectorId) const;
    const StTrackTopologyMap&      topologyMap() const;
    StTrackGeometry*               geometry();
    const StTrackGeometry*         geometry() const;
    StTrackGeometry*               outerGeometry();
    const StTrackGeometry*         outerGeometry() const;
    StTrackDetectorInfo*           detectorInfo();
    const StTrackDetectorInfo*     detectorInfo() const;
    StTrackFitTraits&              fitTraits();
    const StTrackFitTraits&        fitTraits() const;
    const StSPtrVecTrackPidTraits& pidTraits() const;
    StSPtrVecTrackPidTraits&       pidTraits();
    StPtrVecTrackPidTraits         pidTraits(StDetectorId) const;
    const StParticleDefinition*    pidTraits(StPidAlgorithm&) const;
    StTrackNode*                   node();
    const StTrackNode*             node() const;
    UShort_t                       seedQuality() const {return mSeedQuality;}
    Bool_t       isCtbMatched()            {return testBit(kCtbMatched);}   
    Bool_t       isToFMatched()  	   {return testBit(kToFMatched);}   
    Bool_t       isBToFMatched()  	   {return testBit(kToFMatched);}   
    Bool_t       isBemcMatched() 	   {return testBit(kBemcMatched);}  
    Bool_t       isEemcMatched() 	   {return testBit(kEemcMatched);}  

    Bool_t       isCtbNotMatched()         {return testBit(kCtbNotMatched);}   
    Bool_t       isToFNotMatched()  	   {return testBit(kToFNotMatched);}   
    Bool_t       isBToFNotMatched()  	   {return testBit(kToFNotMatched);}   
    Bool_t       isBemcNotMatched() 	   {return testBit(kBemcNotMatched);}  
    Bool_t       isEemcNotMatched() 	   {return testBit(kEemcNotMatched);}  

    Bool_t       isDecayTrack()  	   {return testBit(kDecayTrack);}   
    Bool_t       isPromptTrack() 	   {return testBit(kPromptTrack);}       
    Bool_t       isPostXTrack()            {return testBit(kPostXTrack);} 
    Bool_t       isMembraneCrossingTrack() {return testBit(kXMembrane);} 
    Bool_t       isShortTrack2EMC()        {return testBit(kShortTrack2EMC);}
    Bool_t       isRejected()              {return testBit(kRejectedTrack);}
    Bool_t       isWestTpcOnly()           {return testBit(kWestTpcOnlyTrack);}
    Bool_t       isEastTpcOnly()           {return testBit(kEastTpcOnlyTrack);}

    virtual void setCtbMatched()           {setBit(kCtbMatched);}   
    virtual void setToFMatched()  	   {setBit(kToFMatched);}   
    virtual void setBToFMatched()  	   {setBit(kToFMatched);}   
    virtual void setBemcMatched() 	   {setBit(kBemcMatched);}  
    virtual void setEemcMatched() 	   {setBit(kEemcMatched);}  

    virtual void setCtbNotMatched()        {setBit(kCtbNotMatched);}   
    virtual void setToFNotMatched()  	   {setBit(kToFNotMatched);}   
    virtual void setBToFNotMatched()  	   {setBit(kToFNotMatched);}   
    virtual void setBemcNotMatched() 	   {setBit(kBemcNotMatched);}  
    virtual void setEemcNotMatched() 	   {setBit(kEemcNotMatched);}  
    virtual void setDecayTrack()  	   {setBit(kDecayTrack);}   
    virtual void setPromptTrack() 	   {setBit(kPromptTrack);}       
    virtual void setPostCrossingTrack()    {setBit(kPostXTrack);} 
    virtual void setMembraneCrossingTrack(){setBit(kXMembrane);} 
    virtual void setShortTrack2EMC()       {reSetBit(kRejectedTrack); setBit(kShortTrack2EMC);}
    virtual void setRejected()             {setBit(kRejectedTrack);}
    virtual void setWestTpcOnly()          {setBit(kWestTpcOnlyTrack);}
    virtual void setEastTpcOnly()          {setBit(kEastTpcOnlyTrack);}
    virtual void setFlagExtension(UInt_t i){mFlagExtension = i;}
    void         setFlag(Short_t);
    void         setKey(Int_t val) { mKey = val; }
    void         setEncodedMethod(UShort_t);
    void         setImpactParameter(float);
    void         setLength(float);
    void         setTopologyMap(const StTrackTopologyMap&);
    void         setGeometry(StTrackGeometry*);
    void         setOuterGeometry(StTrackGeometry*);
    void         setFitTraits(const StTrackFitTraits&);
    void         addPidTraits(StTrackPidTraits*);
    void         setDetectorInfo(StTrackDetectorInfo*);
    void         setNode(StTrackNode*);
    Int_t        bad() const;
    void         setNumberOfPossiblePoints(unsigned char, StDetectorId);
    void         setSeedQuality(UShort_t qa) 		{mSeedQuality = qa;}
    Int_t        idTruth() const 			{ return mIdTruth;}
    Int_t        qaTruth() const 			{ return mQuality; }
    Int_t        idParentVx() const {return mIdParentVx;}
    void         setIdTruth(Int_t idtru,Int_t qatru=0) 	{mIdTruth = (UShort_t) idtru; mQuality = (UShort_t) qatru;}
    void         setIdTruth(); 				//setting on hits info
    void         setIdParentVx(Int_t id) {mIdParentVx = id;}
   //----- bit manipulation
    void         setBit(UInt_t f, Bool_t set) {(set) ? setBit(f) : reSetBit(f);}
    void         setBit(UInt_t f) { mFlagExtension |= f; }
    void         reSetBit(UInt_t f) { mFlagExtension &= ~(f); }
    Bool_t       testBit(UInt_t f) const { return (Bool_t) ((mFlagExtension & f) != 0); }
    Int_t        testBits(UInt_t f) const { return (Int_t) (mFlagExtension & f); }
    void         invertBit(UInt_t f) { mFlagExtension ^= f; }
    
protected:
    void         setNumberOfPossiblePoints(UShort_t); // obsolete
    
protected:
    Char_t                  mBeg[1]; //!
    Int_t                   mKey;
    Short_t                 mFlag;
    UInt_t                  mFlagExtension; // bit wise fast detector matching status
    UShort_t                mEncodedMethod;
    UShort_t                mSeedQuality;   // ITTF: this is seed quality
    UChar_t                 mNumberOfPossiblePointsTpc;
    UChar_t                 mNumberOfPossiblePointsFtpcWest;
    UChar_t                 mNumberOfPossiblePointsFtpcEast;
    UChar_t                 mNumberOfPossiblePointsSvt;
    UChar_t                 mNumberOfPossiblePointsSsd;
    UChar_t                 mNumberOfPossiblePointsPxl;
    UChar_t                 mNumberOfPossiblePointsIst;
    Float_t                 mImpactParameter;
    Float_t                 mLength;
    StTrackGeometry        *mGeometry;
    StTrackGeometry        *mOuterGeometry;
    UShort_t                mIdTruth; // MC track id 
    UShort_t                mQuality; // quality of this information (percentage of hits coming from the above MC track)
    Int_t                   mIdParentVx; // MC Parent vertex Id
    Char_t                  mEnd[1]; //!
    StTrackTopologyMap      mTopologyMap;
    StTrackFitTraits        mFitTraits;
    
//  StTrackDetectorInfo         *mDetectorInfo;         //$LINK
//  StTrackNode                 *mNode;                 //$LINK
#ifdef __CINT__
    StObjLink                mDetectorInfo;         
    StObjLink      	         mNode;                 	
#else
    StLink<StTrackDetectorInfo>  mDetectorInfo;         
    StLink<StTrackNode>          mNode;                 	
#endif //__CINT__

    StSPtrVecTrackPidTraits mPidTraitsVec;

    ClassDef(StTrack,9)
};
#endif
