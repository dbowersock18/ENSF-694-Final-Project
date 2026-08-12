#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <chrono>
#include <cstdlib>
using namespace std;
#include "Room.h"
#include "Building.h"
#include "Campus.h"
#include "Graph.h"
#include "Request.h"
#include "HashTable.h"

// TODO LIST:
// IMPLEMENT A CHECK TO ENSURE THE USER IS ENTERING A VALID NUMBER
// Output the current Queue of historical searches
// Consider moving the class Priority Que from  building to Graph (logistical placement)

void interactWithUser(Campus*, Graph*); // Method that serves as the Client Interface (instad of another class)
void cliBookingManagement(Campus*); // Client Interface for mananaging the users wishes relative to the booking software
int obtainUserInput(); // Obtains a numerical user input
void importBookings(Campus*, const string &); // Method to obtain a list of bookings from a text file
void importRoomInformation(Campus*, const string&); // Method ot obtain Room information from a text file
void demoPriorityServiceQueue(); // Demonstrates the 2.4 Priority-Based Service Queue feature
void demoRequestPipeline(); // Demonstrates the 2.6 Incoming Request Processing feature
void demoFastLookup(Campus*); // Demonstrates the 2.5 Fast Building and Resource Lookup feature

int main(void) {

    // TEST BLOCK ROOM
    // file housing campus data. MUST BE LOADED FIRST! Contains building objects
    const string campusMap= "CampusMap.txt";
    // create objects
    Campus campus("University of Calgary");
    Graph graph(&campus);
    // run program and display information
    cout << endl;
    graph.read_input_file(campusMap);
    cout << endl;
    const string roomInformation = "roomInformation.txt";
    importRoomInformation(&campus, roomInformation);
    campus.buildRoomIndex(); // 2.5: index rooms only after they've all finished loading
    cout << endl << endl;
    const string bookingInformation = "RoomBooking.txt";
    importBookings(&campus, bookingInformation);
    cout << endl << endl;

    interactWithUser(&campus, &graph);
}

/*
* PROMISES: The integer value a user enters
*/
int obtainUserInput(){
    cout << "Obtaining user Input: ";
    int userInput;
    cin.clear();
    cin >> userInput;
    cout << endl;
    //TODO: VALIDATION CHECK TO ENSURE USER IS ENTERING CORRECT NUMBERS
    return userInput;
}

/*
* Serves as the Client Interface for obtaining, validating, and processing the User's request for calculating
* the shortest distance between two points on campus.
* REQUIRES: Campus object, graph object, and a boolean value depicting if we are starting 'fresh' or loading a historical data set
* PROMISES: Populates Campus and Graph objects with the outcomes of the dijkstra algorithm: populates linked list for naviagation 
* and weights for distance calculations to each object
*/
void shortestDistanceCalculator(Campus* campus, Graph* graph, bool lastQueue){
    int check = 0;
    int startIndex, endIndex;
    // If false (and by negation enters loop) obtains a new start and end from the user
    if(!lastQueue){
        while (check == 0){
            // Obtain start and end from user
            cout << "Please enter the number representing the builidng you would like to start from" << endl;
            for (int i = 0; i < (int) campus -> campusBuildings.size(); i++){
                cout << "   " << i << ": " << campus -> campusBuildings[i] -> get_building_id() <<endl;
            }
            startIndex = obtainUserInput();
            cout << "And now the end point, from the same list above" << endl;
            endIndex = obtainUserInput();
            cout << "You have selected the following: " << endl
            << "    Start: " << campus -> campusBuildings[startIndex] -> get_building_id() << endl
            << "    End: " << campus -> campusBuildings[endIndex] -> get_building_id() << endl;
            cout << endl << "Is this correct? " <<
            "press 0 if no" << " press 1 if yes" << endl;
            if (obtainUserInput() == 1) break;
            else cout << endl;
        }
        // End of obtaining start and end from user
        // Sets the start (head) and end (tail) of campus
        graph -> setStartEnd( campus -> campusBuildings[startIndex], campus -> campusBuildings[endIndex]);
        // run the algorithm
        graph -> dijkstra();
        // output the results to the user
        cout << "Starting from " << graph -> getStart() -> get_building_id() << " it takes "
        << graph -> getEnd() -> distance << " minutes to get to " << graph -> getEnd() -> get_building_id() << " with a route of: ";
        graph -> printPath( graph -> getEnd());
        // logs the start/end in the historical stack
        graph -> setHistorical();
    }
    // If true, a start/end is already provided and so not required to obtain from user
    if(lastQueue){
        cout << "The previous query you have requested is: " << endl
        << "    Start: " << graph -> getStart() -> get_building_id() << endl
        << "    End: " << graph -> getEnd() -> get_building_id() << endl;
        // re-runs dijkstra algorithm
        graph -> dijkstra();
        cout << endl;
        // output the results to the user
        cout << "Starting from " << graph -> getStart() -> get_building_id() << " it takes "
        << graph -> getEnd() -> distance << " minutes to get to " << graph -> getEnd() -> get_building_id() << " with a route of: ";
        graph -> printPath( graph -> getEnd());
        cout << endl;
    }
}

