#ifndef CAMPUS_H
#define CAMPUS_H

#include <iostream>
#include <string>
#include <vector>
#include "Building.h"
using namespace std;

class Campus {
private:
    string campus_id;
public:
    // Collection of building objects
    vector<Building> campusBuildings;
    Campus(); // Default constructor
    void print_information(); // TESTING PURPOSES PRINT INFORMATION
};

#endif // CAMPUS_H