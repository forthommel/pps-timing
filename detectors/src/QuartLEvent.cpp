#include "QuartLEvent.h"

ClassImp(Quartic::QuartLEvent)

namespace Quartic
{
  QuartLEvent::QuartLEvent() :
    fName(""), fHitsCollection(0)
  {}

  QuartLEvent::QuartLEvent(TString name) :
    fName(name), fHitsCollection(0)
  {
    fHitsCollection = new HitsCollection;
  }

  QuartLEvent::~QuartLEvent()
  {
    if (fHitsCollection) delete fHitsCollection;
  }

  void
  QuartLEvent::AddPhoton(QuartLPhotonHit* hit)
  {
    if (fHitsCollection) fHitsCollection->push_back(hit);
  }

  void
  QuartLEvent::Clear(Option_t*)
  {
    if (fHitsCollection) fHitsCollection->clear();
  }  
}

