#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"


using namespace std;

class LHEevent {
public:
  LHEevent() { };
  ~LHEevent() { };


  /* 
     This assumes we have an LHE file with a photophilic ALP Primakoff production process, or, 
     its decay products (two photons). Generally these are two different LHE files but we use 
     the same parser for convenience.
     The ALP PDGID is assumed to be 666 (hardwired below).
   */

  
  int pdgEl;
  int pdgGam1, pdgGam2, pdgALP;

  TLorentzVector vEl; //beam e-
  TLorentzVector vGam1, vGam2;// outgoing e-,e+
  TLorentzVector vALP; //produced ALP before/undecayed
  TLorentzVector vGamGam; // di-gamma fourvector

  unsigned npart;
  double weight;
  double scale;
  double xsec;
  double nevts;
  double nele;
  double ngamma;
  double nALP;
};


bool rewind(std::istringstream *iss, std::string line) { 
  (*iss).clear();
  (*iss).str(line);
  (*iss).seekg(0,ios::beg);
  return true;
}



int main( int argc, char** argv ) { 
  std::cout << "start" << std::endl;
  ifstream ifs(argv[1]);

  int pdgid;
  int status,mo1,mo2,dau1,dau2;
  double px, py, pz, e, m;
  double d1,d2;

  unsigned npart;
  int dunno1;
  double weight, dunno2, dunno3, dunno4;

  TFile * f = new TFile(argv[2], "RECREATE");
  TTree * t = new TTree( "t","t");
  LHEevent myevent;
  myevent.xsec = strtod(argv[3], NULL);
  myevent.nevts = strtod(argv[4], NULL);


  t->Branch( "xsec", &(myevent.xsec) );
  t->Branch( "nevts", &(myevent.nevts) );
  t->Branch( "npart", &(myevent.npart) );
  t->Branch( "weight", &(myevent.weight) );
  t->Branch( "scale", &(myevent.scale) );
  t->Branch( "nele", &(myevent.nele) );
  t->Branch( "ngamma", &(myevent.ngamma) );
  t->Branch( "nALP", &(myevent.nALP) );
  t->Branch( "pdgEl", &(myevent.pdgEl) );
  t->Branch( "vEl", &(myevent.vEl) );
  t->Branch( "pdgGam1", &(myevent.pdgGam1) );
  t->Branch( "vGam1", &(myevent.vGam1) );
  t->Branch( "pdgGam2", &(myevent.pdgGam2) );
  t->Branch( "vGam2", &(myevent.vGam2) );
  t->Branch( "vGamGam", &(myevent.vGamGam) );
  t->Branch( "pdgALP", &(myevent.pdgALP) );
  t->Branch( "vALP", &(myevent.vALP) );

  
  int fill_count=0;
  int line_count=0;
  int ele_count=0;
  int gam_count=0;
  int ALP_count=0;
  string line;
  bool foundFirstGamma = false;
  while( !ifs.eof() ) {
    std::getline(ifs,line);
    std::istringstream iss;
    if( rewind(&iss,line) && (iss >> pdgid >> status >> mo1 >> mo2 >> dau1 >> dau2 
				     >> px >> py >> pz >> e  >> m >> d1 >> d2) 
	) {
#ifdef DEBUG
      cout << "index: " << line_count << "\tpdgid: " << pdgid << "\tstatus: " << status 
	   << "\tmo1: " << mo1 << "\tmo2: " << mo2 
	   << "\tpx: " << px << "\tpy: " << py 
      	   << "\te: " << e << "\td1: " << d1 << "\tlc: " << line_count << endl;
      cout.flush();
#endif
      line_count++;
      
      if ( pdgid == 11 && status==1){ //find beam e-
		myevent.vEl.SetPxPyPzE(px,py,pz,e);
		myevent.pdgEl = pdgid;
		ele_count++;
	
#ifdef DEBUG
	cout << "found beam e pdg: " << myevent.pdgEl << "\tpx: " << myevent.vEl.Px() << endl;
#endif
      } else if ( pdgid == 22 && status==1){ //find first outgoing photon (from ALP decay)

	 if (foundFirstGamma) { //find second outgoing gamma (from ALP decay)
	  myevent.vGam2.SetPxPyPzE(px,py,pz,e);
	  myevent.pdgGam2 = pdgid;
	  gam_count++;
	  // we have both gammas. construct the photon pair 4-vec
	  myevent.vGamGam = myevent.vGam1+myevent.vGam2;
	  foundFirstGamma = false; //reset
#ifdef DEBUG
	cout << "found second gamma pdg: " << myevent.pdgGam2 << "\tpx: " << myevent.vGam2.Px() << endl;
#endif
	}
	 else {
	  myevent.vGam1.SetPxPyPzE(px,py,pz,e);
	  myevent.pdgGam1 = pdgid;
	  gam_count++;
	  foundFirstGamma = true;
#ifdef DEBUG
	  cout << "found first gamma pdg: " << myevent.pdgGam1 << "\tpx: " << myevent.vGam1.Px() << endl;
#endif

	}      }// found (decay) photons
    } else if ( pdgid == 666 && status==1){ //find ALP
	  myevent.vALP.SetPxPyPzE(px,py,pz,e);
	  myevent.pdgALP = pdgid;
	  ALP_count++;
#ifdef DEBUG
	  cout << "found ALP pdg: " << myevent.pdgALP << "\tpx: " << myevent.vALP.Px() << endl;
#endif

    } else if( rewind(&iss,line) && (iss >> npart >> dunno1 >> weight >> dunno2 >> dunno3 >> dunno4)
	       ){
#ifdef DEBUG
      cout << "weight: " << weight << "\tnpart: " << npart << endl;
#endif
      myevent.npart = npart;
      myevent.weight = weight;
      myevent.scale = dunno2;
    } else {
#ifdef DEBUG      
      cout << "------------------------------" << endl;
#endif
      npart=0;
    }
    
    if( !npart ){
#ifdef DEBUG
      cout << "!npart" << endl;
#endif
      myevent.nele = ele_count;
      
      if( myevent.nele || myevent.ngamma || myevent.nALP){
		t->Fill();
		fill_count++;
#ifdef DEBUG
	cout << "filled ..." << fill_count 
	     << endl;
#endif
      }
      
      line_count=0;
      myevent.vGam1.SetPxPyPzE(0.,0.,0.,0.);
      myevent.vGam2.SetPxPyPzE(0.,0.,0.,0.);
      myevent.vGamGam.SetPxPyPzE(0.,0.,0.,0.);
      myevent.vALP.SetPxPyPzE(0.,0.,0.,0.);
      myevent.vEl.SetPxPyPzE(0.,0.,0.,0.);
      ele_count=0;
    }
    npart--;
  }
  cout << "fill_count: " << fill_count << endl;
  t->Write();
  f->Close();
  
}
