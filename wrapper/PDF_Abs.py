from wrapper import *
from wrapper.RooAbsPdf import RooAbsPdf
from wrapper.RooArgList import RooArgList


PDF_Abs = mod.add_class('PDF_Abs')
PDF_Abs.add_method('getPdf', retval('RooAbsPdf *', reference_existing_object=True), [])
PDF_Abs.add_method('build', None, [])
PDF_Abs.add_method('buildPdf', None, [])
PDF_Abs.add_method('buildCov', None, [])
PDF_Abs.add_method('initObservables', None, [])
PDF_Abs.add_method('initParameters', None, [])
PDF_Abs.add_method('initRelations', None, [])
PDF_Abs.add_method('setCorrelations', None, [param('config', 'c')])
PDF_Abs.add_method('setObservables', None, [param('config', 'c',)])
PDF_Abs.add_method('setUncertainties', None, [param('config', 'c')])
PDF_Abs.add_method('getTitle', retval('TString'), [])
PDF_Abs.add_method('getName', retval('TString'), [])
PDF_Abs.add_method('getGcId', retval('int'), [])
PDF_Abs.add_method('getParameters', retval('RooArgList *', reference_existing_object=True), [])

