#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <string>

//Based on the structures from Assignment 5

struct Info{
    long time;
    long endTime;
    std::string purpose;    //Holds the purpose of this booking, IE lecture, study, and event.
};

struct Node {
    Info data;
    Node* left;
    Node* right;
    //Node* parent;
    int height;

    Node(long a, long b, std::string c, Node* p = nullptr) : data{a, b, c}, left(nullptr), right(nullptr), height(1) {}
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
    Node* insert(Node* node, long time, long endTime, std::string purpose);
    //Adds a new node to the tree, checking if it has time conflicts. If a conflict is detected it will fail to add a new node and print a message to the console.
    void find(Node* root, long time);
    //Finds a node starting at that exact specified time 
    //void destroy();
    //Completely destroys the AVL tree
    //copy(const AVLTree& source);

    
    //Node* copy(Node* node, Node* parent);
    //void destroy(Node* node);
    
public:
    AVLTree();
    ~AVLTree();
    AVLTree& operator= (const AVLTree& rsh);
    AVLTree(const AVLTree& src);

    int size() const;
    //Returns the amount of nodes in the tree
    
    void insert(long time, long endTime, std::string purpose);
    //Interface for adding nodes to the tree, which will also balance the tree if needed.
    
    int height(const Node* N);
    //If node N exists, returns its height. Otherwise, returns 0.
    
    void inorder(const Node* root);
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
