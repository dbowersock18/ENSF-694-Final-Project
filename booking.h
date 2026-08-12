#ifndef BOOKING_H
#define BOOKING_H

#include <iostream>
#include <string>
using namespace std;

//Define a function for turning a booking time into a single integer that can be compared.

class Booking{
    private:
    int year;
    int month;
    int day;
    double hour;
    double duration;

    public:
    Booking();  //Default constructor
    Booking(int year, int month, int day, double hour, double duration);
    void displayInformationBooking(int option);
    string convertFractionToTime(double hourD)

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
    else {
        hourF += ":";
        hourF += "00";
    }
    return hourF;
}



//Define the functions for an AVL tree to hold the bookings, as well as functions to search the tree, add nodes, and delete nodes.
//The key number for the node will be the time the booking starts.



//Function to display all events within a timeframe with upper and lower bounds








#endif //BOOKING_H