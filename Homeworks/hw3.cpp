/*
Tiffany Chan
tc2965
HW 3
Medieval Game
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// read into vector of warriors
// warrior class has private weapon class 
// status prints os which asks warrior class to ask weapon class 
// battles is method now 

// Warrior class with private nested Weapon class
class Warrior{
  // friend prototypes and class declaration
  class Weapon; 
  friend ostream& operator<<(ostream& os, const Warrior& warrior);
  friend ostream& operator<<(ostream& os, const Warrior::Weapon& weapon);

  public:
    Warrior(const string& warrior_name, const string& weapon_name, int strength) :
        warrior_name(warrior_name), weapon(weapon_name, strength){}
    string get_name() const{return warrior_name;}
    string get_weapon_name() const{return weapon.get_weapon_name();}
    int get_strength() const{return weapon.get_weapon_strength();}

    void wins(){weapon.change_strength(8);}
    void dies(){weapon.change_strength(0);}
      
    // compares and changes
    void battles(Warrior& opponent){
      cout << warrior_name << " battles " << opponent.get_name() << endl;
      if (get_strength() == 0 && opponent.get_strength() == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
      } else if(get_strength() == 0){
        cout << "He's dead, " << opponent.get_name() << endl;
      } else if(opponent.get_strength() == 0){
        cout << "He's dead, " << get_name() << endl;
      } else if(get_strength() > opponent.get_strength()){
        cout << warrior_name << " defeats " << opponent.get_name() << endl;
        wins(); 
        opponent.dies();
      } else if(get_strength() < opponent.get_strength()){
        cout << opponent.get_name() << " defeats " << warrior_name << endl;
        opponent.wins();
        dies();
      } else{
        cout << "Mutual Annihilation: " << warrior_name << " and " << opponent.get_name() << endl;
        dies(); 
        opponent.dies();
      }
    }
  
  private: 
    // Weapon class
    class Weapon{
      friend ostream& operator<<(ostream& os, const Warrior::Weapon& weapon);
      
      public: 
        Weapon(const string& weapon_name, int strength) : 
          weapon_name(weapon_name), weapon_strength(strength){}
        
        // Weapon methods:
        string get_weapon_name() const{return weapon_name;}
        int get_weapon_strength() const{return weapon_strength;}

        void change_strength(int c){
          if (c == 0){
            weapon_strength = 0;
          } else {
            weapon_strength -= c;
          }
        }
      private: 
        string weapon_name; 
        int weapon_strength;
    };
    
    // private variables
    Weapon weapon; 
    string warrior_name;

};

// prototypes
void read_gamefile(vector<Warrior>& list_of_warriors, ifstream& gamefile);
int search_warrior(const vector<Warrior>& list_of_warriors, const string& warrior);

int main(){
  ifstream gamefile("warriors.txt");
  if (!gamefile){
    cerr << "Can't open game file..." << endl;
    exit(1);
  }

  vector<Warrior> list_of_warriors;
  read_gamefile(list_of_warriors, gamefile);
}

// reads file, emplaces, cout <<, and battles
void read_gamefile(vector<Warrior>& list_of_warriors, ifstream& gamefile){
  string word; 
  while (gamefile >> word){
    if (word == "Warrior") {
      string name, weapon; 
      int strength;
      gamefile >> name >> weapon >> strength;
      
      list_of_warriors.emplace_back(Warrior(name, weapon, strength));
    } else if (word == "Status") {
      cout << "There are " << list_of_warriors.size() << " warriors." << endl;
      for (Warrior& w : list_of_warriors){
        cout << w << endl;
      }
    } else {
      string warrior1, warrior2;
      gamefile >> warrior1 >> warrior2;

      int index_1 = search_warrior(list_of_warriors, warrior1);
      int index_2 = search_warrior(list_of_warriors, warrior2);
      if (!(index_1 == -1 || index_2 == -1)){
        list_of_warriors[index_1].battles(list_of_warriors[index_2]);
      }

    }
  }
}

// returns index of warrior
int search_warrior(const vector<Warrior>& list_of_warriors, const string& warrior){
  for (size_t i = 0; i < list_of_warriors.size(); i++){
    if (list_of_warriors[i].get_name() == warrior){
      return i;
    }
  }
  cout << "Warrior not found, returning -1..." << endl; 
  return -1;
}

ostream& operator<<(ostream& os, const Warrior& warrior){
  os << "Warrior: " << warrior.get_name() << ", " << warrior.weapon;
  return os;
}

ostream& operator<<(ostream& os, const Warrior::Weapon& weapon){
  os << "Weapon: " << weapon.get_weapon_name() << ", " << weapon.get_weapon_strength();
  return os;
}