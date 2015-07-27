#ifndef _VECTOR3_H
#define _VECTOR3_H

#include <cmath>

#include "Matrix.hh"

/*
 * Defines a 3-D Vector
 */
template<typename T> class Vector3 {

private:
  T _elems[3];

public:
  // Constructors
  Vector3() : _elems{(T)0, (T)0, (T)0} {}
  Vector3(T x, T y, T z = 0) : _elems {x, y, z} {}
 
  // Destructor
  ~Vector3() {}

  // Access and Assign Elements
  inline T operator[](int i) const {
    assert(i >= 0);
    assert(i < 3);
 
    return _elems[i];
  }

  inline T & operator[](int i) {
    assert(i >= 0);
    assert(i < 3);
   
    return _elems[i];
  }

  // Compound Assignment Operations
  inline Vector3<T> & operator+=(const Vector3<T> &v) {
    if (this != &v) {
      for (int i = 0; i < 3; i++) {
	_elems[i] += v[i];
      }
    }
    return *this;
  }

  inline Vector3<T> & operator-=(const Vector3<T> &v) {
    if (this != &v) {
      for (int i = 0; i < 3; i++) {
	_elems[i] -= v[i];
      }
    }
    return *this;
  }

  inline Vector3<T> & operator*=(T factor) {
    for (int i =0; i < 3; i++) {
      _elems[i] *= factor;
    }
    return *this;
  }

  inline Vector3<T> & operator*=(const Matrix3<T> &m) {
    for (int i = 0; i < 3; i++) {
      _elems[i] = 0;
      for (int j = 0; j < 3; j++) {
	_elems[i] += m.getelem(i,j) * _elems[j];
      }
    }
    return *this;
  }
 
  inline Vector3<T> & operator/=(T factor) {
    for (int i =0; i < 3; i++) {
      _elems[i] /= factor;
    }
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
inline const Vector3<T> operator+(const Vector3<T> &a, const Vector3<T> &b) {
  return Vector3<T>(a) += b;
}

template<typename T>
inline const Vector3<T> operator-(const Vector3<T> &a, const Vector3<T> &b) {
  return Vector3<T>(a) -= b;
}

// Vector * scalar
template<typename T>
inline const Vector3<T> operator*(const Vector3<T> &a, T factor ) {
  return Vector3<T>(a) *= factor;
}

// scalar * Vector
template<typename T>
inline const Vector3<T> operator*(T factor, const Vector3<T> &b) {
  return Vector3<T>(b) *= factor;
}

// Vector * Matrix(3x3)
template<typename T>
inline const Vector3<T> operator*(const Vector3<T> &a, const Matrix3<T> &m) {
  return Vector3<T>(a) *= m;
}

// Matrix(3x3) * Vector
template<typename T>
inline const Vector3<T> operator*(const Matrix3<T> &m, const Vector3<T> &a) {
  return Vector3<T>(a) *= m;
}

// Vector / scalar
template<typename T>
inline const Vector3<T> operator/( const Vector3<T> &a, T factor ) {
  return Vector3<T>(a) /= factor;
}

// -Vector
template<typename T>
inline const Vector3<T> operator-(const Vector3<T> &a) {
  return Vector3<T>(a) *= (T)-1;
}

// Returns dot product
template<typename T>
inline T operator*(const Vector3<T> &a, const Vector3<T> &b) {
  T dot_product = 0;
  for (int i = 0; i < 3; i++) {
    dot_product += a[i] * b[i];
  }
  return dot_product;
}

// Returns cross product
template<typename T>
inline const Vector3<T> cross(const Vector3<T> &a, const Vector3<T> &b) {
  Vector3<T> cross_product;

  cross_product[0] = a[1] * b[2] - a[2] * b[1];
  cross_product[1] = a[2] * b[0] - a[0] * b[2];
  cross_product[2] = a[0] * b[1] - a[1] * b[0];
  
  return cross_product;
}

// Returns projection of a onto b
template<typename T>
inline const Vector3<T> project(const Vector3<T> &a, const Vector3<T> &b) {
  assert (b * b != 0);

  return (b * (a * b)/(b * b));
}

// Output in form (x, y, z)
template<typename T>
std::ostream & operator<<(std::ostream &os, const Vector3<T> &v ) {
  os << "(" << v[0]  << ", " 
     << v[1] << ", " 
     << v[2] << ")";
  return os;
}

// Reads input in the form (x, y, z)
template<typename T>
std::istream & operator>>(std::istream &is, Vector3<T> &v) {
  T values[3];
  char ch;

  if (!is) return is;

  is >> ch;
  if (ch != '(') is.clear(std::ios_base::failbit);
  for (int i = 0; i < 3; i++) {
    is >> values[i] >> ch;

    if ((i < 2 && ch != ',') || (i == 2 && ch != ')')) {
      is.clear(std::ios_base::failbit);
    }
  }

  if (is) {
    v = Vector3<T>(values[0], values[1], values[2]);
  }

  return is;
}
   
typedef Vector3<float> Vector3F;
typedef Vector3<double> Vector3D;
typedef Vector3<int> Vector3I;

#endif // _VECTOR3_H
