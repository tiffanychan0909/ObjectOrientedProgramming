// Rational implementations

#include <fstream>
#include <iostream>
#include <string>
#include "Rational.h"
using namespace std;

namespace CS2124 {
    ostream& operator<<(ostream& os, const Rational& r) {
        os << r.numerator << "/" << r.denominator;
        return os;
    }
    istream& operator>>(istream& is, Rational& r) {
        char slash;
        is >> r.numerator >> slash >> r.denominator;
        r.simplify();
        return is;
    }

    Rational::Rational(int numerator, int denominator)
        : numerator(numerator), denominator(denominator) {
        simplify();
    }

    Rational& Rational::operator+=(const Rational& r) {
        numerator = (r.denominator * numerator) + (r.numerator * denominator);
        denominator *= r.denominator;
        simplify();
        return *this;
    }

    Rational& Rational::operator++() {
        numerator += denominator;
        return *this;
    }
    Rational Rational::operator++(int x) {
        Rational original(*this);
        numerator += denominator;
        return original;
    }

    Rational::operator bool() const { return numerator != 0; }

    // private methods
    void Rational::simplify() {
        int gcd = greatestCommonDivisor(numerator, denominator);
        numerator /= gcd;       
        denominator /= gcd;     
        if (denominator < 0) {  // if the denominator is negative, flip
            denominator *= -1;  // the sign of both denominator and numerator
            numerator *= -1;
        }
    }

    int Rational::greatestCommonDivisor(int x, int y) {
        while (y != 0) {
            int temp = x % y;
            x = y;
            y = temp;
        }
        return x;
    }

    // friends
    bool operator==(const Rational& a, const Rational& b) {
        return a.numerator == b.numerator &&
               a.numerator == b.denominator;
    }

    bool operator<(const Rational& a, const Rational& b) {
        return a.numerator / a.denominator <
               b.numerator / b.denominator;
    }

    // non member non friend
    Rational operator+(const Rational& a, const Rational& b) {
        Rational result(a);
        result += b;
        return result;
    }

    Rational& operator--(Rational& r) {
        r += -1;
        return r;
    }

    Rational operator--(Rational& r, int x) {
        Rational original(r);
        r += -1;
        return original;
    }

    bool operator!=(const Rational& a, const Rational& b) {
        return !(a == b);
    }

    bool operator<=(const Rational& a, const Rational& b) {
        return a < b || a == b;
    }
    bool operator>(const Rational& a, const Rational& b) {
        return !(a <= b);
    }
    bool operator>=(const Rational& a, const Rational& b) {
        return !(a < b);
    }
}  // namespace CS2124