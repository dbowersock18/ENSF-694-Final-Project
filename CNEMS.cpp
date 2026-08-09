#include <iostream> 
using namespace std;
#include "Room.h"
#include "Building.h"
#include "Campus.h"
#include "Graph.h"

// TODO LIST: 
// IMPLEMENT A CHECK TO ENSURE THE USER IS ENTERING A VALID NUMBER

void interactWithUser(Campus*, Graph*); // Client Interface Method
int obtainUserInput(); // Method for interacting with user Input

int main(void) {
    // file housing campus data
    const string fileName= "CampusMap.txt";
    // create objects
    Campus campus;
    Graph graph(&campus);
    // display information for troubleshooting /information
    cout << endl;
    graph.read_input_file(fileName);
    cout << endl;
    // campus.print_information_campus();
    // campus.print_information_buildings();

    interactWithUser(&campus, &graph);

    // dijkstra's algorithm to find shortest path
    // graph.dijkstra("gym"); // Hard coding start. Get user input later.
    // graph.printGraph();
}

int obtainUserInput(){
    cout << "Obtaining user Input: ";
    int userInput;
    cin >> userInput;
    cout << endl;
    //TODO: VALIDATION CHECK TO ENSURE USER IS ENTERING CORRECT NUMBERS
    return userInput;
}

void shortestDistanceCalculator(Campus* campus, Graph* graph){
    int check = 0;
    int startIndex, endIndex;
    while (check == 0){
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
        graph -> setStartEnd( campus -> campusBuildings[startIndex], campus -> campusBuildings[endIndex]);
        graph -> dijkstra();
        // graph -> printGraph();
        cout << "Starting from " << graph -> getStart() -> get_building_id() << " it takes "
        << graph -> getEnd() -> distance << " minutes to get to " << graph -> getEnd() -> get_building_id() << " with a route of: ";
        graph -> printPath( graph -> getEnd());
}

void interactWithUser(Campus* campus, Graph* graph){
    cout << "Entry point of user interaction" << endl;
    cout << "Please press: "  << endl
    << "    0: to terminate program" << endl
    << "    1: to calcuate the distance to a location, given a starting location" << endl; 
    int returnValue = obtainUserInput();
    if (returnValue == 0) return;
    if (returnValue == 1) shortestDistanceCalculator(campus, graph);
    cout << endl;
    int endProgram = 0;
    while (!endProgram){
        cout << endl;
        cout << "Now that the shortest distances have been calculated, the menu options have changed. ";
        cout << "Please press: "  << endl
        << "    0: to terminate program" << endl
        << "    1: reset, and calcuate the distance to a new location, given a new starting location" << endl
        << "    2: walk back to the previous building" << endl
        << "    3: calculate a new end location, given the current end location" << endl;
        int returnValue = obtainUserInput();
        if (returnValue == 0) return;
        if (returnValue == 1) {
            graph -> reset();
            shortestDistanceCalculator(campus, graph);
        }
        cout << endl;
    }
    cout << endl;
    cout << "End point of user interaction" << endl;
}




