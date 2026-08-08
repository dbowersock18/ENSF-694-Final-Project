#include <iostream>
#include <string>
using namespace std;

class Room {
private:
    string room_id;
    int capacity;
    string room_type;
public:
    Room(); // Default constructor
    string get_room_id(); // TESTING PURPOSES PRINT
    void print_information(); // TESTING PURPOSES PRINT
};