/*********************
Name: Marcos Bergami
COSC 2436-004
Purpose: This program is a doubly linked list implementation
**********************/

#include "linkedlist.h"

LinkedList::LinkedList() {
    head = NULL;
}

LinkedList::~LinkedList() {
    clearList();
}

bool LinkedList::addNode(int id, string* data) {
    bool result = false;
    if(id > 0 && !data->empty()) {
        Node* current = head;
        Node* prev = nullptr;
        while (current && current->data.id < id && current->data.id != id) {
            prev = current;
            current = current->next;
        }
        if (!current || current->data.id != id) {
            Node* newNode = createNode(id, data);
            insertNode(newNode, prev, current);
            result = true;
        }
    }
    return result;
}

Node* LinkedList::createNode(int id, string* data) {
    Node* newNode = new (std::nothrow) Node;

    if(newNode) {
        newNode->data.id = id;
        newNode->data.data = *data;
    }

    return newNode;
}

void LinkedList::insertNode(Node* newNode, Node* prev, Node* current) {
    newNode->next = current;
    newNode->prev = prev;
    if (prev) {
        prev->next = newNode;
    } else {
        head = newNode;
    }
    if (current) {
        current->prev = newNode;
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