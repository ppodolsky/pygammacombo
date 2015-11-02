__author__ = 'PashaPodolsky'

import io
from pybindgen import *

mod = Module('PyGammaCombo')
mod.add_include('"RooArgSet.h"')
mod.add_include('"RooRealVar.h"')
mod.add_include('"TString.h"')
mod.add_include('"TMatrixDSymfwd.h"')
mod.add_include('"gammacombo/core/include/Parameter.h"')
mod.add_include('"gammacombo/core/include/ParametersAbs.h"')
mod.add_include('"gammacombo/core/include/PDF_ABS.h"')
mod.add_include('"gammacombo/core/include/PDF_GGSZ.h"')
mod.add_include('"gammacombo/core/include/PDF_GGSZ_cartesian.h"')
mod.add_include('"gammacombo/core/include/UtilsConfig.h"')

utils_namespace = mod.add_cpp_namespace('Utils')
utils_namespace.add_enum('config', ['year2014','babar','babar2007','babar2008',
                                    'babar2010','babar2012','belle','belle2005cleo2009',
                                    'belle2006','belle2007','belle2009','belle2012','belle2012preliminary',
                                    'belle2013','belle2014','belle2013cleo2014','cdf2007','cdf2012',
                                    'cdf2013','ckm2014','cleo','cleo2001','cleo2009','cleo2012','cleo2014',
                                    'cleo2015','cleoFullDP','combos2008','combpipi','default_config',
                                    'excludeKdDdK3pi','exclusive2014','inclusive2014','focus2000','hfag',
                                    'hfagFP2014','hfagLP2011','hfagCHARM2015','highrb','highstattoy','lhcb',
                                    'lhcb2011','lhcb2012','lhcb2013','lhcb2013KK','lhcb2013pipi',
                                    'lhcb2013preliminary','lhcb2014','lhcb2018KK_extrap','lhcb_upgrade_extrap',
                                    'lhcbphis','lhcbcomb','lhcb_old','lumi40pb','lumi1fb','lumi1fbConfcFit',
                                    'lumi1fbConfsFit','lumi1fbNoAfav','lumi1fbPapercFit','lumi1fbPapercFitExpected',
                                    'lumi1fbPapersFit','lumi1fbSystCor','lumi1fbprompt','lumi1fbsl','lumi2fb',
                                    'lumi3fb','lumi3fbCPVA','lumi3fbFix','lumi3fbFullDP','lumi3fbPaper',
                                    'lumi3fbDKstz','lumi3fb_estimate','lumi5ab','lumi5fb','lumi9fb','lumi50ab',
                                    'lumi50fb','lambda1_3fb','lambdafree_3fb','manual','milc_update','none',
                                    'nophicorr','onlyGsDGs','pdg','sneha','toy','truth','useBicubic',
                                    'useCartCoords','useGaussian','useHistogram','useParametric','usePolarCoords',
                                    'useTradObs','world_average','zero'])
from wrapper.Parameter import Parameter
from wrapper.ParametersGammaCombo import ParametersGammaCombo
from wrapper.ParametersVector import ParametersVector
from wrapper.PDF_Abs import PDF_Abs
from wrapper.PDF_GGSZ import PDF_GGSZ
from wrapper.PDF_GGSZ_cartesian import PDF_GGSZ_cartesian
from wrapper.RooAbsArg import RooAbsArg
from wrapper.RooAbsPdf import RooAbsPdf
from wrapper.RooAbsReal import RooAbsReal
from wrapper.RooArgSet import RooArgSet
from wrapper.RooGaussian import RooGaussian
from wrapper.RooRealVar import RooRealVar
from wrapper.TObject import TObject
from wrapper.TString import TString
from wrapper.ParametersAbs import ParametersAbs

def generate():
    codegen = io.StringIO("")
    mod.generate(codegen)
    codegen = codegen.getvalue()
    # Monkey patch - pybindgen makes incorrect cast
    codegen = codegen.replace("(cmpfunc)NULL","NULL")
    # ---------------------------------------------
    return codegen