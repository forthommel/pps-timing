#include "EventInformation.h"

ClassImp(PPS::EventInformation)

namespace PPS
{
  EventInformation::EventInformation() :
    TTree("events", "Information on the event")
  {
    fDetCollection = new DetectorRefCollection;
    Clear("");
  }

  EventInformation::~EventInformation()
  {
    delete fDetCollection;
  }
}

