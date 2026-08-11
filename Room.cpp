#include <iostream>
#include <string>
#include <cmath>
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

string Room::get_room_id(){
    return this -> room_id;
}

void Room::addBooking(int year, int month, int day, double hour, double duration){
    // TODO: ENSURE THERE IS NO COLLISIONS WITH ADDING A BOOKING
    bookings.push_back(Booking(year, month, day, hour, duration));
}

void Room::displayInformationAllBookings(){
    cout << "For room " << this->get_room_id() << " the following books are as shown: " << endl;
    for (int i = 0; i < (int) this->bookings.size(); i++ ){
        this->bookings[i].displayInformationBooking();
    }
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

/*
* PROMISES: to return information related to a specific booking 
*/
void Booking::displayInformationBooking(){
    cout << "   a booking occurs " <<  this -> year << "/" << this -> month << "/" << this -> day
    << " at " << this -> convertFractionToTime() << " for " << this->duration << " minutes" << endl;
}

/*
 * PROMISES: to convert the fractionalized double, represting the hour, into a usable format
 */
string Booking::convertFractionToTime(){
    int hour =  (this->hour) / 1;
    string hourF = to_string(hour);
    int remainder = ((this -> hour) - hour)*100;
    remainder = (remainder * (0.6));
    string minuteF = to_string(remainder);
    hourF += ":";
    hourF += minuteF;
    return hourF;
}
