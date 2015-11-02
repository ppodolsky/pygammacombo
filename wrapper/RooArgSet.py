from wrapper import *

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