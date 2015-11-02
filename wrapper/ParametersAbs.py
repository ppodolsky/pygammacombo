from wrapper import *
from wrapper.Parameter import Parameter
from wrapper.Parameter import Range
from wrapper.RooRealVar import RooRealVar
from wrapper.TString import TString

ParametersAbs = mod.add_class('ParametersAbs')
ParametersAbs.add_constructor([])
ParametersAbs.add_method('var', retval('Parameter *', reference_existing_object=False), [param('TString', 'name')])
ParametersAbs.add_method('get', retval('RooRealVar *', reference_existing_object=False), [param('TString', 'name')])
ParametersAbs.add_method('range', retval('Parameter::Range'), [param('float', 'min'), param('float', 'max')])
ParametersAbs.add_method('newParameter', retval('Parameter *', caller_owns_return=True, reference_existing_object=True),
                         [param('TString', 'name')])
