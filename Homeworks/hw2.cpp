/*
Tiffany Chan
tc2965
HW 2
Medieval Game: Match two warriors for battle
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// structure for warriors
struct Warrior{
  string name; 
  int strength; 
};

void read_gamefile(vector<Warrior>& list_of_warriors, ifstream& gamefile);
void insert_new_warrior(vector<Warrior>& list_of_warriors, string& name, int strength);
void print_status(vector<Warrior> list_of_warriors);
vector<int> search_warrior(vector<Warrior> list_of_warriors, const string& name);
void battle_time(vector<Warrior>& list_of_warriors, const string& warrior1, const string& warrior2);


int main(){
  ifstream gamefile("warriors.txt");
  if (!gamefile){
    cerr << "Can't open gamefile" << endl;
    exit(1);
  }
  vector<Warrior> list_of_warriors;
  read_gamefile(list_of_warriors, gamefile);
}

// creates and inserts a new warrior into the vector of warriors
void insert_new_warrior(vector<Warrior>& list_of_warriors, string& name, int strength){
  Warrior NewWarrior; 
  NewWarrior.name = name; 
  NewWarrior.strength = strength; 

  list_of_warriors.push_back(NewWarrior);
}

// prints out the statuses of each warrior
void print_status(vector<Warrior> list_of_warriors){
  cout << "There are " << list_of_warriors.size() << " warriors." << endl;
  for (Warrior w : list_of_warriors){
    cout << "Warrior: " << w.name << ", strength: " << w.strength << endl;
  }
}

// find warrior strength and index in vector
vector<int> search_warrior(vector<Warrior> list_of_warriors, const string& name){
  vector<int> strength_index;
  for (size_t i = 0; i < list_of_warriors.size(); i++ ){
    if (list_of_warriors[i].name == name){
      strength_index.push_back(list_of_warriors[i].strength);
      strength_index.push_back(i);

      return strength_index;
    } 
  }
  cout << "Warrior not found, returning empty vector..." << endl;
  return strength_index;
}

// compares two warriors and outputs dialogue
// 1 > 2, 1 loses 8 strength, 2 dies
void battle_time(vector<Warrior>& list_of_warriors, const string& warrior1, const string& warrior2){
  vector<int> warrior1_stats = search_warrior(list_of_warriors, warrior1);
  int warrior1_strength = warrior1_stats[0];
  int warrior1_index = warrior1_stats[1];

  vector<int> warrior2_stats = search_warrior(list_of_warriors, warrior2);
  int warrior2_strength = warrior2_stats[0];
  int warrior2_index = warrior2_stats[1];

  cout << warrior1 << " battles " << warrior2 << endl;
  if (warrior1_strength == 0 && warrior2_strength == 0){
    cout << "Oh, NO! They're both dead! Yuck!" << endl;

  } else if(warrior1_strength == 0){
    cout << "He's dead, " << warrior2 << endl;

  } else if(warrior2_strength == 0){
    cout << "He's dead, " << warrior1 << endl;

  } else if(warrior1_strength > warrior2_strength){
    cout << warrior1 << " defeats " << warrior2 << endl;
    list_of_warriors[warrior1_index].strength -= 8;
    list_of_warriors[warrior2_index].strength = 0;

  } else if(warrior1_strength < warrior2_strength){
    cout << warrior2 << " defeats " << warrior1 << endl;
    list_of_warriors[warrior2_index].strength -= 8;
    list_of_warriors[warrior1_index].strength = 0;


  } else{
    cout << "Mutual Annihilation: " << warrior1 << " and " << warrior2 << " die at each other's hands." << endl;
    list_of_warriors[warrior1_index].strength = 0;
    list_of_warriors[warrior2_index].strength = 0;


  }
}

// reads gamefile for each command and calls functions
void read_gamefile(vector<Warrior>& list_of_warriors, ifstream& gamefile){
  string word; 
  while (gamefile >> word){
    if (word == "Warrior") {
      string name; 
      gamefile >> name; 
      int strength; 
      gamefile >> strength; 

      insert_new_warrior(list_of_warriors, name, strength);
    } else if (word == "Status") {
      print_status(list_of_warriors);
    } else {
      string warrior1; 
      gamefile >> warrior1;
      string warrior2;
      gamefile >> warrior2;
      battle_time(list_of_warriors, warrior1, warrior2);
      
    }
  }
}