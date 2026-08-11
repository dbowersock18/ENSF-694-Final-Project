#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Booking;

class Room {
private:
    string room_id; // unique ID of room
    int capacity; // capacity of room
    string room_type; // type of room
public:
    vector <Booking> bookings; // list of booking objects objects
    Room(); // Default constructor
    Room(string, int, string); // Overloaded consructor
    string get_room_id(); // Getter for room_id
    void print_information(); // Prints infoormation related to the room
    void addBooking(int, int, int, double, double); // Add a booking to the building
    void removeBooking(); // Remove a booking from the building
    void displayInformationAllBookings();  // display information related to all bookings
    vector<Booking>* bookingList(); // returns a pointer to the vector containing ALL the bookings
    void queryFilterForBookings(); // CLI for interacting with user filtering books
    void printBookingListFiltered(Booking*, Booking*); // filters and prints the bookings within the time window specified by the two inputs. Called by CLI queryFilterForBookings()
        // TODO: this might require a copy opertaor function in the booking class to complete
};

class Booking {
    // TODO populate
    // TODO ask team about decision not to do private variables. Not part of project guidelines BUT not the standard c++ way of doing things
public:
    int year; // year of booking
    int month; // month of booking
    int day; // day of booking
    double hour; // hour of booking, represented by a fraction. eg, 4.5 is 4:30.
    double duration; // duration of booking, represented by a fraction. eg) 1.5 is an hour and a half
    // ~ Booking(); // deconstructor
    Booking(); // default contructor
    Booking(int, int, int, double, double); // Overloaded constructor to set up a booking object with all required properties
    void displayInformationBooking(int); // displays information related to a specific booking 
    string convertFractionToTime(double); // converts the hour property, into a digestible format
};

#endif // ROOM_H