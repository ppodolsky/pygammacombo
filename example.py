import PyGammaCombo
tstr = PyGammaCombo.TString

parameters = PyGammaCombo.ParametersAbs()
g = parameters.newParameter(tstr("g"))
g.startvalue=0.09
r_dk = parameters.newParameter(tstr("r_dk"))
r_dk.startvalue = 0.2
r_dk.scan = parameters.range(0.1, 0.3)
kek = r_dk.scan
d_dk = parameters.newParameter(tstr("d_dk"))
GGSZ_pdf = PyGammaCombo.PDF_GGSZ(pars=parameters)
pdf = GGSZ_pdf.getPdf()
print(pdf.getLogVal())
print(pdf.getValV())
r_dk.scan = parameters.range(0.3, 0.5)
r_dk.startvalue = 0.4
GGSZ_pdf.initParameters()
GGSZ_pdf.initRelations()
GGSZ_pdf.initObservables()
GGSZ_pdf.build()
pdf = GGSZ_pdf.getPdf()
print(pdf.getLogVal())
print(pdf.getValV())