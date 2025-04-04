
// Polymorphism: Method Overloading (Compile-time Polymorphism)

#include <bits/stdc++.h>
using namespace std;

class Math {
public:
    // Overloaded function
    int add(int a, int b) {
        return a + b;
    }

    double add(double a, double b) {
        return a + b;
    }
};

int main() {
    Math obj;
    cout << obj.add(10, 20) << endl;     // Calls int version
    cout << obj.add(10.5, 20.5) << endl; // Calls double version

    return 0;
}
