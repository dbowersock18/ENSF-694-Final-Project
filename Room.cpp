#include <iostream>
#include <string>
using namespace std;
#include "Room.h"

Room::Room(){
    this -> room_id = "Room - default ID";
}

void Room::print_information(){
    cout << "Information on the room: " << this -> room_id << endl;
}