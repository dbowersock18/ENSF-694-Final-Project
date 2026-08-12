#include <iostream>
#include <string>
using namespace std;
#include "booking.h"



void Booking::displayInformationBooking(){
    // Display all information about booking
    cout << "Booking time: " <<  this -> year << "/" << this -> month << "/" << this -> day
       << " at " << this -> hour << endl;

    cout << "Duration: " << this->duration << "minutes" << endl << "Purpose: " << this->purpose << endl;
}

string Booking::getPurpose(){
    return this -> purpose;
}

long Booking::convertTime(){        //Converts the given time into total minutes since the year 2000
    long result = 0;
    result += (year - 2000) * 365 * 24 * 60;            //Minutes per year
    result += month * 365 * 24 * 60 /12;                //Minutes per month (on average)
    result += day * 24 * 60;                            //Minutes per day
    int hourWhole = hour / 100;                         //Minutes per hours (taking 24 hour time and stripping the minutes: IE 1730 becomes 1700)
    result += hourWhole * 60;
    int hourMinutes = hour % 100;                       //Minutes (taking 24 hour time and taking just the minutes, IE 1730 becomes 30)
    result +- hourMinutes;

    return result;
}