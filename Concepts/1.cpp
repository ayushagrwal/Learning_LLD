
// Classes & Objects (Encapsulation)

#include <bits/stdc++.h>
using namespace std;

class Car {
    public:
        string brand;
        int speed;

    //constructor
    Car(string b, int s){
        brand = b;
        speed = s;
    }

    //Method
    void showDetails(){
        cout << "Brand: " << brand << ", Speed: " << speed << " km/h" << endl;
    }
};

int main() {
    Car c1("Tesla", 40);
    Car c2("BMW", 400);

    c1.showDetails();
    c2.showDetails();
    return 0;
}