#include "../../softwares/MiModule/include/MiEvent.h"
#include "../../softwares/MiModule/include/MiVertex.h"
#include "../../softwares/MiModule/include/MiVector3D.h"
#include "../../softwares/MiModule/include/MiPTD.h"

#include <TFile.h>
#include <TTree.h>
#include <TH2F.h>
#include <TSystem.h>
#include <TROOT.h>
#include <vector>
#include <iostream>

R__LOAD_LIBRARY(../../softwares/MiModule/lib/libMiModule.so);


void get_vertices() 
{
  TH2F *hAll = new TH2F("hAll", "Vertices of all events;Y [mm];Z [mm]",
  			2000, -2500, 2500,
  			2000, -2000, 2000);
  			
  for (int i=0; i<100; i++) 
  {
  	TString folder = Form("DATA/%d", i);
  	TString infile = folder + "/Default.root"; //Concatenates the folder path with the input file name
  	TString outfile = folder + "/vertices.root"; //Same, but output
  	
  	TFile* f = TFile::Open(infile, "READ");
  	TTree* t = (TTree*)f->Get("Event"); //get tree named "Event"
  
  	MiEvent* Eve = new MiEvent(); //Attach MiEvent object
  	t->SetBranchAddress("Eventdata", &Eve);
  
  
  	TH2F* hVertices = new TH2F("hVertices", "Vertex positions;Y [mm];Z [mm]",
  			  	   2000, -2500, 2500,     //ybins, ymin, ymax
  				   2000, -2000, 2000);    //zbins, zmin, zmax
  	//loop over entries
  	Long64_t nentries = t->GetEntries(); //returns number of entries stored in the tree
  	for (Long64_t ie=0; ie<nentries; ie++)  //ie is for i entries
  	{
  		t->GetEntry(ie); //loads the ith event from Default.root to MiEvent Eve object
  	
  		//loop over particles in the event i
  		int nPart = Eve->getPTDNoPart(); 
  		for (int ip=0; ip<nPart; ip++) 
  		{
  			int nVert = Eve->getPTDNoVert(ip); 
  			for (int iv=0; iv<nVert; iv++) 
  			{
  				double y = Eve->getPTDverY(ip, iv);
  				double z = Eve->getPTDverZ(ip, iv);
  				hVertices->Fill(y, z);
  				hAll->Fill(y, z);
  			}
  		}
  	}
  
  	TFile* f_output = new TFile(outfile, "RECREATE");
  	hVertices->Write();
  	f_output->Close();
  
  	f->Close();
 }
 TFile *f_output_all = new TFile("DATA/all_vertices.root", "RECREATE");
 hAll->Write();
 f_output_all->Close();
}
  					  					  
  
  

