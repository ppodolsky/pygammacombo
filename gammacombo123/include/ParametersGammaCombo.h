/**
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: April 2013
 *
 * Abstract class to define the (nuisance) parameters:
 * Gamma Combination
 *
 **/

#ifndef ParametersGammaCombo_h
#define ParametersGammaCombo_h

#include "ParametersAbs.h"
#include "OptParser.h"
#include "Utils.h"

using namespace std;
using namespace Utils;

class ParametersGammaCombo : public ParametersAbs
{
public:
    ParametersGammaCombo();
    inline ~ParametersGammaCombo(){};
    
protected:
    void defineParameters();
};

#endif
