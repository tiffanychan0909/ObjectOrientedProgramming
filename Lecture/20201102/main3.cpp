#include <iostream>

using namespace std;

class Shape {  // abstract class
public:
    Shape(int x, int y) : x(x), y(y) {}

    void move(int x, int y) {
        this->x = x;;
        this->y = y;
    }

    virtual void draw() = 0; // In C++ this is known as "pure virtual" (abstract method), assign 0.
        // Can't know the implementation in the base class, but we know every derived class must have an
        // implementation of draw()

private:
    int x;
    int y;
};

class Triangle : public Shape {
public:
    Triangle(int x, int y) : Shape(x, y) {}

    void draw() { cout << "Triangle::draw()" << endl; }
};

class Isosceles : public Triangle {
public:
    Isosceles(int x, int y) : Triangle(x, y) {}

    // inherits draw() from Triangle!
};

class Circle : public Shape {
public:
    Circle(int x, int y) : Shape(x, y) {}

    void draw() { cout << "Circle::draw()" << endl; }
};

int main() {
//    Shape shape(0,0);  // Can't do this, Shape is abstract
    Triangle tri(1,1);
    tri.draw();

    Isosceles iso(2, 2);
    iso.draw();

    Circle circ(3, 3);
    circ.draw();
};

// Facts:
// 1. A class is abstract if it has at least one pure virtual function/method.

// 2. We can have pointers and references of abstract class type. For example:
//    Shape* sh = new Circle();

// 3. If we do not override the pure virtual function/method in the derived class, then the
//    derived class also becomes abstract.

// 4. An abstract class can have constructors.