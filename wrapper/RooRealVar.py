from wrapper import *

RooRealVar = mod.add_class('RooRealVar')
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