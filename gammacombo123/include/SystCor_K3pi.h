/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef SystCor_K3pi_h
#define SystCor_K3pi_h

#include <sstream>
#include <iostream>
#include <stdlib.h>

#include "Utils.h"

using namespace std;
using namespace Utils;

class SystCor_K3pi
{
public:
    SystCor_K3pi();
    ~SystCor_K3pi();
    float getCor(TString tmkObs1, TString tmkObs2);
    
private:
    int     obsMalcolmToId(TString malcolmObs);
    TMatrixDSym* cor;
};

#endif