/*
* REQUIRES: Campus object, and graph object, pointer
* PROMISES: Returns to the previous building. Does not perform any additional calculations
*/
void walkBack(Campus* campus, Graph* graph){
    // Validates that you can actually 'walkback' and your not at the start
    if (graph -> getEnd() == graph -> getStart()) {
        cout << "Sorry ... you can't walk back farther than your starting point!";
        return;
    }
    // 'Walks back' by resetting the start/end to be start/end-1 
    graph->setStartEnd(graph -> getStart(), graph -> getEnd() -> prevBuilding);
    cout << "Now ... starting from " << graph -> getStart() -> get_building_id() << " it takes "
    << graph -> getEnd() -> distance << " minutes to get to " << graph -> getEnd() -> get_building_id() << " with a route of: ";
    graph -> printPath( graph -> getEnd());
}

/*
* REQUIRES: Campus object, and graph object, pointer
* PROMISES: Returns to the previous query by setting the head/end to be the last head/end and re-running the algorithm 
*/
void reloadLastQuery(Campus* campus, Graph* graph){
    // Validates that your stack is not empty
    if (graph->sizeOfHistorical() == 1) {
        cout << "Sorry! ... You have no previous records!" << endl;
        return;
    }
    // Obtains the previous start/end
    Building* start = graph -> getStartHistorical();
    Building* end = graph -> getEndHistorical();
    // reset the graph, set the start/end, and re-run the algorithm to calculate shortestst distance
    graph -> reset();
    graph -> setStartEnd(start, end);
    shortestDistanceCalculator(campus, graph, true);
}

/*
* REQUIRES: Campus object, and graph object, pointer
* PROMISES: Interaction with the client. Will not break until the user enters 0
* Other methods are called, namely those above, when a user enters a specific key
*/
void interactWithUser(Campus* campus, Graph* graph){
    cout << "Entry point of user interaction" << endl;
    int endProgram = 1;
    while(endProgram){
        cout << "Please press: "  << endl
        << "    0: to terminate program" << endl
        << "    1: display all information relevant to current campus" << endl
        << "    2: to calcuate the distance to a location, given a starting location" << endl
        << "    3: to manage bookings" << endl
        << "    4: demo the priority-based service queue" << endl
        << "    5: demo the incoming request processing pipeline" << endl
        << "    6: demo fast building/room lookup" << endl;
        int returnValue = obtainUserInput();
        endProgram = returnValue;
        if (returnValue == 0) return;
        if (returnValue == 1) {
            campus -> print_information_campus();
            cout << endl;
            campus -> print_information_buildings();
        }
        if (returnValue == 2){
            shortestDistanceCalculator(campus, graph, false);
            int secondaryMenu = 1;
            while (secondaryMenu){
                cout << endl;
                cout << "Now that the shortest distances have been calculated, the menu options have changed. ";
                cout << "Please press: "  << endl
                << "    0: to terminate program" << endl
                << "    1: go back to main menu" << endl
                << "    2: reset, and calcuate the distance to a new location, given a new starting location" << endl
                << "    3: walk back to the previous building" << endl
                << "    4: reload your last query" << endl;
                int returnValue = obtainUserInput();
                if (returnValue == 0) {
                    endProgram = 0;
                    break;
                }
                if (returnValue == 1) {
                    break;
                    continue;
                }
                if (returnValue == 2) {
                    graph -> reset();
                    shortestDistanceCalculator(campus, graph, false);
                }
                if (returnValue == 3) walkBack(campus, graph);
                cout << endl;
                if (returnValue == 4) {
                    reloadLastQuery(campus, graph);
                }
            }
        }
        if (returnValue == 3){
            // TODO: IMPLEMENT
            cliBookingManagement(campus);
        }
        if (returnValue == 4){
            demoPriorityServiceQueue();
        }
        if (returnValue == 5){
            demoRequestPipeline();
        }
        if (returnValue == 6){
            demoFastLookup(campus);
        }
    }
    cout << endl;
    cout << "End point of user interaction" << endl;
}

