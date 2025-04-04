// Create an expense sharing application.

// An expense sharing application is where you can add your expenses and split it among different people. The app keeps balances between people as in who owes how much to whom.
// Requirements
// User: Each user should have a userId, name, email, mobile number.
// Expense: Could either be EQUAL, EXACT or PERCENT
// Users can add any amount, select any type of expense and split with any of the available users.
// The percent and amount provided could have decimals upto two decimal places.
// In case of percent, you need to verify if the total sum of percentage shares is 100 or not.
// In case of exact, you need to verify if the total sum of shares is equal to the total amount or not.
// The application should have a capability to show expenses for a single user as well as balances for everyone.
// When asked to show balances, the application should show balances of a user with all the users where there is a non-zero balance.
// The amount should be rounded off to two decimal places. Say if User1 paid 100 and amount is split equally among 3 people. Assign 33.34 to first person and 33.33 to others.
// Input
// You can create a few users in your main method. No need to take it as input.
// There will be 3 types of input:
// Expense in the format: EXPENSE <user-id-of-person-who-paid> <no-of-users> <space-separated-list-of-users> <EQUAL/EXACT/PERCENT> <space-separated-values-in-case-of-non-equal>
// Show balances for all: SHOW
// Show balances for a single user: SHOW <user-id>
// Output
// When asked to show balance for a single user. Show all the balances that user is part of:
// Format: <user-id-of-x> owes <user-id-of-y>: <amount>
// If there are no balances for the input, print No balances
// In cases where the user for which balance was asked for, owes money, they’ll be x. They’ll be y otherwise.
// Sample Input
// SHOW
// SHOW u1
// EXPENSE u1 1000 4 u1 u2 u3 u4 EQUAL
// SHOW u4
// SHOW u1
// EXPENSE u1 1250 2 u2 u3 EXACT 370 880
// SHOW
// EXPENSE u4 1200 4 u1 u2 u3 u4 PERCENT 40 20 20 20
// SHOW u1
// SHOW
// Sample Output
// No balances
// No balances
// User4 owes User1: 250
// User2 owes User1: 250
// User3 owes User1: 250
// User4 owes User1: 250
// User2 owes User1: 620
// User3 owes User1: 1130
// User4 owes User1: 250
// User1 owes User4: 230
// User2 owes User1: 620
// User3 owes User1: 1130
// User1 owes User4: 230
// User2 owes User1: 620
// User2 owes User4: 240
// User3 owes User1: 1130
// User3 owes User4: 240
// Expectations
// Make sure that you have a working and demonstrable code
// Make sure that the code is functionally correct
// Code should be modular and readable
// Separation of concern should be addressed
// Please do not write everything in a single file
// Code should easily accommodate new requirements and minimal changes
// There should be a main method from where the code could be easily testable
// [Optional] Write unit tests, if possible
// No need to create a GUI


#include <bits/stdc++.h>
using namespace std;

enum class ExpenseType { EQUAL, EXACT, PERCENT };

class User {
private:
    string userId;
    string name;
    string email;
    string mobile;

public:
    User(string id, string n, string e, string m) : userId(id), name(n), email(e), mobile(m) {}

    string getId() { return userId; }
    string getName() { return name; }
};

class BalanceSheet {
    unordered_map<string, unordered_map<string, double>> balanceMap; // u1 -> {u2: amount}

public:
    void addTransaction(string paidBy, vector<string>& users, vector<double>& amounts) {
        for (int i = 0; i < users.size(); ++i) {
            string user = users[i];
            if (user == paidBy) continue;
            double amount = amounts[i];
            balanceMap[user][paidBy] += amount;
            balanceMap[paidBy][user] -= amount;
        }
    }

    void showAll() {
        bool any = false;
        for (auto& userEntry : balanceMap) {
            string from = userEntry.first;
            for (auto& toEntry : userEntry.second) {
                string to = toEntry.first;
                double amt = toEntry.second;
                if (amt > 0.009) {
                    cout << from << " owes " << to << ": " << fixed << setprecision(2) << amt << endl;
                    any = true;
                }
            }
        }
        if (!any) cout << "No balances" << endl;
    }

