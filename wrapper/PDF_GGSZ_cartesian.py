from wrapper import *
from wrapper.PDF_Abs import PDF_Abs

PDF_GGSZ_cartesian = mod.add_class('PDF_GGSZ_cartesian', parent=PDF_Abs)
PDF_GGSZ_cartesian.add_constructor([param('config', 'cObs', default_value='lumi1fb'),
                                    param('config', 'cErr', default_value='lumi1fb'),
                                    param('config', 'cCor', default_value='lumi1fb'),
                                    param('ParametersAbs *', 'pars', default_value='0', transfer_ownership=True)])