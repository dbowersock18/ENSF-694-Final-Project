#include "AVL.h"

//Adapted from our answers for Assignment 5

AVLTree::AVLTree() : root(nullptr) /*cursor(nullptr)*/ {}

int AVLTree::height(const Node* N) {
	//If N is not a nullptr, returns height. Otherwise, returns 0.
	if (N == nullptr){
		return 0;
	}
	else {
		return N->height;
	}
}

int AVLTree::getBalance(Node* N) {
    //If N is not a nullptr, returns the difference between its right and left sub-trees. Otherwise returns 0.
    if (N == nullptr){
		return 0;
	}
	else {
		return height(N->right) - height(N->left);
	}
}

Node* AVLTree::rightRotate(Node* y) {
    //Right - rotates the specified node and returns the new root.
	Node *x = y->left;
	Node *z = x->right;
	
	x->right = y;
	y->left = z;
	
	//Update height
	y->height = (1 + std::max(height(y->left), height(y->right)));
	x->height = (1 + std::max(height(x->left), height(x->right)));

	return x;
 }

 Node* AVLTree::leftRotate(Node* x) {
    //Left - rotates the specified node and returns the new root.
	 
	Node *y = x->right;
	Node *z = y->left;
	
	y->left = x;
	x->right = z;
	 
	//Update height
	y->height = (1 + std::max(height(y->left), height(y->right)));
	x->height = (1 + std::max(height(x->left), height(x->right)));
    
	return y;
 }

void AVLTree::insert(long time, long endTime, std::string purpose) {
    root = insert(root, time, endTime, purpose);
}

// Recursive function
 Node* AVLTree::insert(Node* node, long time, long endTime, std::string purpose) {
    //Inserts the given value into the tree and rebalances if needed.

	//If we reach the end (the node is nullptr), construct a new node and return it.
	if (node == nullptr) 
        return new Node(time, endTime, purpose); 

	//If the start time is less than the current node, recursively call insert to the left.
    if (time < node->data.time) {
        //For each time it moves left, it will check if the new event starts or ends during the existing event, and end the recursion with a message if it does.
        if (endTime > node->data.time) {
            std::cout << "Time conflict: new event ends after an existing event starts." << std::endl;
            std::cout << "Conflicting event: " << node->data.purpose << " at " << node->data.time << " to " << node->data.endTime << std::endl;
            return node;
        }
        if (time < node->data.endTime){
            std::cout << "Time conflict: new event starts before an existing event ends." << std::endl;
            std::cout << "Conflicting event: " << node->data.purpose << " at " << node->data.time << " to " << node->data.endTime << std::endl;
            return node;
        }
        node->left = insert(node->left, time, endTime, purpose);
    }
	
	//If the start time is greater than the current node, recursively call insert to the right.
    else if (time > node->data.time) {
        if (time < node->data.endTime){
            std::cout << "Time conflict: new event starts before an existing event ends." << std::endl;
            std::cout << "Conflicting event: " << node->data.purpose << " at " << node->data.time << " to " << node->data.endTime << std::endl;
            //TODO; convert that time (internal function time, a single long) to human readable time. Perhaps create a function in booking.h/cpp?
            return node;
        }
        node->right = insert(node->right, time, endTime, purpose); 
    }
	
	//If the start time equals the current node's start time, return the existing node (no booking two events on the same start time)
    else if (time == node->data.time){
		return node;
	}
	 
	//After the recursion, we will have a new node in the tree. Then check for balance,
	//update the height, and rotate as needed.
	node->height = (1 + std::max(height(node->left), height(node->right)));
	
	//Check balance
	int balance = getBalance(node);

	//If the balance is greater than +- 1, rotate appropriately.
	//Note: getBalance() returns height(right) - height(left), so a
	//positive balance means right-heavy (needs a left rotation) and a
	//negative balance means left-heavy (needs a right rotation).

	if (balance < -1 && time < node->left->data.time) {
		return rightRotate(node);
	}

	else if (balance < -1 && time > node->left->data.time) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    else if (balance > 1 && time > node->right->data.time) {
        return leftRotate(node);
	}

    else if (balance > 1 && time < node->right->data.time) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

	//If the balance is okay, just return the node as is.
    else {
		return node;
	}
 }

// Recursive function
void AVLTree::inorder(const Node* root) {
	//Base case: an empty (sub)tree has nothing to print.
	if (root == nullptr){
		return;
	}

	//Visit left subtree, then this node, then right subtree.
	inorder(root->left);
	//Add a cout printout for the booking data, with time conversion, right here.

	inorder(root->right);
}


void AVLTree::find(long time) {
    select_root();
    if(root != nullptr)
        find(root, time);
    else
        std::cout << "There are no bookings at all. Why not create one?" << std::endl;
}

// Recursive funtion
void AVLTree::find(Node* root, long time){
	//Check if we've reached the end of the tree (exit without changing cursor when not found)
	if (root == nullptr){
		return;
	}
	
	//Check if the key is on the current node
	if (time == root->data.time){
		cursor = root;
		return;
	}
	
	//Check if it should go down the left or right branches then continue recursion
	if (time < root->data.time){
		find(root->left, time);
	}
	else {
		find(root->right, time);
	}
  
}

void AVLTree::select_root(){
    if(root != nullptr) {
        cursor = root;
        return;
    }
    cursor = nullptr;
}

