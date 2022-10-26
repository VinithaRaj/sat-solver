#include<iostream>
using namespace std;

class base {
  int a;
};

template <typename Type>
Type sqr( Type x ) {
    return x*x;
}

int main() {
    cout << "Pi squared is " << sqr<double>( 3.141592653589793 ) << endl;
    cout << "3 squared is " << sqr<int>( 3 ) << endl;
    cout << "3 squared is " << sqr<char>( '3' ) << endl;

    return 0;
}

