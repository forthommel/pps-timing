#include "QuartLEvent.h"

ClassImp(PPS::QuartLEvent)

namespace PPS
{
  QuartLEvent::QuartLEvent() :
    fName(""), fHitMap(0)
  {}

  QuartLEvent::QuartLEvent(TString name) :
    fName(name), fHitMap(0)
  {
    fHitMap = new TH2D(Form("hitmap_%s", fName.Data()), Form("Photon hits per event (Quartic \"%s\")", fName.Data()), 5, 0., 5., 4, 0., 4.);
    //fEnergyMap = new TH2D(Form("energymap_%s", fName.Data()), Form("Energy collection per event (Quartic \"%s\")", fName.Data()), 5, 0., 5., 4, 0., 4.);
  }

  QuartLEvent::~QuartLEvent()
  {
    if (fHitMap) delete fHitMap;
  }

  void
  QuartLEvent::AddPhoton(QuartLPhotonHit hit)
  {
    fHitsCollection.push_back(hit);
    fHitMap->Fill(hit.GetCellColumnID(), hit.GetCellRowID());
    //fEnergyMap[fStationId[fNumHits]]->Fill(hit.GetCellColumnID(), hit.GetCellRowID(), hit.Momentum().E());
  }

  void
  QuartLEvent::Clear(Option_t*)
  {
    fHitsCollection.clear();
    fHitMap->Reset();
  }  
}

