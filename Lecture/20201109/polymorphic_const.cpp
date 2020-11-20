#include <iostream>

using namespace std;

class Base {
public:
    Base() { foo(); } // Calls foo in Base, C++ disables polymorphism inside a constructor

    virtual void foo() const { cout << "Base" << endl; }

    void display() const { this->foo(); }
};

class Derived : public Base {
public:
    Derived(int n) : Base(), x(n) {}  // Calls Base's constructor

    void foo() const override { cout << "Derived: x == " << x << endl; }

private:
    int x;
};

int main() {
    Base base;
    base.display();
    cout << endl;

    Derived der(17);
    der.display();
}

// Note: If we always use polymorphism, even in a constructor, then when 'der' got initialized, and the Derived constructor
// called the Base constructor, then the "this" reference inside the constructor (?) would be pointing to the Derived
// instance, and the foo method that is called would be Derived:foo, but that would be before the field Dervied::x had
// ever been initialized, so that otuput would undefined.