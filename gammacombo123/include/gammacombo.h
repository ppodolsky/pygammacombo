/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2014
 *
 **/

#include "GammaComboEngine.h"
#include "PDF_ADS_DKDpi_Kpipi0.h"
#include "PDF_ADS_DK_K3pi.h"
#include "PDF_ADS_DK_Kpi.h"
#include "PDF_ADS_Dpi_K3pi.h"
#include "PDF_ADS_Dpi_Kpi.h"
#include "PDF_B_DKstz_coherence.h"
#include "PDF_CrossCorTest1.h"
#include "PDF_CrossCorTest2.h"
#include "PDF_CrossCorTest3.h"
#include "PDF_CrossCor_DK_K3pi_vs_DK_KSKpi.h"
#include "PDF_CrossCor_DK_K3pi_vs_DKpipi_hh.h"
#include "PDF_CrossCor_DK_K3pi_vs_DKst_hh.h"
#include "PDF_CrossCor_DK_KSKpi_vs_DKpipi_hh.h"
#include "PDF_CrossCor_DK_KSKpi_vs_DKst_hh.h"
#include "PDF_CrossCor_DK_KSKpi_vs_Dhpipi_hh.h"
#include "PDF_CrossCor_DK_hh_vs_DK_K3pi.h"
#include "PDF_CrossCor_DK_hh_vs_DK_KSKpi.h"
#include "PDF_CrossCor_DK_hh_vs_DKpipi_hh.h"
#include "PDF_CrossCor_DK_hh_vs_DKst_hh.h"
#include "PDF_CrossCor_DKst_hh_vs_DKpipi_hh.h"
#include "PDF_CrossCor_DKst_hh_vs_Dhpipi_hh.h"
#include "PDF_CrossCor_Dh_K3pi_vs_DK_KSKpi.h"
#include "PDF_CrossCor_Dh_K3pi_vs_DKst_hh.h"
#include "PDF_CrossCor_Dh_K3pi_vs_Dhpipi_hh.h"
#include "PDF_CrossCor_Dh_hh_vs_DK_KSKpi.h"
#include "PDF_CrossCor_Dh_hh_vs_DKst_hh.h"
#include "PDF_CrossCor_Dh_hh_vs_Dh_K3pi.h"
#include "PDF_CrossCor_Dh_hh_vs_Dhpipi_hh.h"
#include "PDF_D_CleoNoK2pi.h"
#include "PDF_D_CleoNoK2piNoKpi.h"
#include "PDF_D_HFAGfit.h"
#include "PDF_D_K3pi.h"
#include "PDF_D_K3pi_RWS.h"
#include "PDF_D_KSKpi.h"
#include "PDF_D_Kminus3pi.h"
#include "PDF_D_Kpi.h"
#include "PDF_D_Kpipi0.h"
#include "PDF_D_Kpipi0_RWS.h"
#include "PDF_D_Kplus3pi.h"
#include "PDF_D_KstK_DCPV.h"
#include "PDF_D_hhpi0_dilution.h"
#include "PDF_DeltaAcp.h"
#include "PDF_DhhAcp.h"
#include "PDF_Dmixing.h"
#include "PDF_Dmixing_CLEO2D.h"
#include "PDF_Dmixing_CLEOFCP.h"
#include "PDF_Dmixing_xy.h"
#include "PDF_DsK.h"
#include "PDF_GGSZ.h"
#include "PDF_GGSZ_Dpi.h"
#include "PDF_GGSZ_cartesian.h"
#include "PDF_GGSZ_DKstz.h"
#include "PDF_GLWADS_DKDpi_K3pi.h"
#include "PDF_GLWADS_DKDpi_K3pi_Dmix.h"
#include "PDF_GLWADS_DKDpi_KSKpi.h"
#include "PDF_GLWADS_DKDpi_KSKpi_DCPV_Dmix.h"
#include "PDF_GLWADS_DKDpi_KSKpi_Dmix.h"
#include "PDF_GLWADS_DKDpi_hh.h"
#include "PDF_GLWADS_DKDpi_hh_2012.h"
#include "PDF_GLWADS_DKDpi_hh_Dmix.h"
#include "PDF_GLWADS_DKDpi_hhpi0.h"
#include "PDF_GLWADS_DKDpi_hhpi0_Dmix.h"
#include "PDF_GLWADS_DK_K3pi.h"
#include "PDF_GLWADS_DK_K3pi_Dmix.h"
#include "PDF_GLWADS_DK_KSKpi.h"
#include "PDF_GLWADS_DK_KSKpi_DCPV_Dmix.h"
#include "PDF_GLWADS_DK_KSKpi_Dmix.h"
#include "PDF_GLWADS_DK_hh.h"
#include "PDF_GLWADS_DK_hh_Dmix.h"
#include "PDF_GLWADS_DK_hhpi0.h"
#include "PDF_GLWADS_DK_hhpi0_Dmix.h"
#include "PDF_GLWADS_DKpipi_hh.h"
#include "PDF_GLWADS_DKpipi_hh_Dmix.h"
#include "PDF_GLWADS_DKstz_hh.h"
#include "PDF_GLWADS_DKstz_hh_Dmix.h"
#include "PDF_GLWADS_Dhpipi_hh.h"
#include "PDF_GLWADS_Dhpipi_hh_Dmix.h"
#include "PDF_GLWADS_Dpi_K3pi.h"
#include "PDF_GLWADS_Dpi_K3pi_Dmix.h"
#include "PDF_GLWADS_Dpi_hh.h"
#include "PDF_GLWADS_Dpi_hh_Dmix.h"
#include "PDF_GLWADS_DKDpi_hh_Dmix_newVars.h"
#include "PDF_GLWADS_DK_hh_Dmix_newVars.h"
#include "PDF_GLWADS_Dpi_hh_Dmix_newVars.h"
#include "PDF_GLWADS_DKDpi_K3pi_Dmix_newVars.h"
#include "PDF_GLWADS_DK_K3pi_Dmix_newVars.h"
#include "PDF_GLW_DK.h"
#include "PDF_GLW_Dpi.h"
#include "PDF_gamma.h"
#include "PDF_rBK.h"
#include "PDF_Dmixing_K3pi.h"

using namespace std;
using namespace RooFit;
using namespace Utils;

Combiner* dkonlyDmix(OptParser *arg, GammaComboEngine& pdf, float Mxy)
{
	PDF_Abs* kpi  = new PDF_GLWADS_DK_hh_Dmix(lumi1fb, lumi1fb, lumi1fb, Mxy);
	PDF_Abs* k3pi = new PDF_GLWADS_DK_K3pi_Dmix(lumi1fb, lumi1fb, lumi1fb, Mxy);
	Combiner* c = new Combiner(arg, Form("dkonlyDmixMxy%4.2f",Mxy), Form("DK only (w/ D mixing, Mxy=%4.2f)",Mxy));
	c->addPdf(pdf[18], kpi, k3pi, pdf[9], pdf[17], pdf[23]);
	return c;
}


Combiner* dpionlyDmix(OptParser *arg, GammaComboEngine& pdf, float Mxy)
{
	PDF_Abs* kpi  = new PDF_GLWADS_Dpi_hh_Dmix(lumi1fb, lumi1fb, lumi1fb, Mxy);
	PDF_Abs* k3pi = new PDF_GLWADS_Dpi_K3pi_Dmix(lumi1fb, lumi1fb, lumi1fb, Mxy);
	Combiner* c = new Combiner(arg, Form("dpionlyDmixMxy%4.2f",Mxy), Form("D#pi only (w/ D mixing, Mxy=%4.2f)",Mxy));
	c->addPdf(kpi, k3pi, pdf[9], pdf[17], pdf[23]);
	return c;
}


Combiner* dkdpiDmix(OptParser *arg, GammaComboEngine& pdf, float Mxy)
{
	PDF_Abs* kpi  = new PDF_GLWADS_DKDpi_hh_Dmix(lumi1fb, lumi1fb, lumi1fb, Mxy);
	PDF_Abs* k3pi = new PDF_GLWADS_DKDpi_K3pi_Dmix(lumi1fb, lumi1fb, lumi1fb, Mxy);
	Combiner* c = new Combiner(arg, Form("dkdpiDmixMxy%4.2f",Mxy), Form("B#rightarrowDK and B#rightarrowD#pi (w/ D mixing, Mxy=%4.2f)",Mxy));
	c->addPdf(pdf[18], kpi, k3pi, pdf[9], pdf[17], pdf[23]);
	return c;
}

