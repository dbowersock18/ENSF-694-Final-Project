#include <iostream>
#include <string>
using namespace std;
#include "Room.h"

// Default constructor for the room object 
Room::Room(){
    this -> room_id = "Room - default ID";
    this -> capacity = 0;
    this -> room_type = "Room - default room type";
}

/*
 * PROMISES: Prints information relevant to the room
 */
void Room::print_information(){
    cout << "Information on the room: " << endl; 
    cout << "Room ID: " << this -> room_id << endl;
    cout << "Room capacity " << this -> capacity << endl;
    cout << "Room type: " << this -> room_type << endl;
    cout << "End of information on room" << endl << endl;
}