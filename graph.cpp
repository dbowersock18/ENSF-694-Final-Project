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
    PriorityQueue q;
    vector<Building> visited;
    Building* startB;
    for (int i = 0; i < (int) campus->campusBuildings.size(); i++){
        if(campus -> campusBuildings[i].get_building_id() == start){
            startB = &(campus -> campusBuildings[i]);
            break;
        }
    }
    q.enqueue(startB);
    cout << "Starting Building is: " << startB->get_building_id();
}

void Graph::printGraph(){
    campus -> print_information();
    cout << endl;
}