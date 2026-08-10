#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
using namespace std;

class Room {
private:
    string room_id; // unique ID of room
    int capacity; // capacity of room
    string room_type; // type of room
public:
    Room(); // Default constructor
    string get_room_id(); // Getter for room_id
    void print_information(); // Prints infoormation related to the room
};

#endif // ROOM_H