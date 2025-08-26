#include <TFile.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <iostream>

void visu()
{
 TFile* f = TFile::Open("DATA/str_vertices.root", "READ");
 TH2F* hVertices = (TH2F*)f->Get("hAll");
 
 TCanvas *c1 = new TCanvas("c1", "Vertex Distribution - straight tracks", 1000, 800);
 
 gStyle->SetNumberContours(255);
 
 gStyle->SetStatFontSize(0.04);
 
 hVertices->SetTitle("Vertices - straight tracks;Y [mm];Z [mm]");
 
 hVertices->Draw("COLZ");
 c1->SetLogz();
 
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
 
 c1->SaveAs("DATA/str_vert_visu.png");
 
}

