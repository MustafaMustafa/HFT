#!/usr/bin/python
from ROOT import  gStyle,TCanvas,TLegend,TPaveText,gPad
from ROOT import TGraph,TColor,TGaxis
from numpy import array

def get_a_canvas(name="canvas"):
    return TCanvas(name,"",800,450)

def get_a_legend(header="",lx=0.2,ly=0.67,ux=0.3,uy=0.88):
  legend = TLegend(lx,ly,ux,uy)
  legend.SetFillColor(0)
  legend.SetBorderSize(0)
  legend.SetTextFont(132)
  legend.SetTextSize(0.035)
  if header != "": legend.SetHeader(header)
  return legend

def get_pavetext(lx=.05,ly=.1,ux=.95,uy=.8):
  pt = TPaveText(lx,ly,ux,uy)
  pt.SetFillColor(0);
  pt.SetTextSize(0.03);
  pt.SetTextFont(132);
  pt.SetTextAlign(12);
  return pt

def set_style(gr,name=None,title=None,marker=None,color=1,xtitle=None,ytitle=None
              ,xmin=None,xmax=None,ymin=None,ymax=None,minimum=None,maximum=None
              ,size=None,width=None,line=None,fill=None):

  gr.SetLineColor(color)

  if marker is not None: 
    gr.SetMarkerStyle(marker)
    gr.SetMarkerColor(color)
  if size is not None: gr.SetMarkerSize(size)
  if width is not None: gr.SetLineWidth(width)
  if line is not None: gr.SetLineStyle(line)
  if name is not None: gr.SetName(name)
  if title is not None: gr.SetTitle(title)
  if xtitle is not None: gr.GetXaxis().SetTitle(xtitle)
  if ytitle is not None: gr.GetYaxis().SetTitle(ytitle)
  if maximum is not None: gr.SetMaximum(maximum)
  if minimum is not None: gr.SetMinimum(minimum)
  if (xmin and xmax) is not None: gr.GetXaxis().SetRangeUser(xmin,xmax)
  if (ymin and ymax) is not None: gr.GetXaxis().SetRangeUser(ymin,ymax)
  if fill is not None: 
    gr.SetFillStyle(fill)
    gr.SetFillColor(color)

def get_shade(grUp,grDn):
  n = grUp.GetN()
  grShade = TGraph(2*n)

  for i in xrange(0,n):
    grShade.SetPoint(i,grUp.GetX()[i],grUp.GetY()[i])
    grShade.SetPoint(i+n,grUp.GetX()[n-i-1],grDn.GetY()[n-i-1])

  return grShade

def set_gstyle():
  gStyle.SetEndErrorSize(8);
  gStyle.SetOptTitle(0);
  gStyle.SetOptStat(0);
  gStyle.SetOptFit(111);
  gStyle.SetPadTickX(1);
  gStyle.SetPadTickY(1);
  gStyle.SetPalette(1);
  gStyle.SetCanvasColor(10);
  gStyle.SetFrameFillColor(10);
  gStyle.SetFillColor(0);
  gStyle.SetPadTopMargin(0.055);
  gStyle.SetPadBottomMargin(0.15);
  gStyle.SetPadRightMargin(0.026);
  gStyle.SetPadLeftMargin(0.115);
  gStyle.SetLabelSize(0.03,"X");
  gStyle.SetLabelSize(0.03, "Y");
  gStyle.SetTitleSize(0.04, "X");
  gStyle.SetTitleSize(0.04, "Y");
  gStyle.SetTitleFontSize(0.1);
  gStyle.SetTitleFont(132, "X");
  gStyle.SetTitleFont(132, "Y");
  gStyle.SetTitleFont(132, "Z");
  gStyle.SetTitleOffset(1.2, "Y");
  gStyle.SetStatFont(132);
  gStyle.SetStatFontSize(0.035);
  gStyle.SetStatBorderSize(0);
  gStyle.SetStatX(0.99);
  gStyle.SetStatY(0.87);
  gStyle.UseCurrentStyle();

  NRGBs = 5;
  NCont = 255;
  stops = array([0.00, 0.34, 0.61, 0.84, 1.00],dtype=float)
  reds = array([0.00, 0.00, 0.87, 1.00, 0.51],dtype=float)
  greens = array([0.00, 0.81, 1.00, 0.20, 0.00],dtype=float)
  blues = array([0.51, 1.00, 0.12, 0.00, 0.00],dtype=float)
  color = TColor()
  FI  = color.CreateGradientColorTable(NRGBs, stops, reds, greens, blues, NCont);
  gStyle.SetNumberContours(NCont);

  gaxis = TGaxis()
  gaxis.SetMaxDigits(4)

