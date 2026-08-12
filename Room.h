#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <vector>
#include "booking.h"
#include "AVL.h"

using namespace std;

class Room {
private:
    string room_id; // unique ID of room
    int capacity; // capacity of room
    string room_type; // type of room
    AVLTree AVL;    //AVL tree of bookings
public:
    Room(); // Default constructor
    Room(string, int, string); // Overloaded consructor
    string get_room_id(); // Getter for room_id
    void print_information(); // Prints infrmation related to the room
    void addBooking(int, int, int, int, int, string); // Add a booking to the building
    void removeBooking(); // Remove a booking from the building
    void displayInformationAllBookings();  // display information related to all bookings
    void queryFilterForBookings(); // CLI for interacting with user filtering books
    void printBookingListFiltered(Booking*, Booking*); // filters and prints the bookings within the time window specified by the two inputs. Called by CLI queryFilterForBookings()
        // TODO: this might require a copy opertaor function in the booking class to complete
    void printNextBooking(); //Displays the next booking, starting from the first booking if one is not selected.
};

#endif // ROOM_H