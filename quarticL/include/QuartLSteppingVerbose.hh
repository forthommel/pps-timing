#ifndef QuartLSteppingVerbose_h
#define QuartLSteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"

class QuartSteppingVerbose;

class QuartLSteppingVerbose : public G4SteppingVerbose
{
 public:   

   QuartLSteppingVerbose();
  ~QuartLSteppingVerbose();

   void StepInfo();
   void TrackingStarted();

};

#endif
