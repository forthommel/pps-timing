#include "RunInformation.h"

ClassImp(PPS::RunInformation)

namespace PPS
{
  RunInformation::RunInformation() :
    TTree("run", "Information on the run"), fIPCollection(0)
  {
    fIPCollection = new std::vector<IncomingParticle*>; //FIXME switch to a std::vector ?
    Clear("");

    Branch("fIPCollection", fIPCollection);
  }

  RunInformation::~RunInformation()
  {
    delete fIPCollection;
  }
}

