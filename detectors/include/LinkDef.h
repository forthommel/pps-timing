#include "PPSReader.h"
#include "QuartLInformation.h"
#include "QuartLEvent.h"
#include "QuartLPhotonHit.h"

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace Quartic;
#pragma link C++ class Quartic::QuartLInformation+;
#pragma link C++ class Quartic::QuartLEvent+;
#pragma link C++ class Quartic::QuartLPhotonHit+;
#pragma link C++ class Quartic::HitsCollection+;

#pragma link C++ namespace PPS;
#pragma link C++ class PPS::PPSReader+;
#pragma link C++ function PPS::PPSReader::SetDetectorEventsAddress(TString,Quartic::QuartLEvent*)+;

#endif
