import os

import megazord
import wrapper

#General Dictionary
dict_h = ['RooBinned2DBicubicBase.h', 'RooCrossCorPdf.h', 'RooHistPdfAngleVar.h', 'RooHistPdfVar.h', 'RooPoly3Var.h', 'RooPoly4Var.h', 'RooSlimFitResult.h', 'coreLinkDef.h']
rcint = ['rootcint', '-cint', '-f', 'gammacombo/gammacomboCoreDict.cxx', '-c', '-p', '-Igammacombo/include']
megazord.system.call(*(rcint+dict_h))
megazord.system.move('gammacombo/gammacomboCoreDict.cxx', 'gammacombo/src/gammacomboCoreDict.cpp')
megazord.system.move('gammacombo/gammacomboCoreDict.h', 'gammacombo/include/gammacomboCoreDict.h')

#Combiner Dictionary
dict_h = ['RooAdsCartCoordVar.h', 'RooGLWADSDmixAcpADSVar.h', 'RooGLWADSDmixAcpVar.h', 'RooGLWADSDmixMaster.h',
          'RooGLWADSDmixRADSVar.h', 'RooGLWADSDmixRcpVar.h', 'RooGLWADSDmixRcpNewVar.h', 'RooGLWADSDmixRcpRatioVar.h',
          'RooGLWADSDmixRkpVar.h', 'RooGLWADSDmixRpmVar.h', 'RooGlwCartCoordVar.h', 'gammacomboLinkDef.h']
rcint = ['rootcint', '-cint', '-f', 'gammacombo/gammacomboDict.cxx', '-c', '-p', '-Igammacombo/include']
megazord.system.call(*(rcint+dict_h))
megazord.system.move('gammacombo/gammacomboDict.cxx', 'gammacombo/src/gammacomboDict.cpp')
megazord.system.move('gammacombo/gammacomboDict.h', 'gammacombo/include/gammacomboDict.h')

gammacombo_library = megazord \
    .Target('./gammacombo/src/*.cpp', delayed=False, output='libgammacomboCoreComponents.so')\
    .add_include_path('./gammacombo/include')\
    .add_support("root")\
    .add_library(["RooFitCore", "RooFit", "Html", "Minuit", "Thread", "RooStats", "Gui", "TreePlayer", "GenVector"])\
    .set_optimization_level(3)

codegen = wrapper.generate('PyGammaCombo.cpp')

# Compiling wrapper
wrapper_library = megazord \
    .Target('PyGammaCombo.cpp', output='PyGammaCombo.so')\
    .depends_on(gammacombo_library)\
    .add_library_path('./')\
    .add_include_path('./gammacombo/include')\
    .add_support(["root", "python3"])\
    .add_library(['RooFitCore'])\
    .set_optimization_level(3)

wrapper_library.assembly()
megazord.system.mkdir_p(('./output'))
wrapper_library.deploy_to('./output')
os.remove('PyGammaCombo.cpp')



