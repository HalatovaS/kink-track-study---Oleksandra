#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <TLegend.h>
#include <iostream>

void comparison_knk()
{
  TFile* f_knkNew = TFile::Open("DATA/ellipse_scaled_knk_energy.root", "READ");
  TFile* f_knkOld = TFile::Open("DATA/scaled_knk_energy.root", "READ");
  
  TH1D* hKnkOld = (TH1D*)f_knkOld->Get("hScaled");
  TH1D* hKnkNew = (TH1D*)f_knkNew->Get("hScaled");
  
  gStyle->SetOptStat(1100);
  gStyle->SetStatFontSize(0.04);
 
  hKnkOld->SetLineColor(kBlue);
  hKnkOld->SetLineWidth(2);
  hKnkNew->SetLineColor(kRed);
  hKnkNew->SetLineWidth(2);
  
  TCanvas* c2 = new TCanvas("c1", "Old vs New kinked tracks", 1000, 800);
  hKnkOld->SetTitle("Old vs New kinked tracks;Energy [keV];Counts");
  
  hKnkOld->Draw("HIST");
  hKnkNew->Draw("HIST SAME");
  
  TLegend* leg = new TLegend(0.65, 0.75, 0.88, 0.88);
  leg->AddEntry(hKnkOld, "Old Kinked tracks", "l");
  leg->AddEntry(hKnkNew, "New Kinked tracks", "l");
  leg->Draw();
  
  c2->Update();
  
  TPaveStats *stbox = (TPaveStats*)hKnkOld->FindObject("stats");
  if (stbox) {
  	stbox->SetX1NDC(0.1);
  	stbox->SetX2NDC(0.3);
  	stbox->SetY1NDC(0.8);
  	stbox->SetY2NDC(0.9);
  }
 
  c2->Modified();
  c2->Update();
  
  c2->SaveAs("DATA/comparison_knk.png");
  
}
  
  
  
  
  
  
  
