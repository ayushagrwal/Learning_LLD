#include <bits/stdc++.h>
using namespace std;

enum class VehicleType {
    TWO_WHEELER,
    FOUR_WHEELER
};

enum class PassType {
    SINGLE,
    RETURN,
    SEVEN_DAY
};

class Vehicle {
private:
    string registrationNumber;
    VehicleType type;

public:
    Vehicle(const string& regNum, VehicleType vType) : registrationNumber(regNum), type(vType) {}
    
    string getRegistrationNumber() const { return registrationNumber; }
    VehicleType getType() const { return type; }
    
    string getVehicleTypeString() const {
        return (type == VehicleType::TWO_WHEELER) ? "Two Wheeler" : "Four Wheeler";
    }
};

class TollPass {
protected:
    string vehicleRegNum;
    PassType passType;
    time_t purchaseTime;
    double amount;
    bool used;

public:
    TollPass(const string& regNum, PassType type, double amt) 
        : vehicleRegNum(regNum), passType(type), amount(amt), used(false) {
        purchaseTime = time(0);
    }
    
    virtual ~TollPass() {}
    virtual bool isValid() const = 0;
    virtual string getDescription() const = 0;
    
    string getVehicleRegNum() const { return vehicleRegNum; }
    PassType getPassType() const { return passType; }
    double getAmount() const { return amount; }
    time_t getPurchaseTime() const { return purchaseTime; }
    bool isUsed() const { return used; }
    void markAsUsed() { used = true; }
};

// Single Pass - one time use
class SinglePass : public TollPass {
public:
    SinglePass(const string& regNum, double amt) 
        : TollPass(regNum, PassType::SINGLE, amt) {}
    
    bool isValid() const override {
        return !used;
    }
    
    string getDescription() const override {
        return "Single Pass (One-time use) - " + to_string((int)amount);
    }
};

// Return Pass - valid for 24 hours with return trip
class ReturnPass : public TollPass {
private:
    int usageCount;
    
public:
    ReturnPass(const string& regNum, double amt) 
        : TollPass(regNum, PassType::RETURN, amt), usageCount(0) {}
    
    bool isValid() const override {
        time_t currentTime = time(0);
        double hoursPassed = difftime(currentTime, purchaseTime) / 3600.0;
        return (hoursPassed <= 24.0) && (usageCount < 2);
    }
    
    void use() {
        usageCount++;
    }
    
    string getDescription() const override {
        return "Return Pass (Valid for 24 hours, 2 trips) - " + to_string((int)amount);
    }
    
    int getUsageCount() const { return usageCount; }
};

// Seven Day Pass - unlimited for 7 days
class SevenDayPass : public TollPass {
public:
    SevenDayPass(const string& regNum, double amt) 
        : TollPass(regNum, PassType::SEVEN_DAY, amt) {}
    
    bool isValid() const override {
        time_t currentTime = time(0);
        double daysPassed = difftime(currentTime, purchaseTime) / (24.0 * 3600.0);
        return daysPassed <= 7.0;
    }
    
    string getDescription() const override {
        return "7-Day Pass (Unlimited for 7 days) - " + to_string((int)amount);
    }
};

// Toll Booth class to track statistics
class TollBooth {
private:
    string boothId;
    string tollId;
    int vehiclesProcessed;
    double totalChargesCollected;

public:
    TollBooth(const string& bId, const string& tId) 
        : boothId(bId), tollId(tId), vehiclesProcessed(0), totalChargesCollected(0.0) {}
    
    void processVehicle(double charge) {
        vehiclesProcessed++;
        totalChargesCollected += charge;
    }
    
    string getBoothId() const { return boothId; }
    string getTollId() const { return tollId; }
    int getVehiclesProcessed() const { return vehiclesProcessed; }
    double getTotalChargesCollected() const { return totalChargesCollected; }
};

// Toll class representing a toll plaza
class Toll {
private:
    string tollId;
    string location;
    vector<TollBooth> booths;
    
    // Pricing structure: [TwoWheeler][PassType], [FourWheeler][PassType]
    double pricing[2][3] = {
        {50, 80, 300},   // Two Wheeler: Single, Return, 7-Day
        {100, 150, 600}  // Four Wheeler: Single, Return, 7-Day
    };

public:
    Toll(const string& id, const string& loc) : tollId(id), location(loc) {
        // Initialize some toll booths
        for(int i = 1; i <= 3; i++) {
            booths.emplace_back(tollId + "_BOOTH_" + to_string(i), tollId);
        }
    }
    
