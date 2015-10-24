from wrapper.commons import *

PDF_GGSZ_cartesian = mod.add_class('PDF_GGSZ_cartesian', parent=PDF_Abs)
PDF_GGSZ_cartesian.add_constructor([param('config', 'cObs', default_value='lumi1fb'),
                                    param('config', 'cErr', default_value='lumi1fb'),
                                    param('config', 'cCor', default_value='lumi1fb'),
                                    param('ParametersAbs *', 'pars', default_value='0', transfer_ownership=True)])
PDF_GGSZ_cartesian.add_method('buildPdf', None, [])
PDF_GGSZ_cartesian.add_method('initObservables', None, [])
PDF_GGSZ_cartesian.add_method('initParameters', None, [])
PDF_GGSZ_cartesian.add_method('initRelations', None, [])
PDF_GGSZ_cartesian.add_method('setCorrelations', None, [param('config', 'c')])
PDF_GGSZ_cartesian.add_method('setObservables', None, [param('config', 'c',)])
PDF_GGSZ_cartesian.add_method('setUncertainties', None, [param('config', 'c')])
PDF_GGSZ_cartesian.add_method('getTitle', retval('TString'), [])
PDF_GGSZ_cartesian.add_method('getName', retval('TString'), [])
PDF_GGSZ_cartesian.add_method('getGcId', retval('int'), [])