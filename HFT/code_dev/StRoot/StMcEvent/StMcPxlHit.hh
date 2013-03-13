/***************************************************************************
 *
 * $Id: $
 * $Log: $
 * 
 **************************************************************************/
#ifndef StMcPxlHit_hh
#define StMcPxlHit_hh
#include "StMcHit.hh"
#include "tables/St_g2t_pix_hit_Table.h" 

class StMcPxlHit : public StMcHit {
public:
  StMcPxlHit() {}
  StMcPxlHit(const StThreeVectorF& x,const StThreeVectorF& p,
	     float de = 0, float ds = 0, float tof = 0, long int k = 0, long int volId = 0, StMcTrack* parent=0) : 
    StMcHit(x,p,de,ds,tof,k,volId,parent) {}
  StMcPxlHit(g2t_pix_hit_st* pt) : 
    StMcHit(StThreeVectorF(pt->x[0], pt->x[1], pt->x[2]),
	    StThreeVectorF(pt->p[0], pt->p[1], pt->p[2]), 
	    pt->de, pt->ds, pt->tof, pt->id, pt->volume_id, 0) {}
  ~StMcPxlHit() {}

  // Get methods
  ULong_t sector() const {return mVolumeId/1000000;}
  ULong_t ladder() const {return  (mVolumeId%1000000)/10000;} // 1-6, 1-18
  ULong_t sensor() const {return  (mVolumeId - sector()*1000000 - ladder()*10000)/100;} 
  virtual void Print(Option_t *option="") const; // *MENU* 

private:
  ClassDef(StMcPxlHit,1)
};

ostream&  operator<<(ostream& os, const StMcPxlHit&);

#endif

/***************************************************************************
 *
 * $Id: StMcPixelHit.hh,v 2.7 2011/10/17 00:24:00 fisyak Exp $
 * $Log: StMcPixelHit.hh,v $
 * Revision 2.7  2011/10/17 00:24:00  fisyak
 * Add time of flight for hits
 *
 * Revision 2.6  2005/11/22 21:44:52  fisyak
 * Add compress Print for McEvent, add Ssd collections
 *
 * Revision 2.5  2005/09/28 21:30:15  fisyak
 * Persistent StMcEvent
 *
 * Revision 2.4  2005/07/06 20:05:28  calderon
 * Remove forward declaration of StThreeVectorF, use #include, and only in
 * StMcHit base class.  StThreeVectorF is not a class anymore, it is now
 * only a typedef, only template version of StThreeVector exists now.
 *
 * Revision 2.3  2005/01/27 23:40:47  calderon
 * Adding persistency to StMcEvent as a step for Virtual MonteCarlo.
 *
 * Revision 2.2  2004/09/14 05:00:30  calderon
 * Added support for Ist, Ssd and changes to Pixel, from "El Kai".
 *
 * Revision 2.1  2003/08/20 18:50:21  calderon
 * Addition of Tof classes and Pixel classes.  Modified track, event, and
 * container code to reflect this.
 * Fix bug in StMcVertex and in clearing of some hit collections.
 *
 *
 **************************************************************************/
