from wrapper import *
from wrapper.RooAbsReal import RooAbsReal

RooAbsRealLValue = mod.add_class('RooAbsRealLValue', parent=RooAbsReal)
RooAbsRealLValue.add_method('getBins', retval('int'), [param('const char*', 'name', default_value='0')])
RooAbsRealLValue.add_method('getMin', retval('double'), [param('const char*', 'name', default_value='0')])
RooAbsRealLValue.add_method('getMax', retval('double'), [param('const char*', 'name', default_value='0')])
RooAbsRealLValue.add_method('setVal', None, [param('double', 'val')], is_pure_virtual=True)
RooAbsRealLValue.add_method('hasBinning', retval('bool'), [param('const char*', 'name')], is_pure_virtual=True)
