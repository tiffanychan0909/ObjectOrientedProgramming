/*
  Vector Class
  Demonstrates:
     Good example of copy control
     Dynamic arrays and pointer arithmetic
     Square bracket operator
     Implementation of an important data structure
 */


#include <iostream>

using namespace std;

class Vector {
public:
    Vector() {
        size = 0;
        capacity = 8;
        data = new int[capacity];  // [0, 1, 2, 3, 4, ...., 7]
    }

    // Constructor with initial values
    Vector(size_t capacity, int value) {
        size = capacity;
        this->capacity = capacity;
        data = new int[capacity];
        for (size_t index = 0; index < capacity; index++) {
            data[index] = value;
        }
    }

private:
    size_t size;
    size_t capacity;
    int* data; // no array notation here!  points to data[0]  &data[1] = &data[0] + sizeof(int)
};

int main() {
    Vector v;
    Vector v2(15, 23);
    
    return 0;
}
