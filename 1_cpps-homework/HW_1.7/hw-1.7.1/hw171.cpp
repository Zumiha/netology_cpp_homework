#include <iostream>

// int main(int argc, char** argv) {
int main() {
    
    short a;
    int b;
    long c;
    long long d;
    float e;
    double f;
    long double g;
    bool h;

    std::cout << "short:\t\t" << &a << "  " << sizeof (a) <<"\n";
    std::cout << "int:\t\t" << &b << "  " << sizeof (b) << "\n";
    std::cout << "long:\t\t" << &c << "  " << sizeof (c) << "\n";
    std::cout << "lomg long:\t" << &d << "  " << sizeof (d) << "\n";
    std::cout << "float:\t\t" << &e << "  " << sizeof (e) << "\n";
    std::cout << "double:\t\t" << &f << "  " << sizeof (f) << "\n";
    std::cout << "long double:\t" << &g << "  " << sizeof (g) << "\n";
    std::cout << "bool:\t\t" << &h << "  " << sizeof (h) << "\n";

    return 0;
}