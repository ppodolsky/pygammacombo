/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#ifndef PDF_CrossCor_DK_hh_vs_DKpipi_hh_h
#define PDF_CrossCor_DK_hh_vs_DKpipi_hh_h

#include "RooGenericPdf.h"
#include "PDF_Abs.h"
#include "PDF_CrossCorAbs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_CrossCor_DK_hh_vs_DKpipi_hh : public PDF_CrossCorAbs
{
public:
  PDF_CrossCor_DK_hh_vs_DKpipi_hh(PDF_Abs* pdf1, PDF_Abs* pdf2, config cCor=lumi1fb);
  ~PDF_CrossCor_DK_hh_vs_DKpipi_hh();
  void          setCorrelations(config c);
};

#endif
