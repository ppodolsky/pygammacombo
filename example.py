import PyGammaCombo
tstr = PyGammaCombo.TString


parameters = PyGammaCombo.ParametersAbs()
g = parameters.newParameter(tstr("g"))
r_dk = parameters.newParameter(tstr("r_dk"))
r_dk.startvalue = 0.09
d_dk = parameters.newParameter(tstr("d_dk"))
GGSZ_pdf = PyGammaCombo.PDF_GGSZ(pars=parameters)
pdf = GGSZ_pdf.getPdf()
print(pdf.getLogVal())
print(pdf.getValV())