#include "Noble.h"
#include "Protector.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std; 
namespace WarriorCraft{
    Protector::Protector(const string& name, double strength) 
        : name(name), strength(strength), boss(nullptr){}
    const string& Protector::getname() const{return name;}
    Lord* Protector::getlord() const{return boss;}
    double Protector::getstrength() const{return strength;}
    bool Protector::isHired() const{return !(boss == nullptr);}
    bool Protector::runaway(){
        if (!boss){return false;}
        boss->ranaway(this); 
        boss = nullptr; 
        return true;
    }
    void Protector::newHired(Lord* newboss){boss = newboss;}
    void Protector::fired(){boss = nullptr;}
    void Protector::updatestrength(double c){strength *= c;}

    Warrior::Warrior(const std::string& name, double strength)
        : Protector(name, strength){}
    void Warrior::battlecry() const{
        cout << getname() << " says: Take that in the name of my lord, " << 
        getlord() -> getname();
    }

    // Wizard 
    Wizard::Wizard(const std::string& name, double strength)
        : Protector(name, strength){}
    void Wizard::battlecry() const {cout << "POOF";}
    // Archer
    Archer::Archer(const std::string& name, double strength)
        : Warrior(name, strength){}
    void Archer::battlecry() const {
        cout << "In protect battlecry" << getname() << endl;
        cout << "TWANG! " << getname() << " says: Take that in the name of my lord, "
        << getlord()-> getname();
    }
    // Swordsman
    Swordsman::Swordsman(const std::string& name, double strength)
        : Warrior(name, strength){}
    void Swordsman::battlecry() const {
        cout << "In protect battlecry" << getname() << endl;
        cout << "CLANG! " << getname() << " says: Take that in the name of my lord, "
        << getlord()-> getname();
    }
}