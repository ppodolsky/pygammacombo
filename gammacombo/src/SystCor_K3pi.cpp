#include "SystCor_K3pi.h"

SystCor_K3pi::SystCor_K3pi()
{
  // build a map from Malcolm's code
  // defined in gammadini Bu2D0H_D02KPIPIPI.C
  const double data[49] = {  1.00,  0.86, -0.00, -0.03, -0.23, -0.12,  0.11,
                             0.86,  1.00, -0.01,  0.04, -0.03, -0.05, -0.02,
                            -0.00, -0.01,  1.00, -0.31, -0.15, -0.14, -0.32,
                            -0.03,  0.04, -0.31,  1.00,  0.53,  0.42,  0.56,
                            -0.23, -0.03, -0.15,  0.53,  1.00,  0.81,  0.68,
                            -0.12, -0.05, -0.14,  0.42,  0.81,  1.00,  0.51,
                             0.11, -0.02, -0.32,  0.56,  0.68,  0.51,  1.00};
  cor = new TMatrixDSym(7, data);
}

SystCor_K3pi::~SystCor_K3pi()
{
  delete cor;
}

///
/// Convert a Malcolm name to a Malcolm ID of the syst cor matrix.
/// This order is defined in gammadini Bu2D0H_D02KPIPIPI.C
///
int SystCor_K3pi::obsMalcolmToId(TString malcolmObs)
{
  if ( malcolmObs=="A_FAV_b2dk_d2kpipipi"    ) return 0;
  if ( malcolmObs=="A_FAV_b2dpi_d2kpipipi"   ) return 1;
  if ( malcolmObs=="R_dk_vs_dpi"             ) return 2;
  if ( malcolmObs=="R_minus_b2dk_d2pikpipi"  ) return 3;
  if ( malcolmObs=="R_minus_b2dpi_d2pikpipi" ) return 4;
  if ( malcolmObs=="R_plus_b2dk_d2pikpipi"   ) return 5;
  if ( malcolmObs=="R_plus_b2dpi_d2pikpipi"  ) return 6;
  assert(0);
}

float SystCor_K3pi::getCor(TString mjObs1, TString mjObs2)
{
  return (*cor)[obsMalcolmToId(mjObs1)][obsMalcolmToId(mjObs2)];
}
