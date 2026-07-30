#include <iostream>
#include <string>
using namespace std;
#include "Building.h"

Building::Building(){
    this -> building_id = "Building - Default ID";
}

void Building::print_information(){
    cout << "Information for building is: " << this -> building_id << endl;
}