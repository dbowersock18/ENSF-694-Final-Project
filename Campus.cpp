#include <iostream>
#include <string>
using namespace std;
#include "Campus.h"

// Default Construtor
Campus::Campus(){
    this -> campus_id = "Default - Campus ID";
}

/*
 * PROMISES: Prints the information relevant to the campus object 
 */
void Campus::print_information_campus(){
    cout << "Campus information: " << this -> campus_id << endl;
    cout << "Campus includes buildings: ";

    for (int i = 0; i < (int) campusBuildings.size(); i++){
        cout << this -> campusBuildings[i] -> get_building_id() << " ";
    }
}
 
/*
 * PROMISES: prints the information relevant to each building in the campus, by calling the speciifc print information 
 * method of each building
 */
void Campus::print_information_buildings(){
    cout << endl;
    for (int i = 0; i < (int) this -> campusBuildings.size(); i++){
        this -> campusBuildings[i]->print_information();
        cout << endl;
    }
}