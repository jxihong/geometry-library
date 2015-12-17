#include <vector>
#include <stack>
#include <algorithm>

#include "../include/Vector2.hh"

template <typename T>
bool left(Vector2<T> &p1, Vector2<T> &p2) {
  return p1[0] < p2[0];
}

template <typename T>
struct CompareSlopes {
  CompareSlopes(Vector2<T> &p): _p(p) {} 
  inline bool operator() (Vector2<T> &p1, Vector2<T> &p2) {
    return ((p1[1] - _p[1]) / (p1[0] - _p[0]) <
	    (p2[1] - _p[1]) / (p2[0] - _p[0]));
  }
private:
  Vector2<T> _p;
};

namespace geometry {
  /*
   * Finds the convex hull given points p.
   */
  template <typename T>
  std::vector<Vector2<T> > convexHull(std::vector<Vector2<T> > &p) {
    //Find leftmost point and remove it
    auto leftmost = std::min_element(p.begin(), p.end(), left);
    std::swap(leftmost, p.back());
    p.pop_back;
    
    // Sort the points by increasing polar angle
    std::sort(p.begin(), p.end(), CompareSlopes<T>(leftmost));
    
    std::vector<Vector2<T> > hull;
    
    hull.push_back(leftmost);
    for (int i = 0; i < p.size(); i++) {
      if (hull.size() < 2) { hull.push_back(p[i]); continue; }
      
      auto prev = hull.back();
      hull.pop_back();
      if (cross(prev - hull.back(), p[i] - prev) < 0) {
	hull.push_back(p[i]);
      } else {
	hull.push_back(prev);
	hull.push_back(p[i]);
      }
    }
    return hull;
  }
}
