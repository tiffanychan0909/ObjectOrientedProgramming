/*
  Tiffany Chan
  rec04.cpp
  Lab 4
  Bank Account and Transaction Classes

 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// All ostream operator overload at the bottom

// Task 1
// Define an Account struct

struct Account{
    string name; 
    int balance;
};

// Task 2
// Define an Account class
class Account2{
  friend ostream& operator<<(ostream& os, const Account2& acc);
  // "Add an output operator for your class, don't make it a friend"
  // ostream& operator<<(ostream& os, const Account2& acc){
  //   os << acc.name << " has $" << acc.balance; 
  //   return os;
  // }

  public: 
    Account2(const string& name, int balance) : name(name), balance(balance) {}

    string getname() const {return name;}

    int getbal() const {return balance;}
  private:
    string name; 
    int balance;
};


// Task 3
// Define an Account and Transaction classes

class Transaction{
  friend ostream& operator<<(ostream& os, const Transaction& transaction);
  public:
    Transaction(const string& type, int money) : type(type), money(money) {}

    string gettype(){return type;}

    int getmoney(){return money;}

  private:
    string type; 
    int money;
};
class Account3{
  friend ostream& operator<<(ostream& os, const Account3& acc);
  public:
    Account3(const string& name, int balance) : name(name), balance(balance) {}

    void updatebalance(string& type, int money){
      if (type == "Withdraw"){
        if (money > balance){
          cout << "Can't withdraw more than your balance, " << name << endl;
        } else{
          balance -= money;
        }
      } else{
        balance += money;
        updatehistory(type, money);
      }
    }

    void updatehistory(string& type, int money){
      history.emplace_back(Transaction(type, money));
    }
    
    string getname() const {return name;}

    int getbalance() const {return balance;}

  private:
    vector<Transaction> history;
    string name; 
    int balance;
};

// Task 4
// Define an Account with a nested public Transaction class

class Account4{
  friend ostream& operator<<(ostream& os, Account4& acc);
  public: 
    class Transaction{
      friend ostream& operator<<(ostream& os, Transaction& transaction);
      public: 
        Transaction(const string& type, int money) : type(type), money(money) {}
        string gettransaction(){return type;}
        int getmoney(){return money;}
      
      private: 
        string type; 
        int money;
    };

  Account4(const string& name, int balance) : name(name), balance(balance) {}
  string getname(){return name;};
  int getbalance(){return balance;}
  vector<Transaction> gethistory(){return history;}

  void withdraw(int money){
    if (money > balance){
      cout << "Can't take out more than your balance, " << name << endl;
    } else{
      balance -= money;
    }
  }

  void deposit(int money){
    balance += money;
  }
  void updatehistory(string& type, int money){
    history.emplace_back(Transaction(type,money));
  }
  
  private: 
    string name; 
    int balance; 
    vector<Transaction> history; 
};

// Task 5
// Define an Account with a nested private Transaction class
class Account5{
  class Transaction;
  friend ostream& operator<<(ostream& os, Account5::Transaction& transaction);
  friend ostream& operator<<(ostream& os, Account5& acc);
  public: 
    Account5(const string& name, int balance) : name(name), balance(balance) {}
    string getname(){return name;};
    int getbalance(){return balance;}
    void withdraw(int money){
      if (money > balance){
        cout << "Can't take out more than your balance" << endl;
      } else{
        balance -= money;
      }
    }
    void deposit(int money){
      balance += money;
    }
    void updatehistory(string& type, int money){
      history.emplace_back(Transaction(type,money));
    }

  
  private: 
    class Transaction{
      friend ostream& operator<<(ostream& os, Account5::Transaction& transaction);

      public: 
        Transaction(const string& type, int money) : type(type), money(money) {}
        string gettransaction(){return type;}
        int getmoney(){return money;}
      
      private: 
        string type; 
        int money;
    };
    string name; 
    int balance; 
    vector<Transaction> history; 
};

// No prototypes, everything is in main 
// Operator overload prototypes in classes

int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";
    ifstream accountfile("accounts.txt");
    string name; 
    int bal; 
    vector<Account> accounts_vector;
    while (accountfile >> name >> bal){
      Account NewAccount;
      NewAccount.name = name; 
      NewAccount.balance = bal; 

      accounts_vector.push_back(NewAccount);
    }

    accountfile.close();
    for (Account a : accounts_vector){
      cout << a.name << ": " << a.balance << endl;
    }

    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";
    accounts_vector.clear(); 
    accountfile.open("accounts.txt");
    while (accountfile >> name >> bal){
      Account NewAccount{name,bal};
      accounts_vector.push_back(NewAccount);
    }

    accountfile.close();
    for (Account a : accounts_vector){
      cout << a.name << ": " << a.balance << endl;
    }

    //==================================
    // Task 2: account as class
    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";

    vector<Account2> classAccountVector;
    accountfile.open("accounts.txt");
    while (accountfile >> name >> bal){
      Account2 NewAccount(name,bal); 
      classAccountVector.push_back(NewAccount);
    }
    accountfile.close();

    cout << "\nTask2b:\n";
    for (Account2& c : classAccountVector){
      cout << c << endl;
    }

    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    for (Account2& c : classAccountVector){
      cout << c << endl;
    }
    cout << "output using output operator with getters\n";
    for (Account2& b : classAccountVector){
        cout << b.getname() << b.getname() << endl;
    }

    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";
    classAccountVector.clear();
    accountfile.open("accounts.txt");
    while (accountfile >> name >> bal){
      classAccountVector.push_back(Account2(name,bal));
    }
    for (Account2& c : classAccountVector){
      cout << c << endl;
    }
    accountfile.close();

    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";
    classAccountVector.clear();
    accountfile.open("accounts.txt");
    while (accountfile >> name >> bal){
      classAccountVector.emplace_back(Account2(name,bal));
    }
    for (Account2& c : classAccountVector){
      cout << c << endl;
    }
    accountfile.close();

    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";

    ifstream transactionfile("transactions.txt");
    string type; 
    int money; 
    int index3 = -1;
    vector<Account3> accounts3_class;
    while (transactionfile >> type){
      if (type == "Account"){
        transactionfile >> name >> bal;
        accounts3_class.emplace_back(Account3(name,bal));
        index3 += 1;
      } else{
        transactionfile >> bal >> money;
        Transaction curr(type, money);
        accounts3_class[index3].updatebalance(type,money);
      }
    }

    for (Account3& a : accounts3_class){
      cout << a << endl;
    }
    transactionfile.close();

    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";

    transactionfile.open("transactions.txt");
    int balance; 
    vector<Account4> accounts4_class;
    int index4 = -1;

    while (transactionfile >> type){
      if (type == "Account"){
        transactionfile >> name >> balance; 
        accounts4_class.emplace_back(Account4(name,balance));
        index4 += 1;

      } else if (type == "Withdraw"){
        transactionfile >> balance >> money;
        if (money < balance){
          accounts4_class[index4].withdraw(money);
          accounts4_class[index4].updatehistory(type,money);
        }
      } else{
        transactionfile >> balance >> money;
        accounts4_class[index4].deposit(money);
        accounts4_class[index4].updatehistory(type,money);
      }
    }

    for (Account4& a : accounts4_class){
      cout << a << endl;
    }

    transactionfile.close();

    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";

    transactionfile.open("transactions.txt");
    vector<Account5> account5_class; 
    int index5 = -1;

    while (transactionfile >> type){
      if (type == "Account"){
        transactionfile >> name >> balance; 
        account5_class.emplace_back(Account5(name,balance));
        index5 += 1;

      } else if (type == "Withdraw"){
        transactionfile >> balance >> money;
        if (money < balance){
          account5_class[index5].withdraw(money);
          account5_class[index5].updatehistory(type,money);
        }
      } else{
        transactionfile >> balance >> money;
        account5_class[index5].deposit(money);
        account5_class[index5].updatehistory(type,money);
      }
    }

    for (Account5& b : account5_class){
      cout << b << endl;
    }

    transactionfile.close();
}


ostream& operator<<(ostream& os, const Account2& acc){
  os << acc.name << "'s Balance: $" << acc.balance; 
  return os;
}

ostream& operator<<(ostream& os, const Account3& acc){
  os << acc.getname() << "'s Balance: $" << acc.getbalance() << "\n";
  os << acc.name << "'s Transaction History\n";
  for (Transaction t : acc.history){
    cout << t << endl;
  }
  return os;
}
ostream& operator<<(ostream& os, Account4& acc){
  os << acc.getname() << "'s Balance: $" << acc.getbalance() << endl;
  os << acc.name << "'s Transaction History\n";
  for (Account4::Transaction& t : acc.gethistory()){
    os << t << endl;
  }
  return os;
}

ostream& operator<<(ostream& os, Account4::Transaction& transaction){
  os << transaction.gettransaction() << ": $" << transaction.getmoney();
  return os;
}

ostream& operator<<(ostream& os, const Transaction& transaction){
  os << transaction.type << ": $" << transaction.money;
  return os;
}

ostream& operator<<(ostream& os, Account5& acc){
  os << acc.name << "'s Transaction History\n";
  os << acc.getname() << "'s Balance: $" << acc.getbalance() << endl;
  for (Account5::Transaction& t : acc.history){
    os << t << endl;
  }
  return os;
}

ostream& operator<<(ostream& os, Account5::Transaction& transaction){
  os << transaction.type << ": $" << transaction.money;
  return os;
}