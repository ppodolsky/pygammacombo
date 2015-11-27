/**
 * Gamma Combination
 * Author: Till Moritz Karbach, moritz.karbach@cern.ch
 * Date: August 2012
 *
 * Combine the DK observables from the D->K3pi ADS measurement.
 *
 **/

#include "PDF_GLWADS_DK_K3pi.h"

	PDF_GLWADS_DK_K3pi::PDF_GLWADS_DK_K3pi(config cObs, config cErr, config cCor, ParametersAbs* pars, TString d)
: PDF_GLWADS_DKDpi_K3pi(pars,d,3)
{
	name = "glwads-dk-k3pi";
	initParameters();
	initRelations();
	initObservables();
	setObservables(cObs);
	setUncertainties(cErr);
	setCorrelations(cCor);
	buildCov();
	buildPdf();
}


PDF_GLWADS_DK_K3pi::~PDF_GLWADS_DK_K3pi(){}


void PDF_GLWADS_DK_K3pi::initParameters()
{
	parameters = new RooArgList("parameters");
	parameters->add(*(p->get("r_dk")));
	parameters->add(*(p->get("d_dk")));
	parameters->add(*(p->get("g")));
	parameters->add(*(p->get("rD_k3pi")));
	parameters->add(*(p->get("dD_k3pi")));
	parameters->add(*(p->get("kD_k3pi")));
}


void PDF_GLWADS_DK_K3pi::initRelations()
{
	theory = new RooArgList("theory"); ///< the order of this list must match that of the COR matrix!
	RooArgSet *p = (RooArgSet*)parameters;
	theory->add(*(new RooFormulaVar("afav_dk_k3pi_th",  "afav_dk_k3pi_th",  "2*r_dk *rD_k3pi*kD_k3pi*sin(g)*sin(d_dk -dD_k3pi) / (1 + r_dk^2  * rD_k3pi^2 + 2*r_dk *rD_k3pi*kD_k3pi*cos(g)*cos(d_dk -dD_k3pi))", *p)));
	theory->add(*(new RooFormulaVar("rp_dk_k3pi_th",    "rp_dk_k3pi_th",    "r_dk^2  + rD_k3pi^2 + 2*r_dk *rD_k3pi*kD_k3pi*cos( g+d_dk +dD_k3pi)", *p)));
	theory->add(*(new RooFormulaVar("rm_dk_k3pi_th",    "rm_dk_k3pi_th",    "r_dk^2  + rD_k3pi^2 + 2*r_dk *rD_k3pi*kD_k3pi*cos(-g+d_dk +dD_k3pi)", *p)));
}


void PDF_GLWADS_DK_K3pi::initObservables()
{
	observables = new RooArgList("observables"); ///< the order of this list must match that of the COR matrix!
	observables->add(*(new RooRealVar("afav_dk_k3pi_obs",  "Afav (DK K3#pi)"    , 0, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rp_dk_k3pi_obs",    "R+ (DK K3#pi ADS)"  , 1, -1e4, 1e4)));
	observables->add(*(new RooRealVar("rm_dk_k3pi_obs",    "R- (DK K3#pi ADS)"  , 1, -1e4, 1e4)));
}


void PDF_GLWADS_DK_K3pi::setUncertainties(config c)
{
	switch(c)
	{
		case lumi1fb:
			{
				obsErrSource = "1fb-1, ExpNll/sept2012K3PIResult.root";
				TString File = this->dir+"/ExpNll/sept2012K3PIResult.root";
				if ( !FileExists(File) ){cout << "PDF_GLWADS_DK_K3pi::setUncertainties : ERROR : File not found : " << File << endl; exit(1);}
				TFile *fr = TFile::Open(File);
				RooFitResult *r = (RooFitResult*)fr->Get("fitresult_model_reducedData_binned");
				assert(r);
				for ( int i=0; i<nObs; i++ )
				{
					RooRealVar* pObs = (RooRealVar*)((RooArgList*)observables)->at(i); assert(pObs);
					RooRealVar* pRes = (RooRealVar*)r->floatParsFinal().find(obsTmkToMalcolm(pObs->GetName())); assert(pRes);
					StatErr[i] = pRes->getError();
				}
				SystErr[0] = 0.018;   // afav_dk_obs
				SystErr[1] = 0.0010;  // rp_dk_obs
				SystErr[2] = 0.0008;  // rm_dk_obs
				fr->Close();
				delete r;
				delete fr;
				break;
			}
		case lumi3fb:{
							/// these are copied over from PDF_GLWADS_DKDpi_K3pi
						 obsErrSource = "3fb-1 ANA v7 unblind"; // https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2D0K/LHCb-ANA-2014-071-v7.pdf (see Vavas email 04/08/15)

						 // these get transformed over from the new inputs using ExpNll/transportGLWADS_new_to_old.py
						 // in the case of the DK only (robust) combination some of the observables don't exist
						 // usemap as the temp store
						 std::map< TString, double > stat_errs;
						 stat_errs["afav_dk_k3pi_obs"]  =  0.0119;    // afav_dk_obs
						 stat_errs["rp_dk_k3pi_obs"]    =  0.002421;  // rp_dk_obs
						 stat_errs["rm_dk_k3pi_obs"]    =  0.001756;  // rm_dk_obs

						 for ( int i=0; i<nObs; i++ )
						 {
							 RooRealVar* pObs = (RooRealVar*)((RooArgList*)observables)->at(i);
							 StatErr[i] = stat_errs[pObs->GetName()];
						 }
						 stat_errs.clear();

						 std::map< TString, double > syst_errs;
						 syst_errs["afav_dk_k3pi_obs"]  = 0.0019;     // afav_dk_obs
						 syst_errs["rp_dk_k3pi_obs"]    = 0.000950;   // rp_dk_obs
						 syst_errs["rm_dk_k3pi_obs"]    = 0.000673;   // rm_dk_obs

						 for ( int i=0; i<nObs; i++ )
						 {
							 RooRealVar* pObs = (RooRealVar*)((RooArgList*)observables)->at(i);
							 SystErr[i] = syst_errs[pObs->GetName()];
						 }
						 syst_errs.clear();

						 break;
					 }
		default:
			cout << "PDF_GLWADS_DK_K3pi::setUncertainties() : ERROR : config "+ConfigToTString(c)+" not found." << endl;
			exit(1);
	}
}
