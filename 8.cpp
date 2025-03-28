// Multiple Inheritance

#include <bits/stdc++.h>
using namespace std;

class Engine {
public:
    void start() {
        cout << "Engine started" << endl;
    }
};

class Wheels {
public:
    void rotate() {
        cout << "Wheels rotating" << endl;
    }
};

// Multiple Inheritance
class Car : public Engine, public Wheels {
public:
    void drive() {
        cout << "Car is driving" << endl;
    }
};

int main() {
    Car myCar;
    myCar.start();
    myCar.rotate();
    myCar.drive();
    return 0;
}
