#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <TLegend.h>
#include <iostream>

void comparison_str()
{
  TFile* f_strNew = TFile::Open("DATA/ellipse_scaled_str_energy.root", "READ");
  TFile* f_strOld = TFile::Open("DATA/scaled_str_energy.root", "READ");
  
  TH1D* hStrOld = (TH1D*)f_strOld->Get("hScaled");
  TH1D* hStrNew = (TH1D*)f_strNew->Get("hScaled");
  
  gStyle->SetOptStat(1100);
  gStyle->SetStatFontSize(0.04);
 
  hStrOld->SetLineColor(kBlue);
  hStrOld->SetLineWidth(2);
  hStrNew->SetLineColor(kRed);
  hStrNew->SetLineWidth(2);
  
  TCanvas* c1 = new TCanvas("c1", "Old vs New straight tracks", 1000, 800);
  hStrOld->SetTitle("Old vs New straight tracks;Energy [keV];Counts");
  
  hStrOld->Draw("HIST");
  hStrNew->Draw("HIST SAME");
  
  TLegend* leg = new TLegend(0.65, 0.75, 0.88, 0.88);
  leg->AddEntry(hStrOld, "Old Straight tracks", "l");
  leg->AddEntry(hStrNew, "New Straight tracks", "l");
  leg->Draw();
  
  c1->Update();
  
  TPaveStats *stbox = (TPaveStats*)hStrOld->FindObject("stats");
  if (stbox) {
  	stbox->SetX1NDC(0.1);
  	stbox->SetX2NDC(0.3);
  	stbox->SetY1NDC(0.8);
  	stbox->SetY2NDC(0.9);
  }
 
  c1->Modified();
  c1->Update();
  
  c1->SaveAs("DATA/comparison_str.png");
  
}
  
  
  
  
  
  
  
