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
  PPS::FileReader* r;
  PPS::Canvas *c_hm, *c_ct, *c_lambda;
  Quartic::QuartLEvent *ev1, *ev2;
  Quartic::QuartLPhotonHit* hit;
  TH2D *hitmap;
  TH1D *lambda;

  r = new PPS::FileReader(filename);
  if (!r->IsOpen()) return;

  const PPS::RunInformation* ri = r->GetRunInformation();
  cout << "=> Run: " << ri->GetNumberOfIncomingParticles() << " incoming particles"
       << " with a mean energy of " << ri->GetMeanIncomingParticlesEnergy() << " GeV"
       << endl;
			     
  r->SetDetectorEventsAddress("quartic1", &ev1);
  r->SetDetectorEventsAddress("quartic2", &ev2);
  const numEvents = r->NumEvents();

  hitmap = new TH2D("hitmap", "", 280, 0., 14., 200, -2.5, 2.5);
  corr_timing = new TH2D("corr_timing", "", 200, 0., 10., 380, 0., 16.);
  lambda = new TH1D("lambda", "", 100, 20., 120.);

  for (int i=0; i<numEvents; i++) {
    r->GetEvent(i);
    // Loop over all hits observed in first QUARTIC
    for (int j=0; j<ev1->GetNumberOfPhotons(); j++) {
      hit = ev1->GetHit(j);
      hitmap->Fill(hit->GetPosition()->Z()*100., hit->GetPosition()->Y()*100.); // we want it in cm...
      corr_timing->Fill(hit->GetPosition()->T()*1.e9, hit->GetPosition()->Z()*100.);
      lambda->Fill(TMath::H()*TMath::C()/(hit->GetMomentum()->E()*1.e-9)*1.e9); // we want it in nm... (and energy is in GeV)
    }
    // Loop over all hits observed in second QUARTIC
    for (int j=0; j<ev2->GetNumberOfPhotons(); j++) {
      hit = ev2->GetHit(j);
      hitmap->Fill(hit->GetPosition()->Z()*100., hit->GetPosition()->Y()*100.); // we want it in cm...
      corr_timing->Fill(hit->GetPosition()->T()*1.e9, hit->GetPosition()->Z()*100.);
    }
  }
  hitmap->Scale(1./numEvents);
  corr_timing->Scale(1./numEvents);
  lambda->Scale(1./numEvents);

  c_hm = new PPS::Canvas("hits", "Photon hits (yields per proton)");
  hitmap->Draw("colz");
  hitmap->GetXaxis()->SetTitle("Z [cm]");
  hitmap->GetYaxis()->SetTitle("Y [cm]");
  c_hm->Save();

  c_ct = new PPS::Canvas("corr_timing", "T-Z correlation (yields per proton)");
  corr_timing->Draw("colz");
  corr_timing->GetXaxis()->SetTitle("Time of arrival [ns]");
  corr_timing->GetYaxis()->SetTitle("Z [cm]");
  c_ct->Pad()->SetLogz();
  c_ct->Save();

  c_lambda = new PPS::Canvas("photon_lambda", "First QUARTIC station, per proton");
  lambda->Draw();
  lambda->GetXaxis()->SetTitle("#lambda(#gamma) (nm)");
  lambda->GetYaxis()->SetTitle("dN/d#lambda(#gamma) (/nm)");
  c_lambda->Save();
}
