//
// Created by Peter DePasquale on 10/19/20.
//

#include "Princess.h"
#include "FrogPrince.h"

using namespace std;

namespace Fantasy {

    Princess::Princess(const string& name) : name(name), spouse(nullptr) {};

    ostream& operator<<(ostream& os, const Princess& princess) {
        os << "Princess: " << princess.name;
        if (princess.spouse != nullptr) {
            os << " is married to: " << *princess.spouse;
        }
        return os;
    }

    void Princess::marries(FrogPrince& betrothed) {
        spouse = &betrothed;
        betrothed.setSpouse(this);
    }

    const string& Princess::getName() const {
        return name;
    }
}
