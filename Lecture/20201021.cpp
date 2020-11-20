#include <iostream>

using namespace std;
// Operator overloading is used to define a set of functions to add, subtract, multiply... user defined type.
// Cannot:
// * create new operators
// * overload ::, ?:, .
// * change the arity (num of operands), precedence, or associativity
//
// Do not overload: &&, ||, or address-of (&)
// Unary operators are usually done as members

class ComplexNumber {
    friend ostream& operator<<(ostream& os, const ComplexNumber& rhs) {
        os << rhs.real;
        if (rhs.imaginary >= 0) { os << "+"; }
        os << rhs.imaginary << "i";
        return os;
    }

    friend bool operator==(const ComplexNumber& lhs, const ComplexNumber& rhs);

public:
    ComplexNumber(double real = 0, double imaginary = 0) : real(real), imaginary(imaginary) {};

    ComplexNumber& operator+=(const ComplexNumber& rhs) {
        real += rhs.real;
        imaginary += rhs.imaginary;
        return *this;
    }

    ComplexNumber& operator++() {
        ++real;
        return *this;
    }

    ComplexNumber operator++(int dummy) {
        ComplexNumber clone(*this);
        ++real;
        return clone;
    }

    explicit operator bool() const {
        return real !=0 || imaginary !=0;
    }

private:
    double real;
    double imaginary;
};


// Friend of ComplexNumber to provide access to .real and .imaginary
bool operator==(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    return (lhs.real == rhs.real) && (lhs.imaginary == rhs.imaginary);
}

bool operator!=(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    return !(lhs == rhs);
}

ComplexNumber operator+(const ComplexNumber& lhs, const ComplexNumber& rhs) {
    ComplexNumber num(lhs);
    num += rhs;
    return num;
}

int main() {
    ComplexNumber c1;         // 0+0i
    ComplexNumber c2(17);     // 17+0i
    ComplexNumber c3(3, -5);  // 3-5i
    cout << "c1: " << c1 << endl
         << "c2: " << c2 << endl
         << "c3: " << c3 << endl << endl;

    cout << "c1 " << (c1 == c2 ? "==" : "!=") << " c2\n";  // operator==(c1, c2)
    cout << "c1 " << (c1 == c1 ? "==" : "!=") << " c1\n\n";

    cout << "c1 " << (c1 != c2 ? "!=" : "==") << " c2\n";
    cout << "c1 " << (c1 != c1 ? "!=" : "==") << " c1\n\n";

    ComplexNumber one(1);
    cout << "one " << (one == 1 ? "==" : "!=") << " 1\n";    // one == 1 -->>> operator==(one, ComplexNumber(1))
    cout << "1  " << (1 == one ? "==" : "!=") << " one\n\n"; // operator==(ComplexNumber(1), one)

    // Test combination operator
    c1 += c2;  // c1 = c1 + c2;    --->> c1.operator+=(c2)
    cout << "c1: " << c1 << endl
         << "c2: " << c2 << endl << endl;

    c1 += c2 += c3;
    cout << "c1: " << c1 << endl
         << "c2: " << c2 << endl
         << "c3: " << c3 << endl << endl;

    // Test op+
    c1 = c2 + c3;
    cout << "c1: " << c1 << endl
         << "c2: " << c2 << endl
         << "c3: " << c3 << endl << endl;

    // Testing pre-increment (no parameter)
    cout << ++c1 << '\t' << c1 << endl;   // c1.operator++()
    cout << c1++ << '\t' << c1 << endl;   // c1.operator++(0)

    ComplexNumber zero(0);
//    cout << zero.operator bool() << endl;
    cout << "zero is " << (zero ? "true" : "false") << endl;  // returns 0, aka false
    cout << "one is " << (one ? "true" : "false") << endl;    // returns 1, aka true
}
