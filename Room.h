#include <iostream>
#include <string>
using namespace std;

class Room {
private:
    string room_id;
    int capacity;
    string room_type;
    // TODO: LIST OF BOOKING OBJECTS. WHAT ARE BOOKING OBJECTS?
public:
    Room();
    string get_room_id();
    void print_information();
};