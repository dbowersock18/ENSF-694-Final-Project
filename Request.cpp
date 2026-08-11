#include <iostream>
#include <string>
using namespace std;
#include "Request.h"

// Default constructor for ServiceRequest
ServiceRequest::ServiceRequest(){
    this -> id = 0;
    this -> description = "Request - default description";
    this -> priority = STANDARD;
}

// Overloaded constructor for ServiceRequest
ServiceRequest::ServiceRequest(int id, string description, RequestPriority priority){
    this -> id = id;
    this -> description = description;
    this -> priority = priority;
}

// Converts the priority enum into a human readable label
string ServiceRequest::priorityToString(){
    if (this -> priority == EMERGENCY) return "Emergency";
    if (this -> priority == STANDARD) return "Standard";
    return "Low";
}

//------------------------------ PriorityServiceQueue (2.4) ---------------------------

PriorityServiceQueue::PriorityServiceQueue() : front(nullptr), count(0) {}

/*
* PROMISES: Returns a boolean truth if the queue is empty
*/
bool PriorityServiceQueue::isEmpty() const {
    return front == nullptr;
}

/*
* REQUIRES: A ServiceRequest pointer
* PROMISES: Inserts the request, keeping the list ordered by priority (Emergency first),
* and by arrival id (lower id first) among requests that share a priority level
*/
void PriorityServiceQueue::addRequest(ServiceRequest* r) {
    ListNode* newNode = new ListNode(r);
    if (isEmpty() ||
        r -> priority < front -> element -> priority ||
        (r -> priority == front -> element -> priority && r -> id < front -> element -> id)) {
        newNode -> next = front;
        front = newNode;
    } else {
        ListNode* current = front;
        while (current -> next != nullptr &&
               (current -> next -> element -> priority < r -> priority ||
                (current -> next -> element -> priority == r -> priority && current -> next -> element -> id <= r -> id))) {
            current = current -> next;
        }
        newNode -> next = current -> next;
        current -> next = newNode;
    }
    count++;
}

/*
* PROMISES: Removes and returns the highest priority request (Emergency before Standard before Low)
*/
ServiceRequest* PriorityServiceQueue::serveNext() {
    if (isEmpty()) {
        cerr << "PriorityServiceQueue is empty." << endl;
        exit(0);
    }
    ServiceRequest* frontItem = front -> element;
    ListNode* old = front;
    front = front -> next;
    delete old;
    count--;
    return frontItem;
}

// Getter for the number of requests currently queued
int PriorityServiceQueue::size() const {
    return count;
}

/*
* PROMISES: Prints the requests currently queued, in the exact order they will be served
*/
void PriorityServiceQueue::printQueue() const {
    ListNode* current = front;
    if (current == nullptr) {
        cout << "   The priority service queue is empty" << endl;
        return;
    }
    while (current != nullptr) {
        cout << "   [" << current -> element -> priorityToString() << "] "
        << "Request #" << current -> element -> id << ": " << current -> element -> description << endl;
        current = current -> next;
    }
}

//------------------------------ RequestPipeline (2.6) ---------------------------

RequestPipeline::RequestPipeline() : front(nullptr), back(nullptr), count(0) {}

/*
* PROMISES: Returns a boolean truth if the pipeline is empty
*/
bool RequestPipeline::isEmpty() const {
    return front == nullptr;
}

/*
* REQUIRES: A ServiceRequest pointer
* PROMISES: Adds the request to the back of the pipeline, preserving arrival order
*/
void RequestPipeline::enqueueRequest(ServiceRequest* r) {
    ListNode* newNode = new ListNode(r);
    if (isEmpty()) {
        front = newNode;
        back = newNode;
    } else {
        back -> next = newNode;
        back = newNode;
    }
    count++;
}

/*
* PROMISES: Removes and returns the request at the front of the pipeline (the oldest, unprocessed request)
*/
ServiceRequest* RequestPipeline::dequeueRequest() {
    if (isEmpty()) {
        cerr << "RequestPipeline is empty." << endl;
        exit(0);
    }
    ServiceRequest* frontItem = front -> element;
    ListNode* old = front;
    front = front -> next;
    if (front == nullptr) back = nullptr;
    delete old;
    count--;
    return frontItem;
}

// Getter for the number of requests currently pending
int RequestPipeline::size() const {
    return count;
}
