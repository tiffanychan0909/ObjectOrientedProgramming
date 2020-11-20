#include "Protector.h"
#include "Noble.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace WarriorCraft{
    // Base class protector
    Protector::Protector(const string& name, double strength = 0) 
        : name(name), strength(strength), boss(nullptr), hired(false), alive(false) {}
    const string& Protector::getname() const{return name;}
    const string& Protector::getbossname() const{return (boss->getname());}
    // Lord* Protector::getboss() const{return boss;}
    double Protector::getstrength() const {return strength;}
    bool Protector::isHired() const{return hired;}
    bool Protector::isAlive() const{return alive;}
    bool Protector::quit(){
        if(!hired){
            return false;
        }
        if (boss->ranaway(*this)){
            boss = nullptr;
            hired = false;
        }
        return true;
    }
    void Protector::gotHired(Lord* newboss){
        hired = true;
        boss = newboss;
        }
    void Protector::fired(){
        hired = false;
        boss = nullptr;
        }
    void Protector::updatestrength(double c){
        if (c == 0){alive = false;}
        strength *= c;
    }

    // Wizard ======================
    Wizard::Wizard(const std::string& name, double strength): Protector(name, strength){}
    void Wizard::battlecry() const{
        cout << "POOF!" << endl;
    }
    // Warrior ======================
    Warrior::Warrior(const std::string& name, double strength) : Protector(name, strength) {}
    void Warrior::battlecry() const{
        cout << getname() 
            << " says: Take that in the name of my lord, "
            // << getboss()->getname() << endl;
            << getbossname() << endl;
    }
    // Archer ========================
    Archer::Archer(const std::string& name, double strength) : Warrior(name, strength) {}
    void Archer::battlecry() const{
        cout << "TWANG! " ;
        Warrior::battlecry(); // call mid-parent cry
    }
    // Swordsman =====================
    Swordsman::Swordsman(const std::string& name, double strength) : Warrior(name, strength) {}
    void Swordsman::battlecry() const{
        cout << "CLANG! " ;
        Warrior::battlecry(); // call mid-parent cry
    }
    



}