from wrapper import *
from wrapper.RooAbsReal import RooAbsReal

RooAbsRealLValue = mod.add_class('RooAbsRealLValue', parent=RooAbsReal)
RooAbsRealLValue.add_method('setVal', None, [param('double', 'val')], is_pure_virtual=True)
RooAbsRealLValue.add_method('hasBinning', retval('bool'), [param('const char*', 'name')], is_pure_virtual=True)
