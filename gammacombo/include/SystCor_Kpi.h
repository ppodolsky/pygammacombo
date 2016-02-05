/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#ifndef SystCor_Kpi_h
#define SystCor_Kpi_h

#include <sstream>
#include <iostream>
#include <stdlib.h>

#include "Utils.h"

using namespace std;
using namespace Utils;

class SystCor_Kpi
{
public:
    SystCor_Kpi();
    ~SystCor_Kpi();
    float getCor(TString tmkObs1, TString tmkObs2);
    
private:
    int     obsMalcolmToId(TString malcolmObs);
    TMatrixDSym* cor;
};

#endif
