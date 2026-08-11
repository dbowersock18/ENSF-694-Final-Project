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

/*
 * REQUIRES: a valid Building pointer
 * PROMISES: inserts (or updates) the building in the fast-lookup index, keyed by building_id
 */
void Campus::indexBuilding(Building* b){
    this -> buildingIndex.insert(b -> get_building_id(), b);
}

/*
 * PROMISES: returns the Building with the given id, or nullptr if none is indexed under that id
 */
Building* Campus::findBuilding(const string& building_id){
    return this -> buildingIndex.lookup(building_id);
}

// Removes a building from the fast-lookup index. Returns true if it was present
bool Campus::removeBuildingIndex(const string& building_id){
    return this -> buildingIndex.remove(building_id);
}

/*
 * PROMISES: (re)builds the room index from scratch by scanning every building's rooms vector.
 * Rooms are stored by value (vector<Room>), so this must be called only after all rooms have
 * finished loading - inserting more rooms afterwards could reallocate the vector and invalidate
 * the pointers stored here.
 */
void Campus::buildRoomIndex(){
    for (int i = 0; i < (int) this -> campusBuildings.size(); i++){
        for (int j = 0; j < (int) this -> campusBuildings[i]->rooms.size(); j++){
            this -> roomIndex.insert(this -> campusBuildings[i]->rooms[j].get_room_id(), &(this -> campusBuildings[i]->rooms[j]));
        }
    }
}

/*
 * PROMISES: returns the Room with the given id, or nullptr if none is indexed under that id
 */
Room* Campus::findRoom(const string& room_id){
    return this -> roomIndex.lookup(room_id);
}

// Removes a room from the fast-lookup index. Returns true if it was present
bool Campus::removeRoomIndex(const string& room_id){
    return this -> roomIndex.remove(room_id);
}