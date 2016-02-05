from wrapper import *
from wrapper.RooArgSet import RooArgSet
from wrapper.RooAbsArg import RooAbsArg

RooAbsReal = mod.add_class('RooAbsReal', parent=RooAbsArg)
RooAbsReal.add_method('getVal', retval('double'), [param('const RooArgSet&', 'set')])
RooAbsReal.add_method('getVal', retval('double'), [param('const RooArgSet*', 'set', default_value='0')])
RooAbsReal.add_method('getValV', retval('double'), [param('const RooArgSet*', 'set', default_value='0')], is_virtual=True)
RooAbsReal.add_method('getUnit', retval('const char*'), [])