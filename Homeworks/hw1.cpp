// hw1.cpp
// Tiffany Chan
// tc2965
// Caesar cypher decryption algorithm

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// if char is lower, will go back in the alphabet.
// Parameters take a char from DecryptString and distance.
// returns the correct character.
char DecryptChar(char decrypted_chr, int distance){
  if (decrypted_chr >= 'a' && decrypted_chr <= 'z'){
    decrypted_chr -= distance;
    if (decrypted_chr < 'a'){
      decrypted_chr += 26;
    }
  }
  return decrypted_chr;
}

// changes each character in the string.
// Parameters take string from main function and the distance to pass into DecryptChar.
void DecryptString(string& str, int distance){
  for(size_t i = 0; i < str.size(); i++){
    str[i] = DecryptChar(str[i], distance);
  }
}

int main(){
  // opens file, pushes into vector, decrypts vector with functions
  ifstream encryptedFile("encrypted.txt");
  if (!encryptedFile){
    cerr << "Can't open encrypted.txt" << endl;
    exit(1);
  }

  int distance;
  encryptedFile >> distance;

  string word;
  vector<string> encrypted_words;

  while (getline(encryptedFile, word)){
    encrypted_words.push_back(word);
  }
  encryptedFile.close();

  for(size_t i = 0; i < encrypted_words.size(); i++){
    string line = encrypted_words[encrypted_words.size()-1-i];
    DecryptString(line,distance);
    cout << line << endl;
  }
}
