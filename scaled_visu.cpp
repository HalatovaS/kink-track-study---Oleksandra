#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <TLegend.h>
#include <iostream>

void scaled_visu()
{
  TFile* f_str = TFile::Open("DATA/scaled_str_energy.root", "READ");
  TFile* f_knk = TFile::Open("DATA/scaled_knk_energy.root", "READ");
  
  TH1D* hStr = (TH1D*)f_str->Get("hScaled");
  TH1D* hKnk = (TH1D*)f_knk->Get("hScaled");
  
  //real data
  TFile* f_real = TFile::Open("/sps/nemo/scratch/ykozina/Falaise/tutorial/CimrmanModule/testing/test2/energy_spectrum.root", "READ");
  TH1D* hReal = (TH1D*)f_real->Get("h_energy");
  
  double integral = hReal->Integral();
  if (integral > 0) hReal->Scale(1.0 / integral);
  
  gStyle->SetOptStat(1100);
  gStyle->SetStatFontSize(0.04);
 
  hStr->SetLineColor(kBlue);
  hStr->SetLineWidth(2);
  hKnk->SetLineColor(kRed);
  hKnk->SetLineWidth(2);
  hReal->SetLineColor(kGreen + 2); 
  hReal->SetLineWidth(2);
  
  TCanvas* c = new TCanvas("c", "Straight + Kinked scaled", 1000, 800);
  hStr->SetTitle("Straight + Kinked tracks;Energy [keV];Counts");
  
  hStr->Draw("HIST");
  hKnk->Draw("HIST SAME");
  hReal->Draw("HIST SAME");
  
  TLegend* leg = new TLegend(0.65, 0.75, 0.88, 0.88);
  leg->AddEntry(hStr, "Straight tracks", "l");
  leg->AddEntry(hKnk, "Kinked tracks", "l");
  leg->AddEntry(hReal, "Real data", "l");
  leg->Draw();
  
  c->Update();
  
  TPaveStats *stbox = (TPaveStats*)hStr->FindObject("stats");
  if (stbox) {
  	stbox->SetX1NDC(0.1);
  	stbox->SetX2NDC(0.3);
  	stbox->SetY1NDC(0.8);
  	stbox->SetY2NDC(0.9);
  }
 
  c->Modified();
  c->Update();
  
  c->SaveAs("DATA/scaled_all.png");
  
  double intStr = hStr->Integral();
  double intKnk = hKnk->Integral();
  double intReal = hReal->Integral();
  std::cout << "Straight tracks = " << intStr << std::endl;
  std::cout << "Kinked tracks = " << intKnk << std::endl;
  std::cout << "Real data = " << intReal << std::endl;
  
}
  
  
  
  
  
  
  
