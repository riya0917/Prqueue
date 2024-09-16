/// @file prqueue.h
/// @Riya Patel 
/// Building priority queue using binary search tree to perfrom varaious task in order to manage priority
/// Incorporating many functions like enqueue, dequeue, begin, next to ensure priority queue is well managed
/// @date October 20, 2023
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class prqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;       // stored data for the p-queue
        bool dup;      // marked true when there are duplicate priorities
         NODE* parent;  // links back to parent
        NODE* link;    // links to linked list of NODES with duplicate priorities
        NODE* left;    // links to left child
        NODE* right;   // links to right child
    };
    NODE* root; // pointer to root node of the BST
    int sz;     // # of elements in the prqueue
    NODE* curr; // pointer to next item in prqueue (see begin and next)
    
public:
    //Default constructor, sets everything to 0 or null
    prqueue() {
        root = nullptr;
        sz = 0;
        curr = nullptr;    
    }
    
    //This function recursively makes a copy of the tree
    void copyTree(NODE* &final, NODE* currentParent, const NODE* source){
        if(source != nullptr){
            NODE* newNode = new NODE;
            newNode->value = source->value;
            newNode->priority = source->priority;
            newNode->dup = source->dup;
            newNode->left = newNode->right = newNode->link = nullptr;

            //Assign the new node to the final or set it as a link of the currentParent
            if(currentParent != nullptr){
                currentParent->link = newNode;
            }else{
                final = newNode;
            }

            //Recursively copies the right, left, and link nodes
            copyTree(newNode->right, nullptr, source->right);
            copyTree(newNode->left, nullptr, source->left);
            copyTree(newNode->link, currentParent, source->link);
        }
    }

    //Overloaded assignment operator for the prqueue class
    //The parameters include the prqueue object to be copied from
    //Returns the modified object after the assignment
    prqueue& operator=(const prqueue& other) {
        //if it is a self assignment, return the current object
        if(this == &other){
            return *this;
        }
        //clear the current priority queue to perform a deep copy
        clear();

        //Perform a deep copy of the other queue's tree structure and set the size
        copyTree(root, nullptr, other.root);
        sz = other.sz;
        return *this;
    }
    
    //This function recursively clears the tree
    void clearRecursively(NODE* node){
        //Recursively clears the prqueue nodes and their linked list links
        if(node != nullptr){
            clearRecursively(node->left);
            clearRecursively(node->right);
            NODE* curr = node;
            while(curr){
                NODE* next = curr->link;
                delete curr;
                curr = next;
            }
        }
    }

    //This function clears the entire prqueue using the clearRecursively function
    void clear() {
        clearRecursively(root);
        //sets sz and root to 0 and nullptr 
        sz = 0;
        root = nullptr;
    }
    //This is the destructor, it frees the memory associated with the priority queue
    ~prqueue() {
        clear(); 
    }

    //This function is intended to create  a new node and add it to the priority queue tree
    //The parameters include a value of the node being inserted of any data type, and an integer value of the priority 
    void enqueue(T value, int priority) {

        //create a new node for the provided value and priority
        NODE* newNode = new NODE();
        newNode->priority = priority;
        newNode->value = value;
        newNode->dup = false;

        //initialize pointers for traversale within the data structure
        NODE* prev = nullptr;
        NODE* curr = root;

        //traverse the data structure to find the position for the new node depending on priority
        while(curr != nullptr){
            //if the priority matches the current nodes priority, indicate a duplicase is found
            if(priority == curr->priority){
                //mark the new node as a dup and attach it at the end of the linked list
                newNode->dup = true;
                while(curr->link){
                    curr = curr->link;
                }
                curr->link = newNode;
                newNode->parent = curr;

                newNode->link = nullptr;
                newNode->left = nullptr;
                newNode->right = nullptr;
                sz++;
                return;
            }

            //adjust the traversal pointers based on the priority comparison
            if(priority < curr->priority){
                prev = curr;
                curr = curr->left;
            }else{
                prev = curr;
                curr = curr->right;
            }
        }

        //insert the new node in the correct position considering priority
        if(prev == nullptr){
            //if the structure is epty, make the new node the root
            root = newNode;
        }else if(priority < prev->priority){
            //if the new node has a lower priority, place it to the left
            prev->left = newNode;
        }else{
            //if the new node has a higher priority, place it to the right
            prev->right = newNode;
        }

        //set node pointers and increment the size of the structures
        newNode->parent = prev;
        newNode->left = nullptr;
        newNode->right = nullptr;
        sz++;
    }


    //This function removes the element with the highest priority (leftmost node) from the priority queue
    //Returns the value of the removed element
    T dequeue() {
        //checks if the priority queue is empty
        if(root == nullptr){
            throw out_of_range("The priority queue is empty.");
        }

        NODE* toRemove = root;
        NODE* parent = nullptr;

        //find the leftmost node, which has the minimum priority
        while(toRemove->left != nullptr){
            parent = toRemove;
            toRemove = toRemove->left;
        }

        //store the value of the element with the highest priority
        T valueOut = toRemove->value;

        //checks if the left node has linked nodes (nodes with the same priority)
        if(toRemove->link != nullptr){
            NODE* temp = toRemove->link;

            //updates the leftmost node with data from the linked node
            toRemove->value = temp->value;
            toRemove->priority = temp->priority;
            toRemove->link = temp->link;
            delete temp;
        }else{
            //if there is no linked node
            if(parent == nullptr){
                root = toRemove->right;
            }else{
                //updates the parents left pointer if there is no linked node
                parent->left = toRemove->right;
            }
            delete toRemove;
        }
        sz--;
        return valueOut;
    }

    //This function is intended to return the number of elements in the prioriry queue
    //Returns the size of the queue
    int size() {
        return sz;  
    }
    
    //This function is intended to set curr to the minimum value
    void begin() {     
        //set curr to the node with the minimum value
        if(root != nullptr){
            curr = findMin(root);
        }
    }

    //This function is intended to retrieve the next element with its priority
    //Parameters include a reference to the value and a reference to the priority queue
    //returns whether the next element was found or not
    bool next(T& value, int &priority){
    
        //checks if the priority queue is empty
        if(curr == nullptr){
            return false;
        }

        //assigns the value and priority of the current node
        value = curr->value;
        priority = curr->priority;

        //if the current node has a link, or connected to another node, return true
        if(curr->link){
            curr = curr->link;
            return true;
        }
        
        //traverse back through dup nodes if available
        while(curr->dup){
            curr = curr->parent;
        }

        //move to the right node and then traverse to the leftmost node to find the next element
        if(curr->right){
            curr = curr->right;
            while(curr->left){
                curr = curr->left;
            }
            return true;
        }
        
        //traverse back through parent nodes checking for elements with higher priority
        while(curr->parent){
            curr = curr->parent;
            //if a higher priority element is found, return true
            if(curr->priority > priority){
                return true;
            }
        }
        //if no higher priority element is found, set curr to null and return false
        curr = nullptr;
        return false;
    }

    //This function is intended to build the string representation of the priority queue
    void buildStringRecursively(NODE* node, stringstream& output){
        //checks if the node is empty
        if(node == nullptr){
            return;
        }

        //if the node has a left child, recursively call the function on the left subtree
        if(node->left != nullptr){
            buildStringRecursively(node->left, output);
        }
        
        //append the current node's priority and value to the stringstream output
        output << node->priority << " value: " << node->value << "\n";
        NODE* linkedNode = node->link;

        //checks if there are linked nodes with the same priority, traverses through them and append to the output
        while(linkedNode != nullptr){
            output << linkedNode->priority << " value: " << linkedNode->value << "\n";
            linkedNode = linkedNode->link;
        }

        //if the node has a right child, recursively call the function on the right subtree
        if(node->right != nullptr){
            buildStringRecursively(node->right, output);
        }
    }

    //This function is intended to generate the string representation of the priority queue
    //Returns the stringstream converted to a string
    string toString(){
        //initialize a stringstream to store the output
        stringstream ss;
        buildStringRecursively(root, ss);
        return ss.str();
    }
    
    
    //This function is intended to find the minimum priority node in the tree
    //The parameter includes the node to traverse
    //Returns the leftmost node with the minimum priority
    NODE* findMin(NODE* node){
        //traverse to the leftmost node
        while(node->left != nullptr){
            node = node->left;
        }
        return node;
    }
    
    //This function is intended to view the value of the minimum-priority element in the priority queue
    //Returns the value of the minimum-priority node
    T peek() {
        //checks if the queue is empty
        if(root == nullptr){
            throw out_of_range("The priority queue is empty.");
        }

        //finds the minimum priority node
        NODE* min = findMin(root);
        return min->value;
    }
   
    //This function recursively checks if two nodes are equal in terms of values, priorities, and tree structure
    bool isEqual(NODE* first, NODE* second) const{
        //if they are null, they are equal
        if(first == nullptr && second == nullptr){
            return true;
        }

        //if only one is null, they are not equal
        if(first == nullptr || second == nullptr){
            return false;
        }

        //check if the values, priorities, and child nodes are equal for both nodes
        //recursively checks linked nodes, left child nodes and right child nodes 
        return (first->value == second->value) && 
               (first->priority == second->priority) &&
               isEqual(first->link, second->link) &&
               isEqual(first->left, second->left) &&
               isEqual(first->right, second->right);
    }

    //this function is overload the equality operator to compare two priority queues
    //The parameters include a reference to another priority queue to compare 
    //Returns if there are equal or not
    bool operator==(const prqueue& other) const {
        //if it is a self assignment, it is equal
        if(this == &other){
            return true;
        }
        //check equality based on size and tree structure recursively
        return sz == other.sz && isEqual(root, other.root);
    }

    void* getRoot() {
        return root;
    }
};