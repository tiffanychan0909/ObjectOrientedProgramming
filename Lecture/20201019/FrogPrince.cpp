//
// Created by Peter DePasquale on 10/19/20.
//

#include "FrogPrince.h"
#include "Princess.h"

using namespace std;

namespace Fantasy {

    FrogPrince::FrogPrince(const string& name) : name(name), spouse(nullptr) {};

    ostream& operator<<(ostream& os, const FrogPrince& frog) {
        os << "Frog Prince: " << frog.name;
        if (frog.spouse != nullptr) {
            os << " is married to: " << frog.spouse->getName();
        }
        return os;
    }

    void FrogPrince::setSpouse(Princess* betrothed) {
        spouse = betrothed;
    }
}