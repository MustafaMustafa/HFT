#!/usr/bin/python
__author__ = 'Mustafa Mustafa'
__email__ = 'mmustafa@lbl.gov'
import sys
from ROOT import TFile, TCanvas, TH1F
import root_draw_style

def main():
    inputFile = TFile(sys.argv[1])

    root_draw_style.set_gstyle()

    canvas = root_draw_style.get_a_canvas()

    for key in inputFile.GetListOfKeys():
        hist = inputFile.Get(key.GetName())

        canvas.cd()
        hist.Draw()
        canvas.SaveAs(str(key.GetName())+".png")
    

if __name__ == '__main__':
    main()
