#include "QuartLEvent.h"

ClassImp(PPS::QuartLEvent)

namespace PPS
{
  QuartLEvent::QuartLEvent() :
    fName("")
  {}

  QuartLEvent::QuartLEvent(TString name) :
    fName(name)
  {}

  QuartLEvent::~QuartLEvent()
  {}

  void
  QuartLEvent::AddPhoton(QuartLPhotonHit hit)
  {
    fHitsCollection.push_back(hit);
  }

  void
  QuartLEvent::Clear(Option_t*)
  {
    fHitsCollection.clear();
  }  
}

