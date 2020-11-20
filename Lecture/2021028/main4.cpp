#include <iostream>
#include <vector>

using namespace std;

class Base {
public:
    void a() const { cout << "base::a called" << endl; }

    virtual void b() const { cout << "base::b called" << endl; }

    virtual void c() const { cout << "base::c called" << endl; }
};

class Derived : public Base {
public:
    void a() const { cout << "derived::a called" << endl; }  // override base::a

    void b() const { cout << "derived::b called" << endl; }
};

class Derived_Two : public Base {
};

class Derived_Three : public Base {
};

//void do_base(Base base_obj) {  // polymorphism & slicing
void do_base(Base& base_obj) {   // polymorphism
    cout << "Call functions in the base class" << endl;

    base_obj.a();   // outputs base::a
    base_obj.b();   // is virtual, may be executed from derived class
    base_obj.c();   // is virtual, may be executed from derived class, but is not defined there, so base class is used
}

int main() {
    Derived a_derived;
    Base b_base;

    cout << "Calling functions within the derived class:" << endl;
    a_derived.a();  // derived::a
    a_derived.b();  // derived::b
    a_derived.c();  // base::c
    cout << endl;

//    do_base(b_base);
    do_base(a_derived);   // principle of substitutibility: Barbara Liskov
    // if S is a subtype of T, then objects of type T in a program may be replaced with objects of type S
    // without altering any of the desirable properties of that program.

    b_base = a_derived;  // slicing
//    a_derived = b_base;

    //-------
    Derived one;
    Derived_Two two;
    Derived_Three three;
    cout << endl;

//    vector<Base&> other_vec;  // won't compile:
    vector<Base> data_vec;   // slicing ... will only hold Base objects, but we'll put in Derived objects
    data_vec.push_back(one);
    data_vec.push_back(two);
    data_vec.push_back(three);

    for (Base& element : data_vec) {
        element.a();
        element.b();
        element.c();
    }

    cout << endl;
    vector<Base*> data_vec_2;
    data_vec_2.push_back(&one);
    data_vec_2.push_back(&two);
    data_vec_2.push_back(&three);

    for (const Base* element : data_vec_2) {
        element->a();
        element->b();
        element->c();
    }
}

// Derived has 3 member functions. Two of them are self-defined (a and b). The third, c, is inherited from Base class.
// When we call a, C+++ looks at the Derived class first to see whether that class defines the function. (It does.)
// When we call b, the same things happens. It does not matter whether the base class defines a and b or not!

// The Derived class does not contain a member function named c. When we call a_derived.c(), C++ tries to find the c
// function in the Derived class and fails. Then it tries to find the member function in the base class. It finds it
// there.  (None of this deals with virtual...)

// do_base function introduces polymorphism. do_base takes a Base object as its parameter, so C++ restrict its search for
// member functions to the Base class.
// When we use virtual on a base method, it tells C++ that the search rules are changed.  C++ first checks the Derived
// class for member 'b' (.b()), and then would check the Base class. In the case of calling .b(), it's in the Derived
// class so it execute 'b()' from the Derived class.  Member function 'c' is aso virtual, therefore, C++ starts by looking
// in the Derived class. It's not defined there, so C++ then look in the Base class, where it is defined.