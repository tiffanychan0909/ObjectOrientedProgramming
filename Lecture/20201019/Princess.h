//
// Created by Peter DePasquale on 10/19/20.
//

#ifndef INC_20201019PM_PRINCESS_H
#define INC_20201019PM_PRINCESS_H

#include <string>
#include <iostream>

namespace Fantasy {

    class FrogPrince;

    class Princess {
        friend std::ostream& operator<<(std::ostream& os, const Princess& princess);

    public:
        explicit Princess(const std::string& name);

        void marries(FrogPrince& betrothed);

        const std::string& getName() const;

    private:
        std::string name;
        FrogPrince* spouse;
    };
}
#endif //INC_20201019PM_PRINCESS_H
