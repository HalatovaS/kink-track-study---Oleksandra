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
  TFile* f = TFile::Open("/sps/nemo/scratch/ohalatova/kink_track_study/Bi-207/DATA/3/Default.root", "READ");
  TTree* t = (TTree*)f->Get("Event"); //ged tree named "Event"
  
  MiEvent* Eve = new MiEvent(); //Attach MiEvent object
  t->SetBranchAddress("Eventdata", &Eve);
  
  
  TH2F* hVertices = new TH2F("hVertices", "Vertex positions;Y [mm];Z [mm]",
  					  1000, -2500, 2500,     //ybins, ymin, ymax
  					  1000, -2000, 2000);     //zbins, zmin, zmax
  //loop over entries
  Long64_t nentries = t->GetEntries(); //returns number of entries stored in the tree
  for (Long64_t i=0; i<nentries; i++)  
  {
  	t->GetEntry(i); //loads the ith event from Default.root to MiEvent Eve object
  	
  	//loop over particles in the event i
  	int nPart = Eve->getPTDNoPart(); 
  	for (int ip=0; ip<nPart; ip++) 
  	{
  		int nVert = Eve->getPTDNoVert(ip); //"how many "
  		for (int iv=0; iv<nVert; iv++) 
  		{
  			double y = Eve->getPTDverY(ip, iv);
  			double z = Eve->getPTDverZ(ip, iv);
  			hVertices->Fill(y, z);
  		}
  	}
  }
  
  TFile* f_output = new TFile("/sps/nemo/scratch/ohalatova/kink_track_study/Bi-207/DATA/3/vertices.root", "RECREATE");
  
  hVertices->Write();
  f_output->Close();
  
  f->Close();
 }
  					  
  					  
  					  
  					  
  					  
  					  
  					  
  					  
  					  
  					  
  					  
  
  

