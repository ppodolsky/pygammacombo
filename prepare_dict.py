import megazord
"""Generate dictionaries for code (require rootcint tool"""


dict_h = ['RooBinned2DBicubicBase.h', 'RooCrossCorPdf.h', 'RooHistPdfAngleVar.h', 'RooHistPdfVar.h',
          'RooPoly3Var.h', 'RooPoly4Var.h', 'RooSlimFitResult.h', 'coreLinkDef.h']
rcint = ['rootcint', '-cint', '-f', 'gammacombo/gammacomboCoreDict.cxx', '-c', '-p', '-Igammacombo/include']
megazord.system.call(*(rcint+dict_h))
megazord.system.move('gammacombo/gammacomboCoreDict.cxx', 'gammacombo/src/gammacomboCoreDict.cpp')
megazord.system.move('gammacombo/gammacomboCoreDict.h', 'gammacombo/include/gammacomboCoreDict.h')


dict_h = ['RooAdsCartCoordVar.h', 'RooGLWADSDmixAcpADSVar.h', 'RooGLWADSDmixAcpVar.h', 'RooGLWADSDmixMaster.h',
          'RooGLWADSDmixRADSVar.h', 'RooGLWADSDmixRcpVar.h', 'RooGLWADSDmixRcpNewVar.h', 'RooGLWADSDmixRcpRatioVar.h',
          'RooGLWADSDmixRkpVar.h', 'RooGLWADSDmixRpmVar.h', 'RooGlwCartCoordVar.h', 'RooGLWAcpVar.h', 'RooGLWRcpVar.h',
          'RooADSAVar.h', 'RooADSRVar.h', 'RooADSRpmVar.h', 'gammacomboLinkDef.h']
rcint = ['rootcint', '-cint', '-f', 'gammacombo/gammacomboDict.cxx', '-c', '-p', '-Igammacombo/include']
megazord.system.call(*(rcint+dict_h))
megazord.system.move('gammacombo/gammacomboDict.cxx', 'gammacombo/src/gammacomboDict.cpp')
megazord.system.move('gammacombo/gammacomboDict.h', 'gammacombo/include/gammacomboDict.h')
