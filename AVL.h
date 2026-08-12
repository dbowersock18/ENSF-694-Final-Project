#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <string>
#include "booking.h"

//Based on the structures from Assignment 5

struct Info{
    long time;
    long endTime;
};

struct Node {
    Info data;
    Booking booking;
    Node* left;
    Node* right;
    Node* parent;
    int height;

    Node(long time, long endTime, Booking booking, Node* p = nullptr) : data{time, endTime}, booking(booking), 
                                                                                    left(nullptr), right(nullptr), parent(p), height(1) {}
};

class AVLTree {
private:
    Node* root;
    Node* cursor;
    int getBalance(Node* N);
    //Returns the right height minus the left height for the given node

    Node* rightRotate(Node* y);
    //Makes a right rotation on the node "y"
    
    Node* leftRotate(Node* x);
    //Makes a left rotation on the node "x"
    
    Node* insert(Node* node, long time, long endTime, Booking booking, Node* parent);
    //Adds a new node to the tree, checking if it has time conflicts. If a conflict is detected it will fail to add a new node and print a message to the console.
    
    void find(Node* root, long time);
    //Finds a node starting at that exact specified time 

    int size;
    //Contains the size of the tree

    void printAll(Node* node);
    
    
    //void destroy();
    //Completely destroys the AVL tree
    //copy(const AVLTree& source);

    
    //Node* copy(Node* node, Node* parent);
    //void destroy(Node* node);
    
public:
    AVLTree();
    //Uncomment these if things stop working, otherwise delete
    //AVLTree& operator= (const AVLTree& rsh);
    //AVLTree(const AVLTree& src);

    int getSize();
    //Returns the amount of nodes in the tree
    
    void insert(long time, long endTime, Booking booking);
    //Interface for adding nodes to the tree, which will also balance the tree if needed.
    
    int height(const Node* N);
    //If node N exists, returns its height. Otherwise, returns 0.
    
    void printAll();
    //Prints out the entire tree in order of start times, presenting the start times and end times for each booking.
    
    void find(long time);
    //Interface for searching for a booking starting at a certain time.

    void query(long time, long endTime);
    //Interface for searching for all bookings starting between two given times. Can also be used for finding all bookings on a given day.

    void remove(Node* N);
    //Deletes the specified node, rotating and fixing the AVL tree as needed.

    void printNext();
    //Shifts the cursor/selection up to the next node, and then prints it out.
    //TODO: perhaps implemented with the same logic as "inorder", just running it a single time instead of recursively?

    void select_root();
    
 
};

#endif // AVL_H
