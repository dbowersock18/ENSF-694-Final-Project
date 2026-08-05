#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "Building.h"

// Default Constructor
Building::Building(){
    this -> building_id = "Building - Default ID";
    // edge property is not dealt with (yet?)
}

// Overloaded Constructor w/o edge
Building::Building(string building_id){
    this -> building_id = building_id;
}

// Overloaded Constructor for Building with one Edge
Building::Building(string building_id, Edge edge){
    this -> building_id = building_id;
    this -> edges.push_back(edge);
}

void Building::add_edge(Edge edge){
    this -> edges.push_back(edge);
}

void Building::print_information(){
    cout << "Information for building is: " << this -> building_id << endl;
    cout << "It has edges: " << endl;
    if ((int) this -> edges.size() != 0 ){
        for (int i = 0; i < (int) this -> edges.size(); i++)
        cout << "To: " << this -> edges[i].connectedBuilding.building_id
        << " With weight: " << this -> edges[i].weight << endl;
    }
    else {
        cout << "0" << endl;
    }
}

// Default Constructor for Edge
Edge::Edge() {
    Building defaultBuilding;
    this -> connectedBuilding = defaultBuilding;
    this -> weight = 0;
    //TODO: TEST CASE
}

// Detailed Constructor for Edge 
Edge::Edge (Building connectedBuilding, int weight){
    this -> connectedBuilding = connectedBuilding;
    this -> weight = weight;
    //TODO: TEST CASE
}

