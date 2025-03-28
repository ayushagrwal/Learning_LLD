// Abstraction (Hiding Implementation Details)

#include <bits/stdc++.h>
using namespace std;

// Abstract Class
class Payment{
    public:
        virtual void pay(int amount)=0; // Pure virtual function
};

class CreditCardPayment : public Payment {
    public:
        void pay(int amount) override{
            cout << "Paid " << amount << " using Credit Card" << endl;
        }
};

class PayPalPayment : public Payment {
    public:
        void pay(int amount) override{
            cout << "Paid " << amount << " using Pay Pal" << endl;
        }
};

int main(){

    Payment* P1 = new CreditCardPayment();
    Payment* P2 = new PayPalPayment();

    P1->pay(400);
    P2->pay(600);

    delete P1;
    delete P2;

    return 0;
}