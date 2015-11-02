from wrapper import *

RooAbsPdf = mod.add_class('RooAbsPdf')
RooAbsPdf.add_method('getLogVal', retval('double'), [])
RooAbsPdf.add_method('getValV', retval('double'), [])