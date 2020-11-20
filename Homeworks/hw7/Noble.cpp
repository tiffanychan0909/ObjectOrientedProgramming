#include "Noble.h"
#include "Protector.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std; 

namespace WarriorCraft{
 
    Noble::Noble(const string& name, double strength) : name(name), strength(strength), alive(true) {}
    double Noble::getstrength() const{return strength;}
    const string& Noble::getname() const{return name;}
    bool Noble::is_alive() const{return alive;}
    // compare strengths and battlecry
    void Noble::battle(Noble& opponent){
        cout << name << " battles " << opponent.getname() << endl;
        if (opponent.getstrength() == 0 && getstrength() == 0
            && !opponent.is_alive() && !(this->is_alive())){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if(opponent.getstrength() == 0 && !opponent.is_alive()){
            this->defend();
            cout << "He's dead, " << this->getname() << endl;
        } else if(getstrength() == 0 && !(this->is_alive())){
            opponent.defend();
            cout << "He's dead, " << opponent.getname() << endl;
        } else if(opponent.getstrength() > getstrength()){
            this->defend();
            opponent.defend();
            cout << opponent.getname() << " defeats " << getname() << endl;
            // r = 1 - oppon/self and is multiplied
            double r = 1 - ((getstrength())/(opponent.getstrength()));
            dies();
            opponent.wins(r);
        } else if(getstrength() > opponent.getstrength()){
            this->defend();
            opponent.defend();
            cout << getname() << " defeats " << opponent.getname() << endl;
            // r = 1 - oppon/self and is multiplied
            double r = 1 - ((opponent.getstrength())/(getstrength()));
            wins(r); 
            opponent.dies();
        } else{
            // there is no example for battlecries for when they have the same strength
            this->defend();
            opponent.defend();
            cout << "Mutual Annihilation: " << getname() << " and " << opponent.getname() 
            << " die at each other's hands" <<  endl;
            
            dies(); 
            opponent.dies();
        }
    }
    // update strength
    void Noble::wins(double c){
        updatestrength(c);
    }
    // 0 to all warriors and dead
    void Noble::dies(){
        updatestrength(0); 
        alive = false;
    }
    // self strength * c
    void Noble::updatestrength(double c){
        strength *= c;
    }
    // this is used by the lord class to update their strength after hiring
    void Noble::increaseStrength(double s){
        strength += s;
    }

    // Lord methods ============================
    Lord::Lord(const std::string& name) : Noble(name) {}
    // update strength ratio for all protectors
    void Lord::wins(double c){
        updatestrength(c); // update army
        Noble::wins(c); // update personal
    }
    // kill all and self
    void Lord::dies(){
        updatestrength(0); // army
        Noble::dies(); // personal
    }
    void Lord::updatestrength(double c){
        for (Protector* p : army){
            p-> updatestrength(c);
        }

        Noble::updatestrength(c);
    }

    // find warrior in noble's vector
    size_t Lord::find_warrior_i(const Protector* protector) const{
        for (size_t i = 0; i < army.size(); i++){
            if (army[i] == protector){
                return i;
            }
        }

        return army.size();
    }
    // everyone in army cries
    void Lord::defend() const {
        for (const Protector* p : army){
            p->battlecry();
        }
    }

    // check, then add to vector
    bool Lord::hires(Protector& protector){
        if (!protector.isHired() && this->is_alive()){
            army.push_back(&protector);
            Noble::increaseStrength(protector.getstrength());
            // tell warrior new boss
            protector.gotHired(this);
            return true; 
        } else{ 
            return false;
        }
    }
    // check, then swap-remove, and is available
    bool Lord::fires(Protector& protector){
        if (!protector.isHired() && !is_alive() && !protector.isAlive()){return false;}
        size_t i = find_warrior_i(&protector);
        if (i == army.size()){return false;}
        Protector* temp;
        while(i < army.size()){
            temp = army[i];
            army[i] = army[i+1];
            army[i+1] = temp;
            i++;
        }
        cout << "You don't work for me anymore "; 
        cout << protector.getname() << "! -- " << getname() << endl;
        protector.fired();
        increaseStrength(-1 * (protector.getstrength()));
        army.pop_back();
        return true;

    }
    // check if belongs to this noble first and then remove
    bool Lord::ranaway(const Protector& runaway){
        size_t i = find_warrior_i(&runaway);
        if (i == army.size()){return false;}
        Protector* temp;
        while(i < army.size()){
            temp = army[i];
            army[i] = army[i+1];
            army[i+1] = temp;
            i++;
        }
        cout << runaway.getname() << " flees in terror, abandoning his lord, " << this->getname() << endl;
        this->increaseStrength(-1 * (runaway.getstrength()));
        army.pop_back();
        return true;
    }

    // Personwithstrengthtofight
    PersonWithStrengthToFight::PersonWithStrengthToFight(const std::string& name, double strength) : Noble(name, strength) {}
    void PersonWithStrengthToFight::defend() const{
        cout << "Ugh!" << endl;
    }
    
}