#ifndef CAMPUS_H
#define CAMPUS_H

#include <iostream>
#include <string>
#include <vector>
#include "Building.h"
using namespace std;

class Campus {
private:
    string campus_id; // unique campus I 
public:
    vector<Building*> campusBuildings;     // Collection of building objects
    Campus(); // Default constructor
    void print_information_campus(); // Prints information relevant to campus
    void print_information_buildings(); // Prints information relevant to the buildings within the campus
};

#endif // CAMPUS_H