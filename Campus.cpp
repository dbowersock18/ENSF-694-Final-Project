#include <iostream>
#include <string>
using namespace std;
#include "Campus.h"

Campus::Campus(){
    this -> campus_id = "Default - Campus ID";
}

void Campus::print_information(){
    cout << "Campus information: " << this -> campus_id << endl;
    cout << "Campus includes buildings: ";
    for (int i = 0; i < (int) campusBuildings.size(); i++){
        cout << this -> campusBuildings[i] -> get_building_id() << ", ";
    }
}