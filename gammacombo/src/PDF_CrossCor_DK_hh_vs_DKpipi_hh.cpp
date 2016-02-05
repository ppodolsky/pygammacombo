/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#include "PDF_CrossCor_DK_hh_vs_DKpipi_hh.h"

PDF_CrossCor_DK_hh_vs_DKpipi_hh::PDF_CrossCor_DK_hh_vs_DKpipi_hh(PDF_Abs* pdf1, PDF_Abs* pdf2, config cCor)
: PDF_CrossCorAbs(pdf1,pdf2)
{
  name = "CrossCor_DK_hh_vs_DKpipi_hh";
  setCorrelations(cCor);
	buildCov();
  buildPdf();
}


PDF_CrossCor_DK_hh_vs_DKpipi_hh::~PDF_CrossCor_DK_hh_vs_DKpipi_hh(){}


void PDF_CrossCor_DK_hh_vs_DKpipi_hh::setCorrelations(config c)
{
  resetCorrelations();
	copyMeasurementCovariance();
  switch(c)
  {
    case ckm2014:{
      corSource = "cross correlations";
			float c = 0.95;
			corSystMatrix[ 3][1+nObs1] = c;	
			corSystMatrix[ 4][1+nObs1] = c;	
			corSystMatrix[ 5][1+nObs1] = c;	
			corSystMatrix[ 3][2+nObs1] = c;	
			corSystMatrix[ 4][2+nObs1] = c;	
			corSystMatrix[ 5][2+nObs1] = c;	
			corSystMatrix[ 3][3+nObs1] = c;	
			corSystMatrix[ 4][3+nObs1] = c;	
			corSystMatrix[ 5][3+nObs1] = c;	
      break;
		}
    default:{
      cout << "PDF_CrossCor_DK_hh_vs_DKpipi_hh::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }
  }
}
