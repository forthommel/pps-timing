#include "FileWriter.hh"

FileWriter::FileWriter(G4String filename) :
  fFile(0), fTree(0), fFilename(filename),
  fNumHits(0), fNumEvents(0), fRunId(0)
{
  /*G4int threadId = G4Threading::G4GetThreadId();
  fFilename.ReplaceAll(".root", Form("%.4i.root", threadId));*/

  fFile = new TFile(fFilename, "RECREATE");
  fFile->mkdir("plots");
  fFile->cd();
  
  /*fQuartLInfo = new PPS::QuartLInformation;
  fQuartLInfo->SetRunId(fRunId);*/

  fTree = new TTree("events", "PPS simulation events");
  //fTree->Branch("run_info", "QuartLInformation", fQuartLInfo, 64000, 1);
  /*fTree->Branch("hits", &fNumHits, "hits/I");
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
  fTree->Branch("cell_id", fCellId, "cell_id[hits]/I");*/

  fFile->cd("plots");
  for (G4int i=0; i<MAX_MODULES; i++) {
    fHitMap[i] = new TH2D(Form("hitmap_%i", i), Form("Photon hits per event (Quartic #%i)", i ), 5, 0., 5., 4, 0., 4.);
  }
  for (G4int i=0; i<MAX_MODULES; i++) {
    fEnergyMap[i] = new TH2D(Form("energymap_%i", i), Form("Energy collection per event (Quartic #%i)", i), 5, 0., 5., 4, 0., 4.);
  }

  G4cout << __PRETTY_FUNCTION__ << " New file with name ' " << fFilename << " ' created and ready to be populated !" << G4endl;
}

FileWriter::~FileWriter()
{
  //Store();
  fFile->Write();
  fFile->Close();
  
  G4cout << __PRETTY_FUNCTION__ << " File ' " << fFilename << " ' successfully created and filled with " << fNumEvents << " events !" << G4endl;
  /* FIXME
  // Y U no destructors, ROOT ? ლ(ಠ_ಠლ) 
  for (G4int i=0; i<MAX_MODULES; i++) {
    delete fHitMap[i];
  }
  delete fTree;
  delete fFile;
  */
  
  //delete fQuartLInfo;
}

void
FileWriter::AddHitInEvent(G4Step* step)
{
  /*if (fNumHits>MAX_HITS) return;
  
  G4Track *track = step->GetTrack();
  G4ThreeVector momentum = track->GetMomentum();
  G4ThreeVector vertex = track->GetVertexPosition();

  fVx[fNumHits] = vertex.x()/CLHEP::m;
  fVy[fNumHits] = vertex.y()/CLHEP::m;
  fVz[fNumHits] = vertex.z()/CLHEP::m;
  fProductionTime[fNumHits] = step->GetPreStepPoint()->GetGlobalTime()/CLHEP::second;
  fTrackLength[fNumHits] = track->GetTrackLength()/CLHEP::m;

  fPx[fNumHits] = momentum.x()/CLHEP::GeV;
  fPy[fNumHits] = momentum.y()/CLHEP::GeV;
  fPz[fNumHits] = momentum.z()/CLHEP::GeV;
  fE[fNumHits] = track->GetTotalEnergy()/CLHEP::GeV;

  G4int globalId = step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo();

  if (globalId<0) return; // FIXME one needs to see what happens to such events

  fCellId[fNumHits] = globalId%20;
  fStationId[fNumHits] = (globalId-fCellId[fNumHits])/20;

  if (fStationId[fNumHits]<MAX_MODULES) {
    //
    // Cells mapping (downstream from the beam) :
    // -------------------------
    // |  3  |  7  | 11  | 15  | 
    // -------------------------
    // |  2  |  6  | 10  | 14  | 
    // -------------------------
    // |  1  |  5  |  9  | 13  | 
    // -------------------------
    // |  0  |  4  |  8  | 12  | 
    // -------------------------
    //
    G4int rowId = fCellId[fNumHits]%4;
    G4int colId = (fCellId[fNumHits]-rowId)/4;
    //
    fHitMap[fStationId[fNumHits]]->Fill(colId, rowId);
    fEnergyMap[fStationId[fNumHits]]->Fill(colId, rowId, fE[fNumHits]);
  }
  */
  fNumHits += 1;
}

void
FileWriter::Store()
{
  if (!fFile or !fTree) return;
  fNumEvents += 1;
  fTree->Fill();
  // We want to normalize all histograms by the number of events generated
  /*for (G4int i=0; i<MAX_MODULES; i++) {
    fHitMap[i]->Scale(1./fNumEvents);
    fEnergyMap[i]->Scale(1./fNumEvents);
  }*/
   
  //fRunId += 1;
  //fQuartLInfo->SetRunId(fRunId);
}

