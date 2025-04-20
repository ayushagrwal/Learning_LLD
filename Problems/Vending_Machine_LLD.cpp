// 🧠 LLD INTERVIEW PROBLEM: Design a Vending Machine
// ❓ Problem Statement
// Design the core classes and logic for a Vending Machine that:

// Accepts coins and notes.

// Allows a user to select a product.

// Dispenses the product if payment is sufficient.

// Returns change if excess money is inserted.

// Allows admin to refill items and coins.

// Can report inventory and coin status.

// ✅ Requirements
// ✅ Functional Requirements:
// The vending machine should allow users to:

// Insert money (coins, notes).

// Select a product by its code.

// Cancel transaction (and refund).

// Receive change if overpaid.

// The vending machine should allow admin to:

// Refill inventory (products, quantity).

// Load coins/notes into the machine.

// Check inventory and coin levels.

// ✅ Supported Denominations:
// Coins: 1, 5, 10

// Notes: 20, 50, 100

// ✅ Product Attributes:
// Code (e.g., A1, B2)

// Name

// Price

// Quantity

// 🔧 Class Requirements (Suggested)
// VendingMachine

// Product

// Inventory

// Payment

// UserSession (to track ongoing purchase)

// AdminInterface (or commands to refill/report)

// 🧪 Sample Input / Output Scenarios
// 🧪 Test Case 1: Normal Purchase with Exact Change
// plaintext
// Copy
// Edit
// Insert 50
// Select A1 (Price: 50)
// Output:

// plaintext
// Copy
// Edit
// Product A1 - Chips dispensed.
// No change to return.
// 🧪 Test Case 2: Purchase with Extra Money (Requires Change)
// plaintext
// Copy
// Edit
// Insert 100
// Select B1 (Price: 60)
// Output:

// plaintext
// Copy
// Edit
// Product B1 - Soda dispensed.
// Change returned: 40 (2 x 20)
// 🧪 Test Case 3: Insufficient Balance
// plaintext
// Copy
// Edit
// Insert 10
// Select A1 (Price: 50)
// Output:

// plaintext
// Copy
// Edit
// Insufficient balance. Please insert 40 more.
// 🧪 Test Case 4: Cancel Transaction
// plaintext
// Copy
// Edit
// Insert 50
// Cancel
// Output:

// plaintext
// Copy
// Edit
// Transaction canceled. Refund: 50
// 🧪 Test Case 5: Admin Refilling Inventory
// plaintext
// Copy
// Edit
// Admin: Add 10 units of product C2 (Candy)
// Output:

// plaintext
// Copy
// Edit
// Product C2 restocked. New quantity: 15

#include <bits/stdc++.h>
using namespace std;

class Product {
private:
    string code;
    string name;
    int price;
public:
    Product(string c, string n, int p) : code(c), name(n), price(p) {}

    string getCode() const { return code; }
    string getName() const { return name; }
    int getPrice() const { return price; }
};

class Inventory {
private:
    unordered_map<string, pair<Product*, int>> productInventory; // code -> {Product*, quantity}
    unordered_map<int, int> moneyInventory; // denomination -> quantity

public:
    Inventory() {
        for (int d : {1, 5, 10, 20, 50, 100}) {
            moneyInventory[d] = 0;
        }
    }

    ~Inventory() {
        for (auto& entry : productInventory) {
            delete entry.second.first;
        }
    }

    void addProduct(Product* p, int qty) {
        string code = p->getCode();
        if (productInventory.count(code)) {
            delete productInventory[code].first; // Clean old object
            productInventory[code].first = p;
            productInventory[code].second += qty;
        } else {
            productInventory[code] = {p, qty};
        }
    }

    void addMoney(int denom, int qty) {
        moneyInventory[denom] += qty;
    }

    bool hasProduct(string code) {
        return productInventory.count(code) && productInventory[code].second > 0;
    }

    Product* getProduct(string code) {
        return productInventory.count(code) ? productInventory[code].first : nullptr;
    }

    bool deductProduct(string code) {
        if (hasProduct(code)) {
            productInventory[code].second--;
            return true;
        }
        return false;
    }

    void displayInventory() {
        cout << "\nAvailable Products:\n";
        for (auto& entry : productInventory) {
            auto& code = entry.first;
            auto& pairVal = entry.second;
            cout << "Code: " << code << ", Name: " << pairVal.first->getName()
                 << ", Price: " << pairVal.first->getPrice()
                 << ", Quantity: " << pairVal.second << "\n";
        }
    }

