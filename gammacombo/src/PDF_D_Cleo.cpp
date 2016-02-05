/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 **/

#include "PDF_D_Cleo.h"

	PDF_D_Cleo::PDF_D_Cleo(config cObs, config cType, config cUseKdDdK3pi, TString d)
: PDF_Abs(13)
{
	constructorBody(cObs, cType, cUseKdDdK3pi, d);
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cleo);
	setCorrelations(cleo);
	buildCov();
	buildPdf();
}

	PDF_D_Cleo::PDF_D_Cleo(config cObs, config cType, config cUseKdDdK3pi, TString d, int nObs)
: PDF_Abs(nObs)
{
	constructorBody(cObs, cType, cUseKdDdK3pi, d);
}

void PDF_D_Cleo::constructorBody(config cObs, config cType, config cUseKdDdK3pi, TString d)
{
	name = "dcleo";
	this->dir = d;
	this->cType = cType;
	this->cUseKdDdK3pi = cUseKdDdK3pi; // to exclude kD_k3pi and dD_k3pi from Gaussian (blow up their errors)
	if ( cUseKdDdK3pi==excludeKdDdK3pi && cType==useHistogram )
	{
		cout << "PDF_D_Cleo::PDF_D_Cleo() : ERROR : You cannot exclude kD_k3pi and dD_k3pi and still use their histogram." << endl;
		exit(1);
	}
}


PDF_D_Cleo::~PDF_D_Cleo(){}


void PDF_D_Cleo::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("rD_k3pi")));
	parameters->add(*(p.get("kD_k3pi")));
	parameters->add(*(p.get("dD_k3pi")));
	parameters->add(*(p.get("rD_kpipi0")));
	parameters->add(*(p.get("kD_kpipi0")));
	parameters->add(*(p.get("dD_kpipi0")));
	parameters->add(*(p.get("xD")     ));
	parameters->add(*(p.get("yD")     ));
	parameters->add(*(p.get("rD_kpi") ));
	parameters->add(*(p.get("dD_kpi") ));
	parameters->add(*(p.get("B1")     ));
	parameters->add(*(p.get("B3")     ));
	parameters->add(*(p.get("B5")     ));
}


void PDF_D_Cleo::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("kD_k3pi_th", "kD_k3pi_th", "kD_k3pi", *p)));
	theory->add(*(new RooFormulaVar("dD_k3pi_th", "dD_k3pi_th", "dD_k3pi", *p)));
	theory->add(*(new RooFormulaVar("kD_kpipi0_th", "kD_kpipi0_th", "kD_kpipi0", *p)));
	theory->add(*(new RooFormulaVar("dD_kpipi0_th", "dD_kpipi0_th", "dD_kpipi0", *p)));
	theory->add(*(new RooFormulaVar("xD_th", "xD_th", "xD", *p)));
	theory->add(*(new RooFormulaVar("yD_th", "yD_th", "yD", *p)));
	theory->add(*(new RooFormulaVar("dD_kpi_th", "dD_kpi_th", "dD_kpi", *p)));
	theory->add(*(new RooFormulaVar("B1_th", "B1_th", "B1", *p)));
	theory->add(*(new RooFormulaVar("B2_th", "B2_th", "B1*rD_kpi^2 *(1-(yD/rD_kpi)         *cos(dD_kpi) +(xD/rD_kpi)         *sin(dD_kpi) +(yD^2+xD^2)/(2*rD_kpi^2))",  *p)));
	theory->add(*(new RooFormulaVar("B3_th", "B3_th", "B3", *p)));
	theory->add(*(new RooFormulaVar("B4_th", "B4_th", "B3*rD_k3pi^2*(1-(yD/rD_k3pi)*kD_k3pi*cos(dD_k3pi)+(xD/rD_k3pi)*kD_k3pi*sin(dD_k3pi)+(yD^2+xD^2)/(2*rD_k3pi^2))", *p)));
	theory->add(*(new RooFormulaVar("B5_th", "B5_th", "B5", *p)));
	theory->add(*(new RooFormulaVar("B6_th", "B6_th", "B5*rD_kpipi0^2*(1-(yD/rD_kpipi0)*kD_kpipi0*cos(dD_kpipi0)+(xD/rD_kpipi0)*kD_kpipi0*sin(dD_kpipi0)+(yD^2+xD^2)/(2*rD_kpipi0^2))", *p)));
}


