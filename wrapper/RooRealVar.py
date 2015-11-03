from wrapper import *
from wrapper.RooAbsRealLValue import RooAbsRealLValue

RooRealVar = mod.add_class('RooRealVar', parent=RooAbsRealLValue)
RooRealVar.add_constructor([])
RooRealVar.add_constructor([param('const char *', 'name'), param('const char *', 'title'),
                            param('double', 'value'), param('const char *', 'unit', default_value='""')])
RooRealVar.add_constructor([param('const char *', 'name'), param('const char *', 'title'),
                            param('double', 'minValue'), param('double', 'maxValue'),
                            param('const char *', 'unit', default_value='""')])
RooRealVar.add_constructor([param('const char *', 'name'), param('const char *', 'title'),
                            param('double', 'value'), param('double', 'minValue'),
                            param('double', 'maxValue'), param('const char *', 'unit', default_value='""')])
RooRealVar.add_constructor([param('RooRealVar&', 'other'), param('const char *', 'name', default_value='0')])
RooRealVar.add_method('setVal', None, [param('double', 'val')], is_virtual=True)
RooRealVar.add_method('hasBinning', retval('bool'), [param('const char*', 'name')], is_virtual=True)
RooRealVar.add_method('clone', retval('TObject*', caller_owns_return=True, reference_existing_object=True), [param('const char*', 'newname')], is_virtual=True)