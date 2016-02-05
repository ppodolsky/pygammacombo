/**
 * HFAG WA Gamma Combination
 * Author: Matthew Kenzie (matthew.kenzie@cern.ch)
 * Date: June 2015
 *
 **/

#include "GammaComboEngine.h"

// observables
#include "PDF_GLW_DK_2var.h"
#include "PDF_GLW_DK_4var.h"
#include "PDF_GLW_DstK_4var.h"
#include "PDF_GLW_DKst_4var.h"
#include "PDF_GLW_DKpipi_2var.h"
#include "PDF_GLW_DK_pipipi0_2var.h"
#include "PDF_GLW_DK_KKpi0_2var.h"
#include "PDF_GLW_DK_pipipi0_1var.h"
#include "PDF_GLW_DKstz_2var.h"
#include "PDF_ADS_DK_Kpi_2var.h"
#include "PDF_ADS_DK_Kpipi0_2var.h"
#include "PDF_ADS_DK_K3pi_2var.h"
#include "PDF_ADS_DstK_Kpi_2var.h"
#include "PDF_ADS_DKst_Kpi_2var.h"
#include "PDF_ADS_DKpipi_Kpi_2var.h"
#include "PDF_ADS_DKstz_Kpi_2var.h"
#include "PDF_GGSZ.h"
#include "PDF_GGSZ_DKst.h"
#include "PDF_GGSZ_DstK.h"
#include "PDF_GGSZ_DKstz.h"
// externals
#include "PDF_D_HFAGfit.h"
#include "PDF_D_hhpi0_dilution.h"
#include "PDF_D_Kpipi0.h"
#include "PDF_D_Kpipi0_RWS.h"
#include "PDF_Dmixing_CLEO2D.h"
#include "PDF_D_K3pi_RWS.h"

using namespace std;
using namespace RooFit;
using namespace Utils;

