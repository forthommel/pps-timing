#include "FileReader.h"

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#include "QuartLInformation.h"
#include "QuartLEvent.h"
#include "QuartLPhotonHit.h"

#pragma link C++ namespace Quartic;
#pragma link C++ class Quartic::QuartLInformation+;
#pragma link C++ class Quartic::QuartLEvent+;
#pragma link C++ class Quartic::QuartLPhotonHit+;
#pragma link C++ class Quartic::HitsCollection+;

#pragma link C++ function PPS::FileReader::SetDetectorEventsAddress(TString,Quartic::QuartLEvent*)+;

#if false
#include "TrackingMaterialEvent.h"

#pragma link C++ class TrackingMaterialEvent+;
#pragma link C++ function PPS::FileReader::SetDetectorEventsAddress(TString,TrackingMaterialEvent*)+;
#fi

#endif
