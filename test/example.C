gSystem->Load("sw/libPPS.so");
gSystem->Load("detectors/libDetectors.so");

void
example(TString filename)
{
  TFile *file;
  TTree *tree;
  PPS::QuartLEvent *ev1, *ev2;
  TH2D *hitmap;
  PPS::Canvas *c;

  file = new TFile(filename, "READ");
  if (!file->IsOpen()) return;
  tree = (TTree*)(file->Get("events"));
  tree->SetBranchAddress("quartic1__PPS::QuartLEvent", &ev1);
  tree->SetBranchAddress("quartic2__PPS::QuartLEvent", &ev2);

  hitmap = new TH2D("hitmap", "", 260, 0., 13., 200, -2.5, 2.5);

  for (int i=0; i<tree->GetEntries(); i++) {
    tree->GetEntry(i);
    if (i%50==0) {
      cout << "-> Loading entry " << i << " / " << tree->GetEntries()
	   << " --> " << ev1->GetNumberOfPhotons() << " / " << ev2->GetNumberOfPhotons() << " photon hits in this event"
	   << endl;
    }
    // Loop over all hits observed in first QUARTIC
    for (int j=0; j<ev1->GetNumberOfPhotons(); j++) {
      PPS::QuartLPhotonHit hit = ev1->GetHit(j);
      hitmap->Fill(hit.Position().Z()*100., hit.Position().Y()*100.); // we want it in cm...
    }
    // Loop over all hits observed in second QUARTIC
    for (int j=0; j<ev2->GetNumberOfPhotons(); j++) {
      PPS::QuartLPhotonHit hit = ev2->GetHit(j);
      hitmap->Fill(hit.Position().Z()*100., hit.Position().Y()*100.); // we want it in cm...
    }
  }
  hitmap->Scale(1./tree->GetEntries());

  c = new PPS::Canvas("hits", "Photon hits (yields per proton)");
  hitmap->Draw("colz");
  hitmap->GetXaxis()->SetTitle("Z [cm]");
  hitmap->GetYaxis()->SetTitle("Y [cm]");
  c->Save("hits");
}
