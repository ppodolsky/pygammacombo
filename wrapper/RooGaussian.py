from wrapper import *
from wrapper.RooAbsPdf import RooAbsPdf

RooGaussian = mod.add_class('RooGaussian', parent=RooAbsPdf)
RooGaussian.add_constructor([param('const char *', 'name'), param('const char *', 'title'),
                            param('RooAbsReal&', '_x'), param('RooAbsReal&', 'mean'),
                            param('RooAbsReal&', '_sigma')])
RooGaussian.add_constructor([param('RooGaussian&', 'other'), param('const char *', 'name', default_value='0')])