/**
 * Gamma Combination
 * Author: Matthew Kenzie, matthew.kenzie@cern.ch
 * Date: Dec 2015
 *
 * B Coherence factor, R_B and Deltadelta_B in B0 -> D0 K*0
 *
 **/

#include "PDF_B_DKstz_constraints.h"

	PDF_B_DKstz_constraints::PDF_B_DKstz_constraints(config cObs, config cErr, config cCor)
: PDF_Abs(3)
{
	name = "dkstzconstraints";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_B_DKstz_constraints::~PDF_B_DKstz_constraints(){}


void PDF_B_DKstz_constraints::initParameters()
{
	ParametersGammaCombo p;
	parameters = new RooArgList("parameters");
	parameters->add(*(p.get("k_dkstz")));
  parameters->add(*(p.get("R_dkstz")));
  parameters->add(*(p.get("delta_dkstz")));
}


void PDF_B_DKstz_constraints::initRelations()
{
	RooArgSet *p = (RooArgSet*)parameters;
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	theory->add(*(new RooFormulaVar("k_dkstz_th"    , "k_dkstz_th"    , "k_dkstz"    , *p)));
	theory->add(*(new RooFormulaVar("R_dkstz_th"    , "R_dkstz_th"    , "R_dkstz"    , *p)));
	theory->add(*(new RooFormulaVar("delta_dkstz_th", "delta_dkstz_th", "delta_dkstz", *p)));
}


void PDF_B_DKstz_constraints::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("k_dkstz_obs", "k_dkstz",       1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("R_dkstz_obs", "R_dkstz",       1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("delta_dkstz_obs", "delta_dkstz",       0, -1e4, 1e4)));
}


void PDF_B_DKstz_constraints::setObservables(config c)
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
		case lhcb:
			obsValSource = "B0->D0Kpi Fit Results - Dan's approval slides"; // https://indico.cern.ch/event/470104/session/1/contribution/3/attachments/1204060/1753754/20151211_dcraik.pdf
			setObservable("k_dkstz_obs",0.96);
			setObservable("R_dkstz_obs",1.029);
			setObservable("delta_dkstz_obs",0.024);
			break;

		default:
			cout << "PDF_B_DKstz_constraints::setObservables() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_B_DKstz_constraints::setUncertainties(config c)
{
	switch(c)
	{
		case lhcb:
			obsErrSource = "B0->D0Kpi Fit Results - Dan's approval slides"; // https://indico.cern.ch/event/470104/session/1/contribution/3/attachments/1204060/1753754/20151211_dcraik.pdf
			StatErr[0] = 0.010;
			StatErr[1] = 0.023;
			StatErr[2] = 0.025;

      SystErr[0] = 0.024;
			SystErr[1] = 0.060;
			SystErr[2] = 0.107;
			break;

		default:
			cout << "PDF_B_DKstz_constraints::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_B_DKstz_constraints::setCorrelations(config c)
{
	resetCorrelations();
	switch(c)
	{
		case lhcb:
			corSource = "no correlations";
			break;

		default:
			cout << "PDF_B_DKstz_constraints::setCorrelations() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}


void PDF_B_DKstz_constraints::buildPdf()
{
	pdf = new RooMultiVarGaussian("pdf_"+name, "pdf_"+name, *(RooArgSet*)observables, *(RooArgSet*)theory, covMatrix);
}
