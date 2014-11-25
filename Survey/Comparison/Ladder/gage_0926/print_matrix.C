/*
 * File:   plot_matrix.C
 * Author: mustafa
 *
 * Created on September 27, 2012, 12:27 AM
 */
#include <iostream>
#include <fstream>

#include "TString.h"

using namespace std;

void add_point(TString fileName);
void print_matrix();

UInt_t gArrayIndx;
Double_t gX[20][2];
Double_t gY[20][2];
Double_t gZ[20][2];

void read_multiple_measurements_files()
{
    gArrayIndx = 0;
    add_point("vision_with_movement.txt");

//    add_point("m1_vision_1.txt");
//    add_point("m2_vision_grid_1.txt");
//    add_point("m3_stylus_1.txt");
//    add_point("m4_vision_2.txt");
//    add_point("m5_vision_grid_2.txt");
//    add_point("m6_stylus_2.txt");
//    add_point("m7_vision_3.txt");
//    add_point("m8_vision_grid_3.txt");
//    add_point("m9_stylus_3.txt");
}
//__________________
void add_point(TString fileName)
{
    ifstream ifs(fileName.Data());

    Double_t x[10];
    Double_t y[10];
    Double_t z[10];

    UInt_t i = 0;
    Double_t xMean,yMean,zMean;
    xMean =0; yMean =0; zMean=0;
    while(ifs >> x[i] >> y[i] >> z[i])
    {
	xMean +=x[i];
	yMean +=y[i];
	zMean +=z[i];
	++i;
    }

    if(i!=10)
    {
	cout<<"Something is wrong"<<endl;
	abort();
    }

    xMean = xMean/10.0;
    yMean = yMean/10.0;
    zMean = zMean/10.0;

    Double_t xRMS,yRMS,zRMS;
    xRMS =0; yRMS =0; zRMS=0;
    for(int j=0;j<10;j++)
    {
	xRMS += pow(x[j]-xMean,2);
	yRMS += pow(y[j]-yMean,2);
	zRMS += pow(z[j]-zMean,2);
    }
    xRMS = sqrt(xRMS/10);
    yRMS = sqrt(yRMS/10);
    zRMS = sqrt(zRMS/10);

    //add
    gX[gArrayIndx][0] = xMean;
    gX[gArrayIndx][1] = xRMS;
    gY[gArrayIndx][0] = yMean;
    gY[gArrayIndx][1] = yRMS;
    gZ[gArrayIndx][0] = zMean;
    gZ[gArrayIndx][1] = zRMS;
    ++gArrayIndx;

    ifs.close();
}
//__________________
void print_matrix()
{
    for(int r=0;r<gArrayIndx;r++) // rows
    {
	for(int c=0;c<gArrayIndx;c++) // columns
	{
	    cout<<gZ[r][0]-gZ[c][0]<<",";
	}

	cout<<endl;
    }

    for(int i=0;i<gArrayIndx;i++)
    {
	cout<<gZ[i][0]<<" +- "<<gZ[i][1]<<endl;
    }
}
