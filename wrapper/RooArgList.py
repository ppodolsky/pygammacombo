from wrapper import *
from wrapper.RooAbsArg import RooAbsArg

RooArgList = mod.add_class('RooArgList')
RooArgList.add_method('index', retval('int'), [param('const char*', 'name')])
RooArgList.add_method('at', retval('RooAbsArg*', reference_existing_object=True), [param('int', 'idx')])