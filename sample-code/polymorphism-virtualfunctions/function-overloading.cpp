#include <iostream>
using namespace std;

int Volume(int s) {  // Volume of a cube.
  return s * s * s;
}

double Volume(double r, int h) {  // Volume of a cylinder.
  return 3.1415926 * r * r * static_cast<double>(h);
}

long Volume(long l, int b, int h) {  // Volume of a cuboid.
  return l * b * h;
}

int main() {
  std::cout << Volume(10) << endl;
  std::cout << Volume(2.5, 8) << endl;
  std::cout << Volume(100l, 75, 15) << endl;
}

