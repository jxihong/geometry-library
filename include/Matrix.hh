#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
#include <cassert>

/**
 * Defines a Matrix class of variable size. 
 */
template<typename T> class Matrix {
 
private:
  int _numRows;
  int _numCols;

  T *_contents;

  inline void cleanup() { delete[] _contents; }

  inline void copy(const Matrix<T> &m) {
      _numRows = m._numRows;
      _numCols = m._numCols;
      
      int size = m._numRows * m._numCols;
      _contents = new T[size];
      for (int i = 0; i < size; i++) {
	_contents[i] = m._contents[i];
      }
  }
  
public:
  Matrix(): _numRows(0), _numCols(0) {
    _contents = new T[0];
  }

  Matrix(int rows, int cols): _numRows(rows), _numCols(cols) {
    int size = rows * cols;
    
    _contents = new T[size];
    for (int i = 0; i < size; i++) {
      _contents[i] = (T)0;
    }
  }

  Matrix(const Matrix<T> &m) { copy(m); }

  ~Matrix() { cleanup(); }

  inline int getrows() const {return _numRows;}
  inline int getcols() const {return _numCols;}
  
  inline T getelem(int a, int b) const {
    int index = a * _numCols + b;
    assert (index < _numRows * _numCols);

    return _contents[index];
  }

  inline void setelem(int a, int b, T n) {
    int index = a * _numCols + b;
    assert (index < _numRows * _numCols);

    _contents[index] = n;
  }

  inline Matrix<T> & operator=(const Matrix<T> &m) {
    if (this != &m){
      cleanup();
      copy(m);
    }
    return *this;
  }

  inline Matrix<T> & operator+=(const Matrix<T> &m) {
    if (this != &m) {
      assert (_numRows * _numCols == m._numRows * m._numCols);
      for (int i = 0; i < _numRows * _numCols; i++) {
	_contents[i] += m._contents[i];
      }
    }
    return *this;
  }
  
  inline Matrix<T> & operator-=(const Matrix<T> &m) {
    if (this != &m) {
      assert (_numRows * _numCols == m._numRows * m._numCols);
      for (int i = 0; i < _numRows * _numCols; i++) {
	_contents[i] -= m._contents[i];
      }
    }
    return *this;
  }

  inline Matrix<T> & operator*=(const Matrix<T> &m) {
    if (this != &m) {
      assert (_numCols == m._numRows);
      Matrix tempResult(_numRows, m._numCols);
      for (int i = 0; i < _numRows; i++) { 
	for (int j = 0; j < m._numCols; j++) {
	  int d_prod = 0;
	  for (int k=0; k < _numCols; k++) {
	    d_prod += getelem(i, k) * m.getelem(k, j);
	  }
	  tempResult.setelem(i, j, d_prod);
	}
      }
      *this = tempResult;
    }
    return *this;
  }

  inline Matrix<T> & operator*=(T factor) {
    for (int i = 0; i < _numRows * _numCols; i++) {
      _contents[i] *= factor;
    }
    return *this;
  }

  inline Matrix<T> & operator/=(T factor) {
    assert (factor != (T) 0);

    for (int i = 0; i < _numRows * _numCols; i++) {
      _contents[i] /= factor;
    }
    return *this;
  } 

  inline bool operator==(const Matrix<T> &m) const {
    if (_numRows * _numCols != m._numRows * m._numCols) {
      return false;
    }
    
    for (int i = 0; i < _numRows * _numCols; i++){
      if (_contents[i] != m._contents[i]){
	return false;
      }
    }
    return true;
  }
  
  inline bool operator!=(const Matrix<T> &m) const {
    return !(*this == m);
  }
    
};

template<typename T>
inline const Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &b) {
  return Matrix<T>(a) += b;
}

template<typename T>
inline const Matrix<T> operator-(const Matrix<T> &a, const Matrix<T> &b) {
  return Matrix<T>(a) -= b;
}

template<typename T>
inline const Matrix<T> operator*(const Matrix<T> &a, const Matrix<T> &b) {
  return Matrix<T>(a) *= b;
}

template<typename T>
inline const Matrix<T> operator*(const Matrix<T> &m, T factor) {
  return Matrix<T>(m) *= factor;
}

template<typename T>
inline const Matrix<T> operator*(T factor, const Matrix<T> &m) {
  return Matrix<T>(m) *= factor;
}

template<typename T>
inline const Matrix<T> operator/(const Matrix<T> &m, T factor) {
  return Matrix<T>(m) /= factor;
}

template<typename T>
inline const Matrix<T> transpose(const Matrix<T> &m) {
  Matrix<T> trans(m.getcols(), m.getrows());

  for (int i = 0; i < m.getrows(); i++) {
    for (int j = 0; j < m.getcols(); j++) {
      trans.setelem(j, i, m.getelem(i,j));
    }
  }

  return trans;
}
  
template<typename T>
std::ostream & operator<<(std::ostream &os, const Matrix<T> &m) {
  os << "[";
  for (int i = 0; i < m.getrows(); i++) {
    for (int j = 0; j < m.getcols(); j++) {
      if (j == m.getcols() - 1) {
	os << m.getelem(i, j) << " ; ";
      }
      else {
	os << m.getelem(i, j) << ", ";
      }
    }
  }
  os << "]"; 
  return os;
}

#endif // _MATRIX_H
