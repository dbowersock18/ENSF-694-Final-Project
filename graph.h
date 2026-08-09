#include <iostream>
#include <string>
#include <cmath>
#include "Building.h"
#include "Campus.h"

using namespace std;

class Graph{
private:
    Campus* campus;
public:
    Graph(); // Default Construcotr
    Graph(Campus*); // Overloaded Constructor, given Campus Object
    void read_input_file(const string&); // processes Campus Map, in the form of a text file
    void dijkstra(string); // Calculuation of shortest path. Takes a start String by Building ID
    void printGraph(); // Prints the Graph Calculation
    void printPath(Building*); // Taken from Assignment
};