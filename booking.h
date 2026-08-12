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

    public:
    Booking();  //Default constructor
    
    Booking(int year, int month, int day, int hour, int duration);
    
    void displayInformationBooking(int option);
    //Function for displaying information about the given booking.

    void 

};


// Default constructor Booking object
Booking::Booking(){
    this -> year = 2000;
    this -> month = 1;
    this -> day = 1;
    this -> hour = 0; 
    this -> duration = 60;
    //Sets a default time and duration in the case of an otherwise uninitialized booking object
}

// Overloaded constructor Booking object
Booking::Booking(int year, int month, int day, int hour, int duration){
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
        << " at " << this -> hour << " for " << this->duration << " minutes" << endl;
    }
    // Drops information regarding duration
    if (option == 1){
        cout << this -> year << "/" << this -> month << "/" << this -> day
        << " at " << this -> hour;
    }
}




//Define the functions for an AVL tree to hold the bookings, as well as functions to search the tree, add nodes, and delete nodes.
//The key number for the node will be the time the booking starts.



//Function to display all events within a timeframe with upper and lower bounds








#endif //BOOKING_H