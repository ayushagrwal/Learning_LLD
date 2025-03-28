// ----------Design an ATM System----------
// Problem Statement
// Design an ATM Machine that allows:
// ✅ User authentication (Card & PIN verification)
// ✅ Cash withdrawal, deposit, balance inquiry
// ✅ Different types of accounts (Savings, Checking)
// ✅ Low balance and daily withdrawal limit check

// 👉 Think about: Encapsulation (Account class), Abstraction (ATMInterface), and Dependency Injection.

#include <bits/stdc++.h>
using namespace std;

enum class AccountType{SAVING, CHECKING};

class Account{
    private:
        int accNumber;
        int balance;
        AccountType accType;
        const int dailyWithdrawalLimit = 5000;  // Daily withdrawal limit

    public:

        Account(int accNum, int initialBalance, AccountType type)
        : accNumber(accNum), balance(initialBalance), accType(type) {}

        int getBalance() const { return balance; }
        int getAccountNumber() const { return accNumber; }
        AccountType getAccountType() const { return accType; }

        
        void deposit(int amount) {
            balance += amount;
            cout << "Deposit successful! New balance: " << balance << endl;
        }

        bool withdraw(int amount) {
            if (amount > dailyWithdrawalLimit) {
                cout << "Withdrawal failed! Exceeds daily limit of " << dailyWithdrawalLimit << endl;
                return false;
            }
    
            if (balance >= amount) {
                balance -= amount;
                cout << "Withdrawal successful! New balance: " << balance << endl;
                return true;
            } else {
                cout << "Insufficient balance!" << endl;
                return false;
            }
        }
};

// Abstract ATM interface
class ATMInterface {
    public:
        virtual bool authenticateUser(int cardNumber, int pin) = 0;
        virtual void showBalance(int cardNumber) = 0;
        virtual void deposit(int cardNumber, int amount) = 0;
        virtual void withdraw(int cardNumber, int amount) = 0;
};

// User class
class User {
    private:
        int userId;
        string userName;
        int cardNumber;
        int pin;
        Account* account;

    public:
        User(int id, string name, int cardNo, int pinCode, Account* acc)
            : userId(id), userName(name), cardNumber(cardNo), pin(pinCode), account(acc) {}

        int getCardNumber() const { return cardNumber; }
        int getPin() const { return pin; }
        Account* getAccount() { return account; }
};

// ATM Machine class implementing ATMInterface
class ATM : public ATMInterface {
    private:
        unordered_map<int, User*> users; // cardNumber -> User mapping
    
    public:
        void addUser(User* user) {
            users[user->getCardNumber()] = user;
        }
    
        bool authenticateUser(int cardNumber, int pin) override {
            if (users.find(cardNumber) != users.end() && users[cardNumber]->getPin() == pin) {
                cout << "Authentication successful!" << endl;
                return true;
            }
            cout << "Invalid credentials!" << endl;
            return false;
        }
    
        void showBalance(int cardNumber) override {
            if (users.find(cardNumber) != users.end()) {
                cout << "Current balance: " << users[cardNumber]->getAccount()->getBalance() << endl;
            } else {
                cout << "User not found!" << endl;
            }
        }
    
        void deposit(int cardNumber, int amount) override {
            if (users.find(cardNumber) != users.end()) {
                users[cardNumber]->getAccount()->deposit(amount);
            } else {
                cout << "User not found!" << endl;
            }
        }
    
        void withdraw(int cardNumber, int amount) override {
            if (users.find(cardNumber) != users.end()) {
                users[cardNumber]->getAccount()->withdraw(amount);
            } else {
                cout << "User not found!" << endl;
            }
        }
    };


int main(){
    // Creating accounts
    Account acc1(101, 10000, AccountType::SAVING);
    Account acc2(102, 15000, AccountType::CHECKING);

    // Creating users
    User user1(1, "Alice", 1234, 1111, &acc1);
    User user2(2, "Bob", 5678, 2222, &acc2);

    // ATM machine
    ATM atm;
    atm.addUser(&user1);
    atm.addUser(&user2);

    // Simulating ATM operations
    int cardNumber, pin, amount;

    cout << "Insert card (Enter card number): ";
    cin >> cardNumber;
    cout << "Enter PIN: ";
    cin >> pin;

    if (atm.authenticateUser(cardNumber, pin)) {
        int choice;
        do {
            cout << "\n1. Check Balance\n2. Deposit\n3. Withdraw\n4. Exit\nEnter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    atm.showBalance(cardNumber);
                    break;
                case 2:
                    cout << "Enter deposit amount: ";
                    cin >> amount;
                    atm.deposit(cardNumber, amount);
                    break;
                case 3:
                    cout << "Enter withdrawal amount: ";
                    cin >> amount;
                    atm.withdraw(cardNumber, amount);
                    break;
                case 4:
                    cout << "Thank you for using the ATM!" << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
        } while (choice != 4);
    }
    return 0;
}