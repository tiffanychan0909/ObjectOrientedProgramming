#include <iostream>
#include <string>

using namespace std;

class FrogPrince;

class Princess {
    friend ostream& operator<<(ostream& os, const Princess& princess);

public:
    explicit Princess(const string& name);

    void marries(FrogPrince& betrothed);

private:
    string name;
    FrogPrince* spouse;
};


class FrogPrince {
    friend ostream& operator<<(ostream& os, const FrogPrince& frog);

    friend void Princess::marries(FrogPrince& betrothed);

public:
    explicit FrogPrince(const string& name);

    const string& getName() const;

    static int add(int a, int b) { return a + b; }  // possible implicitly inline

private:
    string name;
    Princess* spouse;
};

int main() {
    Princess snowy("Snow White");
    FrogPrince frogger("Froggy");
    cout << snowy << endl
         << frogger << endl;

    snowy.marries(frogger);
    cout << snowy << endl
         << frogger << endl;

    int alpha = FrogPrince::add(5,3);  // translated to: int alpha = 5 + 3;
}


ostream& operator<<(ostream& os, const FrogPrince& frog) {
    os << "Frog Prince: " << frog.name;
    if (frog.spouse != nullptr) {
        os << " is married to: " << *frog.spouse;
    }
    return os;
}

ostream& operator<<(ostream& os, const Princess& princess) {
    os << "Princess: " << princess.name;
    if (princess.spouse != nullptr) {
        os << " is married to: " << princess.spouse->getName();
    }
    return os;
}

void Princess::marries(FrogPrince& betrothed) {
    spouse = &betrothed;
    betrothed.spouse = this;
}

const string& FrogPrince::getName() const {
    return name;
}

FrogPrince::FrogPrince(const string& name) : name(name), spouse(nullptr) {};

Princess::Princess(const string& name) : name(name), spouse(nullptr) {}