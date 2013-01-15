/***************************************************************************
 *
 * $Id: StContainers.cxx,v 2.25 2012/04/16 20:22:16 ullrich Exp $
 *
 * Author: Thomas Ullrich, Oct 1999
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StContainers.cxx,v $
 * Revision 2.25  2012/04/16 20:22:16  ullrich
 * Changes necessary to add Fgt package.
 *
 * Revision 2.24  2012/01/24 02:57:09  perev
 * Etr detector added
 *
 * Revision 2.23  2011/04/25 21:24:33  ullrich
 * Added containers for MTD.
 *
 * Revision 2.22  2011/02/01 19:47:36  ullrich
 * Added HLT branch and hooks.
 *
 * Revision 2.21  2010/01/08 22:43:44  ullrich
 * Updates needed to add StFmsCollection and related classes.
 *
 * Revision 2.20  2009/11/23 22:22:25  ullrich
 * Minor cleanup performed and hooks for RPS added.
 *
 * Revision 2.19  2008/12/24 22:15:53  fisyak
 * Add implementation for BTof containers
 *
 * Revision 2.18  2006/01/19 21:50:40  ullrich
 * Added RnD containers.
 *
 * Revision 2.17  2005/04/11 22:35:24  calderon
 * Tof Classes for Run 5.  Modifications and additions from Xin to
 * take care of new TOF daq and electronics.  Added StTofRawData and
 * modified containers and includes.
 *
 * Revision 2.16  2003/05/21 18:22:46  ullrich
 * Major Revision of ToF classes (F. Geurts)
 *
 * Revision 2.15  2002/12/20 22:34:42  ullrich
 * Added containers for PMD hits and clusters.
 *
 * Revision 2.14  2001/12/01 15:39:19  ullrich
 * Added macros for StDetectorState.
 *
 * Revision 2.13  2001/11/10 23:53:22  ullrich
 * Added calibration vertices.
 *
 * Revision 2.12  2001/10/01 19:40:31  ullrich
 * Added StTofData.
 *
 * Revision 2.11  2001/08/02 01:27:08  ullrich
 * Added containers for StL3AlgorithmInfo.
 *
 * Revision 2.10  2001/04/16 20:29:45  ullrich
 * Added Tof containers.
 *
 * Revision 2.9  2001/03/14 02:29:16  ullrich
 * Added StPsd container.
 *
 * Revision 2.8  2000/11/25 11:52:21  lasiuk
 * addition of Rich Photon Info
 *
 * Revision 2.7  2000/09/28 10:56:33  ullrich
 * Added Rich PID classes.
 *
 * Revision 2.6  2000/06/19 01:32:15  perev
 *  Thomas StEvent branches added
 *
 * Revision 2.5  2000/05/22 21:42:41  ullrich
 * Add RICH related classes.
 *
 * Revision 2.4  2000/03/23 22:24:06  akio
 * Initial version of Emc Point, and Inclusion of track pointers
 *
 * Revision 2.3  2000/02/23 17:35:54  ullrich
 * Changes due to the addition of the EMC to StEvent
 *
 * Revision 2.2  2000/01/05 16:02:20  ullrich
 * SSD hits added to StEvent.
 *
 * Revision 2.1  1999/10/28 22:06:16  ullrich
 * Initial Revision
 *
 **************************************************************************/
#include "StCalibrationVertex.h"
#include "StContainers.h"
#include "StDetectorState.h"
#include "StSvtHit.h"
#include "StSsdHit.h"
#include "StTpcHit.h"
#include "StFtpcHit.h"
#include "StEtrHit.h"
#include "StRichHit.h"
#include "StRichPixel.h"
#include "StRichPid.h"
#include "StRichPhotonInfo.h"
#include "StRichCluster.h"
#include "StRichMCInfo.h"
#include "StRpsCluster.h"
#include "StEmcRawHit.h"
#include "StEmcCluster.h"
#include "StEmcPoint.h"
#include "StFmsHit.h"
#include "StTofHit.h"
#include "StTofSlat.h"
#include "StTofCell.h"
#include "StTofData.h"
#include "StTofRawData.h"
#include "StPrimaryTrack.h"
#include "StPrimaryVertex.h"
#include "StPsd.h"
#include "StTrackNode.h"
#include "StTrackPidTraits.h"
#include "StTrackDetectorInfo.h"
#include "StV0Vertex.h"
#include "StXiVertex.h"
#include "StKinkVertex.h"
#include "StL3AlgorithmInfo.h"
#include "StPhmdHit.h"
#include "StPhmdCluster.h"
#include "StRnDHit.h"
#include "StPxlHit.h"
#include "StIstHit.h"
#include "StHltBEmcTowerHit.h"
#include "StHltBTofHit.h"
#include "StHltVpdHit.h"
#include "StHltTrack.h"
#include "StHltTrackNode.h"
#include "StHltHighPt.h"
#include "StHltHeavyFragment.h"
#include "StHltDiElectron.h"
#include "StHltTriggerReason.h"
#include "StMtdHit.h"
#include "StMtdRawHit.h"
#include "StFgtStrip.h"
#include "StFgtPoint.h"
#include "StFgtHit.h"

StCollectionImp(Object)
StCollectionImp(CalibrationVertex)
StCollectionImp(DetectorState)
StCollectionImp(Hit)
StCollectionImp(PrimaryTrack)
StCollectionImp(PrimaryVertex)
StCollectionImp(Psd)
StCollectionImp(SvtHit)
StCollectionImp(SsdHit)
StCollectionImp(TpcHit)
StCollectionImp(FtpcHit)
StCollectionImp(EtrHit)
StCollectionImp(RichHit)
StCollectionImp(RichCluster)
StCollectionImp(RichPixel)
StCollectionImp(RichPid)
StCollectionImp(RichPhotonInfo)
StCollectionImp(RichMCInfo)
StCollectionImp(RpsCluster)
StCollectionImp(EmcRawHit)
StCollectionImp(EmcCluster)
StCollectionImp(EmcPoint)
StCollectionImp(FmsHit)
StCollectionImp(TofHit)
StCollectionImp(TofSlat)
StCollectionImp(TofCell)
StCollectionImp(TofData)
StCollectionImp(TofRawData)
StCollectionImp(BTofHit)
StCollectionImp(BTofRawHit)
StCollectionImp(MtdHit)
StCollectionImp(MtdRawHit)
StCollectionImp(Track)
StCollectionImp(TrackNode)
StCollectionImp(TrackPidTraits)
StCollectionImp(TrackDetectorInfo)
StCollectionImp(V0Vertex)
StCollectionImp(XiVertex)
StCollectionImp(KinkVertex)
StCollectionImp(L3AlgorithmInfo)
StCollectionImp(PhmdHit)
StCollectionImp(PhmdCluster)
StCollectionImp(RnDHit)
StCollectionImp(PxlHit)
StCollectionImp(IstHit)
StCollectionImp(HltBEmcTowerHit)
StCollectionImp(HltBTofHit)
StCollectionImp(HltVpdHit)
StCollectionImp(HltTrack)
StCollectionImp(HltTrackNode)
StCollectionImp(HltHighPt)
StCollectionImp(HltHeavyFragment)
StCollectionImp(HltDiElectron)
StCollectionImp(HltTriggerReason)
StCollectionImp(FgtHit)
StCollectionImp(FgtStrip)
StCollectionImp(FgtPoint)
