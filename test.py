import unittest
import math
import PyGammaCombo
tstr = PyGammaCombo.TString

def degToRad(degs):
    return degs*(math.pi/180)

class TestStringMethods(unittest.TestCase):

    def test_PDF_class(self):
        lower_limit = 0
        upper_limit = math.pi
        parameters = PyGammaCombo.ParametersAbs()
        g = parameters.newParameter(tstr("g"))
        g.unit = tstr('Rad')
        g.scan = parameters.range(lower_limit, upper_limit)
        g.phys = parameters.range(-7, 7)
        g.force = parameters.range(lower_limit, upper_limit/2)
        g.bboos = parameters.range(lower_limit, upper_limit)

        r_dk = parameters.newParameter(tstr("r_dk"))
        r_dk.scan = parameters.range(0.02, 0.2)
        r_dk.phys = parameters.range(0, 1e-4)
        r_dk.force = parameters.range(0.02, 0.16)
        r_dk.bboos = parameters.range(0.01, 0.22)

        d_dk = parameters.newParameter(tstr("d_dk"))
        d_dk.unit = tstr('Rad')
        d_dk.scan = parameters.range(lower_limit, upper_limit)
        g.phys = parameters.range(-7, 7)
        g.force = parameters.range(lower_limit, upper_limit)
        g.bboos = parameters.range(lower_limit, upper_limit)
        GGSZ_pdf = PyGammaCombo.PDF_GGSZ(pars=parameters)
        pdf = GGSZ_pdf.getPdf()
        self.assertAlmostEqual(pdf.getLogVal(), -2.232716334262563)

    def test_GCE(self):
        gce = PyGammaCombo.gammacombo_utils.getGammaComboEngine("")
        gce.printCombinations()
        cmb = gce.getCombiner(26)
        cmb.combine()
        for p_name in cmb.getParameterNames():
            print(p_name)
        parameters = cmb.getParameters()
        parameters.setRealValue('d_dk', 1)
        parameters.setRealValue('g', 0.1)
        parameters.setRealValue('r_dk', 0.01)
        pdf = cmb.getPdf()
        print(pdf.getLogVal())

if __name__ == '__main__':
    unittest.main(verbosity=0)
