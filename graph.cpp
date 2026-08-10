#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include "graph.h"
#include "Building.h"
#include "Campus.h"

using namespace std;

PriorityQueue::PriorityQueue() : front(nullptr) {}

bool PriorityQueue::isEmpty() const {
    return front == nullptr;
}

void PriorityQueue::enqueue(Building* b) {
    ListNode* newNode = new ListNode(b);
    if (isEmpty() || b -> distance < front->element->distance) {
        newNode->next = front;
        front = newNode;
    } else {
        ListNode* current = front;
        while (current->next != nullptr && current->next->element->distance <= b->distance) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

Building* PriorityQueue::dequeue() {
    if (isEmpty()) {
        cerr << "PriorityQueue is empty." << endl;
        exit(0);
    }
    Building* frontItem = front->element;
    ListNode* old = front;
    front = front->next;
    delete old;
    return frontItem;
}

Graph::Graph(Campus* campus){
    this -> campus = campus;
}

void Graph::setStartEnd(Building* start, Building* end){
    this -> start = start;
    this -> end = end;
}
Building* Graph::getStart(){
    return this -> start;
}
Building* Graph::getEnd(){
    return this -> end; 
}
void Graph::setHistorical(){
    this -> startHistorical.push_back(this -> start);
    this -> endHistorical.push_back(this -> end);
}
Building* Graph::getStartHistorical(){
    startHistorical.pop_back();
    Building* returnValue = startHistorical.back();
    return returnValue;
}
Building* Graph::getEndHistorical(){
    endHistorical.pop_back();
    Building* returnValue = endHistorical.back();
    return returnValue;
}
int Graph::sizeOfHistorical(){
    return startHistorical.size();
}

void Graph::dijkstra(){
    PriorityQueue q; // Queue object
    vector<string> visited; // list of buildings, or nodes, that have been visited
    Building* startB = this -> start; // initialization variable for method
    // // Search through Campus buildings for starting Building.
    // // TODO: this is no longer needed due to change in code. Leave alone until 100% sure it can be deleted.
    // for (int i = 0; i < (int) campus->campusBuildings.size(); i++){
    //     if(campus -> campusBuildings[i] -> get_building_id() == start){
    //         startB = (campus -> campusBuildings[i]);
    //         break;
    //     }
    // }
    q.enqueue(startB);
    startB -> distance = 0;
    while (!q.isEmpty()){
        Building* currentB = q.dequeue();
        if(!visited.empty() && find(visited.begin(), visited.end(), currentB -> get_building_id()) != visited.end()) continue;
        else visited.push_back(currentB -> get_building_id());

        // Cycle through edges
        for (int i = 0; i < (int) currentB -> edges.size(); i++){
            // Que current Path
            q.enqueue(currentB -> edges[i].connectedBuilding);
            // Check for infinty, if yes populate and que
            if (currentB->edges[i].connectedBuilding -> distance == infinity()) {
                currentB->edges[i].connectedBuilding -> distance = currentB -> distance + currentB->edges[i].weight;
                currentB->edges[i].connectedBuilding -> prevBuilding = currentB;
            }
            // check if shorter path, update if so
            if (currentB->edges[i].connectedBuilding -> distance > currentB -> distance + currentB->edges[i].weight){
                currentB->edges[i].connectedBuilding -> distance = currentB -> distance + currentB->edges[i].weight;
                currentB->edges[i].connectedBuilding -> prevBuilding  = currentB;
            }
        }
    }
}

void Graph::printGraph(){
    cout << "The algorithm produced the following collective stats: " << endl;
    cout << "The starting location is: " << this -> start ->  get_building_id() << endl;
    for (int i = 0; i < (int) campus->campusBuildings.size(); i++){
        if (campus -> campusBuildings[i] == this -> start) continue;
        cout << "   getting to " << campus -> campusBuildings[i] -> get_building_id() <<
        " takes " << campus -> campusBuildings[i] -> distance <<" minutes and you must navigate via: ... ";
        printPath((campus -> campusBuildings[i]));
        cout << endl;
    }
}

void Graph::printPath(Building* dest) {
    if (dest->prevBuilding != nullptr) {
        printPath(dest->prevBuilding);
        cout << " -> ";
        cout << " " << dest -> get_building_id();
    }
    else{
        cout << dest -> get_building_id();
    }
}

void Graph::read_input_file(const string& filename){
    cout<< "Reading input file " << filename << endl;
    ifstream infile(filename);
    if (!infile) {
        cerr << "Could not open file: " << filename << endl;
        exit(1);
    }
    string a, b;
    int time;
    while (infile >> a >> b >> time) {
        bool a_exists = false;
        bool b_exists = false;
        int a_index = -1;
        int b_index = -1;
        for (int i = 0; i < (int) campus->campusBuildings.size(); i++){
            if(campus -> campusBuildings[i] -> get_building_id() == a){
                a_exists = true;
                a_index = i;
                break;
            }
        }
        for (int i = 0; i < (int) campus->campusBuildings.size(); i++){
            if(campus -> campusBuildings[i] -> get_building_id() == b){
                b_exists = true;
                b_index = i;
                break;
            }
        }
        // create two buildings and add to campus if reqired
        Building* buildingA;
        if (!a_exists) {
            buildingA = new Building(a);
            campus->campusBuildings.push_back(buildingA);
        }
        else buildingA = campus -> campusBuildings[a_index];
        Building* buildingB;
        if (!b_exists) {
            buildingB = new Building(b);
            campus->campusBuildings.push_back(buildingB);
        }
        else buildingB = campus -> campusBuildings[b_index];
        // add edge to both buildings
        buildingA -> add_edge(Edge(buildingB, time));
        buildingB -> add_edge(Edge(buildingA, time));
    }
    cout << "Finished reading from file" << endl;
    infile.close();
}

void Graph::reset(){
    this -> start = nullptr; 
    this -> end = nullptr;
    for (int i = 0; i < (int) campus->campusBuildings.size(); i++) {
        campus -> campusBuildings[i]->distance = infinity();
        campus -> campusBuildings[i]->prevBuilding = nullptr;
    }
}