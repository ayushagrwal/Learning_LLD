// ----------------5️⃣ Design a Ride-Sharing System (Like Uber/Ola)--------------------
// Problem Statement
// Design a cab booking system that allows:
// ✅ Users to request rides and drivers to accept them
// ✅ Users to choose ride types (Mini, Sedan, SUV)
// ✅ Track the ride status (Booked, In Progress, Completed)
// ✅ Fare calculation based on distance

// 👉 Think about: User, Driver, Ride, Payment.

#include <bits/stdc++.h>
using namespace std;

enum RideStatus { BOOKED, IN_PROGRESS, COMPLETED };
enum RideType { MINI, SEDAN, SUV };

class Ride {
public:
    int rideID;
    string user;
    string driver;
    RideStatus status;
    RideType type;
    double distance;
    double fare;

    Ride(int id, string u, RideType t, double d) : rideID(id), user(u), type(t), distance(d) {
        status = BOOKED;
        driver = "";
        fare = calculateFare();
    }

    void assignDriver(string d) {
        driver = d;
        status = IN_PROGRESS;
    }

    void completeRide() {
        status = COMPLETED;
    }

    double calculateFare() {
        double rate;
        switch (type) {
            case MINI: rate = 10; break;
            case SEDAN: rate = 15; break;
            case SUV: rate = 20; break;
        }
        return distance * rate;
    }
};

class User {
public:
    string name;
    User(string n) : name(n) {}

    Ride requestRide(int rideID, RideType type, double distance) {
        cout << name << " requested a ride of type " << type << " for " << distance << " km." << endl;
        return Ride(rideID, name, type, distance);
    }
};

class Driver {
public:
    string name;
    bool available;

    Driver(string n) : name(n), available(true) {}

    bool acceptRide(Ride &ride) {
        if (available) {
            ride.assignDriver(name);
            available = false;
            cout << name << " accepted the ride." << endl;
            return true;
        }
        return false;
    }

    void completeRide(Ride &ride) {
        ride.completeRide();
        available = true;
        cout << name << " completed the ride." << endl;
    }
};

int main(){
    
    User user("Ayush");
    Driver driver1("Rahul");
    Driver driver2("Amit");
    
    Ride ride1 = user.requestRide(1, SEDAN, 10.0);
    if (!driver1.acceptRide(ride1)) {
        driver2.acceptRide(ride1);
    }
    
    cout << "Ride Fare: Rs." << ride1.fare << endl;
    driver1.completeRide(ride1);

    return 0;
}