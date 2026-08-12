#include <iostream>
#include <string>
#include <cmath>
using namespace std;
#include "Room.h"
#include "Booking.h"

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
    cout << "   Room ID: " << this -> room_id << " --";
    cout << " Room capacity " << this -> capacity << " --";
    cout << " Room type: " << this -> room_type << " --";
    cout << " Bookings: " << (int) this -> bookings.size();
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
    if((int) this -> bookings.size() == 0){
        cout << "No bookings are present!";
    }
    else {
        cout << "For room " << this->get_room_id() << " the bookings are as shown: " << endl;
        for (int i = 0; i < (int) this->bookings.size(); i++ ){
            this->bookings[i].displayInformationBooking(0);
        }
    }
}

/*
 * PROMISES: Client Interface for filtering books. Requests a user defined timeframe, and prints the results to the screen 
 */
void Room::queryFilterForBookings(){
    int yearStart, yearEnd;
    int monthStart, monthEnd;
    int dayStart, dayEnd;
    int hourStart, hourEnd;
    cout << "Please enter the following, in this specific format: year day month time" << endl;
    cout << "For example August 11th 2026 7:30am should be entered as, exactly: 2026 8 11 0730" << endl
    << "noting that the time is in 24 hour time" << endl << endl;
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
    }
}

// TODO: CONVERT THE BOOL STATEMENTS TO A USABLE INTEGER
void Room::printBookingListFiltered(Booking* start, Booking* end){
    // cycle through the bookings and print those that fall within the time window
    cout << "The following bookings fall within that timeszone specified: " << endl;
    bool found = 0;
    int startTime = start->year * 365 * 24 * 60 + start->month * 30.4 * 24 * 60 + start->day * 24 * 60 + start->hour * 60;
    int endTime = end->year * 365 * 24 * 60 + end->month * 30.4 * 24 * 60 + end->day * 24 * 60 + end->hour * 60;
    for (int i = 0; i < (int) this->bookings.size(); i++){
        // if ((bookings[i].year >= start->year && bookings[i].year <= end->year) &&
        //     (bookings[i].month >= start->month && bookings[i].month <= end->month) &&
        //     (bookings[i].day >= start->day && bookings[i].day <= end->day) &&
        //     ((bookings[i].hour + bookings[i].duration) >= start->hour && (bookings[i].hour) < end->hour)
        //     ) 
        //     {
        //     bookings[i].displayInformationBooking(0);
        //     found = 1;
        // }
        int time = (this->bookings[i].year) * 365 * 24 * 60 + this->bookings[i].month * 30.4 * 24 * 60 + this->bookings[i].day * 24 * 60 + this->bookings[i].hour * 60 + this->bookings[i].duration;
        if (time >= startTime && time <= endTime){
           bookings[i].displayInformationBooking(0);
            found = 1; 
        }
    }
    if (!found) cout << "Sorry ... no bookings were found in that specified window!" << endl;
}


