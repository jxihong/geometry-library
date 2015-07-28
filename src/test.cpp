#include "geometry.cpp"

#include <iomanip>

using namespace std;
using namespace geometry;

int main() {
  Matrix3F my_m = Matrix3F::identity();
  cout << "Matrix: " << my_m << endl;
  
  Vector3F my_v(1, 2, 3);
  cout << "Vector: " << my_v << endl;
  
  Vector3F transform = my_v * my_m;
  cout << "Vector * Matrix: " << transform << endl;
  
  return 0;
}
