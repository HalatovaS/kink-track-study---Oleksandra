#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <iostream>

void energy_str_visu()
{
 TFile* f = TFile::Open("DATA/total_str_energy.root", "READ");
 TH1D* hEnergy = (TH1D*)f->Get("hAll");
 
 TCanvas *c1 = new TCanvas("c1", "Energy spectrum - straight tracks", 1000, 800);
 
 gStyle->SetOptStat(1100);
 gStyle->SetStatFontSize(0.04);
 
 hEnergy->SetLineColor(kBlue);
 hEnergy->SetLineWidth(2);
 hEnergy->SetTitle("Energy spectrum - straight tracks;Energy [keV];N");
 
 hEnergy->Draw("HIST");
 
 c1->Update();
 
 TPaveStats *stbox = (TPaveStats*)hEnergy->FindObject("stats");
  if (stbox) {
  	stbox->SetX1NDC(0.1);
  	stbox->SetX2NDC(0.3);
  	stbox->SetY1NDC(0.8);
  	stbox->SetY2NDC(0.9);
  }
 
 c1->Modified();
 c1->Update();
  
 c1->SaveAs("DATA/str_energy_spectrum.png");
 
}
 
 
 


