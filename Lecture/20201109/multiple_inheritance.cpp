// Multiple inheritance

#include <iostream>
#include <vector>

using namespace std;

class Flier { // Flier is abstract
public:
    virtual void fly() = 0;
};

void Flier::fly() { cout << "I can fly!" << endl; }

class Animal {
public:
    virtual void display() { cout << "I'm an animal!" << endl; }

};

class Bat : public Animal, public Flier {  // Multiple Inheritance
public:
    void fly() override {
        cout << "Bat-->Shhhhhh" << endl;
        Flier::fly();
    }
};

class Insect : public Animal, public Flier {  // Multiple Inheritance
public:
    void fly() override { cout << "Insect-->Bzzzz." << endl; }
};

class Plane : public Flier {  // Single inheritance
public:
    void fly() override { cout << "Plane-->vrooommmm!" << endl; }
};

int main() {
    Bat batman;
    Plane batplane;
    Insect ladybug;

    cout << "Bat:" << endl;
    batman.display();
    batman.fly();

    cout << "==========\n";
    vector<Flier*> vf;
    vf.push_back(&batman);
    vf.push_back(&batplane);
    vf.push_back(&ladybug);
    for (Flier* flier : vf) {
        flier->fly();
    }
}