from wrapper import mod, param, retval
from wrapper.PDF_Abs import PDF_Abs
from wrapper.RooAbsPdf import RooAbsPdf
from wrapper.RooArgSet import RooArgSet
from wrapper.TString import TString
from wrapper.StringsVector import StringsVector

Combiner = mod.add_class('Combiner')
Combiner.add_method('combine', None, [])
Combiner.add_method('getName', retval('TString'), [])
Combiner.add_method('getParameterNames', retval('std::vector<std::string>'), [])
Combiner.add_method('getParameters', retval('const RooArgSet*', reference_existing_object=True, caller_owns_return=False), [])
Combiner.add_method('getPdfName', retval('TString'), [])
Combiner.add_method('getPdf', retval('RooAbsPdf*', reference_existing_object=True, caller_owns_return=False), [])
Combiner.add_method('getTitle', retval('TString'), [])