#include <iostream>
#include <string>

using namespace std;

class Pet {
    friend ostream& operator<<(ostream& os, const Pet& rhs) {
        os << "Name: " << rhs.name;
        return os;
    }

public:
    Pet(const string& name) : name(name) {}

    virtual void eat() { cout << "Pet eating" << endl; }

    virtual ~Pet() {}

private:
    string name;
};

class Cat : public Pet {
public:
//    Cat(const string& the_name) : name(the_name) {}
    Cat(const string& the_name) : Pet(the_name) {}
};

int main() {
    Pet bob("Bob");
    cout << bob << endl;

    Cat garfield("Garfield");
}