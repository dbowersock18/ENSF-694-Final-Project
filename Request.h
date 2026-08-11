#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <string>
using namespace std;

// Priority levels for the service queue (2.4). Lower numeric value = served first.
enum RequestPriority {
    EMERGENCY = 0,
    STANDARD = 1,
    LOW = 2
};

// A single request flowing through either the Priority Service Queue (2.4)
// or the Incoming Request Processing pipeline (2.6)
class ServiceRequest {
public:
    int id; // unique, ever-increasing id, also used as the arrival order for FIFO/tie-breaking
    string description; // e.g. "IT Support - printer offline"
    RequestPriority priority; // urgency of the request
    ServiceRequest(); // default constructor
    ServiceRequest(int id, string description, RequestPriority priority); // overloaded constructor
    string priorityToString(); // human readable priority label
};

//------------------------------ 2.4 Priority-Based Service Queue ---------------------------
// Requests are served strictly in order of urgency (Emergency > Standard > Low).
// Implemented as a sorted linked list, ordered first by priority then by arrival id,
// so requests of equal urgency are still served first-come-first-served (a stable priority queue).
class PriorityServiceQueue {
public:
    PriorityServiceQueue(); // default constructor
    bool isEmpty() const; // true if no requests are queued
    void addRequest(ServiceRequest* r); // insert a request, keeping the list ordered by urgency
    ServiceRequest* serveNext(); // remove and return the highest priority request
    int size() const; // number of requests currently queued
    void printQueue() const; // prints requests in the order they will be served
private:
    struct ListNode {
        ServiceRequest* element;
        ListNode* next;
        ListNode(ServiceRequest* theElement, ListNode* n = nullptr)
            : element(theElement), next(n) {}
    };
    ListNode* front;
    int count;
};

//------------------------------ 2.6 Incoming Request Processing ---------------------------
// Navigation/service requests arrive continuously and must be processed in arrival order.
// Implemented as a standard FIFO linked-list queue (enqueue at back, dequeue from front).
class RequestPipeline {
public:
    RequestPipeline(); // default constructor
    bool isEmpty() const; // true if no requests are pending
    void enqueueRequest(ServiceRequest* r); // add a request to the back of the pipeline
    ServiceRequest* dequeueRequest(); // remove and return the request at the front (oldest)
    int size() const; // number of requests currently pending
private:
    struct ListNode {
        ServiceRequest* element;
        ListNode* next;
        ListNode(ServiceRequest* theElement, ListNode* n = nullptr)
            : element(theElement), next(n) {}
    };
    ListNode* front;
    ListNode* back;
    int count;
};

#endif // REQUEST_H
