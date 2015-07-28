#ifndef _MATRIX3_H
#define _MATRIX3_H

#include "Matrix.hh"


/**
 * Defines Matrix subclass with fixed size 3x3
 */
template <typename T> class Matrix3 : public Matrix<T> {

private:

public:
  Matrix3(): Matrix<T>(3, 3) {}

  static Matrix3<T> identity() {
    Matrix3<T> identity;

    for (int i = 0; i < 3; i++) {
      identity.setelem(i, i, (T)1);
    }

    return identity;
  }
      
};

typedef Matrix3<float> Matrix3F;
typedef Matrix3<double> Matrix3D;
typedef Matrix3<int> Matrix3I;

#endif //_MATRIX3_H
