#ifndef CAMPUS_H
#define CAMPUS_H

#include <iostream>
#include <string>
#include <vector>
#include "Building.h"
#include "HashTable.h"
using namespace std;

class Campus {
private:
    string campus_id; // unique campus I
    // NOTE! The pathways, are stored under each building object NOT the campus object
    // this is in contradiction to the project guidelines reccommendations but it states, after all, just a recommendation
public:
    vector<Building*> campusBuildings;     // Collection of building objects
    HashTable<Building> buildingIndex; // 2.5: fast O(1) average lookup of buildings by building_id
    HashTable<Room> roomIndex; // 2.5: fast O(1) average lookup of rooms by room_id
    Campus(); // Default constructor
    void print_information_campus(); // Prints information relevant to campus
    void print_information_buildings(); // Prints information relevant to the buildings within the campus
    void indexBuilding(Building* b); // Inserts/updates a building in the fast-lookup index
    Building* findBuilding(const string& building_id); // O(1) average lookup of a building by id
    bool removeBuildingIndex(const string& building_id); // Removes a building from the fast-lookup index
    void buildRoomIndex(); // (Re)builds the room index by scanning every building's rooms. Call once after rooms are loaded
    Room* findRoom(const string& room_id); // O(1) average lookup of a room by id
    bool removeRoomIndex(const string& room_id); // Removes a room from the fast-lookup index
};

#endif // CAMPUS_H