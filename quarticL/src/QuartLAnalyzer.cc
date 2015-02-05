#include "QuartLAnalyzer.hh"

QuartLAnalyzer::QuartLAnalyzer(G4String filename) :
  fFilename(filename), fTree(0), fNumHits(0)
{
  fTree = new TTree("events", "Quartic simulation events");
  fTree->Branch("hits", &fNumHits, "hits/I");
  fTree->Branch("vx", fVx, "vx[hits]/D");
  fTree->Branch("vy", fVy, "vy[hits]/D");
  fTree->Branch("vz", fVz, "vz[hits]/D");
  fTree->Branch("px", fPx, "px[hits]/D");
  fTree->Branch("py", fPy, "py[hits]/D");
  fTree->Branch("pz", fPz, "pz[hits]/D");
  fTree->Branch("E", fE, "E[hits]/D");
  fTree->Branch("cell_id", fCellId, "cell_id[hits]/I");
}

QuartLAnalyzer::~QuartLAnalyzer()
{
  fTree->SaveAs(fFilename);
  delete fTree;
}

void
QuartLAnalyzer::AddHitInEvent(G4Step* step)
{
  G4Track *track = step->GetTrack();
  G4ThreeVector momentum = track->GetMomentum();
  G4ThreeVector vertex = track->GetVertexPosition();
  
  fVx[fNumHits] = vertex.x();
  fVy[fNumHits] = vertex.y();
  fVz[fNumHits] = vertex.z();

  fPx[fNumHits] = momentum.x();
  fPy[fNumHits] = momentum.y();
  fPz[fNumHits] = momentum.z();
  fE[fNumHits] = track->GetTotalEnergy();
  
  fCellId[fNumHits] = step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo();
  
  fNumHits += 1;
}

void
QuartLAnalyzer::Store()
{
  fTree->Fill();
  
  // Reset the hits number counter after each event
  fNumHits = 0;
}
