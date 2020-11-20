#include <iostream>
using namespace std;

class Person {

public:
    Person(const string& name, int age) {
        this->name = name;
        this->age = new int(age);
    } // Takes an integer, but makes a new pointer 

    friend ostream& operator<<(ostream& os, const Person& person) {
        os << "name: " << person.name << " age: " << *person.age;
        return os;
    }

    Person& operator=(const Person& rhs) {  // p3 = p1 --> this = p3,  rhs = p1  --> p3.operator=(p1)
        // Check for self assignment
        // Free up the old data
        // Allocate new heap data location and then copy data
        // Return yourself
        if (this != &rhs) {
            delete age;
            age = new int(*rhs.age);
            name = rhs.name;
        }
        return *this;
    }

    void setAge(int* age) {
        this->age = age;  // memory leak!  must delete age first, then assign to param age
    }

    void incrementAge() {
        *this->age = *this->age + 1;
    }

private:
    string name;
    int* age;
};


int main() {
    Person p1("Alvin Kamara", 25);
    Person p2("Tom Brady", 100);
    cout << p1 << endl;

    Person p3 = p1;  // initializing p3 -> copy constructor
    p3 = p2;  // requires the assignment operator

    p3.setAge(new int(50));
    cout << p3 << endl;
    p3.incrementAge();
    cout << p3 << endl;
    return 0;
}
