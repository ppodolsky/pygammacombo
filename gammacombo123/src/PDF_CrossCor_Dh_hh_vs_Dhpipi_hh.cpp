/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#include "PDF_CrossCor_Dh_hh_vs_Dhpipi_hh.h"

PDF_CrossCor_Dh_hh_vs_Dhpipi_hh::PDF_CrossCor_Dh_hh_vs_Dhpipi_hh(PDF_Abs* pdf1, PDF_Abs* pdf2, config cCor)
: PDF_CrossCorAbs(pdf1,pdf2)
{
  name = "CrossCor_Dh_hh_vs_Dhpipi_hh";
  setCorrelations(cCor);
	buildCov();
  buildPdf();
}


PDF_CrossCor_Dh_hh_vs_Dhpipi_hh::~PDF_CrossCor_Dh_hh_vs_Dhpipi_hh(){}


void PDF_CrossCor_Dh_hh_vs_Dhpipi_hh::setCorrelations(config c)
{
  resetCorrelations();
	copyMeasurementCovariance();
  switch(c)
  {
    case ckm2014:{
      corSource = "cross correlations";
			float c = 0.5;
			corSystMatrix[ 3][1+nObs1] = c;	// afav_dk_obs      : 
			corSystMatrix[ 4][1+nObs1] = c;	// afav_dpi_obs     : 
			corSystMatrix[ 5][1+nObs1] = c;	// acp_dk_kk_obs    : 
			corSystMatrix[ 6][1+nObs1] = c;	// acp_dk_pipi_obs  : 
			corSystMatrix[ 7][1+nObs1] = c;	// acp_dpi_kk_obs   : 
			corSystMatrix[ 8][1+nObs1] = c;	// acp_dpi_pipi_obs : 
			corSystMatrix[ 3][2+nObs1] = c;	// afav_dk_obs      : 
			corSystMatrix[ 4][2+nObs1] = c;	// afav_dpi_obs     : 
			corSystMatrix[ 5][2+nObs1] = c;	// acp_dk_kk_obs    : 
			corSystMatrix[ 6][2+nObs1] = c;	// acp_dk_pipi_obs  : 
			corSystMatrix[ 7][2+nObs1] = c;	// acp_dpi_kk_obs   : 
			corSystMatrix[ 8][2+nObs1] = c;	// acp_dpi_pipi_obs : 
			corSystMatrix[ 3][3+nObs1] = c;	// afav_dk_obs      : 
			corSystMatrix[ 4][3+nObs1] = c;	// afav_dpi_obs     : 
			corSystMatrix[ 5][3+nObs1] = c;	// acp_dk_kk_obs    : 
			corSystMatrix[ 6][3+nObs1] = c;	// acp_dk_pipi_obs  : 
			corSystMatrix[ 7][3+nObs1] = c;	// acp_dpi_kk_obs   : 
			corSystMatrix[ 8][3+nObs1] = c;	// acp_dpi_pipi_obs : 
			corSystMatrix[ 3][4+nObs1] = c;	// afav_dk_obs      : 
			corSystMatrix[ 4][4+nObs1] = c;	// afav_dpi_obs     : 
			corSystMatrix[ 5][4+nObs1] = c;	// acp_dk_kk_obs    : 
			corSystMatrix[ 6][4+nObs1] = c;	// acp_dk_pipi_obs  : 
			corSystMatrix[ 7][4+nObs1] = c;	// acp_dpi_kk_obs   : 
			corSystMatrix[ 8][4+nObs1] = c;	// acp_dpi_pipi_obs :
			corSystMatrix[ 3][5+nObs1] = c;	// afav_dk_obs      : 
			corSystMatrix[ 4][5+nObs1] = c;	// afav_dpi_obs     : 
			corSystMatrix[ 5][5+nObs1] = c;	// acp_dk_kk_obs    : 
			corSystMatrix[ 6][5+nObs1] = c;	// acp_dk_pipi_obs  : 
			corSystMatrix[ 7][5+nObs1] = c;	// acp_dpi_kk_obs   : 
			corSystMatrix[ 8][5+nObs1] = c;	// acp_dpi_pipi_obs : 
			corSystMatrix[ 3][6+nObs1] = c;	// afav_dk_obs      : 
			corSystMatrix[ 4][6+nObs1] = c;	// afav_dpi_obs     : 
			corSystMatrix[ 5][6+nObs1] = c;	// acp_dk_kk_obs    : 
			corSystMatrix[ 6][6+nObs1] = c;	// acp_dk_pipi_obs  : 
			corSystMatrix[ 7][6+nObs1] = c;	// acp_dpi_kk_obs   : 
			corSystMatrix[ 8][6+nObs1] = c;	// acp_dpi_pipi_obs :
      break;
		}
    default:{
      cout << "PDF_CrossCor_Dh_hh_vs_Dhpipi_hh::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }
  }
}
