/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#ifndef PDF_CrossCor_Dh_hh_vs_Dh_K3pi_h
#define PDF_CrossCor_Dh_hh_vs_Dh_K3pi_h

#include "RooGenericPdf.h"
#include "PDF_Abs.h"
#include "PDF_CrossCorAbs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_CrossCor_Dh_hh_vs_Dh_K3pi : public PDF_CrossCorAbs
{
public:
  PDF_CrossCor_Dh_hh_vs_Dh_K3pi(PDF_Abs* pdf1, PDF_Abs* pdf2, config cCor=lumi1fb);
  ~PDF_CrossCor_Dh_hh_vs_Dh_K3pi();
  void          setCorrelations(config c);
};

#endif
