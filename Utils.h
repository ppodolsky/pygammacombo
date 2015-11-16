#include <iostream>
#include <string>
#include "gammacombo.h"
#include "RooRealVar.h"

std::vector<char*> &split(const std::string &s, char delim, std::vector<char*> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        char *cstr = new char[item.length() + 1];
        strcpy(cstr, item.c_str());
        elems.push_back(cstr);
    }
    return elems;
}

std::vector<char*> split(const std::string &s, char delim) {
    std::vector<char*> elems;
    split(s, delim, elems);
    return elems;
}

namespace gammacombo_utils {
    inline std::ostream* getCout() {
        return &std::cout;
    }
    inline RooRealVar* toRooRealVar(RooAbsArg* arg){
        return (RooRealVar*) arg;
    }
    GammaComboEngine& getGammaComboEngine(const char* argv_str){
        std::string argv_full_str("gammacombo ");
        argv_full_str += argv_str;
        std::vector<char*> argv = split(argv_full_str, ' ');
        return loadMainGammaComboEngine(argv.size(), &argv[0]);
    }
}