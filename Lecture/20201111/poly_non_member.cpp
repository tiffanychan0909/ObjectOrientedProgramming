#include <iostream>

using namespace std;

class Base {
public:
    virtual void display(ostream& os) const {
        os << "Base";
    }
};

ostream& operator<<(ostream& os, const Base& rhs) {
    rhs.display(os);
    return os;
}

class Derived : public Base {
public:
    void display(ostream& os) const override {
        os << "Derived";
    }
};

void func(const Base& base) {
    cout << base << endl;
}

int main() {
    Base base;
    cout << base << endl;  // Calls operator<< and runs Base::display
    cout << endl;

    Derived der;
    cout << der << endl;  // Calls operator<< and ...
    cout << endl;

    func(base);
    func(der);
}
