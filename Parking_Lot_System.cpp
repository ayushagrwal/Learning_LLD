
// ----------Design a Parking Lot System---------
// Problem Statement
// Design a parking lot system that supports:
// ✅ Different types of vehicles (Car, Bike, Truck)
// ✅ Multiple parking spots (Small, Medium, Large)
// ✅ Parking, Unparking, and Checking available spots
// ✅ Payment system for calculating parking fees

// 👉 Think about: Classes (Vehicle, ParkingSpot, ParkingLot), inheritance, and method design.


#include <bits/stdc++.h>
using namespace std;

// Enum for Vehicle Type
enum class VehicleType { BIKE, CAR, TRUCK };

// Enum for Parking Spot Size
enum class SpotSize { SMALL, MEDIUM, LARGE };

// Base class for Vehicles
class Vehicle {
public:
    string plateNumber;
    VehicleType type;
    time_t entryTime;

    Vehicle(string plate, VehicleType t) : plateNumber(plate), type(t) {
        entryTime = time(0); // Store entry time
    }

    virtual SpotSize getRequiredSpotSize() = 0;
    virtual ~Vehicle() {}
};

// Derived classes for specific vehicle types
class Bike : public Vehicle {
public:
    Bike(string plate) : Vehicle(plate, VehicleType::BIKE) {}
    SpotSize getRequiredSpotSize() override { return SpotSize::SMALL; }
};

class Car : public Vehicle {
public:
    Car(string plate) : Vehicle(plate, VehicleType::CAR) {}
    SpotSize getRequiredSpotSize() override { return SpotSize::MEDIUM; }
};

class Truck : public Vehicle {
public:
    Truck(string plate) : Vehicle(plate, VehicleType::TRUCK) {}
    SpotSize getRequiredSpotSize() override { return SpotSize::LARGE; }
};

// Parking Spot class
class ParkingSpot {
public:
    int id;
    SpotSize size;
    bool isOccupied;
    Vehicle* parkedVehicle;

    ParkingSpot(int spotId, SpotSize s) : id(spotId), size(s), isOccupied(false), parkedVehicle(nullptr) {}

    bool canFitVehicle(Vehicle* vehicle) {
        return !isOccupied && vehicle->getRequiredSpotSize() <= size;
    }

    void park(Vehicle* vehicle) {
        parkedVehicle = vehicle;
        isOccupied = true;
    }

    void unpark() {
        parkedVehicle = nullptr;
        isOccupied = false;
    }
};

// Parking Lot class
class ParkingLot {
private:
    vector<ParkingSpot> spots;
    unordered_map<string, ParkingSpot*> vehicleMap; // Map vehicle plate to spot
    unordered_map<SpotSize, double> parkingRates = {
        {SpotSize::SMALL, 1.5}, {SpotSize::MEDIUM, 2.5}, {SpotSize::LARGE, 3.5}
    };

public:
    ParkingLot(int small, int medium, int large) {
        int id = 1;
        for (int i = 0; i < small; i++) spots.emplace_back(id++, SpotSize::SMALL);
        for (int i = 0; i < medium; i++) spots.emplace_back(id++, SpotSize::MEDIUM);
        for (int i = 0; i < large; i++) spots.emplace_back(id++, SpotSize::LARGE);
    }

    bool parkVehicle(Vehicle* vehicle) {
        for (auto& spot : spots) {
            if (spot.canFitVehicle(vehicle)) {
                spot.park(vehicle);
                vehicleMap[vehicle->plateNumber] = &spot;
                cout << "Vehicle " << vehicle->plateNumber << " parked at spot " << spot.id << endl;
                return true;
            }
        }
        cout << "No available spot for vehicle " << vehicle->plateNumber << endl;
        return false;
    }

    double unparkVehicle(string plateNumber) {
        if (vehicleMap.find(plateNumber) == vehicleMap.end()) {
            cout << "Vehicle not found in the parking lot!\n";
            return 0;
        }

        ParkingSpot* spot = vehicleMap[plateNumber];
        time_t exitTime = time(0);
        double hours = difftime(exitTime, spot->parkedVehicle->entryTime) / 3600.0;
        double cost = parkingRates[spot->size] * max(1.0, hours);

        cout << "Vehicle " << plateNumber << " unparked from spot " << spot->id << " - Parking Fee: $" << cost << endl;

        spot->unpark();
        vehicleMap.erase(plateNumber);
        return cost;
    }

    void availableSpots() {
        int small = 0, medium = 0, large = 0;
        for (auto& spot : spots) {
            if (!spot.isOccupied) {
                if (spot.size == SpotSize::SMALL) small++;
                else if (spot.size == SpotSize::MEDIUM) medium++;
                else if (spot.size == SpotSize::LARGE) large++;
            }
        }
        cout << "Available Spots - Small: " << small << ", Medium: " << medium << ", Large: " << large << endl;
    }
};

// Main function to test the parking lot system
int main() {
    ParkingLot lot(2, 2, 1); // 2 Small, 2 Medium, 1 Large spots

    Vehicle* bike1 = new Bike("B123");
    Vehicle* car1 = new Car("C456");
    Vehicle* truck1 = new Truck("T789");

    lot.parkVehicle(bike1);
    lot.parkVehicle(car1);
    lot.parkVehicle(truck1);

    lot.availableSpots();

    // Simulate unpark
    lot.unparkVehicle("B123");
    lot.unparkVehicle("C456");

    lot.availableSpots();

    delete bike1;
    delete car1;
    delete truck1;

    return 0;
}
