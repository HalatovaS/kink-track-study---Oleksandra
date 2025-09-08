#include <TFile.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <iostream>

void knk_visu()
{
 TFile* f = TFile::Open("DATA/ellipse_total_knk_vertices.root", "READ");
 TH2F* hVertices = (TH2F*)f->Get("hAll");
 
 TCanvas *c1 = new TCanvas("c1", "Vertex Distribution - kinked", 1000, 800);
 
 gStyle->SetNumberContours(255);
 
 gStyle->SetStatFontSize(0.04);
 
 hVertices->SetTitle("Vertices - kinked tracks;Y [mm];Z [mm]");
 hVertices->GetXaxis()->SetLabelSize(0.025);
 hVertices->GetYaxis()->SetLabelSize(0.025);
 
 hVertices->Draw("COLZ");
 
 c1->Update();
 
 TPaveStats *stbox = (TPaveStats*)hVertices->FindObject("stats");
  if (stbox) {
  	stbox->SetX1NDC(0.1);
  	stbox->SetX2NDC(0.3);
  	stbox->SetY1NDC(0.8);
  	stbox->SetY2NDC(0.9);
  }
  
  c1->Modified();
  c1->Update();
 
 c1->SaveAs("DATA/ellipse_knk_vert_visu.png");
 
}

