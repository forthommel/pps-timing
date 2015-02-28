#include "RunInformation.h"

namespace PPS
{
  RunInformation::RunInformation()
  {
    fIPCollection = new TList;
  }

  RunInformation::~RunInformation()
  {
    delete fIPCollection;
  }

  void
  RunInformation::Clear(Option_t* opt)
  {
    if (!fIPCollection) return;
    fIPCollection->Clear(opt);
  }
}

