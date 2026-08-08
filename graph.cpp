#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
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
    cout << endl;
}

void Graph::printGraph(){
    campus -> print_information();
    cout << endl;
    cout << endl;
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