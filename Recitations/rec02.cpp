#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
Task: Implement Conway's Game of Life
tc2965
Tiffany Chan
Lab 2
*/


void init_world(vector<string>& curr_gen, ofstream& outfile, const string& infile){
  // Opening the input file
  ifstream initialstate(infile);
  if (!initialstate){
    cerr << "Can't open 'life.txt'" << endl;
    exit(1);
  }

  // Write first gen into out
  outfile << "INITIAL STATE" << endl;
  string line;
  while (initialstate >> line){
    curr_gen.push_back(line);
    outfile << line << endl;
  }

  outfile << "=========================" << endl;
  initialstate.close();
}

int count_neighbors(vector<string>& curr_gen, size_t& x, size_t& y){
  int neighbors = 0;
  if (curr_gen[x-1][y-1] == '*'){
    neighbors += 1;
  }
  if (curr_gen[x-1][y] == '*') {
    neighbors += 1;
  }
  if (curr_gen[x-1][y+1] == '*'){
    neighbors += 1;
  }

  if (curr_gen[x][y-1] == '*'){
    neighbors += 1;
  }
  if (curr_gen[x][y+1] == '*'){
    neighbors += 1;
  }

  if (curr_gen[x+1][y-1] == '*'){
    neighbors += 1;
  }
  if (curr_gen[x+1][y] == '*'){
    neighbors += 1;
  }
  if (curr_gen[x+1][y+1] == '*'){
    neighbors += 1;
  }

  return neighbors;

  /* if (1, 1), check (0,0), (0,1), (0,2)
                      (1,0), >(1,1)< , (1,2)
                      (2,0), (2,1), (2,2)

  check, ()
  */
}

void changeChar(char& c, int x, int y, int n){
  if (!(n == 2 || n == 3)){
    if (c == '*'){
    c = '-';
  }
  } else{
    if (n == 3){
    c = '*';
  }
}
}

void display_outfile(const string& name){
  ifstream displayfile(name);
  string line;
  while(getline(displayfile,line)){
    cout << line << endl;
  }
  displayfile.close();
}

int main(){
  // Constants
  vector<string> curr_gen;
  vector<string> next_gen;


  //opens initial state, push into curr
  ofstream outfile("outputfile.txt");
  init_world(curr_gen, outfile,"life.txt");

  next_gen = curr_gen;

  // Compute 10 generations
  for(int gen = 1; gen <= 10; gen++){
    outfile << "GENERATION " << gen << endl;
    for(size_t x = 0; x < curr_gen.size(); x++){
      for(size_t y = 0; y < curr_gen[x].size(); y++){
        int n;
        n = count_neighbors(curr_gen,x,y);
        changeChar(next_gen[x][y],x,y,n);
        }
      }

    // Write each gen into outfile
    for(string line : next_gen){
      outfile << line << endl;
    }

  curr_gen = next_gen;
  next_gen = curr_gen;

  outfile << "=========================" << endl;
}

  outfile.close();

  cout << "DISPLAYING GENERATIONS IN TERMINAL" << endl;
  display_outfile("outputfile.txt");

}
