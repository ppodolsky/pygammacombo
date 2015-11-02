import PyGammaCombo
tstr = PyGammaCombo.TString

parameters = PyGammaCombo.ParametersAbs()
g = parameters.newParameter(tstr("g"))
g.startvalue=0.09
r_dk = parameters.newParameter(tstr("r_dk"))
r_dk.startvalue = 0.2
r_dk.scan = parameters.range(0.3, 0.4)
kek = r_dk.scan
d_dk = parameters.newParameter(tstr("d_dk"))
GGSZ_pdf = PyGammaCombo.PDF_GGSZ(pars=parameters)
pdf = GGSZ_pdf.getPdf()
print(pdf.getLogVal())
print(pdf.getValV())
r_dk.scan = parameters.range(0.15, 0.3)
GGSZ_pdf = PyGammaCombo.PDF_GGSZ(pars=parameters)
pdf = GGSZ_pdf.getPdf()
print(pdf.getLogVal())
print(pdf.getValV())