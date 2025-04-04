// --------Design a Meeting Room Scheduler---------

// You are required to design a Meeting Room Scheduler that allows users to book meeting rooms in an office. Your system should support the following operations:
// Book a meeting room if available.
// Cancel a booking for a previously booked meeting room.
// List all bookings for a given time range.
// Each meeting room is uniquely identified by its name. The booking system should ensure that no two meetings overlap in the same room.

// Constraints:
// Each meeting room can only have one booking at a time (no overlapping meetings).
// If a room is unavailable at the requested time, the booking should fail.
// Meeting start and end times are given in 24-hour format (e.g., "09:00" to "10:30").
// Assume all bookings happen on the same day.

#include <bits/stdc++.h>
using namespace std;

int converter(string s){
    return stoi(s.substr(0, 2)) * 100 + stoi(s.substr(3, 2)); // Corrected substring length
};


class Room {
private:
    string roomName;
    vector<pair<string, string>> bookings; // Stores bookings as (start_time, end_time)

public:
    Room() : roomName("") {}  // Default constructor
    Room(string name) : roomName(name) {}  // Parameterized constructor

    string getRoomName() const { return roomName; }

    const vector<pair<string, string>>& getBookings() const { return bookings; }

    bool addBooking(string start, string end) {
        int startTime = converter(start);
        int endTime = converter(end);

        for (auto &it : bookings) {
            int existingStart = converter(it.first);
            int existingEnd = converter(it.second);

            // Corrected overlapping check
            if (!(endTime <= existingStart || startTime >= existingEnd)) {
                return false; // Conflict detected
            }
        }

        bookings.push_back({start, end});
        return true; // Booking successful
    }

    bool cancelBooking(string start, string end) {
        for (auto it = bookings.begin(); it != bookings.end(); ++it) {
            if (it->first == start && it->second == end) {
                bookings.erase(it);
                return true; // Booking successfully canceled
            }
        }
        return false; // Booking not found
    }
};

class MeetingScheduler {
private:
    unordered_map<string, Room> rooms; // Map of room names to Room objects

public:
    MeetingScheduler() {}

    bool bookMeeting(const string& room, const string& start_time, const string& end_time) {
        auto it = rooms.find(room);
        if (it == rooms.end()) {
            rooms.emplace(room, Room(room));  // Use emplace to construct Room object in-place
        }
        return rooms[room].addBooking(start_time, end_time);
    }

    bool cancelMeeting(const string& room, const string& start_time, const string& end_time) {
        if (rooms.find(room) == rooms.end()) return false;
        return rooms[room].cancelBooking(start_time, end_time);
    }

    vector<tuple<string, string, string>> listBookings(const string& start_time, const string& end_time) {
        vector<tuple<string, string, string>> result;
        int startT = converter(start_time);
        int endT = converter(end_time);

        for (auto& roomPair : rooms) {
            const string& roomName = roomPair.first;
            const vector<pair<string, string>>& bookings = roomPair.second.getBookings();

            for (const auto& booking : bookings) {
                int bookingStart = converter(booking.first);
                int bookingEnd = converter(booking.second);

                if (!(bookingEnd <= startT || bookingStart >= endT)) { 
                    result.push_back({roomName, booking.first, booking.second});
                }
            }
        }
        return result;
    }
};

int main() {
    MeetingScheduler scheduler;

    cout << scheduler.bookMeeting("Room1", "09:00", "10:00") << endl; // Expected: 1 (Success)
    cout << scheduler.bookMeeting("Room1", "09:30", "10:30") << endl; // Expected: 0 (Conflict)

    auto bookings = scheduler.listBookings("08:00", "11:00");
    for (auto& b : bookings) {
        cout << get<0>(b) << " " << get<1>(b) << " " << get<2>(b) << endl;
    }
    
    cout << scheduler.cancelMeeting("Room1", "09:00", "10:00") << endl; // Expected: 1 (Success)
    cout << scheduler.cancelMeeting("Room1", "09:30", "10:30") << endl; // Expected: 0 (No such booking)

    return 0;
}
