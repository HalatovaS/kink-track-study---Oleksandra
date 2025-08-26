#include "../../softwares/MiModule/include/MiEvent.h"
#include "../../softwares/MiModule/include/MiSD.h"
#include "../../softwares/MiModule/include/MiSDParticle.h"

#include <TFile.h>
#include <TTree.h>
#include <TH2F.h>
#include <TSystem.h>
#include <TROOT.h>
#include <vector>
#include <iostream>

R__LOAD_LIBRARY(../../softwares/MiModule/lib/libMiModule.so);

void get_str_energy()
{
 TH1D *hAll = new TH1D("hAll", "Energy spectrum - straight tracks;Energy [keV];N", 100, 0, 2000);
 
 for (int i=0; i<100; i++) 
  {
  	TString folder = Form("DATA/%d", i);
  	TString infile = folder + "/Default.root"; //Concatenates the folder path with the input file name
  	TString outfile = folder + "/str_energy.root"; //Same, but output
  	
  	TFile* f = TFile::Open(infile, "READ");
  	TTree* t = (TTree*)f->Get("Event"); //get tree named "Event"
  
  	MiEvent* Eve = new MiEvent(); //Attach MiEvent object
  	t->SetBranchAddress("Eventdata", &Eve);
  	
  	TH1D* hEnergy = new TH1D("hEnergy", "Energy - straight tracks;Energy [keV];N", 100, 0, 2000); 
  			  	   
  	//loop over entries
  	Long64_t nentries = t->GetEntries(); //returns number of entries stored in the tree
  	for (Long64_t ie=0; ie<nentries; ie++)  //ie is for i entries
  	{
  		t->GetEntry(ie); //loads the ith event from Default.root to MiEvent Eve object
  		MiSD* sd = Eve->getSD(); 
  		
  		//loop over particles in the event i      //double e = Eve->gettotE();
  		int nPart = sd->getpartv()->size();          //hEnergy->Fill(e); 
  		for (int ip=0; ip<nPart; ip++)            //hAll->Fill(e);
  		{
  			MiSDParticle* p = sd->getpart(ip);
  			
  			if (p->getname() == "e-")
  			{
  				double en = p->getE();
  				hEnergy->Fill(en); 
  				hAll->Fill(en);
  			}
  		}
  	}
  	
  	TFile* f_output = new TFile(outfile, "RECREATE");
  	hEnergy->Write();
  	f_output->Close();
  
  	f->Close();
  	
  }
  TFile *f_output_all = new TFile("/DATA/total_str_energy.root", "RECREATE");
  hAll->Write();
  f_output_all->Close();
 } 	
