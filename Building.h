#include <iostream>
#include <string>
using namespace std;

class Building {
private:
    string building_id;
public:
    Building();
    string get_building_id();
    void print_information();
};