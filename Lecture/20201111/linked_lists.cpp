#include <iostream>

using namespace std;

/*
 * listDisplay(Node* headPtr)
 * listInsert / listRemove / listAppend
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
        cout << p->data << " ";
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

void listAddTail(Node* headPtr, int data) {
    // 1. go to the end / find the end of the list
    Node* tail = findTail(headPtr);

    // 2. Create a node for the data
//    Node* p = new Node(data);

    // 3. add that node to the end
//    tail->next = p;

    tail->next = new Node(data);
}

int main() {
    Node* myList = nullptr;
    listAddHead_donotuse(myList, 17);  // listAddHead_donotuse fails to modify the pointer (myList)
    listDisplay(myList);  // displays an empty list!
//    listAddTail(myList, 25);
    cout << listLength(myList) << endl << endl;

    listAddHead(myList, 20);
    listAddHead(myList, 17);   // pass by reference to point allow modification of pointer
    listAddHead(myList, 18);
    listAddTail(myList, 25);
    listDisplay(myList);
    cout << listLength(myList) << endl;
    cout << findTail(myList)->data << endl;
}