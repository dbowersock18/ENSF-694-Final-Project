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

// Overloaded constructor to populate all properties
Room::Room(string room_id, int capacity, string room_type){
    this -> room_id = room_id;
    this -> capacity = capacity;
    this -> room_type = room_type;
}

/*
 * PROMISES: Prints information relevant to the room
 */
void Room::print_information(){
    cout << endl;
    cout << "Room ID: " << this -> room_id << endl;
    cout << "Room capacity " << this -> capacity << endl;
    cout << "Room type: " << this -> room_type << endl;
    cout << endl;
}

void Room::addBooking(int year, int month, int day, double hour, double duration){
    bookings.push_back(Booking(year, month, day, hour, duration));
}

// Default constructor Booking object
Booking::Booking(){
    // DO SOMETHING
}

// Overloaded constructor Booking object
Booking::Booking(int year, int month, int day, double hour, double duration){
    this -> year = year;
    this -> month = month;
    this -> day = day;
    this -> hour = hour; 
    this -> duration = duration;
}
