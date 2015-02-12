#ifndef SteppingVerbose_h
#define SteppingVerbose_h

#include "G4SteppingVerbose.hh"
#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"

class SteppingVerbose : public G4SteppingVerbose
{
 public:   

   SteppingVerbose();
   ~SteppingVerbose();

   void StepInfo();
   void TrackingStarted();

};

#endif
