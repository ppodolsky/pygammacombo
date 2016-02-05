/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: July 2014
 *
 **/

#include "PDF_CrossCorTest3.h"

PDF_CrossCorTest3::PDF_CrossCorTest3(PDF_Abs* pdf1, PDF_Abs* pdf2, config cCor)
: PDF_CrossCorAbs(pdf1,pdf2)
{
  name = "CrossCorTest3";
  setCorrelations(cCor);
	buildCov();
  buildPdf();
}


PDF_CrossCorTest3::~PDF_CrossCorTest3(){}


void PDF_CrossCorTest3::setCorrelations(config c)
{
  resetCorrelations();
	copyMeasurementCovariance();
  switch(c)
  {
    case lumi1fbPapercFit:{
      corSource = "cross correlations";
			corStatMatrix[0][3] = -0.084;	// c_dsk_obs	: d_dsk_obs
			corStatMatrix[0][4] = -0.103;	// c_dsk_obs	: db_dsk_obs
			corStatMatrix[1][3] =  0.117;	// s_dsk_obs	: d_dsk_obs
			corStatMatrix[1][4] =  0.067;	// s_dsk_obs	: db_dsk_obs
			corStatMatrix[2][3] = -0.022;	// sb_dsk_obs	: d_dsk_obs
			corStatMatrix[2][4] = -0.032;	// sb_dsk_obs	: db_dsk_obs
			corSystMatrix[0][3] = -0.22;	// c_dsk_obs	: d_dsk_obs
			corSystMatrix[0][4] = -0.22;	// c_dsk_obs	: db_dsk_obs
			corSystMatrix[1][3] =  0.17;	// s_dsk_obs	: d_dsk_obs
			corSystMatrix[1][4] =  0.17;	// s_dsk_obs	: db_dsk_obs
			corSystMatrix[2][3] = -0.14;	// sb_dsk_obs	: d_dsk_obs
			corSystMatrix[2][4] = -0.14;	// sb_dsk_obs	: db_dsk_obs
      break;
		}
    default:{
      cout << "PDF_CrossCorTest3::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
      exit(1);
    }
  }
}
