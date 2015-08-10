#include "../include/Vector3.hh"
#include "../include/MatrixSquare.hh"

namespace geometry {

  /*
   * Finds shortest distance between two points
   */
  template <typename T>
  T distance(Vector3<T> &p1, Vector3<T> &p2) {
    return (p1 - p2).magnitude();
  }

  /*
   * Finds shortest distance between a line defined by 
   * p1 and p2, and a point p3
   */
  template <typename T>
  T linePointDistance(Vector3<T> &p1, Vector3<T> &p2,  Vector3<T> &p3,
		      bool isSegment) {
    T dist = cross((p1 - p2), (p1 - p3)).magnitude() / distance(p1, p2);
    
    if (isSegment) {
      if (((p1 - p2) * (p2 - p3)) > 0) {
	dist = distance(p2, p3);
      }
      else if (((p2 - p1) * (p1 - p3)) > 0) {
	dist = distance (p1, p3);
      }
    }
    return std::abs(dist);
  }

  /*
   * Finds the area of a polygon with point-array defined by
   * vector p
   */
  template <typename T>
  T polygonArea(std::vector<Vector3<T> > &p) {
    T area = 0;
    
    // Triangulate polygon into p[0], p[i], and p[i+1]
    for (int i = 1; i + 1 < p.size(); i++) {
      Vector3<T> p1 = p[i] - p[0];
      Vector3<T> p2 = p[i+1] - p[0];
      
      T triangleArea = cross(p1, p2).magnitude_sq();
      if (triangleArea >= 0) {
	area +=  (T)sqrt(triangleArea)/2;
      }
      else {
	area += (T)-1 * (T)sqrt(triangleArea)/2;
      }
    }

    return std::abs(area);
  }

}
