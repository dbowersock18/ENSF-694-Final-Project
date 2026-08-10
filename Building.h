#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "Room.h"
using namespace std;

// Struct data structure to represent the different
// pathways to/from the buliding to different building
struct Edge;

class Building {
private:
    string building_id; // ID of Building TODO: this is used, almost excusively, throughout the code. perhaps edit?
    string name; // name of building.
    tuple <double, double> lat_long; // coordinate of room
    vector <Room> rooms; // list of rooms for object
public:
    vector<Edge> edges; // Stored Vector of pathways
    double distance; // Used in dijstrak's algorithm
    Building* prevBuilding; // Used in dijstrak's algorithm
    Building(); // Default Constructor
    Building(string building_id); // Overloaded Constructor
    Building(string building_id, Edge edge); // Overloaded Constructor
    void add_edge(Edge edge); //Add edge
    string get_building_id(); // TESTING PURPOSES PRINT
    void print_information(); // TESTING PURPOSES PRINT
};

struct Edge {
    Building* connectedBuilding;
    int weight; // minutes to connectedBuilding
    Edge(); // default constructor
    Edge(Building* connectedBuilding, int weight); //overloaded constructor
};


//------------------------------ Priority Queue ---------------------------
// Taken from the last assignment, including the methods, but tailored for this assignment and code
// functions as a queue object, to be used in dikjstra's algorithm
// at the moment (to be fixed) the methods are implemented in graph.cpp and this declaration is housed in building.h
class PriorityQueue {
public:
    PriorityQueue();
    bool isEmpty() const;
    void enqueue(Building* b);
    Building* dequeue();
private:
    struct ListNode {
        Building* element;
        ListNode* next;
        ListNode(Building* theElement, ListNode* n = nullptr)
            : element(theElement), next(n) {}
    };
    ListNode* front;
};

#endif // BUILDING_H