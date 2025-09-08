#include "../../softwares/MiModule/include/MiEvent.h"
#include "../../softwares/MiModule/include/MiVertex.h"
#include "../../softwares/MiModule/include/MiVector3D.h"
#include "../../softwares/MiModule/include/MiPTD.h"
#include "../../softwares/MiModule/include/MiCD.h"
#include "../../softwares/MiModule/include/MiSD.h"

#include <TFile.h>
#include <TTree.h>
#include <TH2F.h>
#include <TSystem.h>
#include <TROOT.h>
#include <vector>
#include <iostream>

R__LOAD_LIBRARY(../../softwares/MiModule/lib/libMiModule.so);


void get_knk_vertices() 
{
  TH2F *hAll = new TH2F("hAll", "Vertices - kinked tracks;Y [mm];Z [mm]",
  			2000, -2500, 2500,
  			2000, -2000, 2000);
  			
  for (int i=0; i<100; i++) 
  {
  	TString folder = Form("DATA/%d", i);
  	TString infile = folder + "/Default.root"; //Concatenates the folder path with the input file name
  	TString outfile = folder + "/ellipse_knk_vertices.root"; //Same, but output
  	
  	std::cout << "Processing folder " << folder << std::endl;
  	
  	TFile* f = TFile::Open(infile, "READ");
  	TTree* t = (TTree*)f->Get("Event"); //get tree named "Event"
  
  	MiEvent* Eve = new MiEvent(); //Attach MiEvent object
  	t->SetBranchAddress("Eventdata", &Eve);
  
  
  	TH2F* hVertices = new TH2F("hVertices", "Vertices - kinked;Y [mm];Z [mm]",
  			  	   2000, -2500, 2500,     //ybins, ymin, ymax
  				   2000, -2000, 2000);    //zbins, zmin, zmax
  	//loop over entries
  	Long64_t nentries = t->GetEntries(); //returns number of entries stored in the tree
  	for (Long64_t ie=0; ie<nentries; ie++)  //ie is for i entries
  	{
  		t->GetEntry(ie); //loads the ith event from Default.root to MiEvent Eve object
  		
  		MiPTD* ptd = Eve->getPTD();
  		int nParts = Eve->getPTDNoPart();
  		for (int ip=0; ip<nParts; ip++) 
  		{
  			MiCDParticle* particle = ptd->getpart(ip);
  			int charge = particle->getcharge();
  			if (charge != 1000) continue;
  			
  			std::vector<MiCDCaloHit>* caloHits = particle->getcalohitv();
  			if (!caloHits || caloHits->empty())
  			{
  				continue;
  			}
  			
  			
  			MiCDCaloHit* hit = particle->getcalohit(0);
  			if (hit)
  			{
  				int nVerts = Eve->getPTDNoVert(ip);
  				if (nVerts > 0)
  				{
  					double x = Eve->getPTDverX(ip, 0);
  					double y = Eve->getPTDverY(ip, 0);
 					double z = Eve->getPTDverZ(ip, 0);  
  			
  					hVertices->Fill(y, z);
  					hAll->Fill(y, z);
  				}
  			}
  		}
  	}
  
  	TFile* f_output = new TFile(outfile, "RECREATE");
  	hVertices->Write();
  	f_output->Close();
  
  	f->Close();
 }
 
 TFile* f_output_all = new TFile("DATA/ellipse_total_knk_vertices.root", "RECREATE");
 hAll->Write();
 f_output_all->Close();
}
  					  					  
  
  

  

