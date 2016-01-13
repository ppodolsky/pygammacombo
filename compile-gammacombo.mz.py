import megazord

gammacombo_library = megazord \
    .Target('./gammacombo/src/*.cpp', compiler='g++', delayed=False, output='libgammacomboCoreComponents.so')\
    .add_include_path('./gammacombo/include')\
    .add_support("root")\
    .add_library(["RooFitCore", "RooFit", "Html", "Minuit", "Thread", "RooStats", "Gui", "TreePlayer", "GenVector"])\
    .add_options('PIC')\
    .set_optimization_level(3)

gammacombo_library.assembly()



