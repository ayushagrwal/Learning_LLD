// Friend Function (Access Private Data)

#include <bits/stdc++.h>
using namespace std;

class Patient{
    private:
        int heartRate;
    
    public:
        Patient(int h){heartRate=h;}

        // Friend Function Declaration
        friend void doctorReport(Patient p);
};

//Friend Function Declaration
void doctorReport(Patient p) {
    cout << "Patient's heart rate: " << p.heartRate << " bpm" << endl;
}

int main(){

    Patient p(72);
    doctorReport(p);

    return 0;
}