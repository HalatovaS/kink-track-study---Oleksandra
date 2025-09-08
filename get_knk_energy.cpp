#include "../softwares/MiModule/include/MiEvent.h"
#include "../softwares/MiModule/include/MiCD.h"
#include "../softwares/MiModule/include/MiCDParticle.h"
#include "../softwares/MiModule/include/MiCDCaloHit.h"
#include "../softwares/MiModule/include/MiPTD.h"

#include <TFile.h>
#include <TTree.h>
#include <TH2F.h>
#include <TSystem.h>
#include <TROOT.h>
#include <vector>
#include <iostream>

R__LOAD_LIBRARY(../../softwares/MiModule/lib/libMiModule.so);

void get_knk_energy()
{
 TH1D *hAll = new TH1D("hAll", "Energy spectrum - kinked tracks;Energy [keV];N", 200, 0, 2000);
 
 for (int i=0; i<100; i++) 
  {
  	TString folder = Form("DATA/%d", i);
  	TString infile = folder + "/Default.root"; //Concatenates the folder path with the input file name
  	TString outfile = folder + "/ellipse_knk_energy.root"; //Same, but output
  	
  	
  	
  	TFile* f = TFile::Open(infile, "READ");
  	TTree* t = (TTree*)f->Get("Event"); //get tree named "Event"
  
  	MiEvent* Eve = new MiEvent(); //Attach MiEvent object
  	t->SetBranchAddress("Eventdata", &Eve);
  	
  	TH1D* hEnergy = new TH1D("hEnergy", "Energy - kinked tracks;Energy [keV];N", 200, 0, 2000); 
  			  	   
  	//loop over entries
  	Long64_t nentries = t->GetEntries();
  	
  	for (Long64_t ie=0; ie<nentries; ie++)  
  	{
  		t->GetEntry(ie); 
  		
  		MiPTD* ptd = Eve->getPTD();
  		int nParts = Eve->getPTDNoPart();
  		for (int ip=0; ip<nParts; ip++) 
  		{
  			MiCDParticle* particle = ptd->getpart(ip);
  			int charge = particle->getcharge();
  			
  			if (charge != 1000) continue;
  			
  			std::vector<MiCDCaloHit>* hits = particle->getcalohitv();
  			if (hits->empty())
  			{
  				continue;
  			}
  			
  			MiCDCaloHit* hit = particle->getcalohit(0);
  			if (hit)
  			{
  				double En = hit->getE();
  					
  				hEnergy->Fill(En);
  				hAll->Fill(En);
  			}
  		}
  	}
  	
  	TFile* f_output = new TFile(outfile, "RECREATE");
  	hEnergy->Write();
  	f_output->Close();
  
  	f->Close();
  	
  }
  TFile *f_output_all = new TFile("DATA/ellipse_total_knk_energy.root", "RECREATE");
  hAll->Write();
  f_output_all->Close();
 } 	