    string getTollId() const { return tollId; }
    string getLocation() const { return location; }
    vector<TollBooth>& getBooths() { return booths; }
    
    double getPrice(VehicleType vehicleType, PassType passType) const {
        int vTypeIndex = (vehicleType == VehicleType::TWO_WHEELER) ? 0 : 1;
        int passTypeIndex = (passType == PassType::SINGLE) ? 0 : (passType == PassType::RETURN) ? 1 : 2;
        return pricing[vTypeIndex][passTypeIndex];
    }
    
    void displayPricing(VehicleType vehicleType) const {
        cout << "\n=== Toll Charges for " << location << " ===\n";
        cout << "Vehicle Type: " << (vehicleType == VehicleType::TWO_WHEELER ? "Two Wheeler" : "Four Wheeler") << "\n";
        cout << "1. Single Pass: " << getPrice(vehicleType, PassType::SINGLE) << "\n";
        cout << "2. Return Pass: " << getPrice(vehicleType, PassType::RETURN) << "\n";
        cout << "3. 7-Day Pass: " << getPrice(vehicleType, PassType::SEVEN_DAY) << "\n";
    }
};

// Main Toll Management System
class TollManagementSystem {
private:
    vector<Toll> tolls;
    map<string, unique_ptr<TollPass>> activePasses; // vehicle reg num -> active pass
public:
    TollManagementSystem() {
        // Initialize some tolls
        tolls.emplace_back("TOLL001", "Delhi-Gurgaon Highway");
        tolls.emplace_back("TOLL002", "Mumbai-Pune Expressway");
        tolls.emplace_back("TOLL003", "Bangalore-Chennai Highway");
    }
    
    Toll* findToll(const string& tollId) {
        for(auto& toll : tolls) {
            if(toll.getTollId() == tollId) {
                return &toll;
            }
        }
        return nullptr;
    }
    
    bool hasValidPass(const string& vehicleRegNum) {
        auto it = activePasses.find(vehicleRegNum);
        if(it != activePasses.end() && it->second->isValid()) {
            return true;
        }
        // Remove invalid pass
        if(it != activePasses.end()) {
            activePasses.erase(it);
        }
        return false;
    }
    
    TollPass* getActivePass(const string& vehicleRegNum) {
        auto it = activePasses.find(vehicleRegNum);
        return (it != activePasses.end()) ? it->second.get() : nullptr;
    }
    
    void purchasePass(const string& vehicleRegNum, VehicleType vehicleType, PassType passType, const string& tollId) {
        Toll* toll = findToll(tollId);
        if(!toll) {
            cout << "Invalid toll ID!\n";
            return;
        }
        
        double price = toll->getPrice(vehicleType, passType);
        unique_ptr<TollPass> pass;
        
        switch(passType) {
            case PassType::SINGLE:
                pass = make_unique<SinglePass>(vehicleRegNum, price);
                break;
            case PassType::RETURN:
                pass = make_unique<ReturnPass>(vehicleRegNum, price);
                break;
            case PassType::SEVEN_DAY:
                pass = make_unique<SevenDayPass>(vehicleRegNum, price);
                break;
        }
        
        activePasses[vehicleRegNum] = move(pass);
        
        // Process through first available booth
        auto& booths = toll->getBooths();
        if(!booths.empty()) {
            booths[0].processVehicle(price);
        }
        
        cout << "Pass purchased successfully!\n";
        cout << "Pass Details: " << activePasses[vehicleRegNum]->getDescription() << "\n";
    }
    
