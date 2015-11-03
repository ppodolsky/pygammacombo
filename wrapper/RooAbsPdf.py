from wrapper import *
from wrapper.RooAbsReal import RooAbsReal
from wrapper.RooArgSet import RooArgSet

RooAbsPdf = mod.add_class('RooAbsPdf', parent=RooAbsReal)
RooAbsPdf.add_method('getLogVal', retval('double'), [param('const RooArgSet*', 'nset', default_value='0')], is_const=True)
RooAbsPdf.add_method('getValV', retval('double'), [param('const RooArgSet*', 'nset', default_value='0')], is_const=True)