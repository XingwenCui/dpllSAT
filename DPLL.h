

#ifndef DPLLSAT_DPLL_H
#define DPLLSAT_DPLL_H

#include "common.h"

class DPLL {
public:
    DPLL(const formula &phi):phi(phi){} // initialize phi as phi
    bool check_sat();
    model get_model();
private:
    formula phi;
    model result;
};

#endif //DPLLSAT_DPLL_H
