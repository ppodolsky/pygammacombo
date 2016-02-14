from wrapper import *
from wrapper.ParametersAbs import ParametersAbs

ParametersGammaCombo = mod.add_class('ParametersGammaCombo', parent=ParametersAbs)
ParametersGammaCombo.add_constructor([])
ParametersGammaCombo.add_method('defineParameters', None, [], visibility='protected')
