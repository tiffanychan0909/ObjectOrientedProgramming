#include <iostream>
#include <string>

using namespace std;

class Pet {
public:  // externally visible everywhere (in main, and in subclasses)
    Pet(const string& name) : name(name) {}


protected:  // not externally visible (in main...), but visible to subclasses
    string name;

private:  // not externally visible (in main...), also not visible to subclasses
};

class Dog : public Pet {
public:
    Dog(const string& name2, int age) : Pet(name2), age(age) {  }

    void change_name(const string& name) { this->name = name; }

private:
    int age;
};

class Poodle : public Dog {
public:
    Poodle(const string& name, int age, bool fluffy) : Dog(name, age), is_fluffy(fluffy) {}

private:
    bool is_fluffy;
};

int main() {
    Dog chris("Chris the dog", 12);
    Poodle fluffy("Fluffy", 4, true);

    cout <<
}