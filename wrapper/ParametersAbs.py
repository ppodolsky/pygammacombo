from wrapper import *
from wrapper.Parameter import Parameter
from wrapper.RooRealVar import RooRealVar
from wrapper.TString import TString

ParametersAbs = mod.add_class('ParametersAbs')
ParametersAbs.add_constructor([])
ParametersAbs.add_method('var', retval('Parameter *', reference_existing_object=True), [param('TString', 'name')])
ParametersAbs.add_method('get', retval('RooRealVar *', reference_existing_object=True), [param('TString', 'name')])
ParametersAbs.add_method('newParameter', retval('Parameter *', reference_existing_object=True), [param('TString', 'name')])
