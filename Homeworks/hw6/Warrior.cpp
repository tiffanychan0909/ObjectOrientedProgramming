#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std; 

namespace WarriorCraft{
    Warrior::Warrior(const string& name, double strength) : name(name), strength(strength) {}
    ostream& operator <<(ostream& os, const Warrior& warrior){
        os << warrior.name << " : " << warrior.strength;
	    return os;
    }

    const string& Warrior::getname() const{return name;}
    double Warrior::getstrength() const {return strength;}
    bool Warrior::isHired() const{return hired;}
    bool Warrior::runaway(){
        if(!hired){
            return false;
        }
        hired = false;
        boss->ranaway(*this);
        boss = nullptr;
        return true;
    }
    void Warrior::newhired(Noble* newboss){
        hired = true;
        boss = newboss;
        }
    void Warrior::fired(){
        hired = false;
        boss = nullptr;
        }
    void Warrior::updatestrength(double c){
        if (c == 0){
            hired = false;
        }
        strength *= c;
    }

}