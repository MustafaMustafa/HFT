#include "TMatrixT.h"
//class TMatrixT<double>;

class Tps{
 protected:
  TMatrixT<double> *matrixX;
  TMatrixT<double> *matrixY;
  TMatrixT<double> *W;
  TMatrixT<double> *A;

 public:
  Tps();
  void Fit(int nMeasurements, double* xMeasurement, double* yMeasurement, double* zMeasurement, double lambda = 0);
  double Ur(double r2);
  double Z(double x, double y);
};