    void showUser(string user) {
        bool any = false;
        for (auto& entry : balanceMap[user]) {
            if (entry.second > 0.009) {
                cout << user << " owes " << entry.first << ": " << fixed << setprecision(2) << entry.second << endl;
                any = true;
            }
        }
        for (auto& entry : balanceMap) {
            if (entry.first != user && entry.second.find(user) != entry.second.end() && entry.second[user] > 0.009) {
                cout << entry.first << " owes " << user << ": " << fixed << setprecision(2) << entry.second[user] << endl;
                any = true;
            }
        }
        if (!any) cout << "No balances" << endl;
    }
};

class ExpenseManager {
    unordered_map<string, User*> users;
    BalanceSheet balanceSheet;

public:
    void addUser(User* user) {
        users[user->getId()] = user;
    }

    void addExpense(string paidBy, double amount, vector<string>& involvedUsers, ExpenseType type, vector<double> values = {}) {
        vector<double> splits(involvedUsers.size(), 0.0);

        if (type == ExpenseType::EQUAL) {
            int n = involvedUsers.size();
            double each = floor((amount / n) * 100.0) / 100.0;
            double remaining = amount - (each * (n - 1));
            for (int i = 0; i < n; ++i) splits[i] = (i == n - 1 ? remaining : each);
        } else if (type == ExpenseType::EXACT) {
            double total = accumulate(values.begin(), values.end(), 0.0);
            if (abs(total - amount) > 0.01) {
                cout << "Invalid EXACT split. Total doesn't match." << endl;
                return;
            }
            splits = values;
        } else if (type == ExpenseType::PERCENT) {
            double totalPercent = accumulate(values.begin(), values.end(), 0.0);
            if (abs(totalPercent - 100.0) > 0.01) {
                cout << "Invalid PERCENT split. Sum != 100%" << endl;
                return;
            }
            for (int i = 0; i < values.size(); ++i) {
                splits[i] = round((amount * values[i]) / 100.0 * 100.0) / 100.0;
            }
        }

        balanceSheet.addTransaction(paidBy, involvedUsers, splits);
    }

    void showBalances() {
        balanceSheet.showAll();
    }

    void showUserBalance(string userId) {
        balanceSheet.showUser(userId);
    }
};

int main() {
    ExpenseManager manager;

    // Adding users
    manager.addUser(new User("u1", "Ayush1", "a1@mail.com", "9100000001"));
    manager.addUser(new User("u2", "Ayush2", "a2@mail.com", "9100000002"));
    manager.addUser(new User("u3", "Ayush3", "a3@mail.com", "9100000003"));
    manager.addUser(new User("u4", "Ayush4", "a4@mail.com", "9100000004"));

    string input;
    while (getline(cin, input)) {
        stringstream ss(input);
        string command;
        ss >> command;

        if (command == "SHOW") {
            string uid;
            ss >> uid;
            if (uid.empty()) {
                manager.showBalances();
            } else {
                manager.showUserBalance(uid);
            }
        } else if (command == "EXPENSE") {
            string paidBy;
            int amount, n;
            ss >> paidBy >> amount >> n;

            vector<string> users(n);
            for (int i = 0; i < n; ++i) ss >> users[i];

            string splitType;
            ss >> splitType;

            vector<double> values;
            if (splitType == "EXACT" || splitType == "PERCENT") {
                for (int i = 0; i < n; ++i) {
                    double v;
                    ss >> v;
                    values.push_back(v);
                }
            }

            if (splitType == "EQUAL")
                manager.addExpense(paidBy, amount, users, ExpenseType::EQUAL);
            else if (splitType == "EXACT")
                manager.addExpense(paidBy, amount, users, ExpenseType::EXACT, values);
            else if (splitType == "PERCENT")
                manager.addExpense(paidBy, amount, users, ExpenseType::PERCENT, values);
        }
    }

    return 0;
}
