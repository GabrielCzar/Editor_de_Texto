#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

struct Node{
    char value;
    Node * next;
    Node * prev;

    Node(char value = ' ', Node * next = nullptr, Node * prev = nullptr){
        this->value = value;
        this->next = next;
        this->prev = prev;
    }

};

#endif // NODE_H
