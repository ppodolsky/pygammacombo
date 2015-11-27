/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#include "PDF_CrossCor_DK_hh_vs_DK_K3pi.h"

PDF_CrossCor_DK_hh_vs_DK_K3pi::PDF_CrossCor_DK_hh_vs_DK_K3pi(PDF_Abs* pdf1, PDF_Abs* pdf2, config cCor)
: PDF_CrossCorAbs(pdf1,pdf2)
{
  name = "CrossCor_DK_hh_vs_DK_K3pi";
  setCorrelations(cCor);
	buildCov();
  buildPdf();
}


PDF_CrossCor_DK_hh_vs_DK_K3pi::~PDF_CrossCor_DK_hh_vs_DK_K3pi(){}


void PDF_CrossCor_DK_hh_vs_DK_K3pi::setCorrelations(config c)
{
  resetCorrelations();
	copyMeasurementCovariance();
  switch(c)
  {
    case ckm2014:{
      corSource = "cross correlations";
			float c = 0.95;
			corSystMatrix[ 3][0+nObs1] = c;
			corSystMatrix[ 4][0+nObs1] = c;
			corSystMatrix[ 5][0+nObs1] = c;
      break;
		}
    default:{
      cout << "PDF_CrossCor_DK_hh_vs_DK_K3pi::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }
  }
}