/*
 * Reads "RoomInformation.txt" to populate all the rooms related to specific buildings 
 */
void importRoomInformation(Campus* campus, const string& filename){
    // TODO: POPULATE
    cout<< "Reading input file " << filename << endl;
    // Validates the file can be accessed
    ifstream infile(filename);
    if (!infile) {
        cerr << "Could not open file: " << filename << endl;
        exit(1);
    }
    string building, room_name, room_type;
    int capacity;
    // populates each building object with the relevant room information
    while (infile >> building >> room_name >> capacity >> room_type) {
        // find building in list of buildings
        for (int i = 0; i < (int) campus->campusBuildings.size(); i++){
            if(campus -> campusBuildings[i] -> get_building_id() == building){
                campus -> campusBuildings[i] -> rooms.push_back(Room(room_name, capacity, room_type));
                break;
            }
        }
    }
    cout << "End of reading input file";
    infile.close();
}

/*
 * Reads "importBooking.txt" to populate all the bookings tagged to a specific room 
 */
void importBookings(Campus* campus, const string & filename){
    // TODO: POPULATE
    cout<< "Reading input file " << filename << endl;
    // Validates the file can be accessed
    ifstream infile(filename);
    if (!infile) {
        cerr << "Could not open file: " << filename << endl;
        exit(1);
    }
    string building, room, purpose;
    int year, month, day, hour, duration;
    // populates each room object with the relevant booking information
    while (infile >> building >> room >> year >> month >> day >> hour >> duration >> purpose) {
        // find building in list of buildings
        for (int i = 0; i < (int) campus->campusBuildings.size(); i++){
            if(campus -> campusBuildings[i] -> get_building_id() == building){
                for (int j = 0; j < (int) campus -> campusBuildings[i]->rooms.size(); j++){
                    if(campus -> campusBuildings[i]->rooms[j].get_room_id() == room){
                        campus -> campusBuildings[i]->rooms[j].addBooking(year, month, day, hour, duration, purpose);
                    }
                }
            }
        }
    }
    cout << "End of reading input file";
    infile.close();
}

void cliBookingManagement(Campus* campus){
    int returnValue = 1;
    while (returnValue){
        cout << "Would you like to: " << endl;
        cout << "   0: Return to the main menu" << endl;
        cout << "   1: View all bookings for a given room" << endl;
        cout << "   2: View bookings for a given room, within a specified window" << endl;
        cout << "   3: Add booking" << endl;
        cout << "Please enter a value: ";
        cin >> returnValue;
        if (returnValue == 0) break;
        if (returnValue == 1) {
            int breakLoop = 1;
            while (breakLoop){
                string building, room;
                cout << "Please type the building, followed by the room id. eg) ict ict_204 Press 0 for either input to return: ";
                cin >> building >> room;
                cout << endl;
                if ((building == "0" || room == "0")) break;
                // Loops below print information regarding the booking in each buildings
                for (int i = 0; i < (int) campus->campusBuildings.size(); i++){
                    if(campus -> campusBuildings[i] -> get_building_id() == building){
                        for (int j = 0; j < (int) campus -> campusBuildings[i]->rooms.size(); j++){
                            if(campus -> campusBuildings[i]->rooms[j].get_room_id() == room){
                                campus->campusBuildings[i]->rooms[j].displayInformationAllBookings();
                                breakLoop = 0;
                                cout << endl;
                                break;
                            }
                        }
                    }
                }
                if (breakLoop == 1) cout << "That building + room combination does not exist!" << endl << endl;
            }
        }
        if (returnValue == 2){
            string building, room;
            cout << "Please type the building, followed by the room id. eg) ict ict_204 Press 0 for either input to return: ";
            cin >> building >> room;
            cout << endl;
            bool found = 0;
            // Loops below print information regarding the booking in each buildings
            for (int i = 0; i < (int) campus->campusBuildings.size(); i++){
                if(campus -> campusBuildings[i] -> get_building_id() == building){
                    for (int j = 0; j < (int) campus -> campusBuildings[i]->rooms.size(); j++){
                        if(campus -> campusBuildings[i]->rooms[j].get_room_id() == room){
                            cout << "Room found!" << endl;
                            campus -> campusBuildings[i] -> rooms[j].queryFilterForBookings();
                            found = 1;
                        }
                    }
                }
            }
            if (!found) cout << "Building + Room could not be found" << endl;
        }
        if (returnValue == 3){
            string building, room, purpose;
            cout << "Please type the building, followed by the room id. eg) ict ict_204 Press 0 for either input to return: ";
            cin >> building >> room;
            cout << endl;
            bool found = 0;
            // Loops below print information regarding the booking in each buildings
            for (int i = 0; i < (int) campus->campusBuildings.size(); i++){
                if(campus -> campusBuildings[i] -> get_building_id() == building){
                    for (int j = 0; j < (int) campus -> campusBuildings[i]->rooms.size(); j++){
                        if(campus -> campusBuildings[i]->rooms[j].get_room_id() == room){
                            cout << "Room found!" << endl;
                            int year, month, day;
                            double hour, duration;
                            cout << "Please enter the following, in this specific format: year day month time duration (min) purpose" << endl;
                            cout << "For example August 11th 2026 7:30am for a class 2 hours should be entered, exactly: 2026 8 11 0730 120 Class" << endl
                            << "noting that the time is in 24 hour format (7:30am becomes 0730) and no leading whitespace (8th of August not 08)" << endl;
                            cout << "Please enter: ";
                            cin >> year >> month >> day >> hour >> duration >> purpose;
                            campus -> campusBuildings[i]->rooms[j].addBooking(year, month, day, hour, duration, purpose);
                            cout << "Booking logged!" << endl;
                            found = 1;
                        }
                    }
                }
            }
            if (!found) cout << "Building + Room could not be found" << endl;
        }
        cout << endl;
    }
    cout << endl;
    return;
}