void PDF_D_Cleo::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("kD_k3pi_obs", "kD (D#rightarrowK3#pi)",      0, -2, 2)));                    // reduced range else toy generation ...
	observables->add(*(new RooRealVar("dD_k3pi_obs", "#deltaD (D#rightarrowK3#pi)", 0, 0, 2*TMath::Pi(), "Rad")));  // produces lots of events very far away
	observables->add(*(new RooRealVar("kD_kpipi0_obs", "kD (D#rightarrowK2#pi)",      0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("dD_kpipi0_obs", "#deltaD (D#rightarrowK2#pi)", 0, -1e4, 1e4, "Rad")));
	observables->add(*(new RooRealVar("xD_obs",      "xD",                          0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("yD_obs",      "yD",                          0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("dD_kpi_obs",  "#deltaD (D#rightarrowK#pi)",  0, -1e4, 1e4, "Rad")));
	observables->add(*(new RooRealVar("B1_obs",      "B1 (Cleo)",                   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("B2_obs",      "B2 (Cleo)",                   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("B3_obs",      "B3 (Cleo)",                   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("B4_obs",      "B4 (Cleo)",                   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("B5_obs",      "B5 (Cleo)",                   0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("B6_obs",      "B6 (Cleo)",                   0, -1e4, 1e4)));
}


void PDF_D_Cleo::setObservables(config c)
{
	switch(c)
	{
		case truth:
			{
				setObservablesTruth();
				break;
			}
		case toy:
			{
				setObservablesToy();
				break;
			}
		case cleo:
			obsValSource = "Cleo 2009 ARXIV:0903.4853";
			setObservable("kD_k3pi_obs",0.33);
			setObservable("dD_k3pi_obs",DegToRad(114.0));
			setObservable("kD_kpipi0_obs",0.84);
			setObservable("dD_kpipi0_obs",DegToRad(227.));
			setObservable("xD_obs",     0.96 /100.);
			setObservable("yD_obs",     0.81 /100.);
			setObservable("dD_kpi_obs", DegToRad(-151.5+360.));
			setObservable("B1_obs",     3.89e-2);
			setObservable("B2_obs",     1.47e-4);
			setObservable("B3_obs",     7.96e-2);
			setObservable("B4_obs",     2.65e-4);
			setObservable("B5_obs",     13.8e-2);
			setObservable("B6_obs",     3.05e-4);
			break;

		default:
			cout << "PDF_D_Cleo::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_D_Cleo::setUncertainties(config c)
{
	switch(c)
	{
		case cleo:
			obsErrSource = "Cleo 2009 ARXIV:0903.4853";
			StatErr[ 0] = 0.26;          // kD_k3pi_obs
			StatErr[ 1] = DegToRad(26);  // dD_k3pi_obs
			StatErr[ 2] = 0.07;          // kD_kpipi0_obs
			StatErr[ 3] = DegToRad(17);  // dD_kpipi0_obs
			StatErr[ 4] = 0.25e-2;       // xD_obs
			StatErr[ 5] = 0.16e-2;       // yD_obs
			StatErr[ 6] = DegToRad(9.6); // dD_kpi_obs
			StatErr[ 7] = 0.05e-2;       // B1_obs
			StatErr[ 8] = 0.07e-4;       // B2_obs
			StatErr[ 9] = 0.19e-2;       // B3_obs
			StatErr[10] = 0.19e-4;       // B4_obs
			StatErr[11] = 0.05e-2;       // B5_obs
			StatErr[12] = 0.07e-4;       // B6_obs

			// exlude kD, dD, to make the LHCb only Ghana plot
			if ( cUseKdDdK3pi==excludeKdDdK3pi )
			{
				cout << "PDF_D_Cleo::setUncertainties() : WARNING : Excluding kD_k3pi and dD_k3pi!" << endl;
				StatErr[ 0] *= 50;
				StatErr[ 1] *= 50;
			}
			break;

		default:
			cout << "PDF_D_Cleo::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_D_Cleo::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case cleo:
			{
				corSource = "Cleo 2009 ARXIV:0903.4853";
				corStatMatrix[0][ 1] = -0.067;
				corStatMatrix[0][ 2] = 0.078 ;
				corStatMatrix[0][ 3] = 0.045 ;
				corStatMatrix[0][ 4] = -0.082;
				corStatMatrix[0][ 5] = -0.020;
				corStatMatrix[0][ 6] = -0.014;
				corStatMatrix[0][ 7] = 0.002 ;
				corStatMatrix[0][ 8] = 0.008 ;
				corStatMatrix[0][ 9] = 0.071 ;
				corStatMatrix[0][10] = 0.325 ;
				corStatMatrix[0][11] = -0.134;
				corStatMatrix[0][12] = 0.051 ;

				corStatMatrix[1][ 2] = 0.127 ;
				corStatMatrix[1][ 3] = 0.256 ;
				corStatMatrix[1][ 4] = -0.008;
				corStatMatrix[1][ 5] = 0.140 ;
				corStatMatrix[1][ 6] = 0.188 ;
				corStatMatrix[1][ 7] = -0.023;
				corStatMatrix[1][ 8] = 0.096 ;
				corStatMatrix[1][ 9] = 0.244 ;
				corStatMatrix[1][10] = -0.031;
				corStatMatrix[1][11] = -0.126;
				corStatMatrix[1][12] = -0.032;

				corStatMatrix[2][ 3] = 0.455 ;
				corStatMatrix[2][ 4] = 0.080 ;
				corStatMatrix[2][ 5] = -0.059;
				corStatMatrix[2][ 6] = -0.046;
				corStatMatrix[2][ 7] = -0.014;
				corStatMatrix[2][ 8] = 0.060 ;
				corStatMatrix[2][ 9] = 0.018 ;
				corStatMatrix[2][10] = 0.098 ;
				corStatMatrix[2][11] = -0.138;
				corStatMatrix[2][12] = 0.150 ;

				corStatMatrix[3][ 4] = -0.033;
				corStatMatrix[3][ 5] = 0.377 ;
				corStatMatrix[3][ 6] = 0.467 ;
				corStatMatrix[3][ 7] = 0.004 ;
				corStatMatrix[3][ 8] = -0.027;
				corStatMatrix[3][ 9] = 0.142 ;
				corStatMatrix[3][10] = 0.131 ;
				corStatMatrix[3][11] = -0.295;
				corStatMatrix[3][12] = 0.114 ;

				corStatMatrix[4][ 5] = -0.189;
				corStatMatrix[4][ 6] = -0.188;
				corStatMatrix[4][ 7] = -0.001;
				corStatMatrix[4][ 8] = 0.005 ;
				corStatMatrix[4][ 9] = -0.037;
				corStatMatrix[4][10] = 0.001 ;
				corStatMatrix[4][11] = 0.047 ;
				corStatMatrix[4][12] = -0.006;

				corStatMatrix[5][ 6] = 0.945 ;
				corStatMatrix[5][ 7] = 0.004 ;
				corStatMatrix[5][ 8] = -0.015;
				corStatMatrix[5][ 9] = 0.107 ;
				corStatMatrix[5][10] = -0.014;
				corStatMatrix[5][11] = -0.146;
				corStatMatrix[5][12] = 0.012 ;

				corStatMatrix[6][ 7] = 0.005 ;
				corStatMatrix[6][ 8] = -0.004;
				corStatMatrix[6][ 9] = 0.121 ;
				corStatMatrix[6][10] = -0.002;
				corStatMatrix[6][11] = -0.071;
				corStatMatrix[6][12] = 0.008 ;

				corStatMatrix[7][ 8] = 0.006 ;
				corStatMatrix[7][ 9] = -0.005;
				corStatMatrix[7][10] = 0.008 ;
				corStatMatrix[7][11] = 0.001 ;
				corStatMatrix[7][12] = -0.002;

				corStatMatrix[8][ 9] = 0.005 ;
				corStatMatrix[8][10] = -0.028;
				corStatMatrix[8][11] = -0.024;
				corStatMatrix[8][12] = 0.008 ;

				corStatMatrix[9][10] = 0.104 ;
				corStatMatrix[9][11] = 0.047 ;
				corStatMatrix[9][12] = -0.001;

				corStatMatrix[10][11] = -0.054;
				corStatMatrix[10][12] = -0.006;

				corStatMatrix[11][12] = 0.028;
				break;
			}

		default:
			cout << "PDF_D_Cleo::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_D_Cleo::buildPdfGaus()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}

///
/// Cleo histogram for kD, dD
///
void PDF_D_Cleo::buildPdfHistogram()
{
	RooMsgService::instance().setGlobalKillBelow(WARNING);
	TString fName = this->dir+"/ExpNll/CLEO_K3PiScan_2009_GaussianRise_pdf2.root";
	TString hName = "hPdf";
	obsValSource += ", "+fName;
	obsErrSource += ", "+fName;
	corSource += ", "+fName;
	if ( !FileExists(fName) ){cout << "PDF_D_CleoNoK2pi::buildPdfHistogram() : ERROR : File not found : " << fName << endl; exit(1);}
	TFile *fExpNll = new TFile(fName, "ro");
	TH2D *hExpNll = (TH2D*)fExpNll->Get(hName);
	assert(hExpNll);
	// hExpNll->Scale(1./1.3027449); // scale so best fit value gives chi2=0.
	hExpNll->Scale(1./0.858588); // scale so best fit value gives chi2=0: run bin/unittests which fits PDFs to minimum. The factor is 1/min.
	RooRealVar *x_hist = new RooRealVar("x_cleo_k3pi_hist", "x_cleo_k3pi_hist", 0,  -1e4, 1e4);
	RooRealVar *y_hist = new RooRealVar("y_cleo_k3pi_hist", "y_cleo_k3pi_hist", 0,  -1e4, 1e4);
	RooDataHist *dhExpNll = new RooDataHist("dh_cleo_k3pi", "dh_cleo_k3pi", RooArgList(*x_hist,*y_hist), Import(*hExpNll));
	RooRealVar *kD_k3pi_obs = (RooRealVar*)observables->find("kD_k3pi_obs");
	RooRealVar *kD_k3pi_th  = (RooRealVar*)theory->find("kD_k3pi_th");
	RooRealVar *dD_k3pi_obs = (RooRealVar*)observables->find("dD_k3pi_obs");
	RooRealVar *dD_k3pi_th  = (RooRealVar*)theory->find("dD_k3pi_th");
	RooHistPdfVar *kD_pdf = new RooHistPdfVar("kD_cleo_k3pi_pdf", "kD_cleo_k3pi_pdf", *kD_k3pi_obs, *kD_k3pi_th, RooConst(0.3325));  // those precise shifts I got from zooming into the exp nll histogram
	RooHistPdfAngleVar *dD_pdf = new RooHistPdfAngleVar("dD_cleo_k3pi_pdf", "dD_cleo_k3pi_pdf", *dD_k3pi_obs, *dD_k3pi_th, RooConst(1.9984));
	RooHistPdf *pdf_kDdD = new RooHistPdf("pdf_cleo_kDdD_k3pi", "pdf_cleo_kDdD_k3pi", RooArgList(*kD_pdf,*dD_pdf), RooArgList(*x_hist,*y_hist), *dhExpNll, 1);

	// Re-use the full multivariate Gaussian for the rest
	// blow up errors of kD and dD
	float largeNumber = 50.;
	StatErr[ 0] *= largeNumber;  // kD_k3pi_obs
	StatErr[ 1] *= largeNumber;  // dD_k3pi_obs
	buildCov();
	RooMultiVarGaussian *pdf_gaus = new RooMultiVarGaussian("pdf_cleo_gaus", "pdf_cleo_gaus", *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);

	// reset errors so that the pull plot remains correct
	StatErr[ 0] /= largeNumber;  // kD_k3pi_obs
	StatErr[ 1] /= largeNumber;  // dD_k3pi_obs

	// multiply both
	pdf = new RooProdPdf("pdf_"+name, "pdf_"+name, RooArgSet(*pdf_kDdD, *pdf_gaus));

	fExpNll->Close();
	RooMsgService::instance().setGlobalKillBelow(INFO);
	// addToTrash(fExpNll); ///< these two get cleaned by fExpNll->Close();
	// addToTrash(hExpNll);
	addToTrash(x_hist);
	addToTrash(y_hist);
	addToTrash(dhExpNll);
	addToTrash(kD_pdf);
	addToTrash(dD_pdf);
	addToTrash(pdf_kDdD);
	addToTrash(pdf_gaus);
}


void PDF_D_Cleo::buildPdf()
{
	if ( cType==useHistogram )
		buildPdfHistogram();
	else if ( cType==useGaussian )
		buildPdfGaus();
}
