#include "SystCor_Kpi.h"

SystCor_Kpi::SystCor_Kpi()
{
  // build a map from Malcolm's code
  // defined in gammadini Bu2D0H_D02HH.C
  const double data[169] = {  1.00,  0.96,  0.82,  0.97, -0.18, -0.18, -0.16,  0.50,  0.51,  0.18,  0.11,  0.09,  0.00,
                              0.96,  1.00,  0.81,  0.96, -0.12, -0.11, -0.07,  0.49,  0.50,  0.12,  0.10,  0.01,  0.02,
                              0.82,  0.81,  1.00,  0.78,  0.08,  0.08,  0.01, -0.16,  0.01, -0.00, -0.32, -0.01,  0.35,
                              0.97,  0.96,  0.78,  1.00, -0.03, -0.03, -0.00,  0.48,  0.53,  0.11,  0.05, -0.06, -0.04,
                             -0.18, -0.12,  0.08, -0.03,  1.00,  0.78,  0.75, -0.17,  0.00, -0.19, -0.18, -0.44, -0.19,
                             -0.18, -0.11,  0.08, -0.03,  0.78,  1.00,  0.76, -0.15,  0.01, -0.24, -0.23, -0.51, -0.23,
                             -0.16, -0.07,  0.01, -0.00,  0.75,  0.76,  1.00, -0.00,  0.00, -0.16, -0.11, -0.39, -0.12,
                              0.50,  0.49, -0.16,  0.48, -0.17, -0.15, -0.00,  1.00,  0.82,  0.20,  0.61, -0.13, -0.67,
                              0.51,  0.50,  0.01,  0.53,  0.00,  0.01,  0.00,  0.82,  1.00,  0.19,  0.57, -0.16, -0.72,
                              0.18,  0.12, -0.00,  0.11, -0.19, -0.24, -0.16,  0.20,  0.19,  1.00,  0.37,  0.39,  0.07,
                              0.11,  0.10, -0.32,  0.05, -0.18, -0.23, -0.11,  0.61,  0.57,  0.37,  1.00,  0.34, -0.13,
                              0.09,  0.01, -0.01, -0.06, -0.44, -0.51, -0.39, -0.13, -0.16,  0.39,  0.34,  1.00,  0.40,
                              0.00,  0.02,  0.35, -0.04, -0.19, -0.23, -0.12, -0.67, -0.72,  0.07, -0.13,  0.40,  1.00};
  cor = new TMatrixDSym(13, data);
}

SystCor_Kpi::~SystCor_Kpi()
{
  delete cor;
}

///
/// Convert a Malcolm name to a Malcolm ID of the syst cor matrix.
/// This order is defined in gammadini Bu2D0H_D02HH.C
///
int SystCor_Kpi::obsMalcolmToId(TString malcolmObs)
{
  if ( malcolmObs=="A_CPP_b2dk_d2kk")    return 0;
  if ( malcolmObs=="A_CPP_b2dk_d2pipi")  return 1;
  if ( malcolmObs=="A_CPP_b2dpi_d2kk")   return 2;
  if ( malcolmObs=="A_CPP_b2dpi_d2pipi") return 3;
  if ( malcolmObs=="A_FAV_b2dk_d2kpi")   return 4;
  if ( malcolmObs=="A_FAV_b2dpi_d2kpi")  return 5;
  if ( malcolmObs=="R_dk_vs_dpi_d2kk")   return 6;
  if ( malcolmObs=="R_dk_vs_dpi_d2kpi")  return 7;
  if ( malcolmObs=="R_dk_vs_dpi_d2pipi") return 8;
  if ( malcolmObs=="R_minus_b2dk_d2pik") return 9;
  if ( malcolmObs=="R_minus_b2dpi_d2pik")return 10;
  if ( malcolmObs=="R_plus_b2dk_d2pik")  return 11;
  if ( malcolmObs=="R_plus_b2dpi_d2pik") return 12;
  assert(0);
}

float SystCor_Kpi::getCor(TString mjObs1, TString mjObs2)
{
  return (*cor)[obsMalcolmToId(mjObs1)][obsMalcolmToId(mjObs2)];
}
