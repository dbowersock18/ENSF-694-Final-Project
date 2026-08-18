#include "AVL.h"

//Adapted from our answers for Assignment 5
// TODO: Function to delete a reservation
// TODO: Display bookings between two time stamps

AVLTree::AVLTree() : root(nullptr), cursor(nullptr) {}

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

    //Update parents
	x->parent = y->parent;
	y->parent = x;

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

    //Update parents
	y->parent = x->parent;
	x->parent = y;
    
	return y;
 }

void AVLTree::insert(long time, long endTime, Booking booking) {
    root = insert(root, time, endTime, booking, nullptr);
}

// Recursive function
 Node* AVLTree::insert(Node* node, long time, long endTime, Booking booking, Node* parent) {
    //Inserts the given value into the tree and rebalances if needed.

	//If we reach the end (the node is nullptr), construct a new node and return it.
	if (node == nullptr){
        size ++;
        return new Node(time, endTime, booking, parent); 
    }

	//If the start time is less than the current node, recursively call insert to the left.
    if (time < node->data.time) {
        //For each time it moves left, it will check if the new event starts or ends during the existing event, and end the recursion with a message if it does.
        if (endTime > node->data.time) {
            std::cout << "Time conflict: new event ends after an existing event starts." << std::endl;
            std::cout << "Conflicting event: " << std::endl;
            node->booking.displayInformationBooking(0);
            return node;
        }
        if (time < node->data.endTime){
            std::cout << "Time conflict: new event starts before an existing event ends." << std::endl;
            std::cout << "Conflicting event: "  << std::endl;
            node->booking.displayInformationBooking(0);
            return node;
        }
        node->left = insert(node->left, time, endTime, booking, node);
    }
	
	//If the start time is greater than the current node, recursively call insert to the right.
    else if (time > node->data.time) {
        if (time < node->data.endTime){
            std::cout << "Time conflict: new event starts before an existing event ends." << std::endl;
            std::cout << "Conflicting event: " << std::endl;
            node->booking.displayInformationBooking(0);
            return node;
        }
        node->right = insert(node->right, time, endTime, booking, node); 
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

//Public function to access full version of printAll
void AVLTree::printAll(){
    printAll(root);
}


// Recursive function
void AVLTree::printAll(Node* node) {
	//Base case: an empty (sub)tree has nothing to print.
	if (node == nullptr){
		return;
	}

	//Visit left subtree, then this node, then right subtree.
	printAll(node->left);
	
    node->booking.displayInformationBooking(0);

	printAll(node->right);
}


void AVLTree::find(long time) {
    selectRoot();
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

void AVLTree::selectRoot(){
    if(root != nullptr) {
        cursor = root;
        return;
    }
    cursor = nullptr;
}

void AVLTree::printNext(){
    if (cursor == nullptr){
        std::cout << "No more bookings!";
    }
    //If there are nodes to the right of cursor, go to that node and then down to the farthest left node beneath it.
    if (cursor->right != nullptr) {
        cursor = cursor->right;
        while (cursor->left != nullptr){
            cursor = cursor->left;
        }
        cursor->booking.displayInformationBooking(0);
    }
    
    //If there is no node to the right, go to the parent node and keep going up the tree until the cursor is to the left of its parent (meaning it is earlier than the parent)
    if (cursor->right == nullptr){
        while (cursor->parent != nullptr && cursor == cursor->parent->right) {    //If the parent is a nullpointer do not continue
            cursor = cursor->parent;                                              //Set the cursor to select its parent and continue
        }
        cursor = cursor->parent;        //One more cursor = cursor->parent so that the cursor is set to the next value
        if (cursor != nullptr){
            cursor->booking.displayInformationBooking(0);
        }
        if (cursor == nullptr){
            std::cout << "No more bookings!";
        }
    }
}

void AVLTree::query(long time, long endTime) {
    query(root, time, endTime);
}

//TODO: FINISH IMPLEMENTING
void AVLTree::query(Node* node, long time, long endTime){
    if (node == nullptr) return;

    // If left subtree might contain valid nodes, search it
    if (node->data.time >= time)
        query(node->left, time, endTime);

    // Check if THIS node is within the range
    if (node->data.time >= time && node->data.endTime <= endTime) {
        node->booking.displayInformationBooking(0);
    }

    // If right subtree might contain valid nodes, search it
    if (node->data.time <= endTime)
        query(node->right, time, endTime);
}

void AVLTree::printCurrent(){
    if (cursor == nullptr){
        std::cout << "No booking selected!";
    }
    if (cursor != nullptr){
        cursor->booking.displayInformationBooking(0);
    }
}

int AVLTree::getSize(){
    return size;
}

bool AVLTree::selectFirst(){
    if (root == nullptr){
        return 0;
    }
    cursor = root;
    
    while (cursor->left != nullptr){
        cursor = cursor->left;
    }
    return 1;
}

bool AVLTree::isRoot(){
    if (cursor == root){
        return 1;
    }
    return 0;
}

void AVLTree::removeBooking(Booking booking){
    long searchKey = booking.convertTime();

    selectRoot();
    if(root != nullptr)
        root = remove(root, searchKey);
    else
        std::cout << "Cannot delete: there are no bookings at all. Why not create one?" << std::endl;   

}

Node* AVLTree::findNextLargest(Node* node){
    //Assigning a new node so we don't affect the original node during this search
    Node* search = node;

    //Continue finding the smallest until we reach the bottom of the left subtree
    while (search->left != nullptr){
        search = search->left;
    }

    return search;
}


Node* AVLTree::remove(Node* node, long time){
    //Search for the node to remove.
    if (node == nullptr){
        std::cout << "Booking not found!";
        return node;
    }
    if (time < node->data.time){
        node->left = remove(node->left, time);
    }
    else if (time > node->data.time){
        node->right = remove(node->right, time);
    }
    else {
        //If the booking to be deleted has no children, we can simply delete it.
        if (node->left == nullptr && node->right == nullptr){
            delete node;
            return nullptr;
        }
        //If there is a child on the left and not on the right, 
        else if (node->left != nullptr && node->right == nullptr){
            //Assign a new node to hold the one being deleted.
            Node* temp = node;
            //Replace the deleted node with its child.
            node = node->left;
            //Fix the node's parent.
            node->parent = temp->parent;
            //Delete the temp node (the one to be deleted)
            delete temp;
        }
        //If there is a child on the right and not on the left,
        else if (node->left == nullptr && node->right !=nullptr){
            Node* temp = node;
            node = node->right;
            node->parent = temp->parent;
            delete temp;
        }
        //If the node has two children,
        else if (node->left != nullptr && node->right !=nullptr){
            //Find the next-largest node from the one we're deleting
            Node* temp = findNextLargest(node->right);
            //Set the node-to-be-deleted's data as the next largest node (essentially replacing everything but the node's parent and child links)
            node->data = temp->data;
            node->booking = temp->booking;
            //Delete the node whose data we just replaced
            node->right = remove(node->right, temp->data.time);
            
        }
    }
    
    //Recalculate heights for the affected nodes (from here on out, it's a similar procedure to adding a node)
    node->height = (1 + std::max(height(node->left), height(node->right)));

    //Check balance
	int balance = getBalance(node);

	//If the balance is greater than +- 1, rotate appropriately.
	//Note: getBalance() returns height(right) - height(left), so a
	//positive balance means right-heavy (needs a left rotation) and a
	//negative balance means left-heavy (needs a right rotation).

	if (balance < -1 && getBalance(node->left) <= 0) {
		return rightRotate(node);
	}

	else if (balance < -1 && getBalance(node->left) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    else if (balance > 1 && getBalance(node->right) >= 0) {
        return leftRotate(node);
	}

    else if (balance > 1 && getBalance(node->right) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

	//If the balance is okay, just return the node as is.
    else {
		return node;
	}
}