#include <TFile.h>
#include <TH1D.h>
#include <iostream>

void scale_energy()
{
  //straight tracks
  TFile* f_str = TFile::Open("DATA/total_str_energy.root", "READ");
  
  TH1D* hStr = (TH1D*)f_str->Get("hAll");
  TH1D* hStrScaled = (TH1D*)hStr->Clone("hStrScaled");
  
  hStrScaled->SetTitle("Scaled - straight tracks;Energy [keV];Counts");
  
  
  if (hStr->Integral() > 0) hStrScaled->Scale(1.0 / hStr->Integral());
  
  TFile* f_out_str = new TFile("DATA/scaled_str_energy.root", "RECREATE"); 
  hStrScaled->Write("hScaled");
  f_out_str->Close();
  f_str->Close();
  
  //kinked tracks
  TFile* f_knk = TFile::Open("DATA/total_knk_energy.root", "READ");
  
  TH1D* hKnk = (TH1D*)f_knk->Get("hAll");
  TH1D* hKnkScaled = (TH1D*)hKnk->Clone("hKnkScaled");
  
  hKnkScaled->SetTitle("Scaled - kinked tracks;Energy [keV];Counts");
  
  if (hKnk->Integral() > 0) hKnkScaled->Scale(1.0 / hKnk->Integral());
  
  TFile* f_out_knk = new TFile("DATA/scaled_knk_energy.root", "RECREATE"); 
  hKnkScaled->Write("hScaled");
  f_out_knk->Close();
  f_knk->Close();
}
  

  
