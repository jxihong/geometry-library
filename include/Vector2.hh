#ifndef _VECTOR2_HH
#define _VECTOR2_HH

#include <vector>
#include <cmath>

#include "MatrixSquare2.hh"

/*
 * Defines a 2D Vector
 */
template<typename T> class Vector2 {

private:
  T _elems[2];

public:
  // Constructors
  Vector2() : _elems{(T)0, (T)0} {}
  Vector2(T x, T y) : _elems {x, y} {}
 
  // Destructor
  ~Vector2() {}

  // Access and Assign Elements
  inline T operator[](int i) const {
    assert(i >= 0);
    assert(i < 2);
 
    return _elems[i];
  }

  inline T & operator[](int i) {
    assert(i >= 0);
    assert(i < 2);
   
    return _elems[i];
  }

  // Compound Assignment Operations
  inline Vector2<T> & operator+=(const Vector2<T> &v) {
    if (this != &v) {
      _elems[0] += v[0];
      _elems[1] += v[1];
    }
    return *this;
  }

  inline Vector2<T> & operator-=(const Vector2<T> &v) {
    if (this != &v) {
      _elems[0] -= v[0];
      _elems[0] -= v[1];
    }
    return *this;
  }

  inline Vector2<T> & operator*=(T factor) {
    _elems[0] *= factor;
    _elems[1] *= factor;
    return *this;
  }
  
  inline Vector2<T> & operator/=(T factor) {
    assert(factor != 0);
    _elems[0] /= factor;
    _elems[1] /= factor;
    return *this;
  }
  
  // Matrix 2x2 * vector
  inline Vector2<T> & operator*=(const MatrixSquare2<T> &m) {
    Vector2<T> temp;
    for (int i = 0; i < 2; i++) {
      T newElem = (T)0;
      for (int j = 0; j < 2; j++) {
	newElem += m.getelem(i,j) * _elems[j];
      }
      temp[i] = newElem;
    }
    *this = temp;
    
    return *this;
  }
 
  // Returns the magnitude of the vector
  inline T magnitude_sq() const {
    return (*this) * (*this);
  }

  inline T magnitude() const {
    return (T) sqrt(magnitude_sq());
  }

  // Normalizes the vector
  inline void normalize() {
    *this /= this->magnitude();
  }

};

template<typename T>
inline const Vector2<T> operator+(const Vector2<T> &a, const Vector2<T> &b) {
  return Vector2<T>(a) += b;
}

template<typename T>
inline const Vector2<T> operator-(const Vector2<T> &a, const Vector2<T> &b) {
  return Vector2<T>(a) -= b;
}

// Vector * scalar
template<typename T>
inline const Vector2<T> operator*(const Vector2<T> &a, T factor ) {
  return Vector2<T>(a) *= factor;
}

// scalar * Vector
template<typename T>
inline const Vector2<T> operator*(T factor, const Vector2<T> &b) {
  return Vector2<T>(b) *= factor;
}

// Vector * Matrix(3x3)
template<typename T>
inline const Vector2<T> operator*(const Vector2<T> &a, const MatrixSquare2<T> &m) {
  return Vector2<T>(a) *= m;
}

// Matrix(3x3) * Vector
template<typename T>
inline const Vector2<T> operator*(const MatrixSquare2<T> &m, const Vector2<T> &a) {
  return Vector2<T>(a) *= m;
}

// Vector / scalar
template<typename T>
inline const Vector2<T> operator/( const Vector2<T> &a, T factor ) {
  return Vector2<T>(a) /= factor;
}

// -Vector
template<typename T>
inline const Vector2<T> operator-(const Vector2<T> &a) {
  return Vector2<T>(a) *= (T)-1;
}

// Returns dot product
template<typename T>
inline T operator*(const Vector2<T> &a, const Vector2<T> &b) {
  return a[0] * b[0] + a[1] * b[1];
}

// Returns cross product
template<typename T>
inline T cross(const Vector2<T> &a, const Vector2<T> &b) {
  return a[0] * a[1] - a[1] * b[0];
}

// Output in form (x, y)
template<typename T>
std::ostream & operator<<(std::ostream &os, const Vector2<T> &v ) {
  os << "(" << v[0]  << ", " 
     << v[1] << ") ";
  return os;
}

// Reads input in the form (x, y, z)
template<typename T>
std::istream & operator>>(std::istream &is, Vector2<T> &v) {
  T values[2];
  char ch;

  if (!is) return is;

  is >> ch;
  if (ch != '(') is.clear(std::ios_base::failbit);
  for (int i = 0; i < 2; i++) {
    is >> values[i] >> ch;

    if ((i = 0 && ch != ',') || (i == 1 && ch != ')')) {
      is.clear(std::ios_base::failbit);
    }
  }

  if (is) {
    v = Vector2<T>(values[0], values[1]);
  }

  return is;
}
   
typedef Vector2<float> Vector2F;
typedef Vector2<double> Vector2D;
typedef Vector2<int> Vector2I;

#endif // _VECTOR2_HH
