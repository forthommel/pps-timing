#include "FileWriter.hh"

namespace PPS
{
  FileWriter::FileWriter(G4String filename) :
    fFilename(filename), fFile(0), fEventsTree(0)
  {
    fFile = new TFile(fFilename, "RECREATE");
    fFile->cd();

    fRun = new RunInformation;
    
    fEventsTree = new TTree("events", "PPS simulation events");
    
    G4cout << __PRETTY_FUNCTION__ << " New file with name ' " << fFilename << " ' created and ready to be populated !" << G4endl;
  }
  
  FileWriter::~FileWriter()
  {
    G4cout << __PRETTY_FUNCTION__ << " File ' " << fFilename << " ' successfully created and filled with " << fEventsTree->GetEntries() << " events !" << G4endl;
    fRun->Write("run");
    fFile->Write();
    fFile->Close();

    //delete fRun;
  }
  
  void
  FileWriter::StoreRun()
  {
    if (!fFile) return;
  }
  
  void
  FileWriter::StoreEvent()
  {
    if (!fFile or !fEventsTree) return;
    fEventsTree->Fill();
  }
}