/*
 * PROMISES: Demonstrates feature 2.4 - the Priority-Based Service Queue.
 * Adds requests across three priority levels (Emergency, Standard, Low) in a deliberately
 * mixed arrival order, then serves them all, showing that urgency - not arrival order - decides
 * service order, and that requests sharing a priority level stay in the order they arrived.
 */
void demoPriorityServiceQueue(){
    cout << "--- Priority-Based Service Queue Demo (Feature 2.4) ---" << endl;
    PriorityServiceQueue serviceQueue;
    ServiceRequest requests[] = {
        ServiceRequest(1, "Room maintenance - flickering lights in ICT-121", LOW),
        ServiceRequest(2, "IT support - projector not powering on", STANDARD),
        ServiceRequest(3, "Help desk - fire alarm malfunction in ENG Block", EMERGENCY),
        ServiceRequest(4, "IT support - wifi outage in Library", STANDARD),
        ServiceRequest(5, "Help desk - gas leak reported in Science A", EMERGENCY),
        ServiceRequest(6, "Room maintenance - broken chair in Student Union", LOW),
        ServiceRequest(7, "IT support - lab computer will not boot", STANDARD)
    };
    int numRequests = 7;

    cout << "Adding " << numRequests << " requests in arrival order: " << endl;
    for (int i = 0; i < numRequests; i++){
        cout << "   Arrived: [" << requests[i].priorityToString() << "] Request #"
        << requests[i].id << ": " << requests[i].description << endl;
        serviceQueue.addRequest(&requests[i]);
    }

    cout << endl << "Current queue, ordered by the sequence requests will be served: " << endl;
    serviceQueue.printQueue();

    cout << endl << "Serving requests: " << endl;
    while (!serviceQueue.isEmpty()){
        ServiceRequest* next = serviceQueue.serveNext();
        cout << "   Now serving [" << next -> priorityToString() << "] Request #"
        << next -> id << ": " << next -> description << endl;
    }
    cout << "--- End of Priority-Based Service Queue Demo ---" << endl;
}

/*
 * PROMISES: Demonstrates feature 2.6 - Incoming Request Processing.
 * Simulates 20 sequential navigation/service requests being enqueued as they arrive,
 * then dequeues and processes each one, showing that the pipeline always preserves
 * strict first-in-first-out (arrival) order.
 */
void demoRequestPipeline(){
    cout << "--- Incoming Request Processing Demo (Feature 2.6) ---" << endl;
    RequestPipeline pipeline;
    const int numRequests = 20;
    ServiceRequest requests[numRequests];

    cout << "Enqueuing " << numRequests << " sequential requests as they arrive: " << endl;
    for (int i = 0; i < numRequests; i++){
        RequestPriority priority = (i % 3 == 0) ? EMERGENCY : (i % 3 == 1) ? STANDARD : LOW;
        string description = (i % 2 == 0)
            ? "Navigation query #" + to_string(i + 1)
            : "Service ticket #" + to_string(i + 1);
        requests[i] = ServiceRequest(i + 1, description, priority);
        cout << "   Enqueued: Request #" << requests[i].id << ": " << requests[i].description << endl;
        pipeline.enqueueRequest(&requests[i]);
    }

    cout << endl << "Processing " << pipeline.size() << " requests, strictly in arrival order: " << endl;
    while (!pipeline.isEmpty()){
        ServiceRequest* next = pipeline.dequeueRequest();
        cout << "   Now processing Request #" << next -> id << ": " << next -> description << endl;
    }
    cout << "--- End of Incoming Request Processing Demo ---" << endl;
}

