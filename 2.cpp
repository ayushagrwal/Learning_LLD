
//Encapsulation (Data Hiding)

#include <bits/stdc++.h>
using namespace std;

class BankAccount {
    private:
        double balance;

    public:
        BankAccount(double b) { balance = b; }

        void deposit(double amount) {
            balance += amount;
            cout << "Deposited: " << amount << endl;
        }

        void withdraw(double amount) {
            if (balance >= amount) {
                balance -= amount;
                cout << "Withdrawn: " << amount << endl;
            } else {
                cout << "Insufficient Balance!" << endl;
            }
        }

        double getBalance() { return balance; }
};

int main() {
    double initial_balance;
    cout << "Enter initial balance to create the account: ";
    cin >> initial_balance;

    BankAccount userAccount(initial_balance);

    int choice;
    double amount;
    do {
        cout << "\nWelcome to the Bank Account System" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter amount to deposit: ";
                cin >> amount;
                userAccount.deposit(amount);
                break;
            case 2:
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                userAccount.withdraw(amount);
                break;
            case 3:
                cout << "Current balance: " << userAccount.getBalance() << endl;
                break;
            case 4:
                cout << "Thank you for using the Bank Account System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
