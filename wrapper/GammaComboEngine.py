from wrapper import mod, param, retval
from wrapper.Combiner import Combiner
from wrapper.PDF_Abs import PDF_Abs
from wrapper.TString import TString

GammaComboEngine = mod.add_class('GammaComboEngine')

GammaComboEngine.add_method('addPdf', None, [param('int', 'id'),
                                            param('PDF_Abs*', 'pdf', transfer_ownership=False),
                                            param('TString', 'title', default_value='""')])
GammaComboEngine.add_method('getCombiner',
                            retval("Combiner* ", reference_existing_object=True, caller_owns_return=False),
                            [param('int', 'id')])
GammaComboEngine.add_method('printCombinations', None, [])
GammaComboEngine.add_method('printPdfs', None, [])
GammaComboEngine.add_method('print', None, [])
GammaComboEngine.add_method('run', None, [])

