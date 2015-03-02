gSystem->Load("sw/libPPS.so");
gSystem->Load("detectors/libDetectors.so");

/**
 * Example CINT macro to read QUARTIC events
 * \author Laurent Forthomme <laurent.forthomme@cern.ch>
 * \date 17 Feb 2015
 */
void
example(TString filename)
{
  TFile *file;
  TTree *tree;
  Quartic::QuartLEvent *ev1, *ev2;
  TH2D *hitmap;
  TH1D *lambda;
  PPS::Canvas *c_hm, *c_lambda;

  file = new TFile(filename, "READ");
  if (!file->IsOpen()) return;
  tree = (TTree*)(file->Get("events"));
  tree->SetBranchAddress("quartic1__Quartic::QuartLEvent", &ev1);
  tree->SetBranchAddress("quartic2__Quartic::QuartLEvent", &ev2);

  hitmap = new TH2D("hitmap", "", 280, 0., 14., 200, -2.5, 2.5);
  lambda = new TH1D("lambda", "", 100, 20., 120.);

  for (int i=0; i<tree->GetEntries(); i++) {
    tree->GetEntry(i);
    if (i%50==0) {
      cout << "-> Loading entry " << i << " / " << tree->GetEntries()
	   << " --> " << ev1->GetNumberOfPhotons() << " / " << ev2->GetNumberOfPhotons() << " photon hits in this event"
	   << endl;
    }
    // Loop over all hits observed in first QUARTIC
    for (int j=0; j<ev1->GetNumberOfPhotons(); j++) {
      Quartic::QuartLPhotonHit hit = ev1->GetHit(j);
      hitmap->Fill(hit.GetPosition().Z()*100., hit.GetPosition().Y()*100.); // we want it in cm...
      lambda->Fill(TMath::H()*TMath::C()/(hit.GetMomentum().E()*1.e-9)*1.e9); // we want it in nm... (and energy is in GeV)
    }
    // Loop over all hits observed in second QUARTIC
    for (int j=0; j<ev2->GetNumberOfPhotons(); j++) {
      Quartic::QuartLPhotonHit hit = ev2->GetHit(j);
      hitmap->Fill(hit.Position().Z()*100., hit.Position().Y()*100.); // we want it in cm...
    }
  }
  hitmap->Scale(1./tree->GetEntries());

  c_hm = new PPS::Canvas("hits", "Photon hits (yields per proton)");
  hitmap->Draw("colz");
  hitmap->GetXaxis()->SetTitle("Z [cm]");
  hitmap->GetYaxis()->SetTitle("Y [cm]");
  c_hm->Save();

  c_lambda = new PPS::Canvas("photon_lambda", "First QUARTIC station, per proton");
  lambda->Draw();
  lambda->GetXaxis()->SetTitle("#lambda(#gamma) (nm)");
  lambda->GetYaxis()->SetTitle("dN/d#lambda(#gamma) (/nm)");
  c_lambda->Save();
}
