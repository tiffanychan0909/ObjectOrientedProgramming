#include <iostream> 
using namespace std;

// boring if i == parity of elem

int findcases(int l, int r){
  int t = 0;
  int p = 1;
  for (int i = l; i <= r; i++){
    if ((i%2 != 0) && (p%2 != 0)){
      t++; 
    } else if((i%2 == 0) && (p%2 == 0)){
      t++;
    }
    p++;
  }
  return t;
}

int main(){
    int cases; 
    cin >> cases; 
    int l, r; 
    for (int i = 1; i <= cases; i ++){
      cin >> l >> r; 
      cout << "Case #" << i << ": "; 
      cout << findcases(l, r) << endl;
    }
}