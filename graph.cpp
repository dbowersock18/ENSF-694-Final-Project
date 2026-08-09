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

void Graph::dijkstra(string start){
    PriorityQueue q; // Queue object
    vector<string> visited; // list of buildings, or nodes, that have been visited
    Building* startB; // initialization variable for method
    // Search through Campus buildings for starting Building
    for (int i = 0; i < (int) campus->campusBuildings.size(); i++){
        if(campus -> campusBuildings[i] -> get_building_id() == start){
            startB = (campus -> campusBuildings[i]);
            break;
        }
    }
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
    for (int i = 0; i < (int) campus->campusBuildings.size(); i++){
        cout << "Campus Building: " << campus -> campusBuildings[i] -> get_building_id() <<
        " takes " << campus -> campusBuildings[i] -> distance <<" minutes and has previous Path of: ... ";
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
    // int count = 0;
    while (infile >> a >> b >> time) {
        // cout << count << endl; 
        // count++;
        // verify bulidings don't already exist in data
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
    cout << endl;
    infile.close();
}
