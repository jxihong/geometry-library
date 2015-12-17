#ifndef _MATRIXSQUARE2_HH
#define _MATRIXSQUARE2_HH

#include "Matrix.hh"

/**
 * Defines 2x2 Matrix subclass
 */
template <typename T> class MatrixSquare2 : public Matrix<T> {

private:

public:
  MatrixSquare2(): Matrix<T>(2, 2) {}

  static MatrixSquare2<T> identity() {
    MatrixSquare2<T> identity;
    
    identity.setelem(0, 0, (T) 1);
    identity.setelem(1, 1, (T) 1);
    return identity;
  }

  static bool isOrthogonal(MatrixSquare2 &m) {
    return (m * transpose(m) == MatrixSquare2<T>::identity());
  } 

};
  
template<typename T>
inline T det(const MatrixSquare2<T> &m) { 
  return (m.getelem(0, 0) * m.getelem(1, 1) 
	  - m.getelem(0, 1) * m.getelem(1,0)); 
}

template<typename T>
inline const MatrixSquare2<T> inverse(const MatrixSquare2<T> &m) {
  MatrixSquare2<T> adj;
  adj.setelem(0, 0, m.getelem(1, 1));
  adj.setelem(0, 1, -1 * m.getelem(0, 1));
  adj.setelem(1, 0, -1 * m.getelem(1, 0));
  adj.setelem(1, 1, m.getelem(0, 0));
  
  return adj / det(m);
}

typedef MatrixSquare2<float> MatrixSquare2F;
typedef MatrixSquare2<double> MatrixSquare2D;
typedef MatrixSquare2<int> MatrixSquare2I;

#endif //_MATRIXSQUARE2_HH
