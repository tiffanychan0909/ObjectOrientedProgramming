#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned int numPages) : numOfPages(numPages) {}
    
    virtual void displayNumPages() const = 0;
    int getVolume() {return this->numOfPages;}

private:
    unsigned int numOfPages;
};

void PrintedMaterial::displayNumPages() const { 
    cout << numOfPages << endl; 
}

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned int numPages) : PrintedMaterial(numPages) {}
    // void displayNumPages() const override { cout << PrintedMaterial::getVolume() << endl; } 
    void displayNumPages() const override { cout << "This is a magazine object" << endl; }

private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned int numPages) : PrintedMaterial(numPages) {}
    void displayNumPages() const override { cout << "This is a book object" << endl; }

private:
};

class TextBook : public Book {
public:
    TextBook(unsigned int numPages, unsigned int numIndxPgs) : Book(numPages), numOfIndexPages(numIndxPgs){}
    void displayNumPages() const override{
        cout << "Pages: ";
        PrintedMaterial::displayNumPages();
        cout << "Index pages: ";
        cout << numOfIndexPages << endl; 
    }
private:
    unsigned int numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned int numPages): Book(numPages) {}
    void displayNumPages() const override { cout << "This is a novel object" << endl; }

private:
};

void displayNumberOfPages(const PrintedMaterial& pm){
    pm.displayNumPages();
}

// tester/modeler code
int main() {
    TextBook text(5430, 23);
    Novel novel(213);
    Magazine mag(6);

    text.displayNumPages();
    novel.displayNumPages();
    mag.displayNumPages();
    cout << "===========\n";

    cout << "\nA PrintedMaterial material object!\n";
    PrintedMaterial pm(2345); // not allowed anymore bc abstract
    pm.displayNumPages();

    cout << "\nA PrintedMaterial variable containing a TextBook value\n";
    pm = text; // like putting a Textbook into a PrintedMaterial
    pm.displayNumPages();
    // slicing: derived assigned to base, but not other way around, only base attributes
    // doesn't display index bc it points to a derived class
    // when doing this, you get the base class unless display is virtual in base (done)

    cout << "pmPtr points to sliced pm" << endl;

    PrintedMaterial* pmPtr;
    pmPtr = &text;
    pmPtr->displayNumPages();
    

    // Storing generic objects in a vector 
    cout << "\n\nNow we'll use a container. Yea!!!\n\n";
    vector< PrintedMaterial* > allThemPrinties;
    allThemPrinties.push_back(&text);
    allThemPrinties.push_back(&novel);
    allThemPrinties.push_back(&mag);
    for(size_t ndx=0; ndx < allThemPrinties.size(); ++ ndx) {
        allThemPrinties[ndx]->displayNumPages();
        cout << endl;
    }
    cout << "===========\n";
    for (const PrintedMaterial* pmPtr : allThemPrinties) {
        pmPtr->displayNumPages();
        cout << endl;
    }

}