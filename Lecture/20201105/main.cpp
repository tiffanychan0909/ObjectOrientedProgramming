// Overload vs. override

#include <iostream>

using namespace std;

class Parent {
public:
    virtual void bar() { cout << "Parent::bar()" << endl; }
};

class Child : public Parent {
public:
    void bar() override { cout << "Child::bar()" << endl; }  // bar is overridden from Parent class
};

class Grandchild : public Child {
    void bar() override { cout << "Grandchild::bar()" << endl; }  // bar is overridden from Child class
};

void func(Parent& base) { cout << "func(parent)" << endl; }  // func is overloaded (two implementations, two diff sigs)

void func(Child& derived) { cout << "func(child)" << endl; }

void otherFunc(Parent& base) {
    func(base);  // pick the overload, it is based on the compile-time type
    base.bar();
}

int main() {
    Parent parent;
    func(parent);
    otherFunc(parent);
    cout << "===" << endl;

    Child child;
    func(child);
    otherFunc(child);
    cout << "===" << endl;

    Grandchild grandc;
    func(grandc);  // Which is called?  Which is more specific?
    otherFunc(grandc);
}
