#include <iostream>
#include <string>
using namespace std;
#include "Campus.h"

Campus::Campus(){
    this -> campus_id = "Default - Campus ID";
}

void Campus::print_information_campus(){
    cout << "Campus information: " << this -> campus_id << endl;
    cout << "Campus includes buildings: " << endl;

    for (int i = 0; i < (int) campusBuildings.size(); i++){
        cout << this -> campusBuildings[i] -> get_building_id() << ", ";
    }
}

void Campus::print_information_buildings(){
    cout << endl;
    cout << endl;
    for (int i = 0; i < (int) this -> campusBuildings.size(); i++){
        this -> campusBuildings[i]->print_information();
        cout << endl;
    }
}