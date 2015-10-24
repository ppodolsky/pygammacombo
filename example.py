import PyGammaCombo

eqs = PyGammaCombo.PDF_GGSZ_cartesian()
pdf = eqs.getPdf()
print(pdf.getLogVal())