// ----------Design a Book My Show System----------
// Problem Statement
// Design an online movie ticket booking system that includes:
// ✅ Users can search for movies in different cities
// ✅ Different seating categories (Gold, Silver, Platinum)
// ✅ Online payment system
// ✅ Show available seats and allow booking

// 👉 Think about: User, Movie, Show, Theater, Seat, Payment.


#include <bits/stdc++.h>
using namespace std;

enum SeatType { GOLD, SILVER, PLATINUM };

class Movie {
private:
    string movieName;
    int duration; // in minutes
    string genre;
public:
    Movie(string n, int d, string g) : movieName(n), duration(d), genre(g) {}
    string getName() { return movieName; }
    string getGenre() { return genre; }
    int getDuration() { return duration; }
};

class Show {
private:
    string showTime;
    Movie movie;
public:
    Show(string t, Movie m) : showTime(t), movie(m) {}
    string getTime() { return showTime; }
    Movie getMovie() { return movie; }
};

class Seat {
private:
    int seatId;
    SeatType sType;
    bool isOccupied;
public:
    Seat(int i, SeatType st) : seatId(i), sType(st), isOccupied(false) {}
    
    int getSeatID() { return seatId; }
    SeatType getSeatType() { return sType; }
    bool getOccupancy() { return isOccupied; }

    void bookSeat() { isOccupied = true; }
};

class Theatre {
private:
    string theatreName;
    vector<Show> shows;
    vector<Seat> seats;
public:
    Theatre(string tn, vector<Show> sh, vector<Seat> se) : theatreName(tn), shows(sh), seats(se) {}

    vector<Show> getTheatreShows() { return shows; }
    vector<Seat> getAvailableSeats() { 
        vector<Seat> availableSeats;
        for (Seat &s : seats) {
            if (!s.getOccupancy()) availableSeats.push_back(s);
        }
        return availableSeats;
    }
};

class City {
private:
    string cityName;
    vector<Theatre> theatres;
public:
    City(string name, vector<Theatre> th) : cityName(name), theatres(th) {}

    vector<Theatre> getTheatres() { return theatres; }
};

class User {
private:
    string name;
    int userId;
public:
    double walletBalance;
    User(int id, string n, double balance) : userId(id), name(n), walletBalance(balance) {}

    bool bookTicket(Theatre &t, int seatId) {
        for (Seat &s : t.getAvailableSeats()) {
            if (s.getSeatID() == seatId) {
                s.bookSeat();
                cout << "Seat " << seatId << " booked successfully!\n";
                return true;
            }
        }
        cout << "Seat not available!\n";
        return false;
    }
};

class Payment {
public:
    static bool processPayment(User &user, double amount) {
        if (user.walletBalance >= amount) {
            user.walletBalance -= amount;
            cout << "Payment Successful! Remaining Balance: " << user.walletBalance << endl;
            return true;
        }
        cout << "Insufficient balance!" << endl;
        return false;
    }
};

int main() {
    // Creating movies
    Movie movie1("Inception", 148, "Sci-Fi");
    Movie movie2("Interstellar", 169, "Sci-Fi");

    // Creating shows
    Show show1("18:00", movie1);
    Show show2("21:00", movie2);

    // Creating seats
    vector<Seat> seats;
    for (int i = 1; i <= 10; i++) {
        seats.push_back(Seat(i, (i % 3 == 0) ? PLATINUM : (i % 2 == 0) ? GOLD : SILVER));
    }

    // Creating theatre
    Theatre theatre1("PVR Cinemas", {show1, show2}, seats);

    // Creating city
    City city("Mumbai", {theatre1});

    // Creating user
    User user1(1, "Ayush", 500);

    // User tries to book a seat
    user1.bookTicket(theatre1, 3);

    return 0;
}
