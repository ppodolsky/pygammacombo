from wrapper import *

utils_namespace.add_enum('config', ['year2014','babar','babar2007','babar2008',
                                    'babar2010','babar2012','belle','belle2005cleo2009',
                                    'belle2006','belle2007','belle2009','belle2012','belle2012preliminary',
                                    'belle2013','belle2014','belle2013cleo2014','cdf2007','cdf2012',
                                    'cdf2013','ckm2014','cleo','cleo2001','cleo2009','cleo2012','cleo2014',
                                    'cleo2015','cleoFullDP','combos2008','combpipi','default_config',
                                    'excludeKdDdK3pi','exclusive2014','inclusive2014','focus2000','hfag',
                                    'hfagFP2014','hfagLP2011','hfagCHARM2015','highrb','highstattoy','lhcb',
                                    'lhcb2011','lhcb2012','lhcb2013','lhcb2013KK','lhcb2013pipi',
                                    'lhcb2013preliminary','lhcb2014','lhcb2018KK_extrap','lhcb_upgrade_extrap',
                                    'lhcbphis','lhcbcomb','lhcb_old','lumi40pb','lumi1fb','lumi1fbConfcFit',
                                    'lumi1fbConfsFit','lumi1fbNoAfav','lumi1fbPapercFit','lumi1fbPapercFitExpected',
                                    'lumi1fbPapersFit','lumi1fbSystCor','lumi1fbprompt','lumi1fbsl','lumi2fb',
                                    'lumi3fb','lumi3fbCPVA','lumi3fbFix','lumi3fbFullDP','lumi3fbPaper',
                                    'lumi3fbDKstz','lumi3fb_estimate','lumi5ab','lumi5fb','lumi9fb','lumi50ab',
                                    'lumi50fb','lambda1_3fb','lambdafree_3fb','manual','milc_update','none',
                                    'nophicorr','onlyGsDGs','pdg','sneha','toy','truth','useBicubic',
                                    'useCartCoords','useGaussian','useHistogram','useParametric','usePolarCoords',
                                    'useTradObs','world_average','zero'])

TString = mod.add_class("TString")
TString.add_constructor([param('const char *', 's')])
TString.add_method('Data', retval('const char*'), [])


TObject = mod.add_class("TObject")


Parameter = mod.add_class('Parameter')
Range = Parameter.add_class('Range')
Range.add_instance_attribute('min', 'float')
Range.add_instance_attribute('max', 'float')
Parameter.add_constructor([])
Parameter.add_method('setVal', None, [param('double', 'v')])
Parameter.add_instance_attribute('name', 'TString')
Parameter.add_instance_attribute('title', 'TString')
Parameter.add_instance_attribute('unit', 'TString')
Parameter.add_instance_attribute('startvalue', 'float')
Parameter.add_instance_attribute('phys', 'Range')
Parameter.add_instance_attribute('scan', 'Range')
Parameter.add_instance_attribute('force', 'Range')
Parameter.add_instance_attribute('bboos', 'Range')
Parameter.add_instance_attribute('free', 'Range')


RooAbsArg = mod.add_class('RooAbsArg')
RooAbsArg.add_constructor([])
RooAbsArg.add_constructor([param('const char *', 'name'), param('const char *', 'title')])
RooAbsArg.add_constructor([param('const RooAbsArg&', 'other'), param('const char *', 'name', default_value='0')])
RooAbsArg.add_method('clone',
                     retval('TObject *', reference_existing_object=True),
                     [param('const char*', 'newname', default_value = '0')],
                     is_pure_virtual=True)


RooAbsReal = mod.add_class('RooAbsReal')


RooArgSet = mod.add_class('RooArgSet')
RooArgSet.add_constructor([param('const RooArgSet&', 'set1'), param('const RooArgSet&', 'set2'),
                           param('const char*', 'name')])
RooArgSet.add_constructor([param('const RooAbsArg&', 'var1'), param('const char*', 'name')])
RooArgSet.add_constructor([param('const RooAbsArg&', 'var1'), param('const RooAbsArg&', 'var2'),
                           param('const char*', 'name')])
RooArgSet.add_constructor([param('const RooAbsArg&', 'var1'), param('const RooAbsArg&', 'var2'),
                           param('const RooAbsArg&', 'var3'), param('const char*', 'name')])
RooArgSet.add_constructor([param('const RooAbsArg&', 'var1'), param('const RooAbsArg&', 'var2'),
                           param('const RooAbsArg&', 'var3'), param('const RooAbsArg&', 'var4'),
                           param('const char*', 'name')])
RooArgSet.add_constructor([param('const RooAbsArg&', 'var1'), param('const RooAbsArg&', 'var2'),
                           param('const RooAbsArg&', 'var3'), param('const RooAbsArg&', 'var4'),
                           param('const RooAbsArg&', 'var5'), param('const char*', 'name')])
