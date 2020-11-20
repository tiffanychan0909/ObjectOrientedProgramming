// Rational prototypes

#ifndef RATIONAL_H
#define RATIONAL_H

#include <fstream>
#include <iostream>
#include <string>

namespace CS2124 {
    class Rational {
        // friend
        friend std::ostream& operator<<(std::ostream& os, const Rational& r);
        friend std::istream& operator>>(std::istream& is, Rational& r);
        friend bool operator==(const Rational& a, const Rational& b);
        friend bool operator<(const Rational& a, const Rational& b);

    public:
        // methods
        Rational(int numerator = 0, int denominator = 1);
        Rational& operator+=(const Rational& r);
        Rational& operator++();
        Rational operator++(int x);
        explicit operator bool() const;
    private:
        void simplify();
        int greatestCommonDivisor(int x, int y);
        int numerator;
        int denominator;
    };  // class Rational

    Rational operator+(const Rational& a, const Rational& b);
    bool operator!=(const Rational& a, const Rational& b);
    bool operator<=(const Rational& a, const Rational& b);
    bool operator>(const Rational& a, const Rational& b);
    bool operator>=(const Rational& a, const Rational& b);
    Rational& operator--(Rational& r);
    Rational operator--(Rational& r, int x);
}  // namespace CS2124
#endif