GammaComboEngine& loadHfagGammaComboEngine(int argc, char* argv[])
{
  GammaComboEngine* gc_ptr = new GammaComboEngine("hfag_gammacombo", argc, argv);
  GammaComboEngine& gc = *gc_ptr;

	///////////////////////////////////////////////////
	//
	// define PDFs
	//
	///////////////////////////////////////////////////

  // GLW analyses
  gc.addPdf(1, new PDF_GLW_DK_4var(babar, babar, none),                   "GLW DK BaBar");
  gc.addPdf(2, new PDF_GLW_DK_4var(belle, belle, none),                   "GLW DK Belle");
  gc.addPdf(3, new PDF_GLW_DK_2var(cdf, cdf, cdf),                        "GLW DK CDF");
  gc.addPdf(4, new PDF_GLW_DK_2var(lhcb, lhcb, lhcb),                     "GLW DK LHCb");
  gc.addPdf(5, new PDF_GLW_DstK_4var(babar, babar, babar),                "GLW D*K BaBar");
  gc.addPdf(6, new PDF_GLW_DstK_4var(belle, belle, belle),                "GLW D*K Belle");
  gc.addPdf(7, new PDF_GLW_DKst_4var(babar, babar, babar),                "GLW DK* BaBar");
  gc.addPdf(8, new PDF_GLW_DKpipi_2var(lhcb_kk, lhcb_kk, lhcb_kk),        "GLW DKpipi (KK) LHCb");
  gc.addPdf(9, new PDF_GLW_DKpipi_2var(lhcb_pipi, lhcb_pipi, lhcb_pipi),  "GLW DKpipi (pipi) LHCb");
  gc.addPdf(10, new PDF_D_hhpi0_dilution(cleo2015,cleo2015,cleo2015),     "CLEO F-factors hhpi0");
  gc.addPdf(11, new PDF_GLW_DK_pipipi0_2var(lhcb, lhcb, lhcb),            "GLW like DK (D->pipipi0) LHCb");
  gc.addPdf(12, new PDF_GLW_DK_pipipi0_1var(babar, babar, babar),         "GLW like DK (D->pipipi0) BaBar");
  gc.addPdf(13, new PDF_GLW_DK_KKpi0_2var(lhcb,lhcb,lhcb),                "GLW like DK (D->KKpi0) LHCb");

  // ADS analyses
  gc.addPdf(14, new PDF_D_HFAGfit(hfagCHARM2015,hfagCHARM2015,hfagCHARM2015),    "HFAG D->Kpi");
  gc.addPdf(15, new PDF_ADS_DK_Kpi_2var(babar,babar,babar),                      "ADS DK (D->Kpi) BaBar");
  gc.addPdf(16, new PDF_ADS_DK_Kpi_2var(belle,belle,belle),                      "ADS DK (D->Kpi) Belle");
  gc.addPdf(17, new PDF_ADS_DK_Kpi_2var(cdf,cdf,cdf),                            "ADS DK (D->Kpi) CDF");
  gc.addPdf(18, new PDF_ADS_DK_Kpi_2var(lhcb,lhcb,lhcb),                         "ADS DK (D->Kpi) LHCb");
  gc.addPdf(19, new PDF_D_Kpipi0(cleo2014,cleo2014,cleo2014,useGaussian),        "CLEO Kpipi0 (dD,kD) Gaussian");
  gc.addPdf(20, new PDF_D_Kpipi0(cleo2014,cleo2014,cleo2014,useHistogram),       "CLEO Kpipi0 (dD,kD) Histogram");
  gc.addPdf(21, new PDF_D_Kpipi0_RWS(pdg,pdg,pdg),                               "PDG Kpipi0 RWS");
  gc.addPdf(22, new PDF_ADS_DK_Kpipi0_2var(babar,babar,babar),                   "ADS DK (D->Kpipi0) BaBar");
  gc.addPdf(23, new PDF_ADS_DK_Kpipi0_2var(belle,belle,belle),                   "ADS DK (D->Kpipi0) Belle");
  gc.addPdf(24, new PDF_ADS_DK_Kpipi0_2var(lhcb,lhcb,lhcb),                      "ADS DK (D->Kpipi0) LHCb");
  gc.addPdf(25, new PDF_Dmixing_CLEO2D(cleo2014,cleo2014,cleo2014,useGaussian),  "CLEO K3pi (dD,kD) Gaussian");
  gc.addPdf(26, new PDF_Dmixing_CLEO2D(cleo2014,cleo2014,cleo2014,useHistogram), "CLEO K3pi (dD,kD) Histogram");
  gc.addPdf(27, new PDF_D_K3pi_RWS(ckm2014,ckm2014,ckm2014),                     "PDF K3pi RWS");
  gc.addPdf(28, new PDF_ADS_DK_K3pi_2var(lhcb,lhcb,lhcb),                        "ADS DK (D->K3pi) LHCb");
  gc.addPdf(29, new PDF_ADS_DstK_Kpi_2var(babar_dpi0,babar_dpi0,babar_dpi0),     "ADS D*K (D*->Dpi, D->Kpi) BaBar");
  gc.addPdf(30, new PDF_ADS_DstK_Kpi_2var(babar_dg,babar_dg,babar_dg),           "ADS D*K (D*->Dg, D->Kpi) BaBar");
  gc.addPdf(31, new PDF_ADS_DstK_Kpi_2var(belle_dpi0,belle_dpi0,belle_dpi0),     "ADS D*K (D*->Dpi, D->Kpi) Belle");
  gc.addPdf(32, new PDF_ADS_DstK_Kpi_2var(belle_dg,belle_dg,belle_dg),           "ADS D*K (D*->Dg, D->Kpi) Belle");
  gc.addPdf(33, new PDF_ADS_DKst_Kpi_2var(babar,babar,babar),                    "ADS DK* (D->Kpi) BaBar");
  gc.addPdf(34, new PDF_ADS_DKpipi_Kpi_2var(lhcb,lhcb,lhcb),                     "ADS DKpipi (D->Kpi) LHCb");

  // GGSZ analyses
  // model dependent
  gc.addPdf(35, new PDF_GGSZ(babar,babar,babar),                                 "GGSZ DK (D->KSpipi) BaBar");
  gc.addPdf(36, new PDF_GGSZ_DKst(babar,babar,babar),                            "GGSZ DK* (D->KSpipi) BaBar");
  gc.addPdf(37, new PDF_GGSZ_DKst(belle,belle,belle),                            "GGSZ DK* (D->KSpipi) Belle");
  gc.addPdf(38, new PDF_GGSZ_DstK(babar,babar,babar),                            "GGSZ D*K (D->KSpipi) BaBar");
  gc.addPdf(39, new PDF_GGSZ_DstK(belle,belle,belle),                            "GGSZ D*K (D->KSpipi) Belle");
  // model independent
  gc.addPdf(40, new PDF_GGSZ(belle,belle,belle),                                 "GGSZ DK (D->KSpipi) Belle");
  gc.addPdf(41, new PDF_GGSZ(lhcb,lhcb,lhcb),                                    "GGSZ DK (D->KSpipi) LHCb");

  // B0 -> DK*0
  gc.addPdf(42, new PDF_GLW_DKstz_2var(lhcb_kk,lhcb_kk,lhcb_kk),                 "GLW B0->DK*0 (D->KK) LHCb");
  gc.addPdf(43, new PDF_GLW_DKstz_2var(lhcb_kk,lhcb_kk,lhcb_kk),                 "GLW B0->DK*0 (D->pipi) LHCb");
  gc.addPdf(44, new PDF_ADS_DKstz_Kpi_2var(lhcb,lhcb,lhcb),                      "ADS B0->DK*0 (D->Kpi) LHCb");
  gc.addPdf(45, new PDF_GGSZ_DKstz(belle,belle,belle),                           "GGSZ D0->DK*0 (D->KSpipi) Belle");

	///////////////////////////////////////////////////
	//
	// Define combinations
	//
	///////////////////////////////////////////////////

	gc.newCombiner(0, "empty", "empty");

  gc.newCombiner(1, "glw_dk",     "GLW B#rightarrowDK", 1,2,3,4);
  gc.newCombiner(2, "glw_dstk",   "GLW B#rightarrowD*K", 5, 6);
  gc.newCombiner(3, "glw_dkst",   "GLW B#rightarrowDK*", 7);
  gc.newCombiner(4, "glw_dkpipi", "GLW B#rightarrowDK#pi#pi", 8, 9);
  gc.newCombiner(5, "glw_like",   "GLW B#rightarrowDK (D#rightarrowhhpi^{0})", 10, 11, 12, 13);

  gc.newCombiner(6, "glw", "GLW Analyses of B^{-} #rightarrow D^{(*)}K^{(*)-}", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13);
  gc.getCombiner(6)->addPdf( gc[42], gc[43] );

  gc.newCombiner(7, "ads_dk_kpi",    "ADS B#rightarrowDK (D#rightarrowK#pi)", 14, 15, 16, 17, 18);
  gc.newCombiner(8, "ads_dk_kpipi0", "ADS B#rightarrowDK (D#rightarrowK#pi#pi^{0})", 20, 21, 22, 23, 24);
  gc.newCombiner(9, "ads_dk_k3pi",   "ADS B#rightarrowDK (D#rightarrowK3#pi)", 26, 27, 28);
  gc.newCombiner(10, "ads_dkst_kpi", "ADS B#rightarrowDK* (D#rightarrowDK#pi)", 14, 29);
  gc.newCombiner(11, "ads_dkpipi_kpi", "ADS B#rightarrowDK#pi#pi (D#rightarrowDK#pi)", 14, 30);

  gc.newCombiner(12, "ads", "ADS Analyses of B^{-} #rightarrowDK D^{(*)}K^{(*)-}", 14, 15, 16, 17, 18, 19, 21, 22, 23, 24, 25, 27);
  gc.getCombiner(12)->addPdf(gc[28], gc[29], gc[30], gc[31], gc[32], gc[33]);
  gc.getCombiner(12)->addPdf(gc[34], gc[44]);

  // GGSZ Comb
  gc.newCombiner(13, "ggsz", "GGSZ Analyses of B#rightarrowDK^{(*)} (D#rightarrowK_{S}#pi#pi)", 35, 36, 37, 38, 39, 40, 41, 45);

  // GLW ADS Comb
  gc.newCombiner(14, "glwads", "GLW+ADS Analyses of B#rightarrowD^{(*)}K^{(*)}");
  gc.getCombiner(14)->addPdf(gc[1], gc[2], gc[3], gc[4], gc[5], gc[6]);
  gc.getCombiner(14)->addPdf(gc[7], gc[8], gc[9], gc[10], gc[11], gc[12]);
  gc.getCombiner(14)->addPdf(gc[13]);
  gc.getCombiner(14)->addPdf(gc[14], gc[15], gc[16], gc[17], gc[18], gc[19]);
  gc.getCombiner(14)->addPdf(gc[21], gc[22], gc[23], gc[24], gc[25], gc[27]);
  gc.getCombiner(14)->addPdf(gc[28], gc[29], gc[30], gc[31], gc[32], gc[33]);
  gc.getCombiner(14)->addPdf(gc[34], gc[44]);

  // BaBar GLW+ADS
  gc.newCombiner(80, "babar_glwads_comb", "BaBar GLW+ADS");
  gc.getCombiner(80)->addPdf(gc[1]);  // GLW B->DK
  gc.getCombiner(80)->addPdf(gc[5]);  // GLW B->D*K
  gc.getCombiner(80)->addPdf(gc[7]);  // GLW B->DK*
  gc.getCombiner(80)->addPdf(gc[10]); // CLEO hhpi0 diltuon
  gc.getCombiner(80)->addPdf(gc[12]); // GLW D->pipipi0
  gc.getCombiner(80)->addPdf(gc[14]); // HFAG
  gc.getCombiner(80)->addPdf(gc[15]); // ADS B->DK, D->Kpi
  gc.getCombiner(80)->addPdf(gc[19]); // CLEO D->Kpipi0 gaus
  gc.getCombiner(80)->addPdf(gc[21]); // PDG RWS D->Kpipi0
  gc.getCombiner(80)->addPdf(gc[22]); // ADS B->DK, D->Kpipi0
  gc.getCombiner(80)->addPdf(gc[29]); // ADS B->D*K, D*->Dpi0, D->Kpi
  gc.getCombiner(80)->addPdf(gc[30]); // ADS B->D*K, D*->Dg  , D->Kpi
  gc.getCombiner(80)->addPdf(gc[33]); // ADS B->DK*, D->Kpi

  // BaBar GGSZ
  gc.newCombiner(81, "babar_ggsz_comb", "BaBar GGSZ");
  gc.getCombiner(81)->addPdf(gc[35]); // GGSZ B->DK, D->KSpipi
  gc.getCombiner(81)->addPdf(gc[36]); // GSSZ B->DK*, D->KSpipi
  gc.getCombiner(81)->addPdf(gc[38]); // GSSZ B->D*K, D->KSpipi

  // BaBar Combined
  gc.newCombiner(90, "babar_comb", "BaBar Combination");
  gc.getCombiner(90)->addPdf(gc[1]);  // GLW B->DK
  gc.getCombiner(90)->addPdf(gc[5]);  // GLW B->D*K
  gc.getCombiner(90)->addPdf(gc[7]);  // GLW B->DK*
  gc.getCombiner(90)->addPdf(gc[10]); // CLEO hhpi0 diltuon
  gc.getCombiner(90)->addPdf(gc[12]); // GLW D->pipipi0
  gc.getCombiner(90)->addPdf(gc[14]); // HFAG
  gc.getCombiner(90)->addPdf(gc[15]); // ADS B->DK, D->Kpi
  gc.getCombiner(90)->addPdf(gc[19]); // CLEO D->Kpipi0 gaus
  gc.getCombiner(90)->addPdf(gc[21]); // PDG RWS D->Kpipi0
  gc.getCombiner(90)->addPdf(gc[22]); // ADS B->DK, D->Kpipi0
  gc.getCombiner(90)->addPdf(gc[29]); // ADS B->D*K, D*->Dpi0, D->Kpi
  gc.getCombiner(90)->addPdf(gc[30]); // ADS B->D*K, D*->Dg  , D->Kpi
  gc.getCombiner(90)->addPdf(gc[33]); // ADS B->DK*, D->Kpi
  gc.getCombiner(90)->addPdf(gc[35]); // GGSZ B->DK, D->KSpipi
  gc.getCombiner(90)->addPdf(gc[36]); // GSSZ B->DK*, D->KSpipi
  gc.getCombiner(90)->addPdf(gc[38]); // GSSZ B->D*K, D->KSpipi

  // Belle GLW+ADS
  gc.newCombiner(82, "belle_glwads_comb", "Belle GLW+ADS");
  gc.getCombiner(82)->addPdf(gc[2]);  // GLW B->DK
  gc.getCombiner(82)->addPdf(gc[6]);  // GLW B->DK*
  gc.getCombiner(82)->addPdf(gc[14]); // HFAG
  gc.getCombiner(82)->addPdf(gc[16]); // ADS B->DK, D->Kpi
  gc.getCombiner(82)->addPdf(gc[19]); // CLEO D->Kpipi0 gaus
  gc.getCombiner(82)->addPdf(gc[21]); // PDG RWS D->Kpipi0
  gc.getCombiner(82)->addPdf(gc[23]); // ADS B->DK, D->Kpipi0
  gc.getCombiner(82)->addPdf(gc[31]); // ADS B->D*K, D*->Dpi0, D->Kpi
  gc.getCombiner(82)->addPdf(gc[32]); // ADS B->D*K, D*->Dg  , D->Kpi

  // Belle GGSZ
  gc.newCombiner(83, "belle_ggsz_comb", "Belle GGSZ");
  gc.getCombiner(83)->addPdf(gc[40]); // GGSZ B->DK, D->KSpipi
  gc.getCombiner(83)->addPdf(gc[37]); // GSSZ B->DK*, D->KSpipi
  gc.getCombiner(83)->addPdf(gc[39]); // GSSZ B->D*K, D->KSpipi
  gc.getCombiner(83)->addPdf(gc[45]); // GGSZ B->DK*0, D->KSpipi

  // Belle Combined
  gc.newCombiner(91, "belle_comb", "Belle Combination");
  gc.getCombiner(91)->addPdf(gc[2]);  // GLW B->DK
  gc.getCombiner(91)->addPdf(gc[6]);  // GLW B->DK*
  gc.getCombiner(91)->addPdf(gc[14]); // HFAG
  gc.getCombiner(91)->addPdf(gc[16]); // ADS B->DK, D->Kpi
  gc.getCombiner(91)->addPdf(gc[19]); // CLEO D->Kpipi0 gaus
  gc.getCombiner(91)->addPdf(gc[21]); // PDG RWS D->Kpipi0
  gc.getCombiner(91)->addPdf(gc[23]); // ADS B->DK, D->Kpipi0
  gc.getCombiner(91)->addPdf(gc[31]); // ADS B->D*K, D*->Dpi0, D->Kpi
  gc.getCombiner(91)->addPdf(gc[32]); // ADS B->D*K, D*->Dg  , D->Kpi
  gc.getCombiner(91)->addPdf(gc[40]); // GGSZ B->DK, D->KSpipi
  gc.getCombiner(91)->addPdf(gc[37]); // GSSZ B->DK*, D->KSpipi
  gc.getCombiner(91)->addPdf(gc[39]); // GSSZ B->D*K, D->KSpipi
  gc.getCombiner(91)->addPdf(gc[45]); // GGSZ B->DK*0, D->KSpipi

  // LHCb GLW+ADS
  gc.newCombiner(84, "lhcb_glwads_comb", "LHCb GLW+ADS");
  gc.getCombiner(84)->addPdf(gc[4]);  // GLW B->DK
  gc.getCombiner(84)->addPdf(gc[8]);  // GLW B->DKpipi, D->KK
  gc.getCombiner(84)->addPdf(gc[9]);  // GLW B->DKpipi, D->pipi
  gc.getCombiner(84)->addPdf(gc[10]); // CLEO D->Kpipi0 gaus
  gc.getCombiner(84)->addPdf(gc[11]); // GLW B->DK, D->pipipi0
  gc.getCombiner(84)->addPdf(gc[13]); // GLW B->DK, D->KKpi0
  gc.getCombiner(84)->addPdf(gc[14]); // HFAG
  gc.getCombiner(84)->addPdf(gc[18]); // ADS B->DK, D->Kpi
  gc.getCombiner(84)->addPdf(gc[19]); // CLEO D->Kpipi0 gaus
  gc.getCombiner(84)->addPdf(gc[21]); // PDG RWS D->Kpipi0
  gc.getCombiner(84)->addPdf(gc[24]); // ADS B->DK, D->Kpipi0
  gc.getCombiner(84)->addPdf(gc[25]); // CLEO D->K3pi gaus
  gc.getCombiner(84)->addPdf(gc[27]); // PDG RWS D->K3pi
  gc.getCombiner(84)->addPdf(gc[28]); // ADS B->DK, D->K3pi
  gc.getCombiner(84)->addPdf(gc[34]); // ADS B->DKpipi, D->Kpi
  gc.getCombiner(84)->addPdf(gc[42]); // GLW B0->DK*0, D->KK
  gc.getCombiner(84)->addPdf(gc[43]); // GLW B0->DK*0, D->pipi
  gc.getCombiner(84)->addPdf(gc[44]); // ADS B0->DK*0, D->Kpi

  // LHCb GGSZ
  gc.newCombiner(85, "lhcb_ggsz_comb", "LHCb GGSZ");
  gc.getCombiner(85)->addPdf(gc[41]); // GGSZ B->DK, D->KSpipi

  // LHCb Combined
  gc.newCombiner(92, "lhcb_comb",  "LHCb Combination");
  gc.getCombiner(92)->addPdf(gc[4]);  // GLW B->DK
  gc.getCombiner(92)->addPdf(gc[8]);  // GLW B->DKpipi, D->KK
  gc.getCombiner(92)->addPdf(gc[9]);  // GLW B->DKpipi, D->pipi
  gc.getCombiner(92)->addPdf(gc[10]); // CLEO D->Kpipi0 gaus
  gc.getCombiner(92)->addPdf(gc[11]); // GLW B->DK, D->pipipi0
  gc.getCombiner(92)->addPdf(gc[13]); // GLW B->DK, D->KKpi0
  gc.getCombiner(92)->addPdf(gc[14]); // HFAG
  gc.getCombiner(92)->addPdf(gc[18]); // ADS B->DK, D->Kpi
  gc.getCombiner(92)->addPdf(gc[19]); // CLEO D->Kpipi0 gaus
  gc.getCombiner(92)->addPdf(gc[21]); // PDG RWS D->Kpipi0
  gc.getCombiner(92)->addPdf(gc[24]); // ADS B->DK, D->Kpipi0
  gc.getCombiner(92)->addPdf(gc[25]); // CLEO D->K3pi gaus
  gc.getCombiner(92)->addPdf(gc[27]); // PDG RWS D->K3pi
  gc.getCombiner(92)->addPdf(gc[28]); // ADS B->DK, D->K3pi
  gc.getCombiner(92)->addPdf(gc[34]); // ADS B->DKpipi, D->Kpi
  gc.getCombiner(92)->addPdf(gc[41]); // GGSZ B->DK, D->KSpipi
  gc.getCombiner(92)->addPdf(gc[42]); // GLW B0->DK*0, D->KK
  gc.getCombiner(92)->addPdf(gc[43]); // GLW B0->DK*0, D->pipi
  gc.getCombiner(92)->addPdf(gc[44]); // ADS B0->DK*0, D->Kpi

  gc.newCombiner(94, "dk_comb", "DK Combination");
  gc.getCombiner(94)->addPdf(gc[1]);  // GLW DK BaBar
  gc.getCombiner(94)->addPdf(gc[2]);  // GLW DK Belle
  gc.getCombiner(94)->addPdf(gc[3]);  // GLW DK CDF
  gc.getCombiner(94)->addPdf(gc[4]);  // GLW DK LHCb
  gc.getCombiner(94)->addPdf(gc[15]); // ADS DK, D->Kpi BaBar
  gc.getCombiner(94)->addPdf(gc[16]); // ADS DK, D->Kpi Belle
  gc.getCombiner(94)->addPdf(gc[17]); // ADS DK, D->Kpi CDF
  gc.getCombiner(94)->addPdf(gc[18]); // ADS DK, D->Kpi LHCb
  gc.getCombiner(94)->addPdf(gc[31]); // GGSZ DK, D->KSpipi BaBar
  gc.getCombiner(94)->addPdf(gc[36]); // GGSZ DK, D->KSpipi Belle
  gc.getCombiner(94)->addPdf(gc[37]); // GGSZ DK, D->KSpipi LHCb

  gc.newCombiner(100, "comb", "World Average");
  gc.getCombiner(100)->addPdf(gc[1]);
  gc.getCombiner(100)->addPdf(gc[2]);
  gc.getCombiner(100)->addPdf(gc[3]);
  gc.getCombiner(100)->addPdf(gc[4]);
  gc.getCombiner(100)->addPdf(gc[5]);
  gc.getCombiner(100)->addPdf(gc[6]);
  gc.getCombiner(100)->addPdf(gc[7]);
  gc.getCombiner(100)->addPdf(gc[8]);
  gc.getCombiner(100)->addPdf(gc[9]);
  gc.getCombiner(100)->addPdf(gc[10]);
  gc.getCombiner(100)->addPdf(gc[11]);
  gc.getCombiner(100)->addPdf(gc[12]);
  gc.getCombiner(100)->addPdf(gc[13]);
  gc.getCombiner(100)->addPdf(gc[14]);
  gc.getCombiner(100)->addPdf(gc[15]);
  gc.getCombiner(100)->addPdf(gc[16]);
  gc.getCombiner(100)->addPdf(gc[17]);
  gc.getCombiner(100)->addPdf(gc[18]);
  gc.getCombiner(100)->addPdf(gc[19]);
  gc.getCombiner(100)->addPdf(gc[21]);
  gc.getCombiner(100)->addPdf(gc[22]);
  gc.getCombiner(100)->addPdf(gc[23]);
  gc.getCombiner(100)->addPdf(gc[24]);
  gc.getCombiner(100)->addPdf(gc[25]);
  gc.getCombiner(100)->addPdf(gc[27]);
  gc.getCombiner(100)->addPdf(gc[28]);
  gc.getCombiner(100)->addPdf(gc[29]);
  gc.getCombiner(100)->addPdf(gc[30]);
  gc.getCombiner(100)->addPdf(gc[31]);
  gc.getCombiner(100)->addPdf(gc[32]);
  gc.getCombiner(100)->addPdf(gc[33]);
  gc.getCombiner(100)->addPdf(gc[34]);
  gc.getCombiner(100)->addPdf(gc[35]);
  gc.getCombiner(100)->addPdf(gc[36]);
  gc.getCombiner(100)->addPdf(gc[37]);
  gc.getCombiner(100)->addPdf(gc[38]);
  gc.getCombiner(100)->addPdf(gc[39]);
  gc.getCombiner(100)->addPdf(gc[40]);
  gc.getCombiner(100)->addPdf(gc[41]);
  gc.getCombiner(100)->addPdf(gc[42]);
  gc.getCombiner(100)->addPdf(gc[43]);
  gc.getCombiner(100)->addPdf(gc[44]);
  gc.getCombiner(100)->addPdf(gc[45]);

	///////////////////////////////////////////////////
	//
	// Run
	//
	///////////////////////////////////////////////////

  return gc;
}
