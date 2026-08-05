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
    Building gym("Gym");
    Building scienceA("Science_A");
    Building engBlock("ENG Block");
    Building mfh("MFH");
    Building library("Libary");
    Building ict("ICT");
    Building studentU("Student U");
    Building parkade("Parkade");
    Building residence("Residence");
     // TODO: ADD ALL EDGES
     // TODO: POSSIBLE OPTZ, SOMETIMES, DECLARING EDGES TWICE. BIT OF A MEMORY USAGE
    gym.add_edge(Edge(scienceA, 5));
    scienceA.add_edge(Edge(engBlock,2));
    scienceA.add_edge(Edge(library,3));
    scienceA.add_edge(Edge(gym,5));
    engBlock.add_edge(Edge(ict,6));
    engBlock.add_edge(Edge(mfh,2));
    engBlock.add_edge(Edge(scienceA,2));
    library.add_edge(Edge(ict,4));
    library.add_edge(Edge(scienceA,3));
    ict.add_edge(Edge(library,4));
    ict.add_edge(Edge(engBlock,6));
    ict.add_edge(Edge(parkade,7));
    ict.add_edge(Edge(studentU,3));
    mfh.add_edge(Edge(engBlock,2));
    studentU.add_edge(Edge(residence,5));
    parkade.add_edge(Edge(ict,7));

    gym.print_information();
    scienceA.print_information();
    engBlock.print_information();
    library.print_information();
    ict.print_information();
    mfh.print_information();
    parkade.print_information();
    studentU.print_information();
    residence.print_information();
    // TODO: CALCULATE PATH OF LEAST TRAVEL
    Campus campus;
    campus.print_information();
    // IDEA: SAVE INFORMATION IN EXCEL AS EACH OBJECT CONNECTS TO ANOTHER OBJECT WITH WALKING TIME
    // BETTER IDEA: WAIT UNTIL HE COVERS SOME OF THE NODE ALGORITHMS IN CLASS FIRST
    // IN TH MEANTIME, FINISH IMPLEMENTING THE CLASS COPIES?
}