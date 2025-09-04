#include "../../softwares/MiModule/include/MiEvent.h"
#include "../../softwares/MiModule/include/MiVertex.h"
#include "../../softwares/MiModule/include/MiVector3D.h"
#include "../../softwares/MiModule/include/MiPTD.h"
#include "../../softwares/MiModule/include/MiCD.h"

#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TROOT.h>
#include <vector>
#include <iostream>
#include <cmath>

R__LOAD_LIBRARY(../../softwares/MiModule/lib/libMiModule.so);

bool isInYZones(double y)
{
	return (y >= -2500 && y <= -2200) ||
	       (y >= -2000 && y <= -1400) ||
	       (y >= -1100 && y <= -500) ||
	       (y >= -300 && y <= 300) ||
	       (y >= 500 && y <= 1100) ||
	       (y >= 1400 && y <= 2000) ||
	       (y >= 2200 && y <= 2500);
}
	       
void rectangle_check() 
{ 
  std::ofstream outfile("events_in_rectangle.txt");
  		
  for (int i=0; i<100; i++) 
  {
  	TString folder = Form("DATA/%d", i);
  	TString infile = folder + "/Default.root"; //Concatenates the folder path with the input file name

  	
  	std::cout << "Processing folder " << folder << std::endl;
  	
  	TFile* f = TFile::Open(infile, "READ");
  	TTree* t = (TTree*)f->Get("Event");
  
  	MiEvent* Eve = new MiEvent(); 
  	t->SetBranchAddress("Eventdata", &Eve);
  
  	
  	Long64_t nentries = t->GetEntries(); //returns number of entries stored in the tree
  	for (Long64_t ie=0; ie<nentries; ie++)  //ie is for i entries
  	{
  		t->GetEntry(ie);
  		
  		MiPTD* ptd = Eve->getPTD();
  		
  		int nParts = Eve->getPTDNoPart();
  		for (int ip=0; ip<nParts; ip++) 
  		{
  			MiCDParticle* particle = ptd->getpart(ip);
  			
  			int charge = particle->getcharge();
  			if (charge != 1000) continue;
  			
  			int nVerts = Eve->getPTDNoVert(ip);
  			if (nVerts > 0)
  			{
  				double x = Eve->getPTDverX(ip, 0);
  				double y = Eve->getPTDverY(ip, 0);
  				double z = Eve->getPTDverZ(ip, 0);  
  				
  				if (isInYZones(y))
  				{
  					std::string line = "Folder " + std::string(folder.Data()) +
  						   " Event " + std::to_string(ie) +
  						   " -> vertex: " 
  						   "y = " + std::to_string(y) +
  						   ", z = " + std::to_string(z);
  					
  					std::cout << line << std::endl;
  					outfile << line << std::endl;
  				}
  				
  			}
  		}
  	}
  
  	f->Close();
 }
 outfile.close();
}
  					  					  
  
  

  

