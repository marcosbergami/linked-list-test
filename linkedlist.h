/*********************
Name: Marcos Bergami
COSC 2436-004
Purpose: This program is a stack implementation.
In this program, I will be implementing a stack object that will work with a struct data type called Data. The struct data type contains an int called id and a string called information.
**********************/

#ifndef CLASSES_LINKEDLIST_H_
#define CLASSES_LINKEDLIST_H_

#include "data.h"
#include <iostream>

class LinkedList {

    public:

    LinkedList();
    ~LinkedList();

    bool addNode(int, string*);
    bool deleteNode(int);
    bool getNode(int, Data*);

    void printList(bool = false);
    int getCount();
    bool clearList();
    bool exists(int);

    private:
        
    Node *head;
    
    // Adding additional methods in order to make addNode() more readable and modular
    Node* createNode(int, string*);
    void insertNode(Node*, Node*, Node*);

};

#endif /* CLASSES_LINKEDLIST_H_ */