    bool processVehicle(const Vehicle& vehicle, const string& tollId, int boothIndex = 0) {
        Toll* toll = findToll(tollId);
        if(!toll) {
            cout << "Invalid toll ID!\n";
            return false;
        }
        
        auto& booths = toll->getBooths();
        if(boothIndex >= booths.size()) {
            cout << "Invalid booth index!\n";
            return false;
        }
        
        cout << "\n Processing Vehicle: " << vehicle.getRegistrationNumber() 
             << " (" << vehicle.getVehicleTypeString() << ")\n";
        cout << "Location: " << toll->getLocation() << "\n";
        cout << "Booth: " << booths[boothIndex].getBoothId() << "\n";
        
        if(hasValidPass(vehicle.getRegistrationNumber())) {
            TollPass* pass = getActivePass(vehicle.getRegistrationNumber());
            cout << "\nValid pass found!\n";
            cout << "Pass Type: " << pass->getDescription() << "\n";
            
            // Handle usage for different pass types
            if(pass->getPassType() == PassType::SINGLE) {
                pass->markAsUsed();
                activePasses.erase(vehicle.getRegistrationNumber());
                cout << "Single pass used and removed.\n";
            } else if(pass->getPassType() == PassType::RETURN) {
                ReturnPass* returnPass = dynamic_cast<ReturnPass*>(pass);
                returnPass->use();
                cout << "Return pass used. Remaining uses: " << (2 - returnPass->getUsageCount()) << "\n";
            }
            
            // Track vehicle processing (no charge for valid pass)
            booths[boothIndex].processVehicle(0);
            cout << "Vehicle allowed to pass through.\n";
            return true;
        } else {
            cout << "\nNo valid pass found.\n";
            toll->displayPricing(vehicle.getType());
            
            cout << "\nChoose a pass (1-3) or 0 to cancel: ";
            int choice;
            cin >> choice;
            
            if(choice >= 1 && choice <= 3) {
                PassType selectedPassType = static_cast<PassType>(choice - 1);
                purchasePass(vehicle.getRegistrationNumber(), vehicle.getType(), 
                           selectedPassType, tollId);
                cout << "Vehicle allowed to pass through.\n";
                return true;
            } else {
                cout << "Transaction cancelled. Vehicle not allowed to pass.\n";
                return false;
            }
        }
    }
    
    void displayLeaderboard() {
        cout << "\nTOLL BOOTH LEADERBOARD\n";
        cout << "===========================================\n";
        
        vector<pair<TollBooth*, string>> allBooths;
        for(auto& toll : tolls) {
            for(auto& booth : toll.getBooths()) {
                allBooths.push_back({&booth, toll.getLocation()});
            }
        }
        
        // Sort by vehicles processed (descending)
        sort(allBooths.begin(), allBooths.end(), 
             [](const auto& a, const auto& b) {
                 return a.first->getVehiclesProcessed() > b.first->getVehiclesProcessed();
             });
        
        cout << "Rank | Booth ID | Location | Vehicles | Revenue\n";
        cout << "-----|----------|----------|----------|----------\n";
        
        for(int i = 0; i < allBooths.size(); i++) {
            TollBooth* booth = allBooths[i].first;
            cout << setw(4) << (i+1) << " | " 
                 << setw(8) << booth->getBoothId() << " | "
                 << setw(8) << allBooths[i].second << " | "
                 << setw(8) << booth->getVehiclesProcessed() << " | "
                 << booth->getTotalChargesCollected() << "\n";
        }
    }
    
    void displayAvailableTolls() {
        cout << "\nAvailable Tolls:\n";
        for(const auto& toll : tolls) {
            cout << "ID: " << toll.getTollId() << " - " << toll.getLocation() << "\n";
        }
    }
    
    void displayMenu() {
        cout << "\nTOLL MANAGEMENT SYSTEM\n";
        cout << "=====================================\n";
        cout << "1. Process Vehicle\n";
        cout << "2. View Leaderboard\n";
        cout << "3. View Available Tolls\n";
        cout << "4. Exit\n";
        cout << "=====================================\n";
        cout << "Enter your choice: ";
    }
    
    void run() {
        cout << " Welcome to Toll Management System!\n";
        
        while(true) {
            displayMenu();
            int choice;
            cin >> choice;
            cin.ignore(); // Clear the newline
            
            switch(choice) {
                case 1: {
                    string regNum, tollId;
                    int vehicleType;
                    
                    cout << "\nEnter vehicle registration number: ";
                    getline(cin, regNum);
                    
                    cout << "Select vehicle type (1: Two Wheeler, 2: Four Wheeler): ";
                    cin >> vehicleType;
                    cin.ignore();
                    
                    VehicleType vType = (vehicleType == 1) ? VehicleType::TWO_WHEELER : VehicleType::FOUR_WHEELER;
                    Vehicle vehicle(regNum, vType);
                    
                    displayAvailableTolls();
                    cout << "Enter toll ID: ";
                    getline(cin, tollId);
                    
                    processVehicle(vehicle, tollId);
                    break;
                }
                case 2:
                    displayLeaderboard();
                    break;
                case 3:
                    displayAvailableTolls();
                    break;
                case 4:
                    cout << "Thank you for using Toll Management System!\n";
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
        }
    }
};

int main() {
    int mode;
    cout << " TOLL MANAGEMENT SYSTEM \n";
    cout << "=====================================\n";
    cout << "Select mode:\n";
    cout << "Press 1 to start...\n";
    cin >> mode;
    
    if(mode == 1) {
        TollManagementSystem system;
        system.run();
    } else {
        cout << "Invalid choice!\n";
    }
    
    return 0;
}