#include "geometry.cpp"
#include "algorithms.cpp"

#include <iomanip>

using namespace std;
using namespace geometry;

int main() {
  MatrixSquare2F my_m = MatrixSquare2F::identity();
  cout << "Matrix: " << my_m << endl;
  
  Vector2F my_v(1, 2);
  cout << "Vector: " << my_v << endl;
  
  Vector2F transform = my_v * my_m;
  cout << "Vector * Matrix: " << transform << endl;
  
  return 0;
}
