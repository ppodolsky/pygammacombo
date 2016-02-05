#include "ParametersGammaCombo.h"

ParametersGammaCombo::ParametersGammaCombo()
{
	defineParameters();
}

///
/// Define all (nuisance) parameters.
///
///  scan:      defines scan range (for Prob and Plugin methods)
///  phys:      physically allowed range (needs to be set!)
///  bboos:     Ranges for Berger-Boos method
///  force:     min, max used by the force fit method
///
void ParametersGammaCombo::defineParameters()
{
	Parameter *p = 0;

	p = newParameter("g");
	p->title = "#gamma";
	p->startvalue = DegToRad(70);
	// p->startvalue = DegToRad(119);
	p->unit = "Rad";
	// p->unit = "";
	p->scan = range(DegToRad(0), DegToRad(180));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(0), DegToRad(90));
	p->bboos = range(DegToRad(0), DegToRad(180));

	p = newParameter("d_dk");
	//p->title = "#delta_{B}^{K}";
	p->title = "#delta_{B}^{DK}";
	p->startvalue = DegToRad(127);
	p->unit = "Rad";
	p->scan = range(DegToRad(0), DegToRad(180));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(0), DegToRad(90));
	p->bboos = range(DegToRad(-180), DegToRad(180)); // B -> DK

	p = newParameter("r_dk");
	// p->title = "r_{B}^{K}";
	p->title = "r_{B}^{DK}";
	p->startvalue = 0.09;
	p->unit = "";
	p->scan = range(0.02, 0.2);
	p->phys = range(0, 1e4);
	p->force = range(0.02, 0.16);
	p->bboos = range(0.01, 0.22); // B -> DK

	p = newParameter("xm_dk");
	p->title = "x- (DK)";
	p->startvalue = 0;
	p->unit = "";
	p->scan = range(-0.2, 0.2);
	p->phys = range(-1e4, 1e4);
	p->force = range(-0.2, 0.2);
	p->bboos = range(0.01, 0.22); // B -> DK

	p = newParameter("ym_dk");
	p->title = "y- (DK)";
	p->startvalue = 0;
	p->unit = "";
	p->scan = range(0.0, 0.3);
	p->phys = range(-1e4, 1e4);
	p->force = range(-0.2, 0.2);
	p->bboos = range(0.01, 0.22); // B -> DK

	p = newParameter("xp_dk");
	p->title = "x+ (DK)";
	p->startvalue = 0;
	p->unit = "";
	p->scan = range(-0.2, 0.2);
	p->phys = range(-1e4, 1e4);
	p->force = range(-0.2, 0.2);
	p->bboos = range(0.01, 0.22); // B -> DK

	p = newParameter("yp_dk");
	p->title = "y+ (DK)";
	p->startvalue = 0;
	p->unit = "";
	p->scan = range(-0.2, 0.2);
	p->phys = range(-1e4, 1e4);
	p->force = range(-0.2, 0.2);
	p->bboos = range(0.01, 0.22); // B -> DK

	p = newParameter("RBRdkdpi");
	p->title = "RBRdkdpi";
	p->startvalue = 0.076;
	p->unit = "";
	p->scan = range(0.07, 0.09);
	p->phys = range(0, 1e4);
	p->force = range(0.07, 0.09);
	p->bboos = range(0.02, 0.27); // B -> DK / B -> Dpi

	p = newParameter("d_dpi");
	// p->title = "#delta_{B}^{#pi}";
	p->title = "#delta_{B}^{D#pi}";
	p->startvalue = DegToRad(223);;
	p->unit = "Rad";
	// p->scan = range(DegToRad(0), DegToRad(180));
	p->scan = range(DegToRad(180), DegToRad(360));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(0), DegToRad(90));
	p->bboos = range(DegToRad(-180), DegToRad(180)); // B -> Dpi

	p = newParameter("r_dpi");
	// p->title = "r_{B}^{#pi}";
	p->title = "r_{B}^{D#pi}";
	p->startvalue = 0.02;
	p->unit = "";
	p->scan = range(0, 0.1);
	p->phys = range(0, 1e4);
	p->force = range(0.001, 0.04);
	p->bboos = range(0, 0.18); // B -> Dpi

	p = newParameter("d_dkpipi");
	p->title = "#delta_{B}^{DK#pi#pi}";
	p->startvalue = DegToRad(338);
	p->unit = "Rad";
	p->scan = range(DegToRad(0), DegToRad(180));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(0), DegToRad(90));
	p->bboos = range(DegToRad(-180), DegToRad(180));

	p = newParameter("r_dkpipi");
	p->title = "r_{B}^{DK#pi#pi}";
	p->startvalue = 0.09;
	p->unit = "";
	p->scan = range(0.02, 0.16);
	p->phys = range(0, 1e4);
	p->force = range(0.02, 0.16);
	p->bboos = range(0.01, 0.22);

	p = newParameter("k_dkpipi");
	p->title = "#kappa_{B}^{DK#pi#pi}";
	p->startvalue = 0.3;
	p->unit = "";
	p->scan = range(0.01, 1.0);
	p->phys = range(0, 1);
	p->force = range(0.01, 1.5);
	p->bboos = range(0.01, 1.5);

	p = newParameter("d_dpipipi");
	p->title = "#delta_{B}^{D#pi#pi#pi}";
	p->startvalue = DegToRad(330);
	p->unit = "Rad";
	p->scan = range(DegToRad(0), DegToRad(180));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(0), DegToRad(90));
	p->bboos = range(DegToRad(-180), DegToRad(180));

	p = newParameter("r_dpipipi");
	p->title = "r_{B}^{D#pi#pi#pi}";
	p->startvalue = 0.015;
	p->unit = "";
	p->scan = range(0.02, 0.16);
	p->phys = range(0, 1e4);
	p->force = range(0.02, 0.16);
	p->bboos = range(0.01, 0.22);

	p = newParameter("k_dpipipi");
	p->title = "#kappa_{B}^{D#pi#pi#pi}";
	p->startvalue = 0.3;
	p->unit = "";
	p->scan = range(0.01, 1.0);
	p->phys = range(0, 1);
	p->force = range(0.01, 1.5);
	p->bboos = range(0.01, 1.5);

	// B -> DKpipi / B -> Dpipipi
	p = newParameter("RBRdhpipi");
	p->title = "R_{cab}^{Dh#pi#pi}";
	p->startvalue = 0.03;
	p->unit = "";
	p->scan = range(0.07, 0.09);
	p->phys = range(0, 1e4);
	p->force = range(0.07, 0.09);
	p->bboos = range(0.02, 0.27);

  // B+ -> D*K+
	p = newParameter("d_dstk");
	p->title = "#delta_{B}^{D*K}";
	p->startvalue = DegToRad(127);
	p->unit = "Rad";
	p->scan = range(DegToRad(0), DegToRad(180));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(0), DegToRad(90));
	p->bboos = range(DegToRad(-180), DegToRad(180)); // B -> D*K

	p = newParameter("r_dstk");
	p->title = "r_{B}^{D*K}";
	p->startvalue = 0.09;
	p->unit = "";
	p->scan = range(0.02, 0.2);
	p->phys = range(0, 1e4);
	p->force = range(0.02, 0.16);
	p->bboos = range(0.01, 0.22); // B -> D*K

	// B+ -> DK*+
  p = newParameter("d_dkst");
	p->title = "#delta_{B}^{DK*}";
	p->startvalue = DegToRad(127);
	p->unit = "Rad";
	p->scan = range(DegToRad(0), DegToRad(180));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(0), DegToRad(90));
	p->bboos = range(DegToRad(-180), DegToRad(180)); // B -> DK*

	p = newParameter("k_dkst");
	p->title = "#kappa_{B}^{DK*}";
	p->startvalue = 0.9;
	p->unit = "";
	p->scan = range(0, 2.5);
	p->phys = range(0, 1);
	p->force = range(0.001, 1);
	p->bboos = range(0, 1);

	p = newParameter("r_dkst");
	p->title = "r_{B}^{DK*}";
	p->startvalue = 0.09;
	p->unit = "";
	p->scan = range(0.02, 0.2);
	p->phys = range(0, 1e4);
	p->force = range(0.02, 0.16);
	p->bboos = range(0.01, 0.22); // B -> DK*


	// B0 -> D0Kst0
	p = newParameter("d_dkstz");
	p->title = "#delta_{D^{0}K^{*}}";
	p->startvalue = DegToRad(330);
	p->unit = "Rad";
	p->scan = range(DegToRad(0), DegToRad(360));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(0), DegToRad(90));
	p->bboos = range(DegToRad(-180), DegToRad(180)); // B0 -> D0Kst0

	p = newParameter("r_dkstz");
	p->title = "r_{D^{0}K^{*}}";
	p->startvalue = 0.3;
	p->unit = "";
	p->scan = range(0, 0.6);
	p->phys = range(0.001, 1);
	p->force = range(0.001, 0.6);
	p->bboos = range(0, 1);

	p = newParameter("k_dkstz");
	p->title = "#kappa_{D^{0}K^{*}}";
	p->startvalue = 0.9;
	p->unit = "";
	p->scan = range(0, 2.5);
	p->phys = range(0, 1);
	p->force = range(0.001, 1);
	p->bboos = range(0, 1);

	// B0 -> D0Kpi
	//p = newParameter("d_dkpi");
	//p->title = "#delta_{D^{0}K#pi}";
	//p->startvalue = DegToRad(270);
	//p->unit = "Rad";
	//p->scan = range(DegToRad(0), DegToRad(180));
	//p->phys = range(-7, 7);
	//p->force = range(DegToRad(0), DegToRad(90));
	//p->bboos = range(DegToRad(-180), DegToRad(180)); // B0 -> D0Kst0

	//p = newParameter("r_dkpi");
	//p->title = "r_{D^{0}K#pi}";
	//p->startvalue = 0.3;
	//p->unit = "";
	//p->scan = range(0, 1.0);
	//p->phys = range(0.001, 1);
	//p->force = range(0.001, 0.5);
	//p->bboos = range(0, 1);

  // Special ratio parameters suggested by Tim
	p = newParameter("delta_dkstz");
	p->title = "#Delta#delta_{D^{0}K*^{0}}";
	p->startvalue = DegToRad(0.);
	p->unit = "Rad";
	p->scan = range(DegToRad(0), DegToRad(180));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(0), DegToRad(90));
	p->bboos = range(DegToRad(-180), DegToRad(180)); // B0 -> D0Kst0

	p = newParameter("R_dkstz");
	p->title = "R_{D^{0}K*^{0}}";
	p->startvalue = 1.;
	p->unit = "";
	p->scan = range(0, 10.0);
	p->phys = range(0.001, 10.);
	p->force = range(0.001, 10.0);
	p->bboos = range(0, 10);

	//p = newParameter("k_dkpi");
	//p->title = "#kappa_{D^{0}K#pi}";
	//p->startvalue = 0.9;
	//p->unit = "";
	//p->scan = range(0, 2.5);
	//p->phys = range(0, 1);
	//p->force = range(0.001, 1);
	//p->bboos = range(0, 1);

	// Bs -> DsK
	p = newParameter("l_dsk");
	// p->title = "#lambda_{D_{s}K}";
	p->title = "r_{D_{s}K}";
	// p->startvalue = 0.37;
	p->startvalue = 0.54;
	p->unit = "";
	p->scan = range(0, 1.4);
	p->phys = range(0, 1e4);
	p->force = range(0.01, 1);
	p->bboos = range(0, 1);

	p = newParameter("d_dsk");
	p->title = "#delta_{D_{s}K}";
	// p->startvalue = DegToRad(20);
	p->startvalue = DegToRad(8);
	p->unit = "Rad";
	p->scan = range(DegToRad(-90), DegToRad(90));
	// p->scan = range(DegToRad(-70), DegToRad(290));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(0), DegToRad(90));
	p->bboos = range(DegToRad(-90), DegToRad(90));

	// Bs mixing phase
	p = newParameter("phis");
	p->title = "#phi_{s}";
	p->startvalue = 0.01;
	//p->unit = "Rad"; // don't use Rad becaus phi cannot wrap around and then bring back angles messes with it
	p->unit = "";
	p->scan = range(-0.25, 0.25);
	p->phys = range(-7, 7);
	p->force = range(-0.25, 0.25);
	p->bboos = range(-0.25, 0.25); // Bs -> DsK

	p = newParameter("rD_kpi");
	p->title = "r_{K#pi}";
	p->startvalue = 0.058;
	p->unit = "";
	p->scan = range(0.054, 0.061);
	p->phys = range(0, 1e4);
	p->force = range(0.001, 0.15);
	p->bboos = range(0.01, 0.21); // D -> Kpi

	p = newParameter("dD_kpi");
	p->title = "#delta_{K#pi}";
	p->startvalue = DegToRad(188);
	p->unit = "Rad";
	p->scan = range(DegToRad(160), DegToRad(250));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(150), DegToRad(250));
	p->bboos = range(DegToRad(150), DegToRad(250)); // D -> Kpi

	p = newParameter("rD_k3pi");
	p->title = "r_{K3#pi}";
	p->startvalue = 0.056;
	p->unit = "";
	p->scan = range(0.045, 0.065);
	p->phys = range(0, 1e4);
	p->force = range(0.001, 0.15);
	p->bboos = range(0.01, 0.15); // D -> Kpipipi

	p = newParameter("dD_k3pi");
	p->title = "#delta_{K3#pi}";
	// p->startvalue = DegToRad(235);
	p->startvalue = DegToRad(127);
	p->unit = "Rad";
	p->scan = range(DegToRad(0), DegToRad(360));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(20), DegToRad(180));
	p->bboos = range(DegToRad(150), DegToRad(300)); // D -> Kpipipi

	p = newParameter("kD_k3pi");
	p->title = "#kappa_{K3#pi}";
	p->startvalue = 0.26;
	p->unit = "";
	p->scan = range(0.01, 1);
	p->phys = range(0, 1);
	p->force = range(0.01, 0.8);
	p->bboos = range(0, 1); // D -> Kpipipi

	p = newParameter("rD_kpipi0");
	p->title = "r_{K#pi#pi^{0}}";
	p->startvalue = 0.046;
	p->unit = "";
	p->scan = range(0.045, 0.065);
	p->phys = range(0, 1e4);
	p->force = range(0.001, 0.15);
	p->bboos = range(0.01, 0.15);

	p = newParameter("dD_kpipi0");
	p->title = "#delta_{K#pi#pi^{0}}";
	p->startvalue = DegToRad(164);
	p->unit = "Rad";
	p->scan = range(DegToRad(0), DegToRad(360));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(20), DegToRad(180));
	p->bboos = range(DegToRad(150), DegToRad(300));

	p = newParameter("kD_kpipi0");
	p->title = "#kappa_{K#pi#pi^{0}}";
	p->startvalue = 0.86;
	p->unit = "";
	p->scan = range(0.01, 1);
	p->phys = range(0, 1);
	p->force = range(0.01, 0.8);
	p->bboos = range(0, 1);

	p = newParameter("F_pipipi0");
	p->title = "F_{pipi#pi^{0}}";
	p->startvalue = 0.97;
	p->unit = "";
	p->scan = range(0,1);
	p->phys = range(0,1);
	p->force = range(0,1);
	p->bboos = range(0,1);

	p = newParameter("F_kkpi0");
	p->title = "F_{KK#pi^{0}}";
	p->startvalue = 0.73;
	p->unit = "";
	p->scan = range(0,1);
	p->phys = range(0,1);
	p->force = range(0,1);
	p->bboos = range(0,1);

	p = newParameter("F_pipipipi");
	p->title = "F_{4#pi}";
	p->startvalue = 0.74;
	p->unit = "";
	p->scan = range(0,1);
	p->phys = range(0,1);
	p->force = range(0,1);
	p->bboos = range(0,1);

	p = newParameter("BR_D_Kminus3pi");
	p->title = "BF(D#rightarrowK^{-}3#pi)";
	p->startvalue = 8.29e-2;
	p->unit = "";
	p->scan = range(0.,0.5);
	p->phys = range(0, 1);
	p->force = range(0.01, 0.8);
	p->bboos = range(0, 1);

	p = newParameter("BR_D_Kplus3pi");
	p->title = "BF(D#rightarrowK^{+}3#pi)";
	p->startvalue = 2.6e-4;
	p->unit = "";
	p->scan = range(0.,0.01);
	p->phys = range(0, 1);
	p->force = range(1.e-5,1.e-3);
	p->bboos = range(0, 1);

	p = newParameter("AcpDKK");
	p->title = "#A_{CP}(D #rightarrow KK)";
	p->startvalue = 0.0;
	p->unit = "";
	p->scan = range(-0.1, 0.1);
	p->phys = range(-1, 1);
	p->force = range(-0.1, 0.1);
	p->bboos = range(-0.1, 0.1); // D->KK

	p = newParameter("AcpDpipi");
	p->title = "#A_{CP}(D #rightarrow pipi)";
	p->startvalue = 0.0;
	p->unit = "";
	p->scan = range(-0.1, 0.1);
	p->phys = range(-1, 1);
	p->force = range(-0.1, 0.1);
	p->bboos = range(-0.1, 0.1); // D->pipi

	p = newParameter("AcpDzKstpKm");
	p->title = "#A_{CP}(D^{0} #rightarrow K^{*+}K^{-})";
	p->startvalue = 0.0;
	p->unit = "";
	p->scan = range(-0.1, 0.1);
	p->phys = range(-1, 1);
	p->force = range(-0.1, 0.1);
	p->bboos = range(-0.1, 0.1);

	p = newParameter("AcpDzKstmKp");
	p->title = "#A_{CP}(D^{0} #rightarrow K^{*-}K^{+})";
	p->startvalue = 0.0;
	p->unit = "";
	p->scan = range(-0.1, 0.1);
	p->phys = range(-1, 1);
	p->force = range(-0.1, 0.1);
	p->bboos = range(-0.1, 0.1);

	p = newParameter("rD_k2pi");
	p->title = "r_{K2#pi}";
	p->startvalue = 0.05;
	p->unit = "";
	p->scan = range(0, 0.1);
	p->phys = range(0, 1e4);
	p->force = range(0.001, 0.15);
	p->bboos = range(0, 0.15); // CLEO

	p = newParameter("kD_k2pi");
	p->title = "k_{K2#pi}";
	p->startvalue = 0.84;
	p->unit = "";
	p->scan = range(0, 1);
	p->phys = range(0, 1);
	p->force = range(0.01, 1);
	p->bboos = range(0, 1); // CLEO

	p = newParameter("dD_k2pi");
	p->title = "#delta_{K2#pi}";
	p->startvalue = 3.96;
	p->unit = "Rad";
	p->scan = range(DegToRad(0), DegToRad(360));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(0), DegToRad(90));
	p->bboos = range(DegToRad(0), DegToRad(360)); // CLEO

	p = newParameter("rD_kskpi");
	p->title = "r_{KSK#pi}";
	p->startvalue = 0.59;
	p->unit = "";
	p->scan = range(0, 0.1);
	p->phys = range(0, 1e4);
	p->force = range(0.001, 0.15);
	p->bboos = range(0, 0.15);

	p = newParameter("kD_kskpi");
	p->title = "k_{KSK#pi}";
	p->startvalue = 1.0;
	p->unit = "";
	p->scan = range(0, 1);
	p->phys = range(0, 1);
	p->force = range(0.01, 1);
	p->bboos = range(0, 1);

	p = newParameter("dD_kskpi");
	p->title = "#delta_{KSK#pi}";
	p->startvalue = DegToRad(26.);
	p->unit = "Rad";
	p->scan = range(DegToRad(0), DegToRad(360));
	p->phys = range(-7, 7);
	p->force = range(DegToRad(0), DegToRad(90));
	p->bboos = range(DegToRad(0), DegToRad(360));

	p = newParameter("xD");
	p->title = "x_{D}";
	p->startvalue = 4.1e-03;
	p->unit = "";
	p->scan = range(0.002, 0.012);
	p->phys = range(-1, 1);
	p->force = range(0.002, 0.012);
	p->bboos = range(0., 0.016); // D mixing

	p = newParameter("yD");
	p->title = "y_{D}";
	p->startvalue = 6.3e-03;
	p->unit = "";
	p->scan = range(0.002, 0.012);
	p->phys = range(-1, 1);
	p->force = range(0.002, 0.012);
	p->bboos = range(0., 0.016); // D mixing

	p = newParameter("B1");
	p->title = "BR(D #rightarrow K#pi)";
	p->startvalue = 3.89e-02;
	p->unit = "";
	p->scan = range(0.0380, 0.0395);
	p->phys = range(0, 1);
	p->force = range(0.0380, 0.0395);
	p->bboos = range(0.01, 0.05); // CLEO

	p = newParameter("B3");
	p->title = "BR(D #rightarrow K3#pi)";
	p->startvalue = 7.96e-02;
	p->unit = "";
	p->scan = range(0.07, 0.09);
	p->phys = range(0, 1);
	p->force = range(0.07, 0.09);
	p->bboos = range(0.02, 0.3); // CLEO

	p = newParameter("B5");
	p->title = "BR(D #rightarrow K2#pi)";
	p->startvalue = 1.38e-01;
	p->unit = "";
	p->scan = range(0.05, 0.2);
	p->phys = range(0, 1);
	p->force = range(0.05, 0.2);
	p->bboos = range(0.01, 0.6); // CLEO

	p = newParameter("Aprod");
	p->title = "Aprod(Bu)";
	p->startvalue = 0.0;
	p->unit = "";
	p->scan = range(-0.1, 0.1);
	p->phys = range(-1, 1);
	p->force = range(-0.1, 0.1);
	p->bboos = range(-0.1, 0.1);

	p = newParameter("a_gaus");
	p->title = "a_{Gaus}";
	p->startvalue = 0;
	p->unit = "";
	p->scan = range(-2.5, 2.5);
	p->phys = range(0, 1e4); // to implement a Feldman-Cousins like forbidden region, change this range and use --pr
	p->force = range(-2, 4);
	p->bboos = range(-2, 4);
	p->free = range(-1e4, 1e4);

	p = newParameter("b_gaus");
	p->title = "b_{Gaus}";
	p->startvalue = 0;
	p->unit = "";
	p->scan = range(-2, 4);
	p->phys = range(-1e4, 1e4);
	p->force = range(-2, 4);
	p->bboos = range(-2, 4);

  p = newParameter("B_k3pi_FAV");
  p->title = "B(D#rightarrowK3#pi FAV)";
  p->startvalue = 8.e-02;
  p->unit = "";
  p->scan = range(0.,1.);
  p->phys = range(0.,1.);
  p->force = range(0.,1.);
  p->bboos = range(0.,1.);

  p = newParameter("B_k3pi_SUP");
  p->title = "B(D#rightarrowK3#pi SUP)";
  p->startvalue = 2.65e-04;
  p->unit = "";
  p->scan = range(0.,1.);
  p->phys = range(0.,1.);
  p->force = range(0.,1.);
  p->bboos = range(0.,1.);

  p = newParameter("B_kpipi0_FAV");
  p->title = "B(D#rightarrowK#pi#pi^{0} FAV)";
  p->startvalue = 13.8e-02;
  p->unit = "";
  p->scan = range(0.,1.);
  p->phys = range(0.,1.);
  p->force = range(0.,1.);
  p->bboos = range(0.,1.);

  p = newParameter("B_kpipi0_SUP");
  p->title = "B(D#rightarrowK#pi#pi^{0} SUP)";
  p->startvalue = 3.e-04;
  p->unit = "";
  p->scan = range(0.,1.);
  p->phys = range(0.,1.);
  p->force = range(0.,1.);
  p->bboos = range(0.,1.);

  p = newParameter("B_kpi_FAV");
  p->title = "B(D#rightarrowK#pi FAV)";
  p->startvalue = 4.e-02;
  p->unit = "";
  p->scan = range(0.,1.);
  p->phys = range(0.,1.);
  p->force = range(0.,1.);
  p->bboos = range(0.,1.);

  p = newParameter("B_kpi_SUP");
  p->title = "B(D#rightarrowK#pi SUP)";
  p->startvalue = 1.5e-04;
  p->unit = "";
  p->scan = range(0.,1.);
  p->phys = range(0.,1.);
  p->force = range(0.,1.);
  p->bboos = range(0.,1.);

}
