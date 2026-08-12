#ifndef BOOKING_H
#define BOOKING_H

#include <iostream>
#include <string>
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

//Function to display all events within a timeframe with upper and lower bounds








#endif //BOOKING_H