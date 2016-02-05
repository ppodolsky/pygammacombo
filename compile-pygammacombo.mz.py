import megazord
import wrapper
import os

codegen = wrapper.generate('PyGammaCombo.cpp')

wrapper_library = megazord \
    .Target('PyGammaCombo.cpp', compiler='g++', output='PyGammaCombo.so')\
    .add_library_path('./')\
    .add_include_path('./gammacombo/include')\
    .add_support(["root", "python3"])\
    .add_library(["RooFitCore", "RooFit"])\
    .add_library("gammacomboCoreComponents")\
    .add_options('PIC')\
    .set_optimization_level(3)

wrapper_library.assembly()
os.remove('PyGammaCombo.cpp')
