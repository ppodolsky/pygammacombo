from wrapper import *
from wrapper.TString import TString

RooPrintable = mod.add_class('RooPrintable')
RooPrintable.add_method('printValue', None, [param('std::ostream&', 'os')], is_const=True, is_pure_virtual=True)
RooPrintable.add_method('printMultiline', None, [param('std::ostream&', 'os'),
                                                 param('int', 'contents'),
                                                 param('bool', 'verbose', default_value='true'),
                                                 param('TString', 'indent', default_value='""')],
                        is_const=True, is_pure_virtual=True)
RooPrintable.add_method('printTree', None, [param('std::ostream&', 'os'),
                                            param('TString', 'indent', default_value='""')],
                        is_const=True, is_pure_virtual=True)