#include <bits/stdc++.h>
using namespace std;

class Ride {
private:
    int rideDistance;
    pair<int, int> startLocation;

public:
    Ride(int distance, pair<int, int> location)
        : rideDistance(distance), startLocation(location) {}

    int getRideDistance() const { return rideDistance; }
    pair<int, int> getStartLocation() const { return startLocation; }
};

class Rider {
private:
    string name;
    string riderID;
    vector<Ride*> rideHistory;

public:
    Rider(string name, string id)
        : name(name), riderID(id) {}

    string getRiderID() const { return riderID; }

    void addRide(Ride* ride) {
        rideHistory.push_back(ride);
    }

    void printRideHistory() const {
        cout << "Ride history for rider " << name << ":\n";
        for (auto ride : rideHistory) {
            auto loc = ride->getStartLocation();
            cout << "  Start Location: (" << loc.first << "," << loc.second << ")"
                 << ", Distance: " << ride->getRideDistance() << " km\n";
        }
    }
};

class Driver {
private:
    string name;
    string driverID;
    bool isAvailable;
    pair<int, int> currentLocation;

public:
    Driver(string name, string id, pair<int, int> location)
        : name(name), driverID(id), currentLocation(location), isAvailable(true) {}

    string getDriverID() const { return driverID; }
    string getName() const { return name; }
    bool available() const { return isAvailable; }
    pair<int, int> getLocation() const { return currentLocation; }

    void updateLocation(pair<int, int> loc) { currentLocation = loc; }
    void setAvailability(bool avail) { isAvailable = avail; }
};

class CabBookingPlatform {
private:
    unordered_map<string, Rider*> riders;
    unordered_map<string, Driver*> drivers;
    const double MAX_PICKUP_DISTANCE = 10.0;

    double calculateDistance(pair<int, int> a, pair<int, int> b) {
        return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
    }

public:
    CabBookingPlatform() {
        // for (auto& [_, rider] : riders) delete rider;
        // for (auto& [_, driver] : drivers) delete driver;
    }

    void registerRider(string name, string id) {
        if (riders.count(id)) {
            cout << "Rider already exists.\n";
            return;
        }
        riders[id] = new Rider(name, id);
        cout << "Rider registered successfully.\n";
    }

    void registerDriver(string name, string id, pair<int, int> location) {
        if (drivers.count(id)) {
            cout << "Driver already exists.\n";
            return;
        }
        drivers[id] = new Driver(name, id, location);
        cout << "Driver registered successfully.\n";
    }

    void updateCabLocation(string driverID, pair<int, int> location) {
        if (!drivers.count(driverID)) {
            cout << "Driver not found.\n";
            return;
        }
        drivers[driverID]->updateLocation(location);
        cout << "Location updated.\n";
    }

    void updateDriverAvailability(string driverID, bool status) {
        if (!drivers.count(driverID)) {
            cout << "Driver not found.\n";
            return;
        }
        drivers[driverID]->setAvailability(status);
        cout << "Driver availability updated.\n";
    }

    void bookCab(string riderID, pair<int, int> pickupLocation) {
        if (!riders.count(riderID)) {
            cout << "Rider not found.\n";
            return;
        }

        Driver* selectedDriver = nullptr;
        double minDist = DBL_MAX;

        for (auto& it : drivers) {
            if (it.second->available()) {
                double dist = calculateDistance(it.second->getLocation(), pickupLocation);
                if (dist <= MAX_PICKUP_DISTANCE && dist < minDist) {
                    minDist = dist;
                    selectedDriver = it.second;
                }
            }
        }

        if (!selectedDriver) {
            cout << "No available drivers nearby.\n";
            return;
        }

        int rideDistance = rand() % 20 + 1; // simulate ride distance
        Ride* ride = new Ride(rideDistance, pickupLocation);
        riders[riderID]->addRide(ride);

        selectedDriver->setAvailability(false);

        cout << "Ride booked with driver: " << selectedDriver->getName() << " (" << selectedDriver->getDriverID() << ")\n";
    }

    void endRide(string driverID) {
        if (!drivers.count(driverID)) {
            cout << "Driver not found.\n";
            return;
        }
        drivers[driverID]->setAvailability(true);
        cout << "Ride ended for driver " << driverID << ".\n";
    }

    void getRideHistory(string riderID) {
        if (!riders.count(riderID)) {
            cout << "Rider not found.\n";
            return;
        }
        riders[riderID]->printRideHistory();
    }
};

int main() {
    CabBookingPlatform platform;

    // Demo: registering users
    platform.registerRider("Ayush", "r1");
    platform.registerDriver("Raj", "d1", {0, 0});
    platform.registerDriver("Aman", "d2", {8, 8});

    // Update locations and availability
    platform.updateCabLocation("d1", {2, 3});
    platform.updateDriverAvailability("d1", true);
    platform.updateDriverAvailability("d2", true);

    // Book a ride
    platform.bookCab("r1", {3, 3});

    // End a ride
    platform.endRide("d1");

    // Check history
    platform.getRideHistory("r1");

    return 0;
}
