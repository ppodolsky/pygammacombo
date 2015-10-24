import os

import megazord
import wrapper

codegen = wrapper.generate()
file = open('PyGammaCombo.cpp', 'w')
file.write(codegen)
file.close()

# Compiling wrapper
libs = ['gammacomboCoreComponents.1.0.0', 'Core', 'RooFit', 'RooFitCore', 'm', 'dl']
libs.extend(megazord.system.library("python3"))
wrapper = megazord \
    .Target('PyGammaCombo.cpp', output='PyGammaCombo.so')\
    .add_library_path('./')\
    .add_library_path(megazord.system.library_paths("root"))\
    .add_library_path(megazord.system.library_paths("python3"))\
    .add_include_path(megazord.system.include_paths("root"))\
    .add_include_path(megazord.system.include_paths("python3"))\
    .add_include_path('./gammacombo/core/include')\
    .add_library(libs)

wrapper.assembly()
os.rename('libPyGammaCombo.so', 'PyGammaCombo.so')
