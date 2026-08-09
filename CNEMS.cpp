#include <iostream> 
using namespace std;
#include "Room.h"
#include "Building.h"
#include "Campus.h"
#include "Graph.h"

// TODO LIST: 
// METHOD THAT INSTANTIATES ALL OBJECTS (4 METHODS, ONE FOR EACH MAYBE)

int main(void) {
    // file housing campus data
    const string fileName= "CampusMap.txt";
    // create objects
    Campus campus;
    Graph graph(&campus);
    graph.read_input_file(fileName);
    campus.print_information_campus();
    campus.print_information_buildings();
    // Creates room object
    // Room room;
    // // room.print_information();
    // // Creates all building objects
    // Building gym("Gym");
    // Building scienceA("Science_A");
    // Building engBlock("ENG Block");
    // Building mfh("MFH");
    // Building library("Libary");
    // Building ict("ICT");
    // Building studentU("Student U");
    // Building parkade("Parkade");
    // Building residence("Residence");
    //  // Adds all Edges to each building Object
    // gym.add_edge(Edge(&scienceA, 5));
    // scienceA.add_edge(Edge(&gym,5));
    // scienceA.add_edge(Edge(&engBlock,2));
    // scienceA.add_edge(Edge(&library,3));
    // engBlock.add_edge(Edge(&ict,6));
    // engBlock.add_edge(Edge(&mfh,2));
    // engBlock.add_edge(Edge(&scienceA,2));
    // library.add_edge(Edge(&ict,4));
    // library.add_edge(Edge(&scienceA,3));
    // ict.add_edge(Edge(&library,4));
    // ict.add_edge(Edge(&engBlock,6));
    // ict.add_edge(Edge(&parkade,7));
    // ict.add_edge(Edge(&studentU,3));
    // mfh.add_edge(Edge(&engBlock,2));
    // studentU.add_edge(Edge(&residence,5));
    // studentU.add_edge(Edge(&ict,3));
    // parkade.add_edge(Edge(&ict,7));
    // residence.add_edge(Edge(&studentU,5));
    // // Print all information as a test
    // cout << "----" << endl << "Buliding information" << endl << endl;
    // gym.print_information();
    // scienceA.print_information();
    // engBlock.print_information();
    // library.print_information();
    // ict.print_information();
    // mfh.print_information();
    // parkade.print_information();
    // studentU.print_information();
    // residence.print_information();
    // cout << "----" << endl << endl;
    // Campus
    // Add buildings to campus
    // campus.campusBuildings.push_back(&gym);
    // campus.campusBuildings.push_back(&scienceA);
    // campus.campusBuildings.push_back(&engBlock);
    // campus.campusBuildings.push_back(&ict);
    // campus.campusBuildings.push_back(&mfh);
    // campus.campusBuildings.push_back(&studentU);
    // campus.campusBuildings.push_back(&residence);
    // campus.campusBuildings.push_back(&parkade);
    // campus.campusBuildings.push_back(&library);

    // dijkstra's algorithm to find shortest path
    graph.dijkstra("gym"); // Hard coding start. Get user input later.
    graph.printGraph();

}



