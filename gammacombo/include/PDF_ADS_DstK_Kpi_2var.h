/**
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 * Class to describe observed measurements in
 * GLW decays which measure only 2 variables
 * e.g. ala LHCb GLW analyses which measure A_{CP+}, R_{CP+}
 *
 **/

#ifndef PDF_ADS_DstK_Kpi_2var_h
#define PDF_ADS_DstK_Kpi_2var_h

#include "PDF_Abs.h"
#include "ParametersGammaCombo.h"

using namespace RooFit;
using namespace std;
using namespace Utils;

class PDF_ADS_DstK_Kpi_2var : public PDF_Abs
{
public:
  PDF_ADS_DstK_Kpi_2var(config cObs=lhcb, config cErr=lhcb, config cCor=lhcb);
  ~PDF_ADS_DstK_Kpi_2var();
  void          buildPdf();
  void          initObservables();
  virtual void  initParameters();
  virtual void  initRelations();
  void          setCorrelations(config c);
  void          setObservables(config c);
  void          setUncertainties(config c);
};

#endif
