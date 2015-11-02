from wrapper import *

ParametersVector = mod.add_container('std::vector<Parameter*>',
                                     retval('Parameter*', caller_owns_return=True),
                                     'vector',
                                     custom_name='ParametersVector')