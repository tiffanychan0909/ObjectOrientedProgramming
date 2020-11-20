#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/* 
Read, store, and sort hydrocarbon entries
Tiffany Chan 
tc2965
Lab 3
*/


struct Hydrocarbon{
  vector<string> Names;
  int Carbons;
  int Hydrogens;
};

void openfile(ifstream& chemfile);
void fill_hcarbon_vector(ifstream& chemfile, vector<Hydrocarbon>& hcarbons);
void insert_info_into_vector(int carb, int hydro, string& name, vector<Hydrocarbon>& hcarbons);
int inVector(int carb, int hydro, const vector<Hydrocarbon>& hcarbons);
void insertionsort_hcarbon_vector(vector<Hydrocarbon>& hcarbons);
void display_vector(const vector<Hydrocarbon>& hcarbons);

int main(){
  // Define vars for the stream and vector
  ifstream chemfile;
  openfile(chemfile);

  vector<Hydrocarbon> hcarbons;
  fill_hcarbon_vector(chemfile, hcarbons);

  insertionsort_hcarbon_vector(hcarbons);

  display_vector(hcarbons);
}

// displays vector, concatenate int and string for c#h#
void display_vector(const vector<Hydrocarbon>& hcarbons){
  string chemname;
  for(size_t i = 0; i < hcarbons.size(); i++){
    chemname = "C" + to_string(hcarbons[i].Carbons) + "H" + to_string(hcarbons[i].Hydrogens);
    cout << chemname << " ";
    for (size_t j = 0; j < hcarbons[i].Names.size(); j++){
      cout << hcarbons[i].Names[j] << " ";
    }
    cout << endl;
  }
}

// insertion sort the vector of hydrocarbons
void insertionsort_hcarbon_vector(vector<Hydrocarbon>& hcarbons){
  int i; 
  int j; 
  Hydrocarbon key;

  for (i = 1; i < hcarbons.size(); i++){
    key = hcarbons[i];
    j = i - 1;

    while (j >= 0 && (hcarbons[j].Carbons >= key.Carbons) ){
      hcarbons[j+1] = hcarbons[j];
      j -= 1;
    }
    hcarbons[j+1] = key;
  }
}

// open the file
void openfile(ifstream& chemfile){
  string filename;
  do {
    cout << "Enter text file name: "<< endl;
    cin >> filename;
    chemfile.open(filename);
  }  while (!chemfile);
  cout << endl;
}

// fill the hydrocarbon vector
void fill_hcarbon_vector(ifstream& chemfile, vector<Hydrocarbon>& hcarbons){
  string name;
  int hydro;
  int carb;
  char s;

  while (chemfile >> name >> s >> carb >> s >> hydro){
    insert_info_into_vector(carb, hydro, name, hcarbons);
  }
}

//insert the info into vector, checks if exists first
void insert_info_into_vector(int carb, int hydro, string& name, vector<Hydrocarbon>& hcarbons){
    if (inVector(carb, hydro, hcarbons) == -1){
      Hydrocarbon current;
      current.Carbons = carb;
      current.Hydrogens = hydro;
      current.Names.push_back(name);

      hcarbons.push_back(current);
   } else{
      hcarbons[inVector(carb, hydro, hcarbons)].Names.push_back(name);
   }
}

// finds and returns index of hydrocarbon if it exists, -1 if it doesn't
int inVector(int carb, int hydro, const vector<Hydrocarbon>& hcarbons){
  for (size_t i = 0; i < hcarbons.size(); i ++){
    if (carb == hcarbons[i].Carbons && hydro == hcarbons[i].Hydrogens){
      return i;
    }
  }
  return -1;
}
