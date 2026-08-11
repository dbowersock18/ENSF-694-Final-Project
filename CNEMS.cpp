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
int obtainUserInput(); // Obtains a numerical user input
void importBookings(); // Method to obtain a list of bookings from a text file
void importBuildingInformation(Campus*, const string&); // Method ot obtain building information from a text file

int main(void) {

    // TEST BLOCK ROOM
    // file housing campus data
    const string campusMap= "CampusMap.txt";
    // create objects
    Campus campus;
    Graph graph(&campus);
    // run program and display information
    cout << endl;
    graph.read_input_file(campusMap);
    cout << endl;
    Room room("ict_204", 100, "classroom");
    room.addBooking(2026, 8, 10, 6.5, 30);
    room.addBooking(2026, 8, 11, 7.75, 90);
    room.displayInformationAllBookings();
    const string buildingInformation = "buildingInformation.txt";
    importBuildingInformation(&campus, buildingInformation);
    // END OF TEST BLOCK

//     // THE BELOW CODE IS FUNCTIONAL ... ONLY COMMENTING OUT TO WORK ON SECTION 2.3
//     // file housing campus data
//     const string fileName= "CampusMap.txt";
//     // create objects
//     Campus campus;
//     Graph graph(&campus);
//     // run program and display information
//     cout << endl;
//     graph.read_input_file(fileName);
//     cout << endl;
//     interactWithUser(&campus, &graph);
//     // END OF COMMENT SECTION
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
    cout << "Please press: "  << endl
    << "    0: to terminate program" << endl
    << "    1: to calcuate the distance to a location, given a starting location" << endl; 
    int returnValue = obtainUserInput();
    if (returnValue == 0) return;
    if (returnValue == 1) shortestDistanceCalculator(campus, graph, false);
    cout << endl;
    int endProgram = 0;
    while (!endProgram){
        cout << endl;
        cout << "Now that the shortest distances have been calculated, the menu options have changed. ";
        cout << "Please press: "  << endl
        << "    0: to terminate program" << endl
        << "    1: reset, and calcuate the distance to a new location, given a new starting location" << endl
        << "    2: walk back to the previous building" << endl
        << "    3: reload your last query" << endl;
        int returnValue = obtainUserInput();
        if (returnValue == 0) return;
        if (returnValue == 1) {
            graph -> reset();
            shortestDistanceCalculator(campus, graph, false);
        }
        if (returnValue == 2) walkBack(campus, graph);
        cout << endl;
        if (returnValue == 3) {
            reloadLastQuery(campus, graph);
        }
    }
    cout << endl;
    cout << "End point of user interaction" << endl;
}

void importBuildingInformation(Campus* campus, const string& filename){
    // TODO: POPULATE
    cout<< "Reading input file " << filename << endl;
    // // Validates the file can be accessed
    // ifstream infile(filename);
    // if (!infile) {
    //     cerr << "Could not open file: " << filename << endl;
    //     exit(1);
    // }
    // string a, b;
    // int time;
    // // Interprets and populates the campus object with buildings (a and b) and the weight
    // // of each path (time)
    // while (infile >> a >> b >> time) {
}


