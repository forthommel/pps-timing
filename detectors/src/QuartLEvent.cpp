#include "QuartLEvent.h"

ClassImp(Quartic::QuartLEvent)

namespace Quartic
{
  QuartLEvent::QuartLEvent() :
    fName(""), fHitsCollection(0), fHitMap(0), fEnergyMap(0)
  {}

  QuartLEvent::QuartLEvent(TString name) :
    fName(name), fHitsCollection(0), fHitMap(0), fEnergyMap(0)
  {
    fHitsCollection = new HitsCollection;
    fHitMap = new TH2D(Form("hitmap_%s", fName.Data()), Form("Photon hits per eveni (Quartic \"%s\")", fName.Data()), 5, 0., 5., 4, 0., 4.);
    fEnergyMap = new TH2D(Form("energymap_%s", fName.Data()), Form("Energy collection per event (Quartic \"%s\")", fName.Data()), 5, 0., 5., 4, 0., 4.);
  }

  QuartLEvent::~QuartLEvent()
  {
    if (fHitsCollection) delete fHitsCollection;
    /*if (fHitMap) delete fHitMap;
    if (fEnergyMap) delete fEnergyMap;*/
  }

  void
  QuartLEvent::AddPhoton(QuartLPhotonHit* hit)
  {
    if (fHitsCollection) fHitsCollection->push_back(hit);
    if (fHitMap) fHitMap->Fill(hit->GetCellColumnID(), hit->GetCellRowID());
    if (fEnergyMap) fEnergyMap->Fill(hit->GetCellColumnID(), hit->GetCellRowID(), hit->GetMomentum().E());
  }

  void
  QuartLEvent::Clear(Option_t*)
  {
    if (fHitsCollection) fHitsCollection->clear();
    if (fHitMap) fHitMap->Reset();
    if (fEnergyMap) fEnergyMap->Reset();
  }  
}

