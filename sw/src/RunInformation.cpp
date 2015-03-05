#include "RunInformation.h"

ClassImp(PPS::RunInformation)

namespace PPS
{
  RunInformation::RunInformation()
  {
    fIPCollection = new IncomingParticlesRef;
  }

  RunInformation::~RunInformation()
  {
    delete fIPCollection;
  }

  void
  RunInformation::Clear(Option_t*)
  {
    if (!fIPCollection) return;
    fIPCollection->clear();
  }
}

