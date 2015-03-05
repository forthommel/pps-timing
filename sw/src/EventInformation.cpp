#include "EventInformation.h"

ClassImp(PPS::EventInformation)

namespace PPS
{
  EventInformation::EventInformation() :
    TTree("events", "Information on the event")
  {
    fDetCollection = new DetectorsRef;
    Clear("");
  }

  EventInformation::~EventInformation()
  {
    delete fDetCollection;
  }
}

