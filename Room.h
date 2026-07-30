#include <iostream>
#include <string>
using namespace std;

class Room {
private:
    string room_id;
public:
    Room();
    string get_room_id();
    void print_information();
};