RooArgSet.add_constructor([param('const RooAbsArg&', 'var1'), param('const RooAbsArg&', 'var2'),
                           param('const RooAbsArg&', 'var3'), param('const RooAbsArg&', 'var4'),
                           param('const RooAbsArg&', 'var5'), param('const RooAbsArg&', 'var6'),
                           param('const char*', 'name')])
RooArgSet.add_constructor([param('const RooAbsArg&', 'var1'), param('const RooAbsArg&', 'var2'),
                           param('const RooAbsArg&', 'var3'), param('const RooAbsArg&', 'var4'),
                           param('const RooAbsArg&', 'var5'), param('const RooAbsArg&', 'var6'),
                           param('const RooAbsArg&', 'var7'), param('const char*', 'name')])
RooArgSet.add_constructor([param('const RooAbsArg&', 'var1'), param('const RooAbsArg&', 'var2'),
                           param('const RooAbsArg&', 'var3'), param('const RooAbsArg&', 'var4'),
                           param('const RooAbsArg&', 'var5'), param('const RooAbsArg&', 'var6'),
                           param('const RooAbsArg&', 'var7'), param('const RooAbsArg&', 'var8'),
                           param('const char*', 'name')])
RooArgSet.add_constructor([param('const RooAbsArg&', 'var1'), param('const RooAbsArg&', 'var2'),
                           param('const RooAbsArg&', 'var3'), param('const RooAbsArg&', 'var4'),
                           param('const RooAbsArg&', 'var5'), param('const RooAbsArg&', 'var6'),
                           param('const RooAbsArg&', 'var7'), param('const RooAbsArg&', 'var8'),
                           param('const RooAbsArg&', 'var9'), param('const char*', 'name')])

RooAbsPdf = mod.add_class('RooAbsPdf')
RooAbsPdf.add_method('getLogVal', retval('double'), [])


RooGaussian = mod.add_class('RooGaussian', parent=RooAbsPdf)
RooGaussian.add_constructor([param('const char *', 'name'), param('const char *', 'title'),
                            param('RooAbsReal&', '_x'), param('RooAbsReal&', 'mean'),
                            param('RooAbsReal&', '_sigma')])
RooGaussian.add_constructor([param('RooGaussian&', 'other'), param('const char *', 'name', default_value='0')])


RooRealVar = mod.add_class('RooRealVar')
RooRealVar.add_constructor([])
RooRealVar.add_constructor([param('const char *', 'name'), param('const char *', 'title'),
                            param('double', 'value'), param('const char *', 'unit', default_value='""')])
RooRealVar.add_constructor([param('const char *', 'name'), param('const char *', 'title'),
                            param('double', 'minValue'), param('double', 'maxValue'),
                            param('const char *', 'unit', default_value='""')])
RooRealVar.add_constructor([param('const char *', 'name'), param('const char *', 'title'),
                            param('double', 'value'), param('double', 'minValue'),
                            param('double', 'maxValue'), param('const char *', 'unit', default_value='""')])
RooRealVar.add_constructor([param('RooRealVar&', 'other'), param('const char *', 'name', default_value='0')])


ParametersVector = mod.add_container('std::vector<Parameter*>',
                                     retval('Parameter*', caller_owns_return=True),
                                     'vector',
                                     custom_name='ParametersVector')


ParametersAbs = mod.add_class('ParametersAbs')
ParametersAbs.add_constructor([])
ParametersAbs.add_method('var', retval('Parameter *', reference_existing_object=True), [param('TString', 'name')])
ParametersAbs.add_method('get', retval('RooRealVar *', reference_existing_object=True), [param('TString', 'name')])
ParametersAbs.add_method('newParameter', retval('Parameter *', reference_existing_object=True), [param('TString', 'name')])


PDF_Abs = mod.add_class('PDF_Abs')
PDF_Abs.add_method('getPdf', retval('RooAbsPdf *', reference_existing_object=True), [])
PDF_Abs.add_method('buildPdf', None, [])
PDF_Abs.add_method('initObservables', None, [])
PDF_Abs.add_method('initParameters', None, [])
PDF_Abs.add_method('initRelations', None, [])
PDF_Abs.add_method('setCorrelations', None, [param('config', 'c')])
PDF_Abs.add_method('setObservables', None, [param('config', 'c',)])
PDF_Abs.add_method('setUncertainties', None, [param('config', 'c')])
PDF_Abs.add_method('getTitle', retval('TString'), [])
PDF_Abs.add_method('getName', retval('TString'), [])
PDF_Abs.add_method('getGcId', retval('int'), [])

