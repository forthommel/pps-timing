#include "QuartLAnalyzer.hh"

QuartLAnalyzer::QuartLAnalyzer(G4String filename) :
  fFile(0), fTree(0), fFilename(filename), fNumHits(0)
{
  G4int threadId = G4Threading::G4GetThreadId();
  fFilename.ReplaceAll(".root", Form("%.4i.root", threadId));
  
  fFile = new TFile(fFilename, "RECREATE");
  
  fTree = new TTree("events", "Quartic simulation events");
  fTree->Branch("hits", &fNumHits, "hits/I");
  fTree->Branch("vx", fVx, "vx[hits]/D");
  fTree->Branch("vy", fVy, "vy[hits]/D");
  fTree->Branch("vz", fVz, "vz[hits]/D");
  fTree->Branch("production_time", fProductionTime, "production_time[hits]/D");
  fTree->Branch("track_length", fTrackLength, "track_length[hits]/D");
  fTree->Branch("px", fPx, "px[hits]/D");
  fTree->Branch("py", fPy, "py[hits]/D");
  fTree->Branch("pz", fPz, "pz[hits]/D");
  fTree->Branch("E", fE, "E[hits]/D");
  fTree->Branch("station_id", fStationId, "station_id[hits]/I");
  fTree->Branch("cell_id", fCellId, "cell_id[hits]/I");
  
  for (G4int i=0; i<MAX_MODULES; i++) {
    fHitMap[i] = new TH2D(Form("hitmap_%i", i), Form("Photon hits map (Quartic #%i)", i ), 5, 0., 5., 4, 0., 4.);
  }
  
  G4cout << "[ROOT] New file with name ' " << fFilename << " ' created and ready to be populated !" << G4endl;
}

QuartLAnalyzer::~QuartLAnalyzer()
{
  Store();
  for (G4int i=0; i<MAX_MODULES; i++) {
    //delete fHitMap[i];
  }
  //delete fTree;
  //delete fFile;
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
  fTrackLength[fNumHits] = track->GetTrackLength();

  fPx[fNumHits] = momentum.x();
  fPy[fNumHits] = momentum.y();
  fPz[fNumHits] = momentum.z();
  fE[fNumHits] = track->GetTotalEnergy();
  
  G4int globalId = step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo();
  
  if (globalId<0) return; // FIXME one needs to see what happens to such events
  
  fCellId[fNumHits] = globalId%20;
  fStationId[fNumHits] = (globalId-fCellId[fNumHits])/20;
  
  //G4cout << "globalId = " << globalId << " -> station/cell = " << fStationId[fNumHits] << " / " << fCellId[fNumHits] << G4endl;
    
  if (fStationId[fNumHits]<MAX_MODULES) {
    G4int rowId = fCellId[fNumHits]%4;
    G4int colId = (fCellId[fNumHits]-rowId)/4;
    
    //G4cout << "--> " << fCellId[fNumHits] << " <-> (" << rowId << ", " << colId << ")" << G4endl;
    fHitMap[fStationId[fNumHits]]->Fill(colId, rowId);
  }
  fNumHits += 1;
}

void
QuartLAnalyzer::FillTree()
{
  fTree->Fill();
  
  // Reset the hits number counter after each event
  fNumHits = 0;
  for (G4int i=0; i<MAX_HITS; i++) {
    fVx[i] = fVy[i] = fVz[i] = -999.;
    fProductionTime[i] = fTrackLength[i] = -999.;
    fPx[i] = fPy[i] = fPz[i] = fE[i] = -999.;
    fCellId[i] = fStationId[i] = -1;
  }
}

void
QuartLAnalyzer::Store()
{
  if (fFile) {
    fFile->Write();
    fFile->Close();
    G4cout << "[ROOT] File ' " << fFilename << " ' successfully created and filled !" << G4endl;
  }
}
