#include "FileWriter.hh"

namespace PPS
{
  FileWriter::FileWriter(G4String filename) :
    fFilename(filename), fFile(0), fRunsTree(0), fEventsTree(0)
  {
    fFile = new TFile(fFilename, "RECREATE");
    fFile->cd();
    
    fRunsTree = new TTree("runs", "PPS simulation runs");
    fEventsTree = new TTree("events", "PPS simulation events");
    
    G4cout << __PRETTY_FUNCTION__ << " New file with name ' " << fFilename << " ' created and ready to be populated !" << G4endl;
  }
  
  FileWriter::~FileWriter()
  {
    G4cout << __PRETTY_FUNCTION__ << " File ' " << fFilename << " ' successfully created and filled with " << fEventsTree->GetEntries() << " events !" << G4endl;
    fFile->Write();
    fFile->Close();
  }
  
  void
  FileWriter::StoreRun()
  {
    if (!fFile or !fRunsTree) return;
    fRunsTree->Fill();
  }
  
  void
  FileWriter::StoreEvent()
  {
    if (!fFile or !fEventsTree) return;
    fEventsTree->Fill();
  }
}

