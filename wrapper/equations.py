from wrapper.commons import *


ParametersGammaCombo = mod.add_class('ParametersGammaCombo', parent=ParametersAbs)
ParametersGammaCombo.add_method('defineParameters', None, [], visibility='protected')


PDF_GGSZ = mod.add_class('PDF_GGSZ', parent=PDF_Abs)
PDF_GGSZ.add_constructor([param('config', 'cObs', default_value='lumi1fb'),
                                    param('config', 'cErr', default_value='lumi1fb'),
                                    param('config', 'cCor', default_value='lumi1fb'),
                                    param('ParametersAbs *', 'pars', default_value='0', transfer_ownership=True)])


PDF_GGSZ_cartesian = mod.add_class('PDF_GGSZ_cartesian', parent=PDF_Abs)
PDF_GGSZ_cartesian.add_constructor([param('config', 'cObs', default_value='lumi1fb'),
                                    param('config', 'cErr', default_value='lumi1fb'),
                                    param('config', 'cCor', default_value='lumi1fb'),
                                    param('ParametersAbs *', 'pars', default_value='0', transfer_ownership=True)])