// hiding

#include <iostream>

using namespace std;

class Base {
public:
    void foo(int n) const { cout << "Base::foo(n)" << endl; }
};

class Derived : public Base {
public:
//    using Base::foo;

//    void foo(int n) const { cout << "Derived::foo(n)" << endl; }

    void foo() const { cout << "Derived::foo()" << endl; }
};

int main() {
    Derived der;
    der.foo(17);
    der.foo();
    der.Base::foo(17);
}

// 1. der.foo(17) calls Base::foo(int) through code reuse, i.e. inheritance
//
// 2. Add Derived::foo(int): der.foo(17) now calls Derived::foo(int) as Derived redefines foo(int).
//
// 3. Add Derived::foo(), remove Derived::foo(int): call to der.foo(17) now fails.
//      Definition of Derived::foo() "hides" any definition of foo in Base
//
// 4. Achieve unhiding:
    // from main:  call der.Base::foo(17)
    // in Derived class: add "using Base::foo;"