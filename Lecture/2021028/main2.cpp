#include <iostream>
using namespace std;

class Pet {
public:
    void eat() {
        cout << "Pet is eating." << endl;
    }
};

class Cat : public Pet {  // Cat is a subclass of Pet (Cat is derived from Pet)
public:
    void eat() {
        Pet::eat();
        cout << "Cat is eating." << endl;
    }

    void purr() {
        cout << "The cat is purring...." << endl;
    }
};

int main() {
    Pet peeve;
    peeve.eat();  // Calls peeve's implementation of eat
    cout << endl;

    Cat felix;
    felix.eat();   // Calls felix's implementation of eat
    felix.purr();  // Calls felix's implementation of purr
}
