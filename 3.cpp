
// Inheritance (Reusability)

#include <bits/stdc++.h>
using namespace std;

// Base Class
class Car {
    public:
        string brand;
        Car(string b){
            brand = b;
        }
        void honk(){
            cout << brand << " says Beep Beep!" << endl;
        }
};

// Derived Class (Inheriting Car)
class SportsCar : public Car{
    public:
    int turboBoost;
    
    SportsCar(string b, int boost) : Car(b){
        turboBoost = boost;
    }

    void showBoost() {
        cout << brand << " has turbo boost of " << turboBoost << " HP!" << endl;
    }

};

int main(){
    SportsCar ferrari("Ferrari", 700);
    ferrari.honk();
    ferrari.showBoost();
    return 0;
}