import os

import megazord
import wrapper

gammacombo_library = megazord \
    .Target('./gammacombo/src/*.cpp', compiler='g++', delayed=False, output='libgammacomboCoreComponents.so')\
    .add_include_path('./gammacombo/include')\
    .add_support("root")\
    .add_library(["RooFitCore", "RooFit", "Html", "Minuit", "Thread", "RooStats", "Gui", "TreePlayer", "GenVector"])\
    .add_options('PIC')\
    .set_optimization_level(3)

codegen = wrapper.generate('PyGammaCombo.cpp')

# Compiling wrapper
wrapper_library = megazord \
    .Target('PyGammaCombo.cpp', compiler='g++', output='PyGammaCombo.so')\
    .depends_on(gammacombo_library)\
    .add_library_path('./')\
    .add_include_path('./gammacombo/include')\
    .add_support(["root", "python3"])\
    .add_library(["RooFitCore", "RooFit"])\
    .add_options('PIC')\
    .set_optimization_level(3)

wrapper_library.assembly()
megazord.system.mkdir_p(('./output'))
wrapper_library.deploy_to('./output', with_dependencies=False)
gammacombo_library.deploy_to('/usr/lib')
os.remove('PyGammaCombo.cpp')



