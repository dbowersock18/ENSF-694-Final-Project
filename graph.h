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
    void dijkstra(string); // Calculuation of shortest path. Takes a start String by Building ID
    void printGraph();
};