//
// Created by Peter DePasquale on 10/19/20.
//

#ifndef INC_20201019PM_FROGPRINCE_H
#define INC_20201019PM_FROGPRINCE_H

#include <string>
#include <iostream>

namespace Fantasy {

    class Princess;

    class FrogPrince {
        friend std::ostream& operator<<(std::ostream& os, const FrogPrince& frog);

    public:
        explicit FrogPrince(const std::string& name);

        void setSpouse(Princess* betrothed);

    private:
        std::string name;
        Princess* spouse;
    };

}
#endif //INC_20201019PM_FROGPRINCE_H
