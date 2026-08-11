#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;
#include "Building.h"

// Default Constructor
Building::Building(){
    this -> building_id = "Building - Default ID";
    this -> prevBuilding = nullptr;
    // edge property is not dealt with (yet?)
}

// Overloaded Constructor w/o edge
Building::Building(string building_id){
    this -> building_id = building_id;
    this -> distance = numeric_limits<double>::infinity();
}

// Overloaded Constructor for Building with one Edge
Building::Building(string building_id, Edge edge){
    this -> building_id = building_id;
    this -> edges.push_back(edge);
}

/*
 * REQUIRES: a valid Edge Object
 * PROMISES: to add the Edge object to the vector of edges, stored inside the building object
 * this represents the 'pathways' from the building to all other buildings specified 
 */
void Building::add_edge(Edge edge){
    this -> edges.push_back(edge);
}

// Getter Method for building ID
string Building::get_building_id(){
    return this -> building_id;
}

/*
 *  PROMISES: To print out all the information relevant to the building object 
 */
void Building::print_information(){
    cout << "Information for building: " << this -> building_id << endl;
    cout << "It has " << (int) this -> rooms.size() << " rooms" << endl;
    for ( int i = 0; i < (int) this -> rooms.size(); i++) {
        this -> rooms[i].print_information();
        for (int j = 0; j < (int) this -> rooms[i].bookings.size(); j++) {
            cout <<"    "; this -> rooms[i].bookings[j].displayInformationBooking(0);
        }
    }
    cout << "It has " << (int) this -> edges.size() << " pathways: " << endl;
    if ((int) this -> edges.size() != 0 ){
        for (int i = 0; i < (int) this -> edges.size(); i++)
        cout << "   to " << this -> edges[i].connectedBuilding -> building_id
        << " that takes " << this -> edges[i].weight << " minutes" << endl;
    }
    else {
        cout << "0" << endl;
    }
}

// Default Constructor for Edge
Edge::Edge() {
    Building defaultBuilding;
    this -> connectedBuilding = &defaultBuilding;
    this -> weight = 0;
}

// Detailed Constructor for Edge 
Edge::Edge (Building* connectedBuilding, int weight){
    this -> connectedBuilding = connectedBuilding;
    this -> weight = weight;
}

