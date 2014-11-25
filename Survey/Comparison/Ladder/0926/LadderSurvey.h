/*
 * File:   SurveyLadder.h
 * Author: mustafa
 *
 * Created on September 13, 2012, 6:23 PM
 *
 * Can be made a class if needed.
 */
#ifndef LADDERSURVEY_H
#define	LADDERSURVEY_H

#include "TGraph2D.h"
#include "TString.h"
#include "TVectorD.h"
//#include "Tps.h"
class Tps;

struct LadderSurvey
{
    UInt_t mNChips;
    UInt_t mNPoints;
    Float_t mXSeparation;

    TGraph2D* mGrandGraph;
    Double_t* grandX;
    Double_t* grandY;
    Double_t* grandZ;

    Tps* mTps[10]; // Assuming 10 chips max

    LadderSurvey(TString filename, UInt_t nPoints = 132, Float_t xSeparation = 26.0)
    : mNPoints(nPoints), mXSeparation(xSeparation)
    {
        // This will read all the data in the ascii file

        mGrandGraph = new TGraph2D(filename.Data());
	TString grandGraphName = Form("grandGraph_%s",filename.ReplaceAll(".txt","\0").Data()); // can be modified to remove any extension
	mGrandGraph->SetName(grandGraphName.Data());
	mGrandGraph->SetMarkerStyle(20);

	if(mGrandGraph->GetN()%mNPoints !=0 )
	{
	    std::cout<<"Some points are missing from "<<filename<<std::endl;
	    std::cout<<"Check measurements."<<std::endl;
	    exit(0);
	}

        mNChips = mGrandGraph->GetN() / mNPoints;

	// ----- Shift X-Coordinate
        // every chip has nPoints measurements with respect to chip local coordinates
        // the ascii file usually contains the nPoints measurements for all/several chips
        // we need to separate these along the x-axis to be able to plot them as a ladder

        grandX = mGrandGraph->GetX();
        grandY = mGrandGraph->GetY();
        grandZ = mGrandGraph->GetZ();

        for (UInt_t iChip = 1; iChip < mNChips; iChip++)
	{
            for (UInt_t iPoint = 0; iPoint < mNPoints; iPoint++)
	    {
                grandX[iChip * mNPoints + iPoint] += mXSeparation * iChip;
            }
        }
    }

    void GenerateTps(Double_t tpsLambda = 0)
    {
	for(UInt_t iChip = 0; iChip<mNChips; iChip++)
	{
	    mTps[iChip] = new Tps();

            mTps[iChip]->Fit(mNPoints,
                    &grandX[iChip * mNPoints],
                    &grandY[iChip * mNPoints],
                    &grandZ[iChip * mNPoints],
                    tpsLambda);
	}
    }

    Double_t GetX(UInt_t iChip,UInt_t iPoint)
    {
	return grandX[iChip*mNPoints+iPoint];
    }

    Double_t GetY(UInt_t iChip,UInt_t iPoint)
    {
	return grandY[iChip*mNPoints+iPoint];
    }

    Double_t GetZ(UInt_t iChip,UInt_t iPoint)
    {
	return grandZ[iChip*mNPoints+iPoint];
    }

    Double_t GetZFit(UInt_t iChip,Double_t x, Double_t y)
    {
	if(!mTps[iChip])
	{
	    std::cout<<"Tps does not exist for this chip. Check code."<<std::endl;
	    exit(1);
	}

	return mTps[iChip]->Z(x,y);
    }

    // **** add code to cleanup the arrays and other objects
    ~LadderSurvey()
    {
        delete mGrandGraph;
    }
};

#endif	/* LADDERSURVEY_H */