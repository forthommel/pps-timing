#include "FileWriter.hh"

namespace PPS
{
  FileWriter::FileWriter(G4String filename) :
    fFilename(filename), fFile(0), fRun(0), fEvent(0)
  {
    fFile = new TFile(fFilename, "RECREATE");
    fFile->cd();

    fRun = new RunInformation;
    fEvent = new EventInformation;
    
    G4cout << __PRETTY_FUNCTION__ << " New file with name ' " << fFilename << " ' created and ready to be populated !" << G4endl;
  }
  
  FileWriter::~FileWriter()
  {
    G4cout << __PRETTY_FUNCTION__ << " File ' " << fFilename << " ' successfully created and filled with " << fEvent->GetEntries() << " events !" << G4endl;
    fFile->Write();
    fFile->Close();
  }
  
  void
  FileWriter::StoreRun()
  {
    if (!fFile or !fRun) return;
    fRun->Fill();
  }
  
  void
  FileWriter::StoreEvent()
  {
    if (!fFile or !fEvent) return;
    fEvent->Fill();
  }
}

