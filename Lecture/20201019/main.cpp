#include "Princess.h"
#include "FrogPrince.h"

using namespace std;
using namespace Fantasy;

int main() {
    Princess snowy("Snow White");
    FrogPrince froggy("Aquaman");
    cout << snowy << endl
         << froggy << endl;

    snowy.marries(froggy);
    cout << snowy << endl
         << froggy << endl;
}
