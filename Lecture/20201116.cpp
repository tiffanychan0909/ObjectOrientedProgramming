#include <iostream>

using namespace std;

/*
 * listDisplay(Node* headPtr)
 * listAddHead /
 * listRemove / listAppend
 * listLength
 * listClear
 * listDuplicate
 * findTail(Node* headPtr)
 * listAddTail(Node* headPtr, int data)
 */

struct Node {  // Singly linked list, stores int
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}

    int data;
    Node* next;
};

void listAddHead_donotuse(Node* headPtr, int data) { // Pass a pointer to a Node and provide an int
    // 1. create a node for the data
//    Node* p = new Node();

    // 1b. set the data field
//    p->data = data;

    // 2. Make the new node point to the old head node
//    p->next = headPtr;

    // 3. set the head pointer to point to this new node
    Node* p = new Node(data, headPtr);
    headPtr = p;
}

void listAddHead(Node*& headPtr, int data) {  // Pass a reference to a pointer and provide an int
    headPtr = new Node(data, headPtr);
}

void listDisplay(const Node* headPtr) {
    cout << "[";
    for (const Node* p = headPtr; p != nullptr; p = p->next) {
        cout << p->data;
        if (p->next != nullptr)
            cout << " ";
    }
    cout << "]" << endl;
}

size_t listLength(Node* headPtr) {
    Node* p = headPtr;
    size_t counter = 0;
    while (p != nullptr) {
        counter++;
        p = p->next;
    }
    return counter;
}

Node* findTail(Node* headPtr) {
    if (headPtr == nullptr) return nullptr;
    Node* p = headPtr;
    while (p->next != nullptr) {
        p = p->next;
    }
    return p;
}

void listAddTail(Node*& headPtr, int data) {
    // 1. go to the end / find the end of the list
    Node* tail = findTail(headPtr);

    // 2. Create a node for the data
//    Node* p = new Node(data);

    // 3. add that node to the end
//    tail->next = p;

    if (tail != nullptr) {
        tail->next = new Node(data);
    } else {
        headPtr = new Node(data);
    }
}

void listRemoveHead(Node*& headPtr) {
    Node* toRemove = headPtr;
    headPtr = headPtr->next;
    delete toRemove;
}

void listRemoveTail(Node*& headPtr) {
    if (headPtr != nullptr) {
        if (headPtr->next == nullptr) { // handles 1 node list
            delete headPtr;
            headPtr = nullptr;
        } else {    // handles > 1 node in list
            Node* p = headPtr;
            while (p->next->next != nullptr) {
                p = p->next;
            }
            delete p->next;
            p->next = nullptr;
        }
    }
}

void listRemove(Node* prior) {  // TODO Write a better version that does not need a node (getNode(indexNum))
    Node* victim = prior->next;
    prior->next = victim->next;
    delete victim;
}


void listClear(Node*& headPtr) {
    while (headPtr != nullptr) {
        listRemoveHead(headPtr);
    }
}


Node* listDuplicate(Node* headPtr) {
    Node* newList = nullptr;
    Node* p = headPtr;
    while (p != nullptr) {
        listAddTail(newList, p->data);
        p = p->next;
    }
    return newList;
}

void populateList(Node*& myList) {
    listAddHead(myList, 20);
    listAddHead(myList, 17);   // pass by reference to point allow modification of pointer
    listAddHead(myList, 18);   // is the head (18, 17, 20, 25)
    listAddTail(myList, 25);
    listDisplay(myList);
}


int main() {
    Node* myList = nullptr;
    listDisplay(myList);  // displays an empty list!

    populateList(myList);
    listClear(myList);
    listDisplay(myList);

//    populateList(myList);
    listRemoveTail(myList);
    listDisplay(myList);

    // TODO Fix the remove
//    populateList(myList);
//    listRemove(new Node(20));

    cout << "---" << endl;
    populateList(myList);
    Node* newList = listDuplicate(myList);
    listDisplay(myList);
    listDisplay(newList);
}