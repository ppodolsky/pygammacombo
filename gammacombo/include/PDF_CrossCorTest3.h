/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#ifndef PDF_CrossCorTest3_h
#define PDF_CrossCorTest3_h

#include "RooGenericPdf.h"
#include "PDF_Abs.h"
#include "PDF_CrossCorAbs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_CrossCorTest3 : public PDF_CrossCorAbs
{
public:
  PDF_CrossCorTest3(PDF_Abs* pdf1, PDF_Abs* pdf2, config cCor=lumi1fb);
  ~PDF_CrossCorTest3();
  void          setCorrelations(config c);
};

#endif
