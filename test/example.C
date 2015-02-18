gSystem->Load("sw/libPPS.so");
gSystem->Load("detectors/libDetectors.so");

void
example()
{
  TString filename = "events.root";

  PPS::QuartLEvent ev1, ev2;
  PPS::Canvas *c;
  PPS::PPSReader* reader;
  TH2D *hitmap;

  reader = new PPS::PPSReader(filename);
  if (!reader->IsOpen()) return;
  cout << "=> " << reader->NumEvents() << " events to be processed" << endl;

  //cout << reader->SetDetectorEventsAddress("quartic1", &ev1) << endl;
  cout << reader->SetDetectorEventsAddress<PPS::QuartLEvent>("quartic1", &ev1) << endl;

  hitmap = new TH2D("hitmap", "", 260, 0., 13., 200, -2.5, 2.5);
  
  for (int i=0; i<reader->NumEvents(); i++) {
    reader->GetEvent(i);
    //if (i%50==0) {
      cout << "-> Loading entry " << i << " / " << reader->NumEvents() 
           << " --> " << ev1.GetNumberOfPhotons() << " / " << ev2.GetNumberOfPhotons() << " photon hits in this event"
           << endl;
    //}
    // Loop over all hits observed in first QUARTIC
    for (int j=0; j<ev1.GetNumberOfPhotons(); j++) {
      PPS::QuartLPhotonHit hit = ev1.GetHit(j);
      hitmap->Fill(hit.Position().Z()*100., hit.Position().Y()*100.); // we want it in cm...
    }
    // Loop over all hits observed in second QUARTIC
    for (int j=0; j<ev2.GetNumberOfPhotons(); j++) {
      PPS::QuartLPhotonHit hit = ev2.GetHit(j);
      hitmap->Fill(hit.Position().Z()*100., hit.Position().Y()*100.); // we want it in cm...
    }
  }
  hitmap->Scale(1./reader->NumEvents());

  c = new PPS::Canvas("hits", "Photon hits (yields per proton)");
  hitmap->Draw("colz");
  hitmap->GetXaxis()->SetTitle("Z [cm]");
  hitmap->GetYaxis()->SetTitle("Y [cm]");
  c->Save("hits");
}
