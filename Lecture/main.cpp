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
    friend ostream& operator<<(ostream& os, const Vector& rhs) {
        for (size_t index = 0; index < rhs.the_size; index++) {
            cout << '\t' << rhs.data[index];
        }
        return os;
    }

public:
    Vector() {
        the_size = 0;
        capacity = 8;
        data = new int[capacity];  // [0, 1, 2, 3, 4, ...., 7]
    }

    // Constructor with initial values
    Vector(size_t capacity, int value=0) {
        the_size = capacity;
        this->capacity = capacity;
        data = new int[capacity];
        for (size_t index = 0; index < capacity; index++) {
            data[index] = value;
        }
    }

    // Copy Constructor
    Vector(const Vector& rhs) {
        the_size = rhs.the_size;
        capacity = rhs.capacity;
        data = new int[capacity];
        for (size_t index = 0; index < rhs.the_size; index++) {  // Copy data values from rhs into this
            data[index] = rhs.data[index];
        }
    }

    ~Vector() {
        delete[] data;
    }

    void push_back(int value) {
        if (the_size == capacity) {
            int* oldData = data;
            data = new int[2 * capacity];
            // Copy data from old to new array
            for (size_t index = 0; index < the_size; index++) {
                data[index] = oldData[index];
            }
            delete[] oldData;
            capacity *= 2;
        }
        data[the_size] = value;
        the_size++;
    }

    size_t size() const {
        return the_size;
    }

    void clear() {
        the_size = 0;
    }

    void pop_back() {
        if (the_size != 0) {
            the_size--;
        }
    }

    int operator[](size_t index) const {
        return data[index];
    }

    Vector& operator=(const Vector& rhs) {
        // Check for self-assignment
        if (this != &rhs) {
            // Free up the old data
            delete[] data;

            // Allocate new heap data for 'data' var
            data = new int[rhs.capacity];

            // Copy old data to new data
            the_size = rhs.the_size;
            capacity= rhs.capacity;
            for (size_t index = 0; index < rhs.the_size; index++) {
                data[index] = rhs.data[index];
            }

        }
        // Return self
        return *this;
    }

private:
    size_t the_size;
    size_t capacity;
    int* data; // no array notation here!  points to data[0]  &data[1] = &data[0] + sizeof(int)
};

int main() {
    Vector v;
    v.push_back(100);
    v.push_back(200);
    v.push_back(300);

//    Vector v2(15, 30);
//    Vector v3(v);   // Vector v3 = v
//
//    v3 = v2;

//    cout << "Vector v: " << v << endl;
//    cout << "Vector v2: " << v2 << endl;

//    cout << "Vector v: " << v << endl;
//    cout << v.size() << endl;
//
//    v2.pop_back();
//    cout << v.size() << endl;
//    cout << v2.size() << endl;

    for (size_t index = 0; index < v.size(); index++) {
        cout << v[index] << endl;
    }

    v[0] = -100;

    for (int value : v) {
        cout << value << endl;
    }

    return 0;
}
