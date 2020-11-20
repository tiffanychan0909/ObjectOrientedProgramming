// Copy Control with Inheritance
#include <iostream>

using namespace std;

class Base {
public:
    Base() {
        cout << "Base()\n";
    }

    Base(const Base& rhs) {
        cout << "Base(const Base&)\n";
    }

    virtual ~Base() {
        cout << "~Base()\n";
    }

    Base& operator=(const Base& rhs) {
        cout << "Base::operator=(const Base&)\n";
        return *this;
    }
};

class Member {
public:
    Member() {
        cout << "Member()\n";
    }

    Member(const Member& rhs) {
        cout << "Member(const Member&)\n";
    }

    Member& operator=(const Member& rhs) {
        cout << "Member::operator=(const Member&)\n";
        return *this;
    }

    ~Member() {
        cout << "~Member()\n";
    }
};

class Derived : public Base {
public:
    //Derived() { cout << "Derived()\n"; }
    Derived() : Base(), mem() { cout << "Derived()\n"; }

    ~Derived() {
        cout << "~Derived()\n";
    }

    Derived(const Derived& rhs) : Base(rhs), mem(rhs.mem) {
        cout << "Derived(const Derived&)\n";
    }

    Derived& operator=(const Derived& rhs) {

        // *this Base::= rhs; // Not valid C++
        // *this Base::operator= rhs; // Not valid C++
        // *this.Base::operator=(rhs); // Not valid C++
        // (*this).Base::operator=(rhs); //  valid C++
        // this->Base::operator=(rhs); //  valid C++
        Base::operator=(rhs); //  valid C++

        mem = rhs.mem;

        cout << "Derived::operator=(const Derived&)\n";
        return *this;
    }

private:
    Member mem;
};

int main() {
    cout << "Derived der;\n------------\n";
    Derived der;
    cout << "===\n";

   cout << "Derived der2(der);\n------------------\n";
   // copy constructor
   Derived der2(der);
   cout << "===\n";

   cout << "Derived der3 = der;\n-------------------\n";
   // copy constructor
   Derived der3 = der;
   cout << "===\n";

   cout << "der = der2;\n-----------\n";
   // = assignment
   der = der2;
   cout << "===\n";

   cout << "Derived* p = new Derived();\n"
        << "delete p;\n"
        << "---------------------------\n";

   Derived* p = new Derived();
   cout << "===\n";

   cout << "Base* bp = new Derived();\n"
        << "delete bp;\n"
        << "---------------------------\n";
   Base* bp = p;
   cout << "===\n";



}