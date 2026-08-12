#include <iostream>
#include <string>
using namespace std;
#include "booking.h"



void Booking::displayInformationBooking(){
    // Display all information about booking
    cout << "Booking time: " <<  this -> year << "/" << this -> month << "/" << this -> day
       << " at " << this -> hour << endl;

    cout << "Booking information:" << endl << "Duration: " << this->duration << endl << "Purpose: " << this->purpose << endl;
}

string Booking::getPurpose(){
    return this -> purpose;
}