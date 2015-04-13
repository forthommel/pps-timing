#include "EnvironmentalEvent.h"

ClassImp(EnvironmentalEvent)

EnvironmentalEvent::EnvironmentalEvent(TString name) :
  fName(name)
{
  //fHist = new TH3D("hits_map", "", 100, -10., 10., 100, -10., 10., 100, -10., 10.);
  fHits = new std::vector<EnvironmentalHit>;
}

EnvironmentalEvent::~EnvironmentalEvent()
{
  //delete fHist;
  delete fHits;
}

void
EnvironmentalEvent::Clear(Option_t*)
{
  //std::cout << "cleared a " << GetNumberOfSecondaries() << " hits collection!" << std::endl;
  fHits->clear();
}

void
EnvironmentalEvent::AddSecondaryHit(EnvironmentalHit hit)
{
  //hit.Dump();
  fHits->push_back(hit);
  //fHist->Fill(hit.GetPosition().X(), hit.GetPosition().Y(), hit.GetPosition().Z());
}

ClassImp(EnvironmentalHit)

void
EnvironmentalHit::Dump() const
{
  std::cout << "========================================" << std::endl
            << " \"Environmental\" hit" << std::endl
            << " PDG id:    " << fPDGId << std::endl
            << " Position: (" << fPosition.X() << ", " << fPosition.Y() << ", " << fPosition.Z() << ", " << fPosition.T() << ")" << std::endl
            << " Momentum: (" << fMomentum.Px() << ", " << fMomentum.Py() << ", " << fMomentum.Pz() << ", " << fMomentum.E() << ")" << std::endl
            << "========================================" << std::endl;
}
