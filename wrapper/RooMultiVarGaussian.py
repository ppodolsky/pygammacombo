from wrapper import *
from wrapper.RooAbsPdf import RooAbsPdf

RooMultiVarGaussian = mod.add_class('RooMultiVarGaussian', parent=RooAbsPdf)
RooMultiVarGaussian.add_method('syncMuVec', None, [], visibility='protected')