    bool returnChange(int change, unordered_map<int, int>& returnedCoins) {
        vector<int> denoms = {100, 50, 20, 10, 5, 1};
        unordered_map<int, int> tempMap = moneyInventory;
        returnedCoins.clear();

        for (int denom : denoms) {
            while (change >= denom && tempMap[denom] > 0) {
                change -= denom;
                tempMap[denom]--;
                returnedCoins[denom]++;
            }
        }

        if (change == 0) {
            moneyInventory = tempMap; // Commit deduction
            return true;
        }

        returnedCoins.clear(); // Can't return exact change
        return false;
    }

    void acceptInsertedMoney(const unordered_map<int, int>& inserted) {
        for (auto& item : inserted) {
            auto& denom = item.first;
            auto& qty = item.second;
            moneyInventory[denom] += qty;
        }
    }
};

class VendingMachine {
private:
    Inventory inventory;
    unordered_map<int, int> currentInsertedMoney;
    int currentBalance = 0;

public:
    void insertMoney(int denom) {
        if (denom != 1 && denom != 5 && denom != 10 && denom != 20 && denom != 50 && denom != 100) {
            cout << "Invalid denomination\n";
            return;
        }
        currentInsertedMoney[denom]++;
        currentBalance += denom;
        cout << "Inserted: " << denom << ", Current balance: " << currentBalance << "\n";
    }

    void selectProduct(string code) {
        if (!inventory.hasProduct(code)) {
            cout << "Product unavailable or out of stock.\n\n";
            return;
        }

        Product* p = inventory.getProduct(code);
        if (!p) {
            cout << "Product not found.\n\n";
            return;
        }

        int price = p->getPrice();

        if (currentBalance < price) {
            cout << "Insufficient balance. Please insert " << (price - currentBalance) << " more.\n\n";
            return;
        }

        unordered_map<int, int> changeToReturn;
        int change = currentBalance - price;

        if (!inventory.returnChange(change, changeToReturn)) {
            cout << "Unable to dispense exact change. Transaction cancelled.\n\n";
            return;
        }

        inventory.acceptInsertedMoney(currentInsertedMoney);
        inventory.deductProduct(code);

        cout << "Product dispensed: " << p->getName() << "\n";

        if (change > 0) {
            cout << "Change returned: ";
            for (auto& item : changeToReturn) {
                auto& denom = item.first;
                auto& qty = item.second;
                if (qty > 0) cout << denom << "x" << qty << " ";
            }
            cout << "\n";
        } else {
            cout << "No change to return.\n";
        }

        cout << "\n";

        // Reset session
        currentInsertedMoney.clear();
        currentBalance = 0;
    }

    void cancelTransaction() {
        cout << "Transaction cancelled. Returning inserted money:\n";
        for (auto& item : currentInsertedMoney) {
            auto& denom = item.first;
            auto& qty = item.second;
            cout << denom << "x" << qty << " ";
        }
        cout << "\n\n";
        currentInsertedMoney.clear();
        currentBalance = 0;
    }

    void adminAddProduct(string code, string name, int price, int qty) {
        Product* p = new Product(code, name, price);
        inventory.addProduct(p, qty);
        cout << "Admin: Product " << name << " added/updated.\n";
    }

    void adminLoadMoney(int denom, int qty) {
        inventory.addMoney(denom, qty);
        cout << "Admin: Loaded " << qty << "x" << denom << " into machine.\n";
    }

    void showProducts() {
        inventory.displayInventory();
    }
};

int main() {
    VendingMachine vm;

    // Admin setup
    vm.adminAddProduct("A1", "Chips", 50, 5);
    vm.adminAddProduct("B2", "Soda", 60, 3);
    vm.adminAddProduct("C3", "Candy", 30, 10);
    vm.adminLoadMoney(10, 5);
    vm.adminLoadMoney(20, 5);
    vm.adminLoadMoney(50, 2);

    vm.showProducts();

    // User interaction
    cout << "\nUser 1:\n";
    vm.insertMoney(100);
    vm.selectProduct("B2");

    cout << "\nUser 2:\n";
    vm.insertMoney(10);
    vm.insertMoney(10);
    vm.cancelTransaction();

    return 0;
}
