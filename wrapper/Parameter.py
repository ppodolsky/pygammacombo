from wrapper import mod, param
from wrapper.TString import TString

Parameter = mod.add_class('Parameter')
Range = Parameter.add_class('Range')
Range.add_instance_attribute('min', 'float')
Range.add_instance_attribute('max', 'float')
Parameter.add_constructor([])
Parameter.add_method('setVal', None, [param('double', 'v')])
Parameter.add_instance_attribute('name', 'TString')
Parameter.add_instance_attribute('title', 'TString')
Parameter.add_instance_attribute('unit', 'TString')
Parameter.add_instance_attribute('startvalue', 'float')
Parameter.add_instance_attribute('phys', 'Range')
Parameter.add_instance_attribute('scan', 'Range')
Parameter.add_instance_attribute('force', 'Range')
Parameter.add_instance_attribute('bboos', 'Range')
Parameter.add_instance_attribute('free', 'Range')