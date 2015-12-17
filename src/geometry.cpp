#include <vector>
#include <algorithm>

#include "../include/Vector2.hh"


/* Finds the intersection of lines defined by A1x + B1y = C1, and     
 * A2x + B2y = C2.
 */
template <typename T>
Vector2<T> intersectionHelper(T A1, T B1, T C1,
			      T A2, T B2, T C2) {
  MatrixSquare2<T> m;
  m.setelem(0, 0, A1);
  m.setelem(0, 1, B1);
  m.setelem(1, 0, A2);
  m.setelem(1, 1, B2);
  
  if (det(m) == 0) { return NULL; } //Parallel
  Vector2<T> v(C1, C2);
  
  return v * inverse(m);
}

namespace geometry {

  /*
   * Finds shortest distance between two points
   */
  template <typename T>
  T distance(Vector2<T> &p1, Vector2<T> &p2) {
    return (p1 - p2).magnitude();
  }

  /*
   * Finds shortest distance between a point p1 and line 
   * defined by p2 and p3.
   */
  template <typename T>
  T linePointDistance(Vector2<T> &p1, Vector2<T> &p2,  Vector2<T> &p3,
		      bool isSegment) {
    T dist = cross((p2 - p1), (p2 - p3)) / distance(p2, p3);
    
    if (isSegment) {
      if (((p2 - p3) * (p3 - p1)) > 0) {
	dist = distance(p3, p1);
      }
      else if (((p3 - p2) * (p2 - p1)) > 0) {
	dist = distance (p2, p1);
      }
    }
    return std::abs(dist);
  }

  /*
   * Finds the area of a polygon with point-array defined by
   * list of points p.
   */
  template <typename T>
  T polygonArea(std::vector<Vector2<T> > &p) {
    T area = 0;
    
    // Triangulate polygon into p[0], p[i], and p[i+1]
    for (int i = 1; i + 1 < p.size(); i++) {
      Vector2<T> p1 = p[i] - p[0];
      Vector2<T> p2 = p[i+1] - p[0];
      
      area += cross(p1, p2) / (T) 2;
    }

    return std::abs(area);
  }

  /*
   * Finds the intersection of the line defined by p1 and p2,
   * and the one by p3 and p4.
   */
  template <typename T>
  Vector2<T> lineIntersection(Vector2<T> &p1, Vector2<T> &p2,
			      Vector2<T> &p3, Vector2<T> &p4,
			      bool isSegment) {
    
    T A1 = p2[1] - p1[1];
    T B1 = p2[0] - p1[0];
    T C1 = A1 * p1[0] + B1 * p1[1];
    
    T A2 = p4[1] - p3[1];
    T B2 = p4[0] - p3[0];
    T C2 = A1 * p3[0] + B1 * p3[1];
    
    auto intersection = intersectionHelper(A1, B1, C1, 
					   A2, B2, C2);

    if (!intersection) { return NULL; }
    
    if (isSegment) {
      // Checks with intersection is within boundaries of each line
      for (int i = 0; i < 2; i++) {
	if (min(p1[i], p2[i]) > intersection[i] || 
	    max(p1[i], p2[i]) < intersection[i]) {
	  return NULL;
	}
	if (min(p3[i], p4[i]) > intersection[i] || 
	    max(p3[i], p4[i]) < intersection[i]) {
	  return NULL;
	}
      }
    }
    return intersection;
  }
  
  /**
   * Finds the image of reflecting a point p1 across line
   * defined by p2 and p3.
   */
  template <typename T>
  Vector2<T> reflect(Vector2<T> &p1, Vector2<T> &p2, Vector2<T> &p3) {
    // Find perpendicular line
    T A = p3[1] - p2[1];
    T B = p3[0] - p2[0];
    T C = A * p2[0] + B * p2[1];
    T D = -1 * B * p1[0] + A * p1[1];
    
    // Find intersection of two lines
    auto intersection = intersectionHelper(A, B, C, 
					   -1 * B, A, D);
    return intersection - (p1 - intersection);
  }
}
