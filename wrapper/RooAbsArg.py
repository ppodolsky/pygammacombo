from wrapper import *
from wrapper.TObject import TObject

RooAbsArg = mod.add_class('RooAbsArg')
RooAbsArg.add_constructor([])
RooAbsArg.add_constructor([param('const char *', 'name'), param('const char *', 'title')])
RooAbsArg.add_constructor([param('const RooAbsArg&', 'other'), param('const char *', 'name', default_value='0')])
RooAbsArg.add_method('clone',
                     retval('TObject *', reference_existing_object=True),
                     [param('const char*', 'newname', default_value = '0')],
                     is_pure_virtual=True)
