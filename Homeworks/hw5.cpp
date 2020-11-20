/*
	Tiffany Chan
	Homework 5 
	Medieval Game with Nobles on Heap 
	10/09/2020
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


// Warrior Class 
class Warrior{
	// ostream overload 
	friend ostream& operator <<(ostream& os, const Warrior& warrior);
	public: 
		Warrior(const string& name, double strength) : name(name), strength(strength) {}
		const string& getname() const{return name;}
		const double getstrength() const {return strength;}
		bool is_available() const{return available;}
		void hired(){available = false;}
		void fired(){available = true;}
		void updatestrength(double c){
			if (c == 0){
				available = false;
			}
			
			strength *= c;
		}

	private: 
		string name; 
		double strength;
		bool available = true; 
};

//Noble Class
class Noble{
	friend ostream& operator <<(ostream& os, const Noble& noble);
	public:
		Noble(const string& name) : name(name) {}
		const double getstrength() const{return army_strength;}
		const string& getname() const{return name;}
		const bool is_alive() const{return alive;}

		// find warrior in noble's vector
		size_t find_warrior_i(const Warrior* warrior) const{
			for (size_t i = 0; i < army.size(); i++){
				if (army[i] == warrior){
					return i;
				}
			}
			// if not found, return -1
			return -1;
		}
		// check, then add to vector
		bool hire(Warrior* warrior){
			if (warrior->is_available() && alive){
				army.emplace_back(warrior);
				army_strength += warrior->getstrength();
				warrior->hired();
				return true; 
			} else{ 
				cout << "The warrior you tried to hire is unavailable." << endl;
				return false;
			}
		}
		// check, then remove and is available
		bool fire(Warrior* warrior){
			if (!warrior->is_available() && alive){
				size_t i = find_warrior_i(warrior);
				if (i >= 0) {
					Warrior* temp; 
					for (size_t i; i < army.size(); i++){
					// while (i < army.size()-1){
						temp = army[i];
						army[i] = army[i+1];
						army[i+1] = temp;
						i++;
					}

					cout << "You don't work for me anymore "; 
					cout << warrior->getname() << "! -- " << getname() << endl;

					warrior->fired();
					army_strength -= warrior->getstrength();
					army.pop_back();

					return true;

				}
			}

			
			return false;
		}
		// compare strengths
		void battle(Noble* opponent){
      		cout << name << " battles " << opponent->getname() << endl;
			if (opponent->getstrength() == 0 && getstrength() == 0){
        		cout << "Oh, NO! They're both dead! Yuck!" << endl;
			} else if(opponent->getstrength() == 0){
				cout << "He's dead, " << name << endl;
			} else if(getstrength() == 0){
				cout << "He's dead, " << opponent->getname() << endl;
			} else if(opponent->getstrength() == 0){
				cout << "He's dead, " << getname() << endl;
			} else if(opponent->getstrength() > getstrength()){
				cout << opponent->getname() << " defeats " << getname() << endl;
				// r = 1 - oppon/self and is multiplied
				double r = 1 - ((getstrength())/(opponent->getstrength()));
				dies();
				opponent->wins(r);
			} else if(getstrength() > opponent->getstrength()){
				cout << getname() << " defeats " << opponent->getname() << endl;
				// r = 1 - oppon/self and is multiplied
				double r = 1 - ((opponent->getstrength())/(getstrength()));
				wins(r); 
				opponent->dies();
			} else{
				cout << "Mutual Annihilation: " << getname() << " and " << opponent->getname() 
				<< " die at each other's hands" <<  endl;
				
				dies(); 
				opponent->dies();
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
void read_gamefile(ifstream& gamefile);
Noble* find_noble(const string& noble, const vector<Noble*>& nobles_list);
Warrior* find_warrior(const string& warrior, const vector<Warrior*>& warrior_list);
void delete_all(vector<Noble*>& nobles_list, vector<Warrior*>& warrior_list);

int main() {
	ifstream gamefile("nobleWarriors.txt");
    if(!gamefile){
        cerr << "Can't open 'nobleWarriors.txt'" << endl;
        exit(1);
    }

    read_gamefile(gamefile);

	gamefile.close();
	
}

void read_gamefile(ifstream& gamefile){
    string word; 
	vector<Noble*> nobles_list; 
	vector<Warrior*> warrior_list; 


    // 7 phrases
    while (gamefile >> word){
        if (word == "Noble"){
			string name; 
			gamefile >> name;
			if (!find_noble(name, nobles_list)){
            	nobles_list.emplace_back(new Noble(name));
			} else{
				cout << name << " already exists in the game." << endl;
			}

        } else if (word == "Warrior"){
			string name; 
			double strength;
			gamefile >> name >> strength;
			if (!find_warrior(name, warrior_list)){
				warrior_list.emplace_back(new Warrior(name, strength));
			} else{
				cout << name << " already exists in the game." << endl;
			}
			
		} else if (word == "Hire"){
			string noble, warrior; 
			gamefile >> noble >> warrior;
			Noble* n = find_noble(noble, nobles_list);
			Warrior* w = find_warrior(warrior, warrior_list);

			if (n && w){
				if (w-> is_available()){
					n-> hire(w);
				}
			} else {
				if (!n && !w){
					cout << noble << " noble and " << warrior << " noble don't exist yet." << endl;
				} else if (!n){
					cout << noble << " noble doesn't exist in the game yet." << endl;
				} else{
					cout << warrior << " warrior doesn't exist in the game yet." << endl;
				}
			}

		} else if (word == "Fire"){
			string noble, warrior; 
			gamefile >> noble >> warrior;
			Noble* n = find_noble(noble, nobles_list);
			Warrior* w = find_warrior(warrior, warrior_list);
			if (n && w){
				bool fire = n-> fire(w);
				if (!fire){
					cout << warrior << " doesn't work for you." << endl;
				}
			} else {
				if (!n && !w){
					cout << noble << " noble and " << warrior << " warrior don't exist yet." << endl;
				} else if (!n){
					cout << noble << " noble doesn't exist in the game yet." << endl;
				} else{
					cout << warrior << " warrior doesn't exist in the game yet." << endl;
				}
			}

		} else if (word == "Battle"){ 
			string noble, noble2; 
			gamefile >> noble >> noble2;
			Noble* n1 = find_noble(noble, nobles_list);
			Noble* n2 = find_noble(noble2, nobles_list);
			if (n1 && n2){
				n1-> battle(n2);
			}	else {
				if (!n1 && !n2){
					cout << noble << " noble and " << noble << " noble don't exist yet." << endl;
				} else if (!n1){
					cout << noble << " noble doesn't exist in the game yet." << endl;
				} else{
					cout << noble2 << " noble doesn't exist in the game yet." << endl;
				}
			}

    	} else if (word == "Clear"){
			delete_all(nobles_list, warrior_list);

		} else {
			cout << "STATUS" << endl; 
			cout << "======" << endl;

			cout << "Nobles:" << endl;
			bool nobles = false;
			for (const Noble* n : nobles_list){
				cout << *n << endl;
				nobles = true;
			}
			if (!nobles){
				cout << "NONE" << endl;
			}

			cout << "Unemployed Warriors" << endl;
			bool warriors = false;
			for (const Warrior* w : warrior_list){
				if (w-> is_available()){
					cout << *w << endl;
					warriors = true;
				}
			}
			if (!warriors){
				cout << "NONE" << endl;
			}
		}
	}
}
// return noble
Noble* find_noble(const string& noble, const vector<Noble*>& nobles_list){
	for (Noble* n : nobles_list){
		if (noble == n->getname()){
			return n;
		}
	}
	return nullptr;
}

Warrior* find_warrior(const string& warrior, const vector<Warrior*>& warrior_list){
	for (Warrior* w : warrior_list){
		if (warrior == w->getname()){
			return w;
		}
	}
	return nullptr;
}

void delete_all(vector<Noble*>& nobles_list, vector<Warrior*>& warrior_list){
	for (Noble* n : nobles_list){
		delete n;
	}

	for (Warrior* w : warrior_list){
		delete w;
	}
	
	nobles_list.clear();
	warrior_list.clear();
}

ostream& operator <<(ostream& os, const Noble& noble){
	os << noble.name << " has an army of " << noble.army.size() << endl;
	for (const Warrior* w : noble.army){
		os << "	" << *w << endl;
	}
	return os;
}
ostream& operator <<(ostream& os, const Warrior& warrior){
	os << warrior.name << " : " << warrior.strength;
	return os;
}
