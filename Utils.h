#include <iostream>
#include "RooRealVar.h"

namespace pybindgen_utils {
    std::ostream* getCout() {
        return &std::cout;
    }
    inline RooRealVar* toRooRealVar(RooAbsArg* arg){
        return (RooRealVar*) arg;
    }
}