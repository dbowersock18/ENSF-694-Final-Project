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

    // TODO: CREATEA ALL BUILDINGS
    Building building("gym");
    Building building2("science_A");
    Edge edge(building2, 5);
    // TODO: ADD ALL EDGES
    building.add_edge(edge);
    building.print_information();
    // TODO: CALCULATE PATH OF LEAST TRAVEL
    Campus campus;
    campus.print_information();
    // IDEA: SAVE INFORMATION IN EXCEL AS EACH OBJECT CONNECTS TO ANOTHER OBJECT WITH WALKING TIME
    // BETTER IDEA: WAIT UNTIL HE COVERS SOME OF THE NODE ALGORITHMS IN CLASS FIRST
    // IN TH MEANTIME, FINISH IMPLEMENTING THE CLASS COPIES?
}