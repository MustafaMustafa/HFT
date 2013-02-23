/*!
 * \class StPxlRawHit 
 * \author Qiu Hao, Jan 2013
 * \pixel raw hit before clustering, one raw hit is one fired pixel
 */
/*
 ***************************************************************************
 */
#ifndef StPxlRawHit_hh
#define StPxlRawHit_hh

#include "StContainers.h"

class StPxlRawHit
{
public:
    StPxlRawHit();
    StPxlRawHit(int sector, int ladder, int sensor, int row, int column, int idTruth);
    ~StPxlRawHit();

    int  sector() const;
    int  ladder() const;
    int  sensor() const;
    int  sensorId() const; //!< (sector-1)*40+(ladder-1)*10+sensor-1, 0-399
    int  row() const;
    int  column() const;
    int  idTruth() const; //!< for embedding, 0 as background

    void setSector(int sector);
    void setLadder(int ladder);
    void setSensor(int sensor);
    void setSensorId(int sensorId);
    void setRow(int row);
    void setColumn(int column);
    void setIdTruth(int idTruth);

    void print(); //!< print all information

protected:
    Short_t mSensorId; //!< (sector-1)*40+(ladder-1)*10+sensor-1, 0-399
    Short_t mRow;
    Short_t mColumn;
    UShort_t mIdTruth; //!< for embedding, 0 as background

    ClassDef(StPxlRawHit, 1)
};
#endif
