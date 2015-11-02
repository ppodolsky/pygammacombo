from wrapper import *

TString = mod.add_class("TString")
TString.add_constructor([param('const char *', 's')])
TString.add_method('Data', retval('const char*'), [])