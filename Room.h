#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Bookings;

class Room {
private:
    string room_id; // unique ID of room
    int capacity; // capacity of room
    string room_type; // type of room
    vector <Bookings> bookings; // list of booking objects
public:
    Room(); // Default constructor
    string get_room_id(); // Getter for room_id
    void print_information(); // Prints infoormation related to the room
};

class Bookings {
    // TODO populate
};

#endif // ROOM_H