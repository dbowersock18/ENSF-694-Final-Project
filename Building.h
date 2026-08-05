#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Struct data structure to represent the different
// pathways to/from the buliding to different building
struct Edge;

class Building {
private:
    string building_id; // ID of Building 
    vector<Edge> edges; // Stored Vector of pathways
public:
    Building(); // Default Constructor
    Building(string building_id); // Overloaded Constructor
    Building(string building_id, Edge edge); // Overloaded Constructor
    void add_edge(Edge edge); //Add edge
    string get_building_id(); // test
    void print_information(); // test
};

struct Edge {
    Building connectedBuilding;
    int weight;
    Edge();
    Edge(Building connectedBuilding, int weight);
};


//IDEA. HAVE EACH BUILDING STORE AN EDGE STRUCT
// THIS STRUCT HOUSES THE NEXT PATHWAY AND WEIGHT
// THIS STRUCT IS STORED IN THE BUILDING AS
// as a vector

#endif // BUILDING_H