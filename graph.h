#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <cmath>
#include "Building.h"
#include "Campus.h"

using namespace std;

class Graph{
private:
    Campus* campus; // Campus Object
    Building* start; // Building Object Pointer, that acts as the "head" for a linked list
    Building* end; // Building Object Pointer, that acts as the "tail" for a linked list
    vector<Building*> startHistorical; // Functions as a stack that keeps track of past queries
    vector<Building*> endHistorical; // Functions as a stack that keeps track of past queries
public:
    Graph(); // Default Construcotr
    Graph(Campus*); // Overloaded Constructor, given Campus Object
    void read_input_file(const string&); // processes Campus Map, in the form of a text file
    void dijkstra(); // Calculuation of shortest path. Takes a start String by Building ID
    void printGraph(); // Prints the Graph Calculation of ALL members
    void printPath(Building*); // Prints the Path calculated by dijkstar's algorithm, for a single building object
    void setStartEnd(Building*, Building*); // Sets private members heads and tails
    Building* getStartHistorical(); // Gets last Start Queue
    Building* getEndHistorical(); // Gets last End Queue
    int sizeOfHistorical(); // returns the size of the historical Queue
    void setHistorical(); // Logs the current start / end Building Pointers in the Stack
    void reset(); // Resets the algorithm
    Building* getStart(); // Returns start Building, or "head"
    Building* getEnd(); // Returns end building, or "tail"
};

#endif // GRAPH_H