GammaComboEngine& loadMainGammaComboEngine(int argc, char* argv[])
{
	GammaComboEngine* gc_ptr = new GammaComboEngine("gammacombo", argc, argv);
	GammaComboEngine& gc = *gc_ptr;

	///////////////////////////////////////////////////
	//
	// define PDFs
	//
	///////////////////////////////////////////////////

	gc.addPdf(1,  new PDF_GLW_DK(), "");
	gc.addPdf(2,  new PDF_GLW_Dpi(), "");
	gc.addPdf(3,  new PDF_ADS_DK_Kpi(), "");
	gc.addPdf(4,  new PDF_ADS_DK_K3pi(), "");
	gc.addPdf(5,  new PDF_ADS_Dpi_Kpi(), "");
	gc.addPdf(6,  new PDF_ADS_Dpi_K3pi(), "");
	gc.addPdf(7,  new PDF_D_Kpi(hfagLP2011,hfagLP2011,hfagLP2011)                , "HFAG D->Kpi, LP2011");
	gc.addPdf(8,  new PDF_D_K3pi(belle2013cleo2014, belle2013cleo2014, belle2013cleo2014, useHistogram), "D->K3pi (Belle 2013, CLEO 2014)");
	gc.addPdf(9,  new PDF_D_CleoNoK2pi(cleo, useHistogram)                       , "CLEO 2009, likelihood");
	gc.addPdf(16, new PDF_D_CleoNoK2pi(cleo, useGaussian)                        , "CLEO 2009, Gaussian");
	gc.addPdf(10, new PDF_GLWADS_DKDpi_hh()                                      , "GLW/ADS, D->hh, 1fb-1");
	gc.addPdf(11, new PDF_GLWADS_DKDpi_K3pi()                                    , "ADS, D->K3pi, 1fb-1");
	gc.addPdf(12, new PDF_DsK(lumi1fbPapersFit,lumi1fbPapersFit,lumi1fbPapersFit), "Bs->DsK, 1fb-1 (sFit)");
	gc.addPdf(13, new PDF_D_CleoNoK2piNoKpi(cleo, useHistogram)                  , "CLEO D->K3pi");
	gc.addPdf(14, new PDF_D_CleoNoK2piNoKpi(cleo, useGaussian)                   , "CLEO D->K3pi (Gaussian)");
	gc.addPdf(15, new PDF_DeltaAcp()                                             , "DeltaAcp");
	gc.addPdf(17, new PDF_DhhAcp()                                               , "HFAG D CPV");
	gc.addPdf(18, new PDF_GGSZ()                                                 , "GGSZ, 1fb-1");
	gc.addPdf(19, new PDF_GLWADS_DK_hh()                                         , "GLWADS, B->DK, D->hh, 1fb-1, (old)");
	gc.addPdf(20, new PDF_GLWADS_DK_K3pi()                                       , "GLWADS, B->DK, D->K3pi, 1fb-1, (old)");
	gc.addPdf(21, new PDF_GLWADS_Dpi_hh()                                        , "GLWADS, B->Dpi, D->hh, 1fb-1, (old)");
	gc.addPdf(22, new PDF_GLWADS_Dpi_K3pi()                                      , "GLWADS, B->Dpi, D->K3pi, 1fb-1, (old)");
	gc.addPdf(23, new PDF_Dmixing()                                              , "LHCb D mixing, 1fb-1");
	gc.addPdf(24, new PDF_GLWADS_DKDpi_hh(lumi1fb, lumi1fb, lumi1fbSystCor)      , "GLWADS, B->Dh, D->hh, 1fb-1, syst.cor.");
	gc.addPdf(25, new PDF_GLWADS_DK_hh(lumi1fb, lumi1fb, lumi1fbSystCor)         , "GLWADS, B->DK, D->hh, 1fb-1, syst.cor.");
	gc.addPdf(26, new PDF_GLWADS_Dpi_hh(lumi1fb, lumi1fb, lumi1fbSystCor)        , "GLWADS, B->Dpi, D->hh, 1fb-1, syst.cor.");
	gc.addPdf(27, new PDF_GLWADS_DKDpi_K3pi(lumi1fb, lumi1fb, lumi1fbSystCor)    , "GLWADS, B->Dh, D->K3pi, 1fb-1, syst.cor.");
	gc.addPdf(28, new PDF_GLWADS_DK_K3pi(lumi1fb, lumi1fb, lumi1fbSystCor)       , "GLWADS, B->DK, D->K3pi, 1fb-1, syst.cor.");
	gc.addPdf(29, new PDF_GLWADS_Dpi_K3pi(lumi1fb, lumi1fb, lumi1fbSystCor)      , "GLWADS, B->Dpi, D->K3pi, 1fb-1, syst.cor.");
	gc.addPdf(30, new PDF_GGSZ(lumi3fb, lumi3fb, lumi3fb)                        , "GGSZ, 3fb-1 (CONF)");
	gc.addPdf(31, new PDF_GGSZ(lumi2fb, lumi2fb, lumi2fb)                        , "GGSZ, 2fb-1 (2012 alone)");
	gc.addPdf(32, new PDF_DeltaAcp(lumi1fbsl)                                    , "DeltaAcp, 1fb-1, semileptonic");
	gc.addPdf(33, new PDF_GGSZ(highrb, lumi3fb, lumi3fb)                         , "GGSZ with high rB");
	gc.addPdf(34, new PDF_GLWADS_DKDpi_hh_Dmix(  lumi1fb, lumi1fb, lumi1fb, 0.6)       , "GLWADS, D->hh, DK&Dpi, 1fb-1, D mixing corrected");
	gc.addPdf(35, new PDF_GLWADS_DK_hh_Dmix(     lumi1fb, lumi1fb, lumi1fb, 0.6)       , "GLWADS, D->hh, DK, 1fb-1, D mixing corrected");
	gc.addPdf(36, new PDF_GLWADS_Dpi_hh_Dmix(    lumi1fb, lumi1fb, lumi1fb, 0.6)       , "GLWADS, D->hh, Dpi, 1fb-1, D mixing corrected");
	gc.addPdf(37, new PDF_GLWADS_DKDpi_K3pi_Dmix(lumi1fb, lumi1fb, lumi1fb, 0.6)       , "ADS, D->K3pi, DK&Dpi, 1fb-1, D mixing corrected");
	gc.addPdf(38, new PDF_GLWADS_DK_K3pi_Dmix(   lumi1fb, lumi1fb, lumi1fb, 0.6)       , "ADS, D->K3pi, DK, 1fb-1, D mixing corrected");
	gc.addPdf(39, new PDF_GLWADS_Dpi_K3pi_Dmix(  lumi1fb, lumi1fb, lumi1fb, 0.6)       , "ADS, D->K3pi, Dpi, 1fb-1, D mixing corrected");
	gc.addPdf(40, new PDF_GLWADS_DKDpi_hh_Dmix(  lumi1fb, lumi1fb, lumi1fbSystCor, 0.6), "GLWADS, D->hh, DK&Dpi, 1fb-1, D mixing corrected, w/ syst.cor.");
	gc.addPdf(41, new PDF_GLWADS_DK_hh_Dmix(     lumi1fb, lumi1fb, lumi1fbSystCor, 0.6), "GLWADS, D->hh, DK, 1fb-1, D mixing corrected, w/ syst.cor.");
	gc.addPdf(42, new PDF_GLWADS_Dpi_hh_Dmix(    lumi1fb, lumi1fb, lumi1fbSystCor, 0.6), "GLWADS, D->hh, Dpi, 1fb-1, D mixing corrected, w/ syst.cor.");
	gc.addPdf(43, new PDF_GLWADS_DKDpi_K3pi_Dmix(lumi1fb, lumi1fb, lumi1fbSystCor, 0.6), "ADS, D->K3pi, DK&Dpi, 1fb-1, D mixing corrected, w/ syst.cor.");
	gc.addPdf(44, new PDF_GLWADS_DK_K3pi_Dmix(   lumi1fb, lumi1fb, lumi1fbSystCor, 0.6), "ADS, D->K3pi, DK, 1fb-1, D mixing corrected, w/ syst.cor.");
	gc.addPdf(45, new PDF_GLWADS_Dpi_K3pi_Dmix(  lumi1fb, lumi1fb, lumi1fbSystCor, 0.6), "ADS, D->K3pi, Dpi, 1fb-1, D mixing corrected, w/ syst.cor.");
	gc.addPdf(46, new PDF_GLWADS_DKstz_hh(lumi3fb, lumi3fb, lumi3fb)                   , "B0 -> DK*0, 3fb-1");
	gc.addPdf(47, new PDF_B_DKstz_coherence(hfag)                                      , "B0 -> DK*0 coherence factor (95+/-3)%");
	gc.addPdf(48, new PDF_ADS_DK_Kpi(lumi1fb, lumi1fb, lumi1fb, useTradObs), "");
	gc.addPdf(49, new PDF_ADS_DK_K3pi(lumi1fb, lumi1fb, lumi1fb, useTradObs), "");
	gc.addPdf(50, new PDF_GGSZ_cartesian(lumi1fb, lumi1fb, lumi1fb), "");
	gc.addPdf(51, new PDF_rBK(lumi1fb, lumi1fb, lumi1fb), "");
	gc.addPdf(52, new PDF_D_KSKpi(cleo,cleo,cleo)                                      , "CLEO 2012 D->K_{S}K#pi");
	gc.addPdf(53, new PDF_GLWADS_DKDpi_KSKpi(lumi3fb, lumi3fb, lumi3fb)                , "B->Dh, D->K_{S}K#pi, 3fb-1");
	gc.addPdf(54, new PDF_GLWADS_DKDpi_KSKpi_Dmix(lumi3fb, lumi3fb, lumi3fb, 0.5)     , "B->Dh, D->K_{S}K#pi, 3fb-1, D mixing corrected");
  //gc.addPdf(54, new PDF_GLWADS_DKDpi_KSKpi_Dmix(lumi3fb, lumi3fb, lumi3fb, 0.70)     , "B->Dh, D->K_{S}K#pi, 3fb-1, D mixing corrected");
	gc.addPdf(55, new PDF_GLWADS_Dhpipi_hh     (lumi3fb, lumi3fb, lumi3fb)             , "B->Dh#pi#pi, D->hh, 3fb-1");
	gc.addPdf(56, new PDF_GLWADS_Dhpipi_hh_Dmix(lumi3fb, lumi3fb, lumi3fb, 0.6)       , "B->Dh#pi#pi, D->hh, 3fb-1, D mixing corrected");
  //gc.addPdf(56, new PDF_GLWADS_Dhpipi_hh_Dmix(lumi3fb, lumi3fb, lumi3fb, 0.65)       , "B->Dh#pi#pi, D->hh, 3fb-1, D mixing corrected");
	gc.addPdf(57, new PDF_DsK(truth,lumi1fbPapercFit,lumi1fbPapercFit)                 , "Bs->DsK, 1fb-1 (cFit, Asimov)");
	gc.addPdf(58, new PDF_DsK(lumi1fbPapercFit,lumi1fbPapercFit,lumi1fbPapercFit)      , "Bs->DsK, 1fb-1 (cFit)");
	gc.addPdf(59, new PDF_GGSZ_Dpi(lumi3fb,lumi3fb,lumi3fb)                            , "GGSZ (B->Dpi), 3fb-1");
	gc.addPdf(60, new PDF_GGSZ(lumi3fbPaper,lumi3fbPaper,lumi3fbPaper)                 , "GGSZ, PAPER, 3fb-1");
	gc.addPdf(61, new PDF_GLWADS_DKstz_hh_Dmix(lumi3fb, lumi3fb, lumi3fb, 0.6)        , "B0 -> DK*0, 3fb-1, D mixing corrected");
  //gc.addPdf(61, new PDF_GLWADS_DKstz_hh_Dmix(lumi3fb, lumi3fb, lumi3fb, 0.68)        , "B0 -> DK*0, 3fb-1, D mixing corrected");
	gc.addPdf(62, new PDF_Dmixing_xy(hfag,hfag,hfag)                                   , "xD,yD from HFAG June 2014");
	gc.addPdf(63, new PDF_D_K3pi(belle2013cleo2014,belle2013cleo2014,belle2013cleo2014,useGaussian), "D->K3pi (Belle 2013, CLEO 2014), Gaussian");
	gc.addPdf(64, new PDF_GLWADS_DKpipi_hh(lumi3fb, lumi3fb, lumi3fb)                  , "B->DK#pi#pi, D->hh, 3fb-1");
	gc.addPdf(65, new PDF_GLWADS_DKpipi_hh_Dmix(lumi3fb, lumi3fb, lumi3fb, 0.6)       , "B->DK#pi#pi, D->hh, 3fb-1, D mixing corrected");
  //gc.addPdf(65, new PDF_GLWADS_DKpipi_hh_Dmix(lumi3fb, lumi3fb, lumi3fb, 0.65)       , "B->DK#pi#pi, D->hh, 3fb-1, D mixing corrected");
	gc.addPdf(66, new PDF_GLWADS_DK_KSKpi(lumi3fb, lumi3fb, lumi3fb)                   , "B->DK, D->K_{S}K#pi, 3fb-1");
	gc.addPdf(67, new PDF_GLWADS_DK_KSKpi_Dmix(lumi3fb, lumi3fb, lumi3fb, 0.5)        , "B->DK, D->K_{S}K#pi, 3fb-1, D mixing corrected");
  //gc.addPdf(67, new PDF_GLWADS_DK_KSKpi_Dmix(lumi3fb, lumi3fb, lumi3fb, 0.70)        , "B->DK, D->K_{S}K#pi, 3fb-1, D mixing corrected");
	gc.addPdf(68, new PDF_D_HFAGfit(hfagFP2014, hfagFP2014, hfagFP2014)                , "HFAG FP2014 D system fit");
	gc.addPdf(69, new PDF_D_K3pi(belle2013cleo2014,belle2013cleo2014,belle2013cleo2014,useGaussian,excludeKdDdK3pi), "rD(K3pi) (Belle 2013)");
	gc.addPdf(70, new PDF_D_K3pi(belle2005cleo2009,belle2005cleo2009,belle2005cleo2009,useHistogram),                "D->K3pi (Belle 2005, CLEO 2009)");
	gc.addPdf(71, new PDF_Dmixing_xy(hfagLP2011,hfagLP2011,hfagLP2011),                                              "xD,yD from HFAG LP2011");
	gc.addPdf(72, new PDF_D_Kminus3pi(cleo2014,cleo2014,cleo2014),                                                   "BF(D#rightarrowK^{-}3#pi");
	gc.addPdf(73, new PDF_D_Kplus3pi(belle2013,belle2013,belle2013),                                                 "BF(D#rightarrowK^{+}3#pi");
	gc.addPdf(74, new PDF_Dmixing_CLEO2D(cleo2014,cleo2014,cleo2014,useHistogram),                                   "CLEO 2014 K3#pi #kappa,#delta_{D}");
	gc.addPdf(101, new PDF_Dmixing_CLEO2D(cleo2009,cleo2009,cleo2009,useHistogram),                                  "CLEO 2009 K3#pi #kappa,#delta_{D}");
	gc.addPdf(75, new PDF_D_HFAGfit(hfagFP2014, hfagFP2014, hfagFP2014),                                             "HFAG FP2014 D system fit w/o Kpi");
	gc.getPdf(75)->StatErr[2] *= 100.; // dD_kpi_obs
	gc.getPdf(75)->StatErr[3] *= 100.; // RD_kpi_obs
	gc.getPdf(75)->build();
	gc.addPdf(76, new PDF_Dmixing_CLEO2D(cleo2014,cleo2014,cleo2014,useGaussian),              "CLEO 2014 K3#pi 2D (Gaussian)");
	gc.addPdf(77, new PDF_CrossCorTest1(lumi1fbPapercFit,lumi1fbPapercFit,lumi1fbPapercFit),   "Cross correlation test PDF 1");
	gc.addPdf(78, new PDF_CrossCorTest2(lumi1fbPapercFit,lumi1fbPapercFit,lumi1fbPapercFit),   "Cross correlation test PDF 2");
	gc.addPdf(79, new PDF_CrossCorTest3(gc[77],gc[78],lumi1fbPapercFit),                       "Cross correlation test PDF 3");
	// "full" cross correlations
	gc.addPdf(80, new PDF_CrossCor_Dh_hh_vs_Dh_K3pi(gc.getPdf(40),gc.getPdf(43),ckm2014));
	gc.addPdf(81, new PDF_CrossCor_Dh_hh_vs_DK_KSKpi(gc.getPdf(40),gc.getPdf(67),ckm2014));
	gc.addPdf(82, new PDF_CrossCor_Dh_hh_vs_DKst_hh(gc.getPdf(40),gc.getPdf(61),ckm2014));
	gc.addPdf(83, new PDF_CrossCor_Dh_hh_vs_Dhpipi_hh(gc.getPdf(40),gc.getPdf(56),ckm2014));
	gc.addPdf(84, new PDF_CrossCor_Dh_K3pi_vs_DK_KSKpi(gc.getPdf(43),gc.getPdf(67),ckm2014));
	gc.addPdf(85, new PDF_CrossCor_Dh_K3pi_vs_DKst_hh(gc.getPdf(43),gc.getPdf(61),ckm2014));
	gc.addPdf(86, new PDF_CrossCor_Dh_K3pi_vs_Dhpipi_hh(gc.getPdf(43),gc.getPdf(56),ckm2014));
	gc.addPdf(87, new PDF_CrossCor_DK_KSKpi_vs_DKst_hh(gc.getPdf(67),gc.getPdf(61),ckm2014));
	gc.addPdf(88, new PDF_CrossCor_DK_KSKpi_vs_Dhpipi_hh(gc.getPdf(67),gc.getPdf(56),ckm2014));
	gc.addPdf(89, new PDF_CrossCor_DKst_hh_vs_Dhpipi_hh(gc.getPdf(61),gc.getPdf(56),ckm2014));
	// "robust" cross correlations
	gc.addPdf(90, new PDF_CrossCor_DK_hh_vs_DK_K3pi(gc.getPdf(41),gc.getPdf(44),ckm2014));
	gc.addPdf(91, new PDF_CrossCor_DK_hh_vs_DK_KSKpi(gc.getPdf(41),gc.getPdf(67),ckm2014));
	gc.addPdf(92, new PDF_CrossCor_DK_hh_vs_DKst_hh(gc.getPdf(41),gc.getPdf(61),ckm2014));
	gc.addPdf(93, new PDF_CrossCor_DK_hh_vs_DKpipi_hh(gc.getPdf(41),gc.getPdf(65),ckm2014));
	gc.addPdf(94, new PDF_CrossCor_DK_K3pi_vs_DK_KSKpi(gc.getPdf(44),gc.getPdf(67),ckm2014));
	gc.addPdf(95, new PDF_CrossCor_DK_K3pi_vs_DKst_hh(gc.getPdf(44),gc.getPdf(61),ckm2014));
	gc.addPdf(96, new PDF_CrossCor_DK_K3pi_vs_DKpipi_hh(gc.getPdf(44),gc.getPdf(65),ckm2014));
	gc.addPdf(97, new PDF_CrossCor_DK_KSKpi_vs_DKst_hh(gc.getPdf(67),gc.getPdf(61),ckm2014)); // same as above
	gc.addPdf(98, new PDF_CrossCor_DK_KSKpi_vs_DKpipi_hh(gc.getPdf(67),gc.getPdf(65),ckm2014));
	gc.addPdf(99, new PDF_CrossCor_DKst_hh_vs_DKpipi_hh(gc.getPdf(61),gc.getPdf(65),ckm2014));
	gc.addPdf(100, new PDF_D_K3pi_RWS(ckm2014,ckm2014,ckm2014), "RWS(D->K3pi)");
	gc.addPdf(102, new PDF_GLWADS_DKDpi_hh(), "B->Dh, D->hh, w/o syst. limited obs.");
	gc.getPdf(102)->SystErr[0] *= 100.;  // rkp_kpi_obs
	gc.getPdf(102)->SystErr[3] *= 100.;  // afav_dk_obs
	gc.getPdf(102)->SystErr[4] *= 100.;  // afav_dpi_obs
	gc.getPdf(102)->SystErr[7] *= 100.;  // acp_dpi_kk_obs
	gc.getPdf(102)->build();
	gc.addPdf(103, new PDF_GLWADS_DKDpi_K3pi(), "B->Dh, D->K3pi, w/o syst. limited obs.");
	gc.getPdf(103)->SystErr[0] *= 100.;
	gc.getPdf(103)->SystErr[2] *= 100.;
	gc.getPdf(103)->build();
	gc.addPdf(104, new PDF_ADS_DK_Kpi(), "B->DK, D->hh, w/o syst. limited obs.");
	gc.getPdf(104)->SystErr[2] *= 100.;
	gc.getPdf(104)->build();
	gc.addPdf(105, new PDF_ADS_Dpi_Kpi(), "B->Dpi, D->Kpi (ADS), w/o syst. limited obs.");
	gc.getPdf(105)->SystErr[2] *= 100.;
	gc.getPdf(105)->build();
	gc.addPdf(106, new PDF_GLW_Dpi(), "B->Dpi, D->hh (GLW), w/o syst. limited obs.");
	gc.getPdf(106)->SystErr[0] *= 100.; // acpp_kk
	gc.getPdf(106)->build();
	gc.addPdf(107, new PDF_ADS_Dpi_K3pi(), "B->Dpi, D->K3pi, w/o syst. limited obs.");
	gc.getPdf(107)->SystErr[2] *= 100.;
	gc.getPdf(107)->build();
	gc.addPdf(108, new PDF_DsK(lumi1fbPapercFit,lumi3fb,lumi1fbPapercFit), 								"Bs->DsK, 3fb-1 (estimate)");
	// moved these from estimates to observed values of unblind LHCb-ANA-2014-071-v7 (and get repeated below for convenience)
	gc.addPdf(109, new PDF_GLWADS_DKDpi_hh_Dmix( lumi1fb, lumi3fb, lumi1fbSystCor, 0.6),  "GLWADS, D->hh, DK&Dpi, 3fb-1 (estimate)");
	gc.addPdf(110, new PDF_GLWADS_DKDpi_K3pi_Dmix(lumi1fb, lumi3fb, lumi1fbSystCor, 0.6), "ADS, D->K3pi, DK&Dpi, 3fb-1 (estimate)");
	gc.addPdf(111, new PDF_GLWADS_DKDpi_hh_Dmix( lumi3fb, lumi3fb, lumi1fbSystCor, 0.6),  "GLWADS, D->hh, DK&Dpi, 3fb-1 (estimate - ANA v7)");
	gc.addPdf(112, new PDF_D_KSKpi(cleo,cleo,cleo,useHistogram),               						"CLEO 2012 D->K_{S}K#pi Hist.");
	gc.addPdf(113, new PDF_D_Kpipi0(cleo2014,cleo2014,cleo2014,useGaussian),              "CLEO 2014 D->K#pi#pi^0 #kappa,#delta_{d} (gaus.)");
	gc.addPdf(114, new PDF_D_Kpipi0_RWS(cleo2014,cleo2014,cleo2014),               		    "CLEO 2014 D->K#pi#pi^0 RWS");
	gc.addPdf(115, new PDF_ADS_DKDpi_Kpipi0(lumi3fb,lumi3fb,lumi3fb),               			"ADS, B->Dh, D->Kpipi0, 3fb-1 (estimate)");
	gc.addPdf(116, new PDF_GLWADS_DKDpi_KSKpi_DCPV_Dmix(lumi3fb,lumi3fb,lumi3fb, 0.6),    "GLS, D->KSKpi, DK&Dpi, 3fb-1, w/ DCPV");
	gc.addPdf(117, new PDF_GLWADS_DK_KSKpi_DCPV_Dmix(lumi3fb,lumi3fb,lumi3fb, 0.6),       "GLS, D->KSKpi, DK, 3fb-1, w/ DCPV");
	gc.addPdf(118, new PDF_D_KstK_DCPV(babar2008,babar2008,babar2008),                    "CPV in D->K*K (Babar 2008)");
	gc.addPdf(119, new PDF_DsK(lumi1fbPapercFit,lumi9fb,lumi1fbPapercFit), 								"Bs->DsK, 9fb-1 (estimate)");
	gc.addPdf(120, new PDF_GLWADS_DKDpi_hh_Dmix( lumi1fb, lumi9fb, lumi1fbSystCor, 0.6),  "GLWADS, D->hh, DK&Dpi, 9fb-1 (estimate)");
	gc.addPdf(121, new PDF_GLWADS_DKDpi_K3pi_Dmix(lumi1fb, lumi9fb, lumi1fbSystCor, 0.6),  "ADS, D->K3pi, DK&Dpi, 9fb-1 (estimate)");
	gc.addPdf(122, new PDF_GLWADS_DK_KSKpi_Dmix(lumi3fb, lumi9fb, lumi3fb, 0.70),          "B->DK, D->K_{S}K#pi, 9fb-1 (estimate)");
	gc.addPdf(123, new PDF_GLWADS_DKstz_hh_Dmix(lumi3fb, lumi9fb, lumi3fb, 0.68),          "B0 -> DK*0, 9fb-1 (estimate)");
	gc.addPdf(124, new PDF_GGSZ(lumi3fbPaper,lumi9fb,lumi3fbPaper),                        "GGSZ, PAPER, 9fb-1 (estimate)");
	gc.addPdf(125, new PDF_GLWADS_Dhpipi_hh_Dmix(lumi3fb, lumi9fb, lumi3fb, 0.65),         "B->Dh#pi#pi, D->hh, 9fb-1 (estimate)");
	gc.addPdf(126, new PDF_DsK(lumi1fbPapercFit,lumi50fb,lumi1fbPapercFit),                "Bs->DsK, 50fb-1 (estimate)");
	gc.addPdf(127, new PDF_GLWADS_DKDpi_hh_2012(lumi3fb,lumi3fb,lumi3fb),                  "GLWADS, D->hh, DK&Dpi, 3fb-1 (2012)");
	gc.addPdf(128, new PDF_gamma(year2014,year2014,year2014),                              "CKMfitter gamma 2014");
	gc.addPdf(129, new PDF_GLWADS_DKDpi_hhpi0(lumi3fb, lumi3fb, lumi3fb),                  "GLWADS, B->Dh, D->hh#pi^{0}, 3fb^{-1}");
	gc.addPdf(130, new PDF_D_hhpi0_dilution(cleo, cleo, cleo),                             "CLEO legacy constraints on D->hhpi0 CP dilution");
	gc.addPdf(131, new PDF_GLWADS_DKDpi_hhpi0_Dmix(lumi3fb, lumi3fb, lumi3fb, 0.592),      "GLWADS, B->Dh, D->hh#pi^{0}, 3fb^{-1}, Dmix corrected");
	gc.addPdf(132, new PDF_GLWADS_DK_hhpi0(lumi3fb, lumi3fb, lumi3fb),                     "GLWADS, B->DK, D->hh#pi^{0}, 3fb^{-1}");
	gc.addPdf(133, new PDF_GGSZ(lumi3fbDKstz,lumi3fbDKstz,lumi3fbDKstz),                   "DK* GGSZ, 3fb^{-1}, estimated from DK");
	gc.addPdf(134, new PDF_GLWADS_DK_hhpi0_Dmix(lumi3fb, lumi3fb, lumi3fb, 0.592),         "GLWADS, B->DK, D->hh#pi^{0}, 3fb^{-1}, Dmix corrected");
	gc.addPdf(135, new PDF_D_Kpipi0(cleo2014,cleo2014,cleo2014,useHistogram),              "CLEO 2014 D->K#pi#pi^0 #kappa,#delta_{d} (hist.)");
  gc.addPdf(136, new PDF_GGSZ_DKstz(lumi3fb, lumi3fb, lumi3fb),                          "DK* GGSZ, 3fb^{-1}, estimate, no correlation");
  gc.addPdf(137, new PDF_GGSZ_DKstz(lumi3fb, lumi3fb, lumi3fb_estimate),                 "DK* GGSZ, 3fb^{-1}, estimate, corrs from DK GGSZ");
	// GLW/ADS update
	// 2-body
	gc.addPdf(138, new PDF_GLWADS_DKDpi_hh_Dmix( lumi3fb, lumi3fb, lumi1fbSystCor, 0.6),  "GLWADS, D->hh, DK&Dpi, 3fb-1 (ANA v7)");
	gc.addPdf(139, new PDF_GLWADS_DK_hh_Dmix( lumi3fb, lumi3fb, lumi1fbSystCor, 0.6),     "GLWADS, D->hh, DK, 3fb-1 (ANA v7)");
	// 4-body
	gc.addPdf(140, new PDF_GLWADS_DKDpi_K3pi_Dmix(lumi3fb, lumi3fb, lumi1fbSystCor, 0.6), "ADS, D->K3pi, DK&Dpi, 3fb-1 (ANA v7)");
	gc.addPdf(141, new PDF_GLWADS_DK_K3pi_Dmix(lumi3fb, lumi3fb, lumi1fbSystCor, 0.6),    "ADS, D->K3pi, DK, 3fb-1 (ANA v7)");
	// with new vars
	gc.addPdf(142, new PDF_GLWADS_DKDpi_hh_Dmix_newVars(lumi3fb, lumi3fb, lumi3fb, 0.594),  "GLWADS, B->Dh, D->hh, 3bf-1 D mixing");
	gc.addPdf(143, new PDF_GLWADS_DK_hh_Dmix_newVars(lumi3fb, lumi3fb, lumi3fb, 0.594),     "GLWADS, B->DK, D->hh, 3fb-1 D mixing");
	gc.addPdf(144, new PDF_GLWADS_DKDpi_K3pi_Dmix_newVars(lumi3fb, lumi3fb, lumi3fb, 0.570),"GLWADS, B->Dh, D->hhhh, 3fb-1 D mixing");
	gc.addPdf(145, new PDF_GLWADS_DK_K3pi_Dmix_newVars(lumi3fb, lumi3fb, lumi3fb, 0.570),   "GLWADS, B->DK, D->hhhh, 3fb-1 D mixing");
	// CLEO D->4pi etc.
	gc.addPdf(146, new PDF_Dmixing_CLEOFCP(cleo2015, cleo2015, cleo2015), 								"CLEO D->4pi CP content");
	// new HFAG
	gc.addPdf(147, new PDF_D_HFAGfit(hfagCHARM2015, hfagCHARM2015, hfagCHARM2015),        "HFAG CHARM2015 D system fit w/o Kpi");
	// CLEO D->hhpi0 update
  gc.addPdf(148, new PDF_D_hhpi0_dilution(cleo2015, cleo2015, cleo2015),                "CLEO D->2hpi0 CP content");
	gc.addPdf(149, new PDF_D_Kpipi0_RWS(pdg,pdg,pdg),               		                  "PDG D->K#pi#pi^0 RWS");

  // Dmixing from Sam
  gc.addPdf(150, new PDF_Dmixing_K3pi(lhcb2012, lhcb2012, lhcb2012), "LHCb 2012 Tagged D->K3pi"  );
  gc.addPdf(151, new PDF_Dmixing_xy(lhcb2012,lhcb2012,lhcb2012)    , "xD,yD from HFAG June 2014");


	///////////////////////////////////////////////////
	//
	// Define combinations
	//
	///////////////////////////////////////////////////

	gc.newCombiner(0, "empty", "empty");
	gc.newCombiner(8, "empty", "empty");

	gc.newCombiner(1,  "dktrad",       "B #rightarrow DK", 18, 1, 48, 49, 9);
	gc.newCombiner(2,  "dhk3pihist",   "Dh K3#pi only (using Cleo histogram)", 11, 13 );
	gc.newCombiner(3,  "dhk3pigaus",   "Dh K3#pi only (using Gaussian Cleo)", 11, 14 );
	gc.newCombiner(4,  "dkdpi",        "DK & D#pi full combination", 18, 10, 11, 9, 15 );
	gc.newCombiner(5,  "dkdpigaus",    "DK & D#pi full combination (all Gaussian Cleo)", 18, 10, 11, 16, 15 );
	gc.newCombiner(6,  "dkdpiNewDacp", "DK & D#pi full combination (new #DeltaAcp treatment)", 18, 10, 11, 9, 17 );
	gc.newCombiner(7,  "ggsz",         "GGSZ (1fb^{-1})", 18 );
	gc.newCombiner(9,  "dpionly",      "D#pi only", 2, 5, 6, 9 );
	gc.newCombiner(10, "dkdpiNoSystLim",   "DK & D#pi full combination (w/o syst. limited obs.)", 18, 9, 17, 102, 103);
	gc.newCombiner(11, "dkonlyNoSystLim",  "DK only (w/o syst. limited obs.)", 18, 1, 104, 4, 9);
	gc.newCombiner(12, "dpionlyNoSystLim", "D#pi only (w/o syst. limited obs.)", 105, 106, 107, 9);
	gc.newCombiner(13, "dkonlycor",          "DK only", 18, 19, 20, 9, 17);
	gc.newCombiner(14, "dpionlycor",         "D#pi only", 21, 22, 9, 17);
	gc.newCombiner(15, "dpionlygaus",        "D#pi only (using Gaussian Cleo)", 2, 5, 6, 16);
	gc.newCombiner(16, "dkdpiNewDacpGgszSystCor", "B#rightarrowDK and B#rightarrowD#pi", 18, 10, 11, 9, 17);
	gc.newCombiner(17, "dkonlycorDmix",      "DK only (with LHCb D mixing)", 18, 19, 20, 9, 17, 23);
	gc.newCombiner(18, "dpionlycorDmix",     "D#pi only (with LHCb D mixing)", 21, 22, 9, 17, 23);
	gc.newCombiner(19, "dkdpiNewDacpGgszSystCorDmix", "DK & D#pi (with LHCb D mixing)", 18, 10, 11, 9, 17, 23);
	gc.newCombiner(20, "dpionlycorTwoBody",     "D#pi only (two body only)", 21, 9, 17);
	gc.newCombiner(21, "dkGlwAds",              "1fb^{-1} B#rightarrowDK GLW/ADS", 19, 20, 9, 17);
	gc.newCombiner(22, "dkonlyWithSystCor",     "DK only (with syst cor)", 18, 25, 28, 9, 17);
	gc.newCombiner(23, "dpionlyWithSystCor",    "D#pi only (with syst cor)", 26, 29, 9, 17);
	gc.newCombiner(24, "dkdpiWithSystCor",      "DK & D#pi (with syst cor)", 18, 24, 27, 9, 17);
	gc.newCombiner(25, "dkonly3fbGGSZ",         "DK only (3fb^{-1} GGSZ)", 30, 25, 28, 9, 17);
	gc.newCombiner(26, "3fbGGSZ",               "3fb^{-1} B#rightarrowDK GGSZ", 30);
	gc.newCombiner(27, "2fbGGSZ",               "2fb^{-1} GGSZ", 31);
	gc.newCombiner(28, "1and2fbGGSZ",           "1+2fb^{-1} GGSZ", 18, 31);
	gc.newCombiner(29, "dkdpiWithDacpSl",       "DK & D#pi (with SL #DeltaA_{CP})", 18, 10, 11, 9, 17, 32);
	gc.newCombiner(30, "dpionlycorWithDacpSl",  "D#pi only (with SL #DeltaA_{CP})", 21, 22, 9, 17, 32);
	gc.newCombiner(31, "dkdpi3fbGGSZ",          "DK & D#pi (3fb^{-1} GGSZ)", 30, 10, 11, 9, 17);
	gc.newCombiner(32, "3fbGGSZtruth",          "3fb^{-1} GGSZ (rB=0.3, g=70, dB=114)", 52,53);

	// using the D mixing corrections
	gc.newCombiner(51, "dkonlyDmixeq",  "DK only (D mix.eq.)",     35, 38, 9, 17, 18);
	gc.newCombiner(52, "dpionlyDmixeq", "D#pi only (D mix.eq.)",   36, 39, 9, 17);
	gc.newCombiner(53, "dkdpiDmixeq",   "DK and D#pi (D mix.eq.)", 34, 37, 9, 17, 18);

	// NOMINAL PUBLISHED 1FB-1 [ adding the LHCb D mixing measurement ]
	gc.cloneCombiner(54, 51, "dkonlyDmixeqDmixmeas",  "B#rightarrowDK (D mix.eq., D mix.meas.)");
	gc.getCombiner(54)->addPdf(gc[23]);
	gc.cloneCombiner(55, 52, "dpionlyDmixeqDmixmeas", "B#rightarrowD#pi (D mix.eq., D mix.meas.)");
	gc.getCombiner(55)->addPdf(gc[23]);
	gc.cloneCombiner(56, 53, "dkdpiDmixeqDmixmeas",   "B#rightarrowDK and B#rightarrowD#pi");
	gc.getCombiner(56)->addPdf(gc[23]);

	// checking the effect of using the GLW/ADS systematic correlations
	gc.newCombiner(57, "dkonlyDmixeqDmixmeasSystcor",  "DK only (D mix.eq., D mix.meas., syst.cor.)",     41, 44, 9, 17, 18, 23);
	gc.newCombiner(58, "dpionlyDmixeqDmixmeasSystcor", "D#pi only (D mix.eq., D mix.meas., syst.cor.)",   42, 45, 9, 17,     23);
	gc.newCombiner(59, "dkdpiDmixeqDmixmeasSystcor",   "DK and D#pi (D mix.eq., D mix.meas., syst.cor.)", 40, 43, 9, 17, 18, 23);

	//   // include 3fb-1 GGSZ
	//   gc.cloneCombiner(60, 54, "dkonlyDmixeqDmixmeas3fbGgsz", "B#rightarrowDK (3fb^{-1} GGSZ)");
	// gc.getCombiner(60)->replacePdf(18, 30);
	//   gc.cloneCombiner(61, 56, "dkdpiDmixeqDmixmeas3fbGgsz",  "B#rightarrowDK and B#rightarrowD#pi (3fb^{-1} GGSZ)");
	// gc.getCombiner(61)->replacePdf(18, 30);

	gc.newCombiner(62, "dkGlwAdsDmixeqDmixmeas", "1fb^{-1} B#rightarrowDK GLW/ADS", 35, 38, 9, 17, 23);

	//   // Check effect of 3fb DK*0 (blinded) on the full combination.
	//   gc.cloneCombiner(63, 54, "dkonlyDmixeqDmixmeasWDKstz",        "B#rightarrowDK (1fb^{-1}) with DK^{*0} (3fb^{-1}, blinded)"));
	// gc.getCombiner(63)->addPdf(46,47);
	// gc.cloneCombiner(64, 60, "dkonlyDmixeqDmixmeas3fbGgszWDKstz", "B#rightarrowDK (3fb^{-1}) with DK^{*0} (3fb^{-1}, blinded)"));
	// gc.getCombiner(64)->addPdf(46,47);
	//   gc.cloneCombiner(65, 61, "dkdpiDmixeqDmixmeas3fbGgszWDKstz",  "B#rightarrowDh (3fb^{-1}) with DK^{*0} (3fb^{-1}, blinded)"));
	// gc.getCombiner(65)->addPdf(46,47);

	// educational: GGSZ in cartesian coordinates with a constraint on rB
	gc.newCombiner(66, "educationalGgsz", "cart. GGSZ", 50);
	gc.getCombiner(66)->fixParameters("xp_dk,yp_dk");
	gc.newCombiner(67, "educationalRb", "cart. rB", 51);
	gc.getCombiner(67)->fixParameters("xp_dk,yp_dk");
	gc.newCombiner(68, "educationalGgszRb", "cart. GGSZ with rB constraint", 50, 51);
	gc.getCombiner(68)->fixParameters("xp_dk,yp_dk");

	// nominal 1fb-1 without GGSZ
	gc.cloneCombiner(69, 56, "dkdpi1fbGlwads",     "B#rightarrowDK and B#rightarrowD#pi GLW/ADS");
	gc.getCombiner(69)->delPdf(gc[18]);

	// debug Bayesians [ nominal 1fb w/o D CPV and D mixing inputs ]:
	gc.cloneCombiner(70, 53, "dkdpiDmixeqNodcpv",  "B#rightarrowDK and B#rightarrowD#pi w/o HFAG D CPV");
	gc.getCombiner(70)->delPdf(gc[17]);

	// DsK
	gc.newCombiner(71, "dsk_sfit", "DsK 1fb-1 (sFit)", 12);

	// KSKPi ADS alone
	gc.newCombiner(72, "KsKpi",     "B#rightarrowDK and D#pi, D#rightarrowK_{S}K#pi (3fb^{-1})", 52,53);
	gc.newCombiner(73, "KsKpiDmix", "B#rightarrowDK and D#pi, D#rightarrowK_{S}K#pi (3fb^{-1}), Dmix", 52,54,23);

	// B->Dhpipi, D->hh, GLW/ADS alone
	gc.newCombiner(74, "Dhpipi",     "B#rightarrowDh#pi#pi, D#rightarrowhh (3fb^{-1})",       55,7,17);
	gc.newCombiner(75, "DhpipiDmix", "B#rightarrowDh#pi#pi, D#rightarrowhh (3fb^{-1}), Dmix", 56,7,17,62);

	// // RUNNING AVERAGE
	// gc.cloneCombiner(76, 61, "dkdpiRunning",  "running average"));
	// gc.getCombiner(76)->addPdf(56);         	// 3fb-1 Dhpipi, D->hh
	// gc.getCombiner(76)->addPdf(54,52); 			// 3fb-1 Dh,     D->KSKpi (published)
	// gc.getCombiner(76)->addPdf(47,61);				// 3fb-1 DK*,    D->hh
	// gc.getCombiner(76)->addPdf(58);         	// 3fb-1 DsK
	// gc.getCombiner(76)->replacePdf(34, 40); 	// replace 1fb-1 hh with the version using syst. correlations
	// gc.getCombiner(76)->replacePdf(37, 43); 	// replace 1fb-1 K3pi with the version using syst. correlations
	// gc.getCombiner(76)->replacePdf(30, 60); 	// replace 3fb-1 GGSZ CONF by PAPER

	// B->DK* alone
	gc.newCombiner(77, "dkstz",      "B#rightarrowDK^{*} (3fb^{-1})", 46,47,17,7);

	// DsK
	gc.newCombiner(78, "dsk_cfit", "DsK 1fb-1 (cFit)", 58);

	// // B->DK* alone with D mixing
	// gc.cloneCombiner(79, 77, "dkstzDmix",  "B#rightarrowDK^{*} (3fb^{-1}), D mixing corrected");
	// gc.getCombiner(79)->replacePdf(46, 61);
	// // gc.getCombiner(79)->addPdf(23); // LHCb D mixing
	// gc.getCombiner(79)->addPdf(62); // HFAG D mixing

	// K3pi ADS alone
	gc.newCombiner(80, "dhk3pi", "B->Dh, D->K3#pi only (using new Cleo)", 37,63,62);

	// CKM 2014: robust combination w/ old Cleo K3pi
	gc.newCombiner(81, "ckm2014robustOldK3pi", "robust (old Cleo K3pi)");
	gc.getCombiner(81)->addPdf(gc[65]);        // B->DK#pi#pi, D->hh, 3fb-1, D mixing corrected
	gc.getCombiner(81)->addPdf(gc[67], gc[52]);   	// B->DK, D->K_{S}K#pi, 3fb-1, D mixing corrected, CLEO D->K_{S}K#pi
	gc.getCombiner(81)->addPdf(gc[61], gc[47]);   	// B0 -> DK*0, 3fb-1, D mixing corrected, B0 -> DK*0 coherence factor (95+/-3)%
	gc.getCombiner(81)->addPdf(gc[58]);        // Bs->DsK, 1fb-1 (cFit)
	gc.getCombiner(81)->addPdf(gc[41]);        // GLWADS, D->hh, DK, 1fb-1, D mixing corrected, w/ syst.cor.
	gc.getCombiner(81)->addPdf(gc[44]);        // ADS, D->K3pi, DK, 1fb-1, D mixing corrected, w/ syst.cor.
	gc.getCombiner(81)->addPdf(gc[60]);        // GGSZ, PAPER, 3fb-1
	gc.getCombiner(81)->addPdf(gc[17], gc[23], gc[9]); // HFAG D CPV, LHCb D mixing, 1fb-1, CLEO 2009, likelihood

	// CKM 2014: full combination w/ old Cleo K3pi
	gc.cloneCombiner(82, 81, "ckm2014fullOldK3pi", "full (old Cleo K3pi)");
	gc.getCombiner(82)->replacePdf(gc[65],gc[56]); // B->DK#pi#pi         => B->Dh#pi#pi
	gc.getCombiner(82)->replacePdf(gc[67],gc[54]); // B->DK, D->K_{S}K#pi => B->Dh, D->K_{S}K#pi
	gc.getCombiner(82)->replacePdf(gc[41],gc[40]); // B->DK, D->hh        => B->Dh, D->hh
	gc.getCombiner(82)->replacePdf(gc[44],gc[43]); // B->DK, D->K3pi      => B->Dh, D->K3pi

	// CKM 2014: robust combination
	gc.newCombiner(83, "ckm2014robust", "robust CKM2014, with Dhpipi");
	gc.getCombiner(83)->addPdf(gc[65]);     		// B->DK#pi#pi, D->hh, 3fb-1, D mixing corrected
	gc.getCombiner(83)->addPdf(gc[67],gc[52]);	// B->DK, D->K_{S}K#pi, 3fb-1, D mixing corrected, CLEO D->K_{S}K#pi
	gc.getCombiner(83)->addPdf(gc[61],gc[47]);	// B0 -> DK*0, 3fb-1, D mixing corrected, B0 -> DK*0 coherence factor (95+/-3)%
	gc.getCombiner(83)->addPdf(gc[58]);      		// Bs->DsK, 1fb-1 (cFit)
	gc.getCombiner(83)->addPdf(gc[41]);      		// GLWADS, D->hh, DK, 1fb-1, D mixing corrected, w/ syst.cor.
	gc.getCombiner(83)->addPdf(gc[44]);      		// ADS, D->K3pi, DK, 1fb-1, D mixing corrected, w/ syst.cor.
	gc.getCombiner(83)->addPdf(gc[60]);      		// GGSZ, PAPER, 3fb-1
	gc.getCombiner(83)->addPdf(gc[68]);      		// HFAG FP2014 D system fit
	gc.getCombiner(83)->addPdf(gc[100],gc[74]);	// auxilary K3pi constraints (using RWS)

	// CKM 2014: full combination
	gc.cloneCombiner(84, 83, "ckm2014full", "full CKM2014, with Dhpipi");
	gc.getCombiner(84)->replacePdf(gc[65],gc[56]); // B->DK#pi#pi         => B->Dh#pi#pi
	gc.getCombiner(84)->replacePdf(gc[41],gc[40]); // B->DK, D->hh        => B->Dh, D->hh
	gc.getCombiner(84)->replacePdf(gc[44],gc[43]); // B->DK, D->K3pi      => B->Dh, D->K3pi

	// CKM 2014: exclude Kpi from full and robust combinations
	gc.cloneCombiner(85, 83, "ckm2014robustNoKpi", "robust w/o Kpi");
	gc.getCombiner(85)->replacePdf(gc[68],gc[75]);
	gc.cloneCombiner(86, 84, "ckm2014fullNoKpi", "full w/o Kpi");
	gc.getCombiner(86)->replacePdf(gc[68],gc[75]);

	// estimate the full 3fb-1 sensitivity
	gc.cloneCombiner(87, 84, "full3invfb", "full, extrapolated to 3fb^{-1}");
	gc.getCombiner(87)->replacePdf(gc[58],gc[108]);
	gc.getCombiner(87)->replacePdf(gc[40],gc[109]);
	gc.getCombiner(87)->replacePdf(gc[43],gc[110]);

	// CKM 2014: exclude B->Dhpipi from full and robust combinations
	gc.cloneCombiner(88, 83, "ckm2014robustNoDhpipi", "robust CKM2014");
	gc.getCombiner(88)->delPdf(gc[65]);
	gc.cloneCombiner(89, 84, "ckm2014fullNoDhpipi", "full CKM2014");
	gc.getCombiner(89)->delPdf(gc[56]);

	// CKM 2014: exclude B->Dhpipi from full and robust combinations, exclude Kpi from full and robust combinations
	gc.cloneCombiner(90, 88, "ckm2014robustNoDhpipiNoKpi", "robust CKM2014 w/o DK#pi#pi and K#pi");
	gc.getCombiner(90)->replacePdf(gc[68],gc[75]);
	gc.cloneCombiner(91, 89, "ckm2014fullNoDhpipiNoKpi", "full CKM2014 w/o DK#pi#pi and K#pi");
	gc.getCombiner(91)->replacePdf(gc[68],gc[75]);

	// CKM 2014: add D->K*K CP violation to full and robust combinations
	gc.cloneCombiner(92, 88, "ckm2014robustNoDhpipiAddKstKCPV", "robust CKM2014 w/ DCPV in K*K");
	gc.getCombiner(92)->replacePdf(gc[67],gc[117]);
	gc.getCombiner(92)->addPdf(gc[118]);
	gc.cloneCombiner(93, 89, "ckm2014fullNoDhpipiAddKstKCPV", "full CKM2014 w/ DCPV in K*K");
	gc.getCombiner(93)->replacePdf(gc[67],gc[117]);
	gc.getCombiner(93)->addPdf(gc[118]);

	// 9fb-1 full combination estimate
	gc.newCombiner(94,  "full9invfb",       "full, extrapolated to 9fb^{-1}", 119, 120, 121, 122, 123, 124, 125, 52, 47, 68, 100, 74);

	gc.newCombiner(95,  "ggszDkstz",         "DK* GGSZ (3fb^{-1})", 132 );

	// B->Dh, D->hhpi0
	gc.newCombiner(96,  "BDKwithDhhpi0",     "B #rightarrow DK, D #rightarrow hh#pi^{0} (3fb^{-1})", 134, 135, 114, 62, 130);
	gc.newCombiner(97,  "BDhwithDhhpi0",     "B #rightarrow Dh, D #rightarrow hh#pi^{0} (3fb^{-1})", 131, 135, 114, 62, 130);

	// FPCP 2015
	gc.cloneCombiner(98, 88, "fpcp2015robust", "robust FPCP2015");
	gc.getCombiner(98)->addPdf(gc[134],gc[135],gc[114],gc[130]); // B->DK, D->hhpi0
	gc.cloneCombiner(99, 89, "fpcp2015full", "full FPCP2015");
	gc.getCombiner(99)->addPdf(gc[131],gc[135],gc[114],gc[130]); // B->Dh, D->hhpi0

	// B->Dhpipi alone (Steve)
	gc.newCombiner(100,  "BDhpipi",   "B#rightarrowDh#pi#pi, D#rightarrowhh, 3fb^{-1}", 56, 147);
	gc.newCombiner(101,  "BDKpipi",   "B#rightarrowDK#pi#pi, D#rightarrowhh, 3fb^{-1}", 65, 147);

  // B->DK* GGSZ (Alexis)
  gc.newCombiner(102, "BDKstzGGSZ", "B^{0}#rightarrow DK*", 136);

	// GLW/ADS studies (for 3fb update)
	gc.newCombiner(103, "B_DK_hh",     "B #rightarrow DK (2-body)"      , 143, 147); // w HFAG charm
	gc.newCombiner(104, "B_Dh_hh",     "B #rightarrow Dh (2-body)"      , 142, 147); // w HFAG charm
	gc.newCombiner(105, "B_DK_K3pi",   "B #rightarrow DK (4-body)"      , 145, 147, 74, 100, 146); // w HFAG, CLEO 2014, RWS, CLEO 4pi
	gc.newCombiner(106, "B_Dh_K3pi",   "B #rightarrow Dh (4-body)"      , 144, 147, 74, 100, 146); // w HFAG, CLEP 2014, RWS, CLEO 4pi
	gc.newCombiner(107, "B_DK_GLWADS", "B #rightarrow DK (2 and 4-body)", 143, 145, 147, 74, 100, 146); // w HFAG, CLEO 2014, RWS, CLEO 4pi
	gc.newCombiner(108, "B_DK_GLWADS", "B #rightarrow Dh (2 and 4-body)", 142, 144, 147, 74, 100, 146); // w HFAG, CLEO 2014, RWS, CLEO 4pi
	// new combinations
	// CKM 2014 robust with GLW/ADS update
	gc.cloneCombiner(109, 83, "ckm2014_robust_wglwads", "B #rightarrow DK CKM2014 + GLWADS");
	gc.getCombiner(109)->replacePdf( gc[41], gc[143] ); // 2-body GLW/ADS
	gc.getCombiner(109)->replacePdf( gc[44], gc[145] ); // 4-body GLW/ADS
	gc.getCombiner(109)->replacePdf( gc[68], gc[147] ); // HFAG charm update
	gc.getCombiner(109)->addPdf( gc[146] ); 						// CLEO 4pi

	// CKM 2014 full with GLW/ADS update
	gc.cloneCombiner(110, 84, "ckm2014_full_wglwads", "B #rightarrow Dh CKM2014 + GLWADS");
	gc.getCombiner(110)->replacePdf( gc[40], gc[142] ); // 2-body GLW/ADS
	gc.getCombiner(110)->replacePdf( gc[43], gc[144] ); // 4-body GLW/ADS
	gc.getCombiner(110)->replacePdf( gc[68], gc[147] ); // HFAG charm update
	gc.getCombiner(110)->addPdf( gc[146] ); 						// CLEO 4pi

	// FPCP 2015 with GLW/ADS update
	gc.cloneCombiner(111, 98, "fpcp2015_robust_wglwads", "B #rightarrow DK Latest");
	gc.getCombiner(111)->replacePdf( gc[41], gc[143] ); // 2-body GLW/ADS
	gc.getCombiner(111)->replacePdf( gc[44], gc[145] ); // 4-body GLW/ADS
	gc.getCombiner(111)->replacePdf( gc[68], gc[147] ); // HFAG charm update
	gc.getCombiner(111)->addPdf( gc[146] ); 						// CLEO 4pi

	gc.cloneCombiner(112, 99, "fpcp2015_full_wglwads", "B #rightarrow Dh Latest");
	gc.getCombiner(112)->replacePdf( gc[40], gc[142] ); // 2-body GLW/ADS
	gc.getCombiner(112)->replacePdf( gc[43], gc[144] ); // 4-body GLW/ADS
	gc.getCombiner(112)->replacePdf( gc[68], gc[147] ); // HFAG charm update
	gc.getCombiner(112)->addPdf( gc[146] ); 						// CLEO 4pi

	// LHCP 2015 robust
	gc.newCombiner(113, "lhcp2015robust", "robust LHCP2015");
	gc.getCombiner(113)->addPdf(gc[143]); 			            // 2-body GLW/ADS, B->DK    , D->hh   , 3fb-1, D mixing
	gc.getCombiner(113)->addPdf(gc[145]); 			            // 4-body GLW/ADS, B->DK    , D->4h   , 3fb-1, D mixing
	gc.getCombiner(113)->addPdf(gc[65]);                    // 2-body GLW/ADS, B->DKpipi, D->hh   , 3fb-1, D mixing
	gc.getCombiner(113)->addPdf(gc[134]); 									// 3-body GLW/ADS, B->DK    , D->hhpi0, 3fb-1, D mixing, CLEO hhpi0 constraints
	gc.getCombiner(113)->addPdf(gc[67],gc[112]);             // 3-body GLW/ADS, B->DK    , D->KSKpi, 3fb-1, D mixing, CLEO D->KSKpi
  // could switch 52 -> 112 to get CLEO histogram instead
	gc.getCombiner(113)->addPdf(gc[61],gc[47]);             // 2-body GLW/ADS, B0->DK*0 , D->hh   , 3fb-1, D mixing, B0 -> DK*0 coherence factor
	gc.getCombiner(113)->addPdf(gc[58]);                    // Bs->DsK       , Bs->DsK            , 1fb-1 (cFit)
	gc.getCombiner(113)->addPdf(gc[60]);                    // GGSZ          , B->DK    , D->KShh , 3fb-1
	gc.getCombiner(113)->addPdf(gc[147]);                   // HFAG CHARM2015 D system fit
	gc.getCombiner(113)->addPdf(gc[100],gc[74]);            // CLEO K3pi constraints (with RWS)
	gc.getCombiner(113)->addPdf(gc[146]);                   // CLEO 4pi constraints
	gc.getCombiner(113)->addPdf(gc[135],gc[149],gc[148]);   // CLEO hhpi0 constraints (with RWS and dilution)

	// LHCP 2015 full
	gc.cloneCombiner(114, 113, "lhcp2015full", "full LHCP2015");
	gc.getCombiner(114)->replacePdf(gc[143],gc[142]);  		  // B->DK      , D->hh     => B->Dh      , D->hh
	gc.getCombiner(114)->replacePdf(gc[145],gc[144]); 			// B->DK      , D->4h     => B->Dh      , D->4h
	gc.getCombiner(114)->replacePdf(gc[65] ,gc[56]); 				// B->DKpipi  , D->hh     => B->Dhpipi  , D->hh
	gc.getCombiner(114)->replacePdf(gc[134],gc[131]); 			// B->DK      , D->hhpi0  => B->Dh      , D->hhpi0
	gc.getCombiner(114)->replacePdf(gc[67],gc[54]);         // B->DK      , D->KSKpi  => B->Dh      , D->KSKpi

	// LHCP 2015 B+ -> DK+ only
	gc.newCombiner(115, "lhcp2015bp2dkp","Only B+ -> DK+ LHCP2015");
	gc.getCombiner(115)->addPdf(gc[143]); 			            // 2-body GLW/ADS, B->DK    , D->hh   , 3fb-1, D mixing
	gc.getCombiner(115)->addPdf(gc[145]); 			            // 4-body GLW/ADS, B->DK    , D->4h   , 3fb-1, D mixing
	gc.getCombiner(115)->addPdf(gc[134]); 									// 3-body GLW/ADS, B->DK    , D->hhpi0, 3fb-1, D mixing, CLEO hhpi0 constraints
	gc.getCombiner(115)->addPdf(gc[67],gc[112]);             // 3-body GLW/ADS, B->DK    , D->KSKpi, 3fb-1, D mixing, CLEO D->KSKpi
  // could switch 52 -> 112 to get CLEO histogram instead
	gc.getCombiner(115)->addPdf(gc[60]);                    // GGSZ          , B->DK    , D->KShh , 3fb-1
	gc.getCombiner(115)->addPdf(gc[147]);                   // HFAG CHARM2015 D system fit
	gc.getCombiner(115)->addPdf(gc[100],gc[74]);            // CLEO K3pi constraints (with RWS)
	gc.getCombiner(115)->addPdf(gc[146]);                   // CLEO 4pi constraints
	gc.getCombiner(115)->addPdf(gc[135],gc[149],gc[148]);   // CLEP hhpi0 constraints (with RWS and dilution)

  //Added by Sam to test Tagged D->K3pi input (and the combination of that with CLEO input)
  gc.newCombiner(116, "CLEO2014", "CLEO D #rightarrow K3#pi", 74);
  gc.newCombiner(117, "lhcbdmixingk3piwHFAG", "LHCb D #rightarrow K3#pi w/ HFAG", 150, 151);
  gc.newCombiner(118, "lhcbdmixingk3piwHFAGandCLEO2014", "LHCb D #rightarrow K3#pi w/ HFAG and CLEO", 74, 150, 151);

	///////////////////////////////////////////////////
	//
	// Run
	//
	///////////////////////////////////////////////////

	return gc;
}
