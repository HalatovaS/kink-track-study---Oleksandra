#include <TFile.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TStyle.h>
#include <iostream>

void visu()
{
 TFile* f = TFile::Open("DATA/3/vertices.root", "READ");
 
 TH2F* hVertices = (TH2F*)f->Get("hVertices");
 TCanvas *c1 = new TCanvas("c1", "Vertex Distribution", 800, 600);
 
 hVertices->SetTitle("Vertex positions;Y [mm];Z [mm]");
 hVertices->Draw("COLZ");
 
 c1->Update();
 
 TPaveStats *stbox = (TPaveStats*)hVertices->FindObject("stats");
  if (stbox) {
  	stbox->SetX1NDC(0.1);
  	stbox->SetX2NDC(0.3);
  	stbox->SetY1NDC(0.9);
  	stbox->SetY2NDC(1.0);
  }
  
  c1->Modified();
  c1->Update();
 
 c1->SaveAs("DATA/3/vert_visu.png");
 
}

