#include <vector>
#include <iostream>
using namespace std;

class Instrument{
public:
    virtual void makeSound() const = 0;

private:

};
void Instrument::makeSound() const {
    cout << "To make a sound... ";
}

class Brass : public Instrument{
public:
    Brass(unsigned int mouthpiece_size) : mouthpiece(mouthpiece_size) {}
    void makeSound() const{
        Instrument::makeSound();
        cout << "blow on mouthpiece of size " << mouthpiece << endl;
    }

private:
    unsigned int mouthpiece;

};

class Trumpet : public Brass{
    using Brass::Brass;
};
class Trombone : public Brass{
    using Brass::Brass;
};

class String : public Instrument{
public:
    String(unsigned int pitch) : pitch(pitch) {}
    void makeSound() const{
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }
private:
    unsigned int pitch;

};

class Violin : public String{
    using String::String;
};
class Cello : public String{
    using String::String;
};


class Percussion : public Instrument{
public:
    void makeSound() const{
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }

private: 
};

class Drum : public Percussion{
    using Percussion::Percussion;
};
class Cymbal : public Percussion{
    using Percussion::Percussion;
};

class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() { 
        Instrument* result(instr); 
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound(); 
        else cerr << "have no instr\n";
    }

private:
    Instrument* instr;
};

class Orch{
    
};

class MILL{
public:
    void receiveInstr(Instrument& instrument){
        instrument.makeSound();
        for (Instrument*& instr : inventory){
            if (!instr){
                instr = &instrument;
                return;
            }
        }

        inventory.emplace_back(&instrument);
    }

    Instrument* loanOut(){
        Instrument* out;
        for (size_t i = 0; i < inventory.size(); i ++){
            if (inventory[i]){
                out = inventory[i];
                inventory[i] = nullptr;
                return out;
            }
        }
        return nullptr;
    }

    void dailyTestPlay() const{
        for (Instrument* instr : inventory){
            instr->makeSound();
        }
    }

private: 
    vector<Instrument*> inventory;

};


// PART ONE
int main() {
    cout << "Define some instruments ------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    // use the debugger to look at the mill
    cout << "Define the MILL --------------------------------------------\n";
    MILL mill;
  
    cout << "Put the instruments into the MILL --------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
  
    cout << "Daily test -------------------------------------------------\n";
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians---------------------------------------\n";
    Musician harpo;
    Musician groucho;
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	
    cout << endl;
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << endl << endl;
  
    groucho.testPlay();	
    cout << endl;
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    harpo.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
  
    // fifth
    mill.receiveInstr(*groucho.giveBackInstr());
    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());

  
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << endl;
}