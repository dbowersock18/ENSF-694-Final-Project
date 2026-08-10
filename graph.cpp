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

PriorityQueue::PriorityQueue() : front(nullptr) {} // Queue for dikjstra's algorithm

/*
* PROMISES: Returns a boolean truth if queue is empty/full
*/
bool PriorityQueue::isEmpty() const {
    return front == nullptr;
}

/*
* REQUIRES: A building object pointer, that will be queue'd
*/
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

/*
* PROMISES: A building object pointer from the queue, the "first in"
*/
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

// Overloaded constructor that earmarks the campus object pointer
Graph::Graph(Campus* campus){
    this -> campus = campus;
}

/* 
* PROMISES: Populates the start and end (head and tail) pointers for the Graph class
*/
void Graph::setStartEnd(Building* start, Building* end){
    this -> start = start;
    this -> end = end;
}
// Getter for start (head)
Building* Graph::getStart(){
    return this -> start;
}
// Getter for end (tail)
Building* Graph::getEnd(){
    return this -> end; 
}
/*
 * PROMISES: Stacks the current start/end (head/tail) onto the Historical Stack
 */
void Graph::setHistorical(){
    this -> startHistorical.push_back(this -> start);
    this -> endHistorical.push_back(this -> end);
}
/*
 * PROMISES: A building object Pointer, that was last on the stack. Removes query from stack 
 */
Building* Graph::getStartHistorical(){
    startHistorical.pop_back();
    Building* returnValue = startHistorical.back();
    return returnValue;
}
/*
 * PROMISES: A building object Pointer, that was last on the stack. Removes query from stack 
 */
Building* Graph::getEndHistorical(){
    endHistorical.pop_back();
    Building* returnValue = endHistorical.back();
    return returnValue;
}
// Getter for the size of the Historical Stack
int Graph::sizeOfHistorical(){
    return startHistorical.size();
}
/*
 * PROMISES: The calculation of the dijkstra algorithm for the current campus and it's buildings
 * populates cumulative times (wieghts) and previous building pointers to build the path from start -> end
 */
void Graph::dijkstra(){
    PriorityQueue q; // Queue object
    vector<string> visited; // list of buildings, or nodes, that have been visited
    Building* startB = this -> start; // initialization variable for method
    q.enqueue(startB);
    startB -> distance = 0;
    while (!q.isEmpty()){
        Building* currentB = q.dequeue();
        // Verify Building was not already visited
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

/*
 * PROMISES: Outputs all information related to the dijkstra algorithm; namely each building 
 * the time to each from the starting point (weights), and the path to it (via printPath method)
 */
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

/*
 * REQUIRES: A building object pointer
 * PROMISES: Outputs the specific path of the requested buildings
 */
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

/* A static method (set and forget) that reads the conents of an input file (specifically formatted) and populates
 * the initial states for the program operationn
 * REQUIRES: A valid, local, path to the text file
 * PROMISES:  The interpretation and population of pertinent properties
 */
void Graph::read_input_file(const string& filename){
    cout<< "Reading input file " << filename << endl;
    // Validates the file can be accessed
    ifstream infile(filename);
    if (!infile) {
        cerr << "Could not open file: " << filename << endl;
        exit(1);
    }
    string a, b;
    int time;
    // Interprets and populates the campus object with buildings (a and b) and the weight
    // of each path (time)
    while (infile >> a >> b >> time) {
        bool a_exists = false;
        bool b_exists = false;
        int a_index = -1;
        int b_index = -1;
        // Checks if buliding "a" is not already present in campus object; if not, populates
        for (int i = 0; i < (int) campus->campusBuildings.size(); i++){
            if(campus -> campusBuildings[i] -> get_building_id() == a){
                a_exists = true;
                a_index = i;
                break;
            }
        }
        // Checks if building object "b" is not already present in campus object; if not, populates
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

/*
 * PROMISES: resets portions of the Graph object, so dijkstra's algorithm can be re-ran
 * namely the start/end (head/tail) and the building objects distance (time) and prev builder pointers (travel path)
 */
void Graph::reset(){
    this -> start = nullptr; 
    this -> end = nullptr;
    for (int i = 0; i < (int) campus->campusBuildings.size(); i++) {
        campus -> campusBuildings[i]->distance = infinity();
        campus -> campusBuildings[i]->prevBuilding = nullptr;
    }
}