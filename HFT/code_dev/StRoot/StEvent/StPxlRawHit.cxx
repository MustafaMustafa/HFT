/*!
 * \class StPxlRawHit 
 * \author Qiu Hao, Jan 2012
 * \pixel raw hit before clustering, one raw hit is one fired pixel
 */
/***************************************************************************
 */
#include "StPxlRawHit.h"

ClassImp(StPxlRawHit)

StPxlRawHit::~StPxlRawHit() { /* noop */ }

StPxlRawHit::StPxlRawHit()
{
    mSensorId = -1;
    mRow = -1;
    mColumn = -1;
    mIdTruth = 0;
}

StPxlRawHit::StPxlRawHit(int sector, int ladder, int sensor, int row, int column, int idTruth)
{
    mSensorId = 40*(sector-1) + 10*(ladder-1) + sensor-1;
    mRow = row;
    mColumn = column;
    mIdTruth = idTruth;
}

int StPxlRawHit::sector() const {return mSensorId/40+1;}
int StPxlRawHit::ladder() const {return mSensorId%40/10+1;}
int StPxlRawHit::sensor() const {return mSensorId%10+1;}
int StPxlRawHit::sensorId() const {return mSensorId;}
int StPxlRawHit::row() const {return mRow;}
int StPxlRawHit::column() const {return mColumn;}
int StPxlRawHit::idTruth() const {return mIdTruth;}

void StPxlRawHit::setSector(int sector)
{
    mSensorId = 40*(sector-1) + 10*(ladder()-1) + sensor()-1;
}

void StPxlRawHit::setLadder(int ladder)
{
    mSensorId = 40*(sector()-1) + 10*(ladder-1) + sensor()-1;
}

void StPxlRawHit::setSensor(int sensor)
{
    mSensorId = 40*(sector()-1) + 10*(ladder()-1) + sensor-1;
}

void StPxlRawHit::setSensorId(int sensorId)
{
    mSensorId = sensorId;
}

void StPxlRawHit::setRow(int row)
{
    mRow = row;
}

void StPxlRawHit::setColumn(int column)
{
    mColumn = column;
}

void StPxlRawHit::setIdTruth(int idTruth)
{
    mIdTruth = idTruth;
}

void StPxlRawHit::print()
{
    printf("StPxlRawHit: sec:%i lad:%i sen:%i sId:%i row:%i col:%i idT:%i\n", sector(), ladder(), sensor(), sensorId(), row(), column(), idTruth());
}
