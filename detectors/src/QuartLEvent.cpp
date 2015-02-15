#include "QuartLEvent.h"

ClassImp(PPS::QuartLEvent)

PPS::QuartLEvent::QuartLEvent() :
  fName("")
{}

PPS::QuartLEvent::QuartLEvent(TString name) :
  fName(name)
{}

PPS::QuartLEvent::~QuartLEvent()
{}

void
PPS::QuartLEvent::AddPhoton(TLorentzVector pos, TLorentzVector mom)
{
  QuartLPhotonHit hit;
  hit.SetPosition(pos);
  hit.SetMomentum(mom);
  fHitsCollection.push_back(hit);
}

void
PPS::QuartLEvent::Clear(Option_t*)
{
  fHitsCollection.clear();
}