/*
 * PROMISES: Demonstrates feature 2.5 - Fast Building and Resource Lookup.
 * Shows insert/lookup/delete on the real building and room indexes (including a lookup
 * for a key that does not exist), then benchmarks average lookup time against synthetic
 * tables of growing size to show lookup performance stays roughly constant regardless
 * of how many records are stored.
 */
void demoFastLookup(Campus* campus){
    cout << "--- Fast Building and Resource Lookup Demo (Feature 2.5) ---" << endl;

    cout << "Building index currently holds " << campus -> buildingIndex.size() << " entries." << endl;
    string existingBuildingId = campus -> campusBuildings[0] -> get_building_id();
    Building* foundBuilding = campus -> findBuilding(existingBuildingId);
    cout << "Lookup '" << existingBuildingId << "': "
    << (foundBuilding != nullptr ? "FOUND -> " + foundBuilding -> get_building_id() : "NOT FOUND") << endl;

    string missingBuildingId = "ZZZ-404";
    Building* missingBuilding = campus -> findBuilding(missingBuildingId);
    cout << "Lookup '" << missingBuildingId << "' (a key that does not exist): "
    << (missingBuilding != nullptr ? "FOUND" : "NOT FOUND, as expected") << endl;

    Building* demoBuilding = new Building("DEMO-BLD");
    campus -> indexBuilding(demoBuilding);
    cout << "Inserted new building 'DEMO-BLD'. Lookup now returns: "
    << (campus -> findBuilding("DEMO-BLD") != nullptr ? "FOUND" : "NOT FOUND") << endl;
    campus -> removeBuildingIndex("DEMO-BLD");
    cout << "Deleted 'DEMO-BLD' from the index. Lookup now returns: "
    << (campus -> findBuilding("DEMO-BLD") != nullptr ? "FOUND" : "NOT FOUND, as expected") << endl;
    delete demoBuilding; // not linked into the graph, safe to free directly

    cout << endl << "Room index currently holds " << campus -> roomIndex.size() << " entries." << endl;
    string existingRoomId = "";
    for (int i = 0; i < (int) campus -> campusBuildings.size() && existingRoomId.empty(); i++){
        if (!campus -> campusBuildings[i] -> rooms.empty()) {
            existingRoomId = campus -> campusBuildings[i] -> rooms[0].get_room_id();
        }
    }
    if (!existingRoomId.empty()){
        Room* foundRoom = campus -> findRoom(existingRoomId);
        cout << "Lookup room '" << existingRoomId << "': "
        << (foundRoom != nullptr ? "FOUND -> " + foundRoom -> get_room_id() : "NOT FOUND") << endl;
    }
    string missingRoomId = "ZZZ-000";
    Room* missingRoom = campus -> findRoom(missingRoomId);
    cout << "Lookup room '" << missingRoomId << "' (a key that does not exist): "
    << (missingRoom != nullptr ? "FOUND" : "NOT FOUND, as expected") << endl;

    cout << endl << "Benchmarking average lookup time as table size grows (synthetic data): " << endl;
    int sizesToTest[] = {1000, 10000, 100000};
    for (int s = 0; s < 3; s++){
        int n = sizesToTest[s];
        HashTable<int> syntheticTable;
        vector<int> values(n);
        vector<string> keys;
        keys.reserve(n);
        for (int i = 0; i < n; i++){
            values[i] = i;
            string key = "key" + to_string(i);
            syntheticTable.insert(key, &values[i]);
            keys.push_back(key);
        }
        const int lookupsToPerform = 20000;
        auto startTime = chrono::high_resolution_clock::now();
        for (int i = 0; i < lookupsToPerform; i++){
            syntheticTable.lookup(keys[rand() % n]);
        }
        auto endTime = chrono::high_resolution_clock::now();
        double avgNanoseconds = chrono::duration<double, nano>(endTime - startTime).count() / lookupsToPerform;
        cout << "   n = " << n << " records -> average lookup time: " << avgNanoseconds
        << " ns (load factor " << syntheticTable.loadFactor() << ")" << endl;
    }
    cout << "--- End of Fast Building and Resource Lookup Demo ---" << endl;
}
