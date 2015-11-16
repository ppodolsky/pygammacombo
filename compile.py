import os

import megazord
import wrapper

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



