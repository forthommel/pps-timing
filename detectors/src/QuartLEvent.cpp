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
    int cellId = hit.GetCellID();
    int rowId = cellId%4;
    int colId = (cellId-rowId)/4;
    fHitMap->Fill(colId, rowId);
    //fEnergyMap[fStationId[fNumHits]]->Fill(colId, rowId, fE[fNumHits]);
  }

  void
  QuartLEvent::Clear(Option_t*)
  {
    fHitsCollection.clear();
    fHitMap->Reset();
  }  
}

