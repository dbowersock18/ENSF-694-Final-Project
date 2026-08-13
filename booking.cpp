#include <iostream>
#include <string>
using namespace std;
#include "booking.h"


// Default constructor Booking object
Booking::Booking(){
    this -> year = 2000;
    this -> month = 1;
    this -> day = 1;
    this -> hour = 0; 
    this -> duration = 60;
    this -> purpose = "Default";
    //Sets a default time and duration in the case of an otherwise uninitialized booking object
}

// Overloaded constructor Booking object
Booking::Booking(int year, int month, int day, int hour, int duration, std::string purpose){
    this -> year = year;
    this -> month = month;
    this -> day = day;
    this -> hour = hour; 
    this -> duration = duration;
    this -> purpose = purpose;
}


void Booking::displayInformationBooking(int option){
    // Display all information about booking
    if(option == 0){
        cout << "Booking time: " <<  this -> year << "/" << this -> month << "/" << this -> day
        << " at " << this -> hour << endl;

        cout << "Duration: " << this->duration << "minutes" << endl << "Purpose: " << this->purpose << endl;
    }
    if (option == 1){
        cout << "Booking time: " <<  this -> year << "/" << this -> month << "/" << this -> day
        << " at " << this -> hour << endl;
    }
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
    result += hourMinutes;

    return result;
}