#include <iostream>
#include <string>
using namespace std;
#include "Campus.h"

Campus::Campus(){
    this -> campus_id = "Default - Campus ID";
}

void Campus::print_information(){
    cout << "Campus information: " << this -> campus_id << endl;
}