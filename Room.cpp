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
    cout << "   Room ID: " << this -> room_id;
    cout << " Room capacity " << this -> capacity;
    cout << " Room type: " << this -> room_type;
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
        this->bookings[i].displayInformationBooking(0);
    }
}

/*
 * PROMISES: Client Interface for filtering books. Requests a user defined timeframe, and prints the results to the screen 
 */
void Room::queryFilterForBookings(){
    int yearStart, yearEnd;
    int monthStart, monthEnd;
    int dayStart, dayEnd;
    double hourStart, hourEnd;
    cout << "Please enter the following, in this specific format: year day month time" << endl;
    cout << "For example August 11th 2026 7:30am should be entered, exactly: 2026 08 11 7.5" << endl
    << "noting that the time is fractionalized (7:30am becomes 7.5) and no leading whitespace (8th of August not 08)" << endl << endl;
    while(1){
        cout << "With that, please enter your date to start: ";
        cin >> yearStart >> monthStart >> dayStart >> hourStart;
        Booking start(yearStart, monthStart, dayStart, hourStart, 0.0);
        cout << endl;
        cout << "Now please enter the date to end querying, in the same format: ";
        cin >> yearEnd >> monthEnd >> dayEnd >> hourEnd;
        Booking end(yearEnd, monthEnd, dayEnd, hourEnd, 0.0);
        cout << endl;
        cout << "You have entered: "; start.displayInformationBooking(1);
        cout << " to "; end.displayInformationBooking(1); cout << endl;
        cout << "Is this correct? 0 if not, 1 if yes ";
        bool test; 
        cin >> test; 
        cout << endl;
        if (test ==1) {
            printBookingListFiltered(&start, &end);
            break;
        }
        // Booking start(2026, 8, 11, 7.0, 0.0);
        // Booking end(2026, 8, 12, 8.5, 0.0);

    }
}

void Room::printBookingListFiltered(Booking* start, Booking* end){
    start->displayInformationBooking(1); cout << endl;
    end->displayInformationBooking(1); cout << endl;
    // cycle through the bookings and print those that fall within the time window
    cout << "The following bookings fall within that timeszone specified: " << endl;
    for (int i = 0; i < (int) this->bookings.size(); i++){
        if ((bookings[i].year >= start->year && bookings[i].year <= end->year) &&
            (bookings[i].month >= start->month && bookings[i].month <= end->month) &&
            (bookings[i].day >= start->day && bookings[i].day <= end->day) &&
            (bookings[i].hour >= start->hour && (bookings[i].hour) < end->hour)
            ) {
            bookings[i].displayInformationBooking(0);
        }
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
void Booking::displayInformationBooking(int option){
    // Display all information about booking
    if (option == 0){
        cout << "   a booking occurs " <<  this -> year << "/" << this -> month << "/" << this -> day
        << " at " << this -> convertFractionToTime( this -> hour) << " for " << this->duration << " minutes" << endl;
    }
    // Drops information regarding duration
    if (option == 1){
        cout << this -> year << "/" << this -> month << "/" << this -> day
        << " at " << this -> convertFractionToTime( this -> hour);
    }
}

/*
 * PROMISES: to convert the fractionalized double, represting the hour, into a usable format
 */
string Booking::convertFractionToTime(double hourD){
    int hour =  (hourD) / 1;
    string hourF = to_string(hour);
    int remainder = ((this -> hour) - hour)*100;
    remainder = (remainder * (0.6));
    string minuteF = to_string(remainder);
    if (remainder != 0) {
        hourF += ":";
        hourF += minuteF;
    }
    return hourF;
}
