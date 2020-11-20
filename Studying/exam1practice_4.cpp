#include <iostream> 
#include <vector> 
using namespace std; 

struct Account {
    int acc_id; 
    int balance; 
    Account(int id, int amount = 0) : acc_id(id), balance(amount) {}

};

int main(){
    Account** accounts; 
    size_t i = 0; 

    while (i < 10){
        accounts[i] = new Account(i, (i*i));
        i++;
    }
}