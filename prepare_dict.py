import megazord
"""Generate dictionaries for code (require rootcint tool"""


dict_h = ['RooBinned2DBicubicBase.h', 'RooCrossCorPdf.h', 'RooHistPdfAngleVar.h', 'RooHistPdfVar.h', 'RooPoly3Var.h', 'RooPoly4Var.h', 'RooSlimFitResult.h', 'coreLinkDef.h']
rcint = ['rootcint', '-cint', '-f', 'gammacombo/transResult.cxx', '-c', '-p', '-Igammacombo/include']
megazord.system.call(*(rcint+dict_h))
megazord.system.move('gammacombo/transResult.cxx', 'gammacombo/src/gammacomboCoreDict.cpp')
megazord.system.move('gammacombo/transResult.h', 'gammacombo/include/gammacomboCoreDict.h')


dict_h = ['RooAdsCartCoordVar.h', 'RooGLWADSDmixAcpADSVar.h', 'RooGLWADSDmixAcpVar.h', 'RooGLWADSDmixMaster.h',
          'RooGLWADSDmixRADSVar.h', 'RooGLWADSDmixRcpVar.h', 'RooGLWADSDmixRcpNewVar.h', 'RooGLWADSDmixRcpRatioVar.h',
          'RooGLWADSDmixRkpVar.h', 'RooGLWADSDmixRpmVar.h', 'RooGlwCartCoordVar.h', 'gammacomboLinkDef.h']
megazord.system.call(*(rcint+dict_h))
megazord.system.move('gammacombo/transResult.cxx', 'gammacombo/src/gammacomboDict.cpp')
megazord.system.move('gammacombo/transResult.h', 'gammacombo/include/gammacomboDict.h')
