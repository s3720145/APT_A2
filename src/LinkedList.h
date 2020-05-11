#ifndef LINKEDLIST
#define LINKEDLIST

#include "Node.h"

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    int size();
    void addBack(Tile::Colour colour);
    Node* dequeue();
    Node* getHeader();
private:
    Node* head;
};

#endif // LINKEDLIST
