// ----------------6️⃣ Design a Hotel Booking System------------------
// Problem Statement
// Design a hotel reservation system that supports:
// ✅ Different room types (Single, Double, Suite)
// ✅ Users can check room availability & book rooms
// ✅ Payment and cancellation system
// ✅ Loyalty program for frequent travelers

// 👉 Think about: User, Hotel, Room, Booking, Payment.

#include <bits/stdc++.h>
using namespace std;

enum class RoomType { SINGLE, DOUBLE, SUITE };

class Room {
private:
    int roomID;
    RoomType type;
    bool isBooked;
    int pricePerNight; // Store price per night

public:
    Room(int r, RoomType t) : roomID(r), type(t), isBooked(false) {
        if (t == RoomType::SINGLE) pricePerNight = 200;
        else if (t == RoomType::DOUBLE) pricePerNight = 400;
        else if (t == RoomType::SUITE) pricePerNight = 1000;
    }

    bool bookRoom() {
        if (isBooked) {
            cout << "Room " << roomID << " is already booked!" << endl;
            return false;
        }
        isBooked = true;
        cout << "Room " << roomID << " booked successfully!" << endl;
        return true;
    }

    bool cancelRoom() {
        if (!isBooked) {
            cout << "Room " << roomID << " is not booked!" << endl;
            return false;
        }
        isBooked = false;
        cout << "Room " << roomID << " canceled successfully!" << endl;
        return true;
    }

    int getFare(int days) {
        return pricePerNight * days;
    }

    int getRoomID() {
        return roomID;
    }

    bool isRoomBooked() {
        return isBooked;
    }
};

class User {
    private:
        int userID;
        unordered_map<int, int> bookings; // roomID -> days booked
    
    public:
        User(int u) : userID(u) {}
    
        void bookRoom(Room& room, int days) {
            if (room.bookRoom()) {
                bookings[room.getRoomID()] = days;
                cout << "Booking confirmed! Total cost: " << room.getFare(days) << endl;
            }
        }
    
        void cancelRoom(Room& room) {
            if (bookings.find(room.getRoomID()) != bookings.end()) {
                if (room.cancelRoom()) {
                    bookings.erase(room.getRoomID());
                    cout << "Booking for Room " << room.getRoomID() << " has been canceled!" << endl;
                }
            } else {
                cout << "You have no booking for this room!" << endl;
            }
        }
    
        void viewBookings() {
            if (bookings.empty()) {
                cout << "No bookings found!" << endl;
                return;
            }
            for (auto &it : bookings) {
                cout << "Room " << it.first << " is booked for " << it.second << " days." << endl;
            }
        }
    };

int main() {
    Room r1(101, RoomType::SINGLE);
    Room r2(102, RoomType::DOUBLE);
    User u1(1);

    u1.bookRoom(r1, 3);
    u1.bookRoom(r2, 5);
    u1.viewBookings();

    u1.cancelRoom(r1);
    u1.viewBookings();

    return 0;
}