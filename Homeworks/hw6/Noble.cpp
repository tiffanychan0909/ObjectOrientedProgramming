#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std; 

namespace WarriorCraft{
    ostream& operator <<(ostream& os, const Noble& noble){
        os << noble.name << " has an army of " << noble.army.size() << endl;
        for (const Warrior* w : noble.army){
            os << "	" << *w << endl;
        }
        return os;
    }
    Noble::Noble(const string& name) : name(name) {}
    double Noble::getstrength() const{return army_strength;}
    const string& Noble::getname() const{return name;}
    bool Noble::is_alive() const{return alive;}

    // find warrior in noble's vector
    size_t Noble::find_warrior_i(const Warrior* warrior) const{
        for (size_t i = 0; i < army.size(); i++){
            if (army[i] == warrior){
                return i;
            }
        }

        return army.size();
    }
    // check, then add to vector
    bool Noble::hire(Warrior& warrior){
        if (!warrior.isHired() && alive){
            army.push_back(&warrior);
            army_strength += warrior.getstrength();
            // tell warrior new boss
            warrior.newhired(this);
            return true; 
        } else{ 
            cout << "The warrior you tried to hire is unavailable." << endl;
            return false;
        }
    }
    // check, then remove and is available
    bool Noble::fire(Warrior& warrior){
        if (warrior.isHired() && alive){
            size_t i = find_warrior_i(&warrior);
            // don't swap down
            if (i >= 0) {
                army[i] = army[army.size() - 1]; 
                cout << "You don't work for me anymore "; 
                cout << warrior.getname() << "! -- " << getname() << endl;

                warrior.fired();
                army_strength -= warrior.getstrength();
                army.pop_back();

                return true;

            }
        }

        return false;
    }

    void Noble::ranaway(Warrior& runaway){
        size_t i = find_warrior_i(&runaway);
        // don't swap down
        if (i >= 0) {
            army[i] = army[army.size() - 1];

            cout << runaway.getname() << " flees in terror, abandoning his lord, " << name << endl;
            army_strength -= runaway.getstrength();
            army.pop_back();
        }
    }

    // compare strengths
    void Noble::battle(Noble& opponent){
        cout << name << " battles " << opponent.getname() << endl;
        if (opponent.getstrength() == 0 && getstrength() == 0){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if(opponent.getstrength() == 0){
            cout << "He's dead, " << name << endl;
        } else if(getstrength() == 0){
            cout << "He's dead, " << opponent.getname() << endl;
        } else if(opponent.getstrength() == 0){
            cout << "He's dead, " << getname() << endl;
        } else if(opponent.getstrength() > getstrength()){
            cout << opponent.getname() << " defeats " << getname() << endl;
            // r = 1 - oppon/self and is multiplied
            double r = 1 - ((getstrength())/(opponent.getstrength()));
            dies();
            opponent.wins(r);
        } else if(getstrength() > opponent.getstrength()){
            cout << getname() << " defeats " << opponent.getname() << endl;
            // r = 1 - oppon/self and is multiplied
            double r = 1 - ((opponent.getstrength())/(getstrength()));
            wins(r); 
            opponent.dies();
        } else{
            cout << "Mutual Annihilation: " << getname() << " and " << opponent.getname() 
            << " die at each other's hands" <<  endl;
            
            dies(); 
            opponent.dies();
        }
    }
    // update strength
    void Noble::wins(double c){
        updatearmystrength(c);
    }
    // 0 to all warriors and dead
    void Noble::dies(){
        updatearmystrength(0); 
        alive = false;
    }
    void Noble::updatearmystrength(double c){
        for (Warrior* w : army){
            w-> updatestrength(c);
        }

        army_strength *= c;
    }
    
}