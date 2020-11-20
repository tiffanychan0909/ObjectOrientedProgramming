/*
	Tiffany Chan
	Homework 4 
	Medieval Game with Nobles 
	10/09/2020
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;


// Warrior Class 
class Warrior{
	// ostream overload 
	friend ostream& operator <<(ostream& os, const Warrior* warrior);
	public: 
		Warrior(const string& name, double strength) : name(name), strength(strength) {}
		const string& getname() const{return name;}
		const double& getstrength() const {return strength;}
		const bool is_available() const{return available;}
		const bool is_alive() const{return alive;}
		void hired(){available = false;}
		void fired(){available = true;}
		void updatestrength(double c){
			if (c == 0){
				available = false;
				alive = false;
			}
			
			strength *= c;
		}

	private: 
		string name; 
		double strength;
		bool available = true; 
		bool alive = true;
};

//Noble Class
class Noble{
	friend ostream& operator <<(ostream& os, const Noble& noble);
	public:
		Noble(const string& name) : name(name) {}
		const double& getstrength() const{return army_strength;}
		const string& getname() const{return name;}

		// find warrior in noble's vector
		int find_warrior_i(Warrior& warrior) const{
			for (size_t i = 0; i < army.size(); i++){
				if (army[i] == &warrior){
					return i;
				}
			}
			// if not found, return -1
			return -1;
		}
		// check, then add to vector
		bool hire(Warrior& warrior){
			if ((warrior.is_available() && warrior.is_alive()) || alive){
				army.push_back(&warrior);
				army_strength += warrior.getstrength();
				warrior.hired();
				return true; 
			} else{ 
				cout << "The warrior you tried to hire is unavailable." << endl;
				return false;
			}
		}
		// check, then remove and is available
		bool fire(Warrior& warrior){
			if ((!warrior.is_available() && warrior.is_alive()) || alive){
				int i = find_warrior_i(warrior);
				if (i >= 0) {
					Warrior* temp; 
					while (i < army.size()){
						temp = army[i];
						army[i] = army[i+1];
						army[i+1] = temp;
						i++;
					}

					cout << "You don't work for me anymore "; 
					cout << warrior.getname() << "! -- " << getname() << endl;
					army_strength -= warrior.getstrength();
					army.pop_back();
					return true;

				}
			}
			return false;
		}
		// compare strengths
		void battle(Noble& opponent){
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
				// ratio = 1 - oppon/self and is multiplied
				double ratio = 1 - ((getstrength())/(opponent.getstrength()));
				dies();
				opponent.wins(ratio);
			} else if(getstrength() > opponent.getstrength()){
				cout << getname() << " defeats " << opponent.getname() << endl;
				// ratio = 1 - oppon/self and is multiplied
				double ratio = 1 - ((opponent.getstrength())/(getstrength()));
				wins(ratio); 
				opponent.dies();
			} else{
				cout << "Mutual Annihilation: " << getname() << " and " << opponent.getname() 
				<< " die at each other's hands" <<  endl;
				
				dies(); 
				opponent.dies();
			}
		}
		// update strength
		void wins(double c){
			updatearmystrength(c);
		}
		// 0 to all warriors and dead
		void dies(){
			updatearmystrength(0); 
			alive = false;
		}

		void updatearmystrength(double c){
			for (Warrior* w : army){
				w-> updatestrength(c);
			}

			army_strength *= c;
		}

	private: 
		string name; 
		vector<Warrior*> army; 
		double army_strength; 
		bool alive = true; 
};

// Your Noble and Warrior classes should go here.

int main() {
	
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");
	
	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);
	Warrior abe("William", 123);
	
	// noble hire warrior
	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	
    cout << "==========\n"
         << "Status before all battles, etc.\n";
	cout << jim << endl;
    cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
    cout << "==========\n";
	
	art.fire(cheetah);
	cout << art << endl;
	
	// noble battle noble
	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
	cout << jim << endl;
    cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
    cout << "==========\n";
	
}


ostream& operator <<(ostream& os, const Noble& noble){
	os << noble.name << " has an army of " << noble.army.size() << endl;
	for (const Warrior* w : noble.army){
		os << "	" << w << endl;
	}
	return os;
}
ostream& operator <<(ostream& os, const Warrior* warrior){
	os << warrior-> name << " : " << warrior-> strength;
	return os;
}
