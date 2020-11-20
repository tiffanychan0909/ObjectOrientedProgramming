#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main(){
  // ---- OUTPUT ----
  // 1)
  std::cout << "What Includes Were Needed?" << std::endl;
  // - "<<", "std::", and "cout" were needed
  // - Main returns 0
  // 2)
  cout << "What Includes Were Needed?" << endl;
  // - This simplifies the main function because it does not require us to repeatedly type std::
  cout << "What Includes Were Needed?\n";

  // ---- STATIC TYPING ----
  // 3)
  int x;
  cout << "x: " << x << endl;

  // 4)
  int y = 17;
  int z = 2000000017;
  double pie = 3.14159;
  cout << y << " "  << z << " " << pie << endl;

  cout << "size of x is " << sizeof(x) << endl;
  cout << "size of y is " << sizeof(y) << endl;
  cout << "size of z is " << sizeof(z) << endl;
  cout << "size of pie is " << sizeof(pie) << endl;

  // 5)
  // x = "felix"
  // - "Assigning to 'int' from incompatible type 'const char [6]'"
  // - Compilation error


  // 6)
  if (y >= 10 && y <= 20) {
    cout << "y is between 10 and 20" << endl;
  }
  else if (y < 10) {
    cout << "y is less than 10" << endl;
  }
  else{
    cout << "y is greater than 20" << endl;
  }

  // ---- LOOPING ----
  // 7)

  for (int x = 10; x < 21; x ++){
    cout << x << " ";
  }

  cout << endl;

  x = 10;
  while (x < 21){
    cout << x << " ";
    x++ ;
  }

  cout << endl;

  x = 10;
  do {
    cout << x << " ";
    x++;
  }
  while (x < 21);

  cout << endl;

  // 8)
  ifstream MyFile;
  string filename;
  do {
    cout << "Enter file name: ";
    cin >> filename;
    MyFile.open(filename);

    if(!MyFile){
      cerr << "Can't open " << filename << endl;
    }
  }
  while (!MyFile);

  // 9)
  string word;
  while (MyFile >> word){
    cout << word << endl;
  }
  MyFile.close();



  // ---- VECTOR ----
  // 10)
  vector<int> IntVector;
  for (int x = 10; x < 101; x+=2) {
    IntVector.push_back(x);

  }

  // 11)
  for (size_t i = 0; i < IntVector.size(); i++){
    cout << IntVector[i] << " ";
  }

  cout << endl;

  for (int e : IntVector) {
    cout << e << " ";
  }

  cout << endl;

  // reversed
  for (size_t i = 0; i < IntVector.size(); i++){
    cout << IntVector[IntVector.size() - i - 1] << " ";
  }

  cout << endl;

  // 12)
  vector<int> PrimeVector{ 2, 3, 5, 7, 11, 13, 17, 19 };
  for (int m : PrimeVector){
    cout << m << endl;
  }




}
