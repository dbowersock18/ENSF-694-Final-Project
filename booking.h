#ifndef BOOKING_H
#define BOOKING_H

#include <iostream>
#include <string>
#include "AVL.h"
using namespace std;


class Booking{
    private:
    int year;
    int month;
    int day;
    int hour;
    int duration;
    std::string purpose;    //Holds the purpose of this booking, IE lecture, study, event.

    public:
    Booking();  //Default constructor
    
    Booking(int year, int month, int day, int hour, int duration, std::string purpose);
    
    void displayInformationBooking();
    //Function for displaying information about the given booking.

    std::string getPurpose();
    //Returns string of booking purpose

    long convertTime();
    //Converts the internal booking time to a single long for use in the AVL tree

};


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






//Define the functions for an AVL tree to hold the bookings, as well as functions to search the tree, add nodes, and delete nodes.
//The key number for the node will be the time the booking starts.



//Function to display all events within a timeframe with upper and lower bounds








#endif //BOOKING_H