/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#include "PDF_CrossCor_DK_KSKpi_vs_Dhpipi_hh.h"

PDF_CrossCor_DK_KSKpi_vs_Dhpipi_hh::PDF_CrossCor_DK_KSKpi_vs_Dhpipi_hh(PDF_Abs* pdf1, PDF_Abs* pdf2, config cCor)
: PDF_CrossCorAbs(pdf1,pdf2)
{
  name = "CrossCor_DK_KSKpi_vs_Dhpipi_hh";
  setCorrelations(cCor);
	buildCov();
  buildPdf();
}


PDF_CrossCor_DK_KSKpi_vs_Dhpipi_hh::~PDF_CrossCor_DK_KSKpi_vs_Dhpipi_hh(){}


void PDF_CrossCor_DK_KSKpi_vs_Dhpipi_hh::setCorrelations(config c)
{
  resetCorrelations();
	copyMeasurementCovariance();
  switch(c)
  {
    case ckm2014:{
      corSource = "cross correlations";
			float c = 0.95;
			corSystMatrix[ 1][1+nObs1] = c;	// 
			corSystMatrix[ 2][1+nObs1] = c;	// 
			corSystMatrix[ 1][2+nObs1] = c;	// 
			corSystMatrix[ 2][2+nObs1] = c;	// 
			corSystMatrix[ 1][3+nObs1] = c;	// 
			corSystMatrix[ 2][3+nObs1] = c;	// 
			corSystMatrix[ 1][4+nObs1] = c;	// 
			corSystMatrix[ 2][4+nObs1] = c;	//
			corSystMatrix[ 1][5+nObs1] = c;	// 
			corSystMatrix[ 2][5+nObs1] = c;	//
			corSystMatrix[ 1][6+nObs1] = c;	// 
			corSystMatrix[ 2][6+nObs1] = c;	//
      break;
		}
    default:{
      cout << "PDF_CrossCor_DK_KSKpi_vs_Dhpipi_hh::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }
  }
}
