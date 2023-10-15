/*********************
Name: Marcos Bergami
COSC 2436-004
Purpose: This program is a doubly linked list implementation
**********************/

#include "linkedlist.h"
#include "data.h"
#include <iostream>

LinkedList::LinkedList() {
    head = NULL;
}

LinkedList::~LinkedList() {
    clearList();
}

bool LinkedList::addNode(int id, string* data) {
    bool result = true;
    Node* newNode = nullptr;
    Node* current = nullptr;

    try {
        if(!isValid(id, data)) {
            result = false;
        } else {
            current = findInsertionPoint(id);
            if(current && current->data.id == id) {
                result = false;
            } else {
                newNode = createNode(id, data);
                if(!newNode) {
                    result = false;
                } else {
                    insertNode(newNode, current);
                }
            }
        }
    } catch(const std::invalid_argument& e) {
        result = false;
    }

    return result;
}

bool LinkedList::isValid(int id, string* data) {
    if(id <= 0) {
        throw std::invalid_argument("id must be a positive number greater than 0");
    }
    if(data->empty()) {
        throw std::invalid_argument("data string must not be empty");
    }

    return true;
}

Node* LinkedList::findInsertionPoint(int id) {
    Node* current = head;
    while(current && current->data.id < id) {
        current = current->next;
    }
    return current;
}

Node* LinkedList::createNode(int id, string* data) {
    Node* newNode = new (std::nothrow) Node;

    if(newNode) {
        newNode->data.id = id;
        newNode->data.data = *data;
    }

    return newNode;
}

void LinkedList::insertNode(Node* newNode, Node* current) {
    if(current == head) {
        newNode->next = head;
        newNode->prev = nullptr;
        if(head) head->prev = newNode;
        head = newNode;
    } else if(current) {
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    } else if(current == nullptr) {
        // Insertion at the end of the list
        Node* temp = head;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
        newNode->next = nullptr;
    }
}

bool LinkedList::deleteNode(int id) {
    bool result = false;
    Node* current = head;

    while(current && current->data.id != id) {
        current = current->next;
    }

    if(current) {
        if(current == head) {
            head = current->next;
            if(head) head->prev = nullptr;
        } else {
            current->prev->next = current->next;
            if(current->next) current->next->prev = current->prev;
        }
        delete current;
        result = true;
    }

    return result;
}

bool LinkedList::getNode(int id, Data* data) {
    bool result = false;
    Node* current = head;

    while(current && current->data.id != id) {
        current = current->next;
    }

    if(current) {
        data->id = current->data.id;
        data->data = current->data.data;
        result = true;
    } else {
        data->id = -1;
        data->data = "";
    }

    return result;
}

void LinkedList::printList(bool reverse) {
    Node* current = head;

    if(reverse) {
        while(current && current->next) {
            current = current->next;
        }
        while(current) {
            std::cout << current->data.id << ": " << current->data.data << std::endl;
            current = current->prev;
        }
    } else {
        while(current) {
            std::cout << current->data.id << ": " << current->data.data << std::endl;
            current = current->next;
        }
    }
}

int LinkedList::getCount() {
    int count = 0;
    Node* current = head;

    while(current) {
        count++;
        current = current->next;
    }

    return count;
}

bool LinkedList::clearList() {
    bool result = true;
    Node* current = head;
    Node* next = nullptr;

    while(current) {
        next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;

    return result;
}

bool LinkedList::exists(int id) {
    bool result = false;
    Node* current = head;

    while(current && current->data.id != id) {
        current = current->next;
    }

    if(current) {
        result = true;
    }

    return result;
}