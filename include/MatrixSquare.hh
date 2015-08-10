#ifndef _MATRIXSQUARE_H
#define _MATRIXSQUARE_H

#include "Matrix.hh"


/**
 * Defines Matrix subclass with square size
 */
template <typename T> class MatrixSquare : public Matrix<T> {

private:

public:
  MatrixSquare(int n): Matrix<T>(n, n) {}

  static MatrixSquare<T> identity(int n) {
    MatrixSquare<T> identity(n);

    for (int i = 0; i < identity.getrows(); i++) {
      identity.setelem(i, i, (T)1);
    }

    return identity;
  }

  static bool isOrthogonal(MatrixSquare<T> &m) {
    return (m * transpose(m) == MatrixSquare<T>::identity(m.getrows()));
  } 

};

typedef MatrixSquare<float> MatrixSquareF;
typedef MatrixSquare<double> MatrixSquareD;
typedef MatrixSquare<int> MatrixSquareI;

#endif //_MATRIXSQUARE_H
