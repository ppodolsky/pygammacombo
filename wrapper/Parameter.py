from wrapper import mod, param
from wrapper.TString import TString

Parameter = mod.add_class('Parameter')

Range = mod.add_struct('Range', outer_class=Parameter)
Range.add_instance_attribute('min', 'float')
Range.add_instance_attribute('max', 'float')

Parameter.add_constructor([])
Parameter.add_method('setVal', None, [param('double', 'v')])
Parameter.add_instance_attribute('name', 'TString')
Parameter.add_instance_attribute('title', 'TString')
Parameter.add_instance_attribute('unit', 'TString')
Parameter.add_instance_attribute('startvalue', 'float')
Parameter.add_instance_attribute('phys', 'Parameter::Range')
Parameter.add_instance_attribute('scan', 'Parameter::Range')
Parameter.add_instance_attribute('force', 'Parameter::Range')
Parameter.add_instance_attribute('bboos', 'Parameter::Range')
Parameter.add_instance_attribute('free', 'Parameter::Range')
