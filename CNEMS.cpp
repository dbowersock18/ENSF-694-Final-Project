#include <iostream> 
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
#include "Room.h"
#include "Building.h"
#include "Campus.h"
#include "Graph.h"

// TODO LIST: 
// IMPLEMENT A CHECK TO ENSURE THE USER IS ENTERING A VALID NUMBER
// Output the current Queue of historical searches
// Consider moving the class Priority Que from  building to Graph (logistical placement)

void interactWithUser(Campus*, Graph*); // Method that serves as the Client Interface (instad of another class)
void cliBookingManagement(Campus*); // Client Interface for mananaging the users wishes relative to the booking software
int obtainUserInput(); // Obtains a numerical user input
void importBookings(Campus*, const string &); // Method to obtain a list of bookings from a text file
void importRoomInformation(Campus*, const string&); // Method ot obtain Room information from a text file

int main(void) {

    // TEST BLOCK ROOM
    // file housing campus data. MUST BE LOADED FIRST! Contains building objects
    const string campusMap= "CampusMap.txt";
    // create objects
    Campus campus;
    Graph graph(&campus);
    // run program and display information
    cout << endl;
    graph.read_input_file(campusMap);
    cout << endl;
    const string roomInformation = "roomInformation.txt";
    importRoomInformation(&campus, roomInformation);
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
        << "    3: to manage bookings" << endl;
        int returnValue = obtainUserInput();
        endProgram = returnValue;
        if (returnValue == 0) return;
        if (returnValue == 1) {
            campus -> print_information_campus();
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
    string building, room;
    int year, month, day;
    double hour, duration;
    // populates each room object with the relevant booking information
    while (infile >> building >> room >> year >> month >> day >> hour >> duration) {
        // find building in list of buildings
        for (int i = 0; i < (int) campus->campusBuildings.size(); i++){
            if(campus -> campusBuildings[i] -> get_building_id() == building){
                for (int j = 0; j < (int) campus -> campusBuildings[i]->rooms.size(); j++){
                    if(campus -> campusBuildings[i]->rooms[j].get_room_id() == room){
                        campus -> campusBuildings[i]->rooms[j].addBooking(year, month, day, hour, duration);
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
        cout << "   1: View room bookings" << endl;
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
    }
    cout << endl;
    return;
}
