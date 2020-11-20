#include <iostream>

using namespace std;

class Base {
public:
    void whereAmI() const { cout << "Base" << endl; }
};

class Derived : public Base {
public:
//    void whereAmI() const override { cout << "Derived" << endl; }
    void whereAmI() const;
};

void do_base(Base& thing) {
    thing.whereAmI();
}

int main() {
    Base b_base;
    Derived a_derived;

    do_base(b_base);
    do_base(a_derived);

}
void Derived::whereAmI() const { cout << "Derived" << endl; }

// override specifier ensures that the function is virtual and is overriding a virtual function from a base class