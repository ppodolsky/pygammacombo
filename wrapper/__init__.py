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
mod.add_include('"gammacombo/core/include/PDF_GGSZ_cartesian.h"')
mod.add_include('"gammacombo/core/include/UtilsConfig.h"')

utils_namespace = mod.add_cpp_namespace('Utils')

from wrapper import commons
from wrapper import equations

def generate():
    codegen = io.StringIO("")
    mod.generate(codegen)
    codegen = codegen.getvalue()
    # Monkey patch - pybindgen makes incorrect cast
    codegen = codegen.replace("(cmpfunc)NULL","NULL")
    # ---------------------------------------------
    return codegen