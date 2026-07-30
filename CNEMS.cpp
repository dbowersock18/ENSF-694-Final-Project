#include <iostream> 
using namespace std;
#include "Room.h"
#include "Building.h"
#include "Campus.h"

int main(void) {
    cout << "test" << endl;
    // TODO: CREATE ALL THE CLASSES AND PUT IN A TEST STATEMENT. MAKE SURE THIS MAIN ENTRY POINT CONNECTS TO ALL CLASSES
    Room room;
    room.print_information();
    Building building; 
    building.print_information();
    Campus campus;
    campus.print_information();
}