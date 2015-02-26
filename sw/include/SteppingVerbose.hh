#ifndef SteppingVerbose_h
#define SteppingVerbose_h

#include "G4SteppingVerbose.hh"
#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"

namespace PPS
{
  /**
   * Object controlling the tracking operation verbosity
   *
   * \date Feb 2015
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \author Vladimir Samoilenko <vladimir.samoilenko@cern.ch>
   */
  class SteppingVerbose : public G4SteppingVerbose
  {
    public:   

     SteppingVerbose();
     ~SteppingVerbose();

     void StepInfo();
     void TrackingStarted();
  };
}

#endif
