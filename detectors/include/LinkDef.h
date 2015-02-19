#include "PPSReader.h"
#include "QuartLInformation.h"
#include "QuartLEvent.h"
#include "QuartLPhotonHit.h"

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace PPS;
#pragma link C++ class PPS::QuartLInformation+;
#pragma link C++ class PPS::QuartLEvent+;
#pragma link C++ class PPS::QuartLPhotonHit+;
#pragma link C++ class PPS::PPSReader+;
#pragma link C++ function PPS::PPSReader::SetDetectorEventsAddress(TString,PPS::QuartLEvent*)+;

#endif
