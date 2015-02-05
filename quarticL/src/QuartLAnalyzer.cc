#include "QuartLAnalyzer.hh"

QuartLAnalyzer::QuartLAnalyzer(G4String filename) :
  fFile(0), fTree(0), fFilename(filename), fNumHits(0)
{
  fFile = new TFile(fFilename, "RECREATE");
  
  fTree = new TTree("events", "Quartic simulation events");
  fTree->Branch("hits", &fNumHits, "hits/I");
  fTree->Branch("vx", fVx, "vx[hits]/D");
  fTree->Branch("vy", fVy, "vy[hits]/D");
  fTree->Branch("vz", fVz, "vz[hits]/D");
  fTree->Branch("production_time", fProductionTime, "production_time[hits]/D");
  fTree->Branch("px", fPx, "px[hits]/D");
  fTree->Branch("py", fPy, "py[hits]/D");
  fTree->Branch("pz", fPz, "pz[hits]/D");
  fTree->Branch("E", fE, "E[hits]/D");
  fTree->Branch("station_id", fStationId, "station_id[hits]/I");
  fTree->Branch("cell_id", fCellId, "cell_id[hits]/I");
  
  for (G4int i=0; i<MAX_MODULES; i++) {
    std::ostringstream ss1; ss1 << "hit_map_" << i;
    std::ostringstream ss2; ss2 << "Photon hits map (Quartic #" << i << ")";
    fHitMap[i] = new TH2D(ss1.str().c_str(), ss2.str().c_str(), 5, 0., 5., 4, 0., 4.);
  }
}

QuartLAnalyzer::~QuartLAnalyzer()
{
  if (fFile) {
    fFile->Write();
    fFile->Close();
  }
  
  delete fFile;
  delete fTree;
  for (G4int i=0; i<MAX_MODULES; i++) {
    delete fHitMap[i];
  }
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
  fProductionTime[fNumHits] = step->GetPreStepPoint()->GetGlobalTime();

  fPx[fNumHits] = momentum.x();
  fPy[fNumHits] = momentum.y();
  fPz[fNumHits] = momentum.z();
  fE[fNumHits] = track->GetTotalEnergy();
  
  G4int globalId = step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo();
  fCellId[fNumHits] = globalId%20;
  fStationId[fNumHits] = (globalId-fCellId[fNumHits])/20;
  
  fNumHits += 1;
    
  if (fStationId[fNumHits]<MAX_MODULES) {
    G4int rowId = fCellId[fNumHits]%4;
    G4int colId = (fCellId[fNumHits]-rowId)/4;
    
    //G4cout << "--> " << fCellId[fNumHits] << " <-> (" << rowId << ", " << colId << ")" << G4endl;
    fHitMap[fStationId[fNumHits]]->Fill(colId-.5, rowId-.5);
  }
  
}

void
QuartLAnalyzer::Store()
{
  fTree->Fill();
  
  // Reset the hits number counter after each event
  fNumHits = 0;
}
