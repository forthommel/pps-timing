#include "RunInformation.h"

ClassImp(PPS::RunInformation)

namespace PPS
{
  RunInformation::RunInformation() :
    TTree("runs", "Information on the run"), fIPCollection(0)
  {
    fIPCollection = new IncomingParticlesRef;
    Clear("");

    Branch("fIPCollection", fIPCollection);
  }

  RunInformation::~RunInformation()
  {
    delete fIPCollection;
  }
}

