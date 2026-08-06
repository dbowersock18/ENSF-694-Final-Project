#include <iostream>
#include <string>
#include <vector>
#include "Building.h"
using namespace std;

class Campus {
private:
    string campus_id;
public:
    // Collection of buildings
    vector<Building> campusBuildings;
    Campus();
    void print_information();
};