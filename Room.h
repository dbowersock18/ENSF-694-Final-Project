#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Room {
private:
    string room_id; // unique ID of room
    int capacity; // capacity of room
    string room_type; // type of room
public:
    Room(); // Default constructor
    Room(string, int, string); // Overloaded consructor
    string get_room_id(); // Getter for room_id
    void print_information(); // Prints infrmation related to the room
    void addBooking(int, int, int, int, int); // Add a booking to the building
    void removeBooking(); // Remove a booking from the building
    void displayInformationAllBookings();  // display information related to all bookings
    vector<Booking>* bookingList(); // returns a pointer to the vector containing ALL the bookings
    void queryFilterForBookings(); // CLI for interacting with user filtering books
    void printBookingListFiltered(Booking*, Booking*); // filters and prints the bookings within the time window specified by the two inputs. Called by CLI queryFilterForBookings()
        // TODO: this might require a copy opertaor function in the booking class to complete
};

#endif // ROOM_H