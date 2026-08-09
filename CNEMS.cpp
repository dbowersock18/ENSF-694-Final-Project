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
    // display information for troubleshooting /information
    graph.read_input_file(fileName);
    campus.print_information_campus();
    campus.print_information_buildings();

    // dijkstra's algorithm to find shortest path
    graph.dijkstra("gym"); // Hard coding start. Get user input later.
    graph.printGraph();

}



