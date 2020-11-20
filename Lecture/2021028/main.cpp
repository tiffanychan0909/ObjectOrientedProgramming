#include <iostream>
using namespace std;

class Pet {
public:
    void eat() {
        cout << "Pet is eating." << endl;
    }
};

class Cat : public Pet {
public:

};

int main() {
    Pet peeve;
    peeve.eat();

    Cat felix;
    felix.eat();  // code reuse - use code from Pet, no need write
}
