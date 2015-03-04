#ifndef SensitiveDetector_h
#define SensitiveDetector_h

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4VSensitiveDetector.hh"
#include "globals.hh"

#include "FileWriter.hh"
#include "RunAction.hh"
#include "TrackInformation.hh"

namespace PPS
{
  /**
   * General handler class for an active detector readout.
   * \date 4 Mar 2015
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   */
  template<class T>
  class SensitiveDetector : public G4VSensitiveDetector 
  {
    public:
      SensitiveDetector(G4String name) :
        G4VSensitiveDetector(name), fRunAction(0), fOutput(0), fEvent(0)
      {}
      
      virtual ~SensitiveDetector() {
        delete fEvent;
      }
  
      virtual void RegisterEvent()
      {
        G4cout << __PRETTY_FUNCTION__ << " new sensitive detector with name \"" << GetName() << "\" added to the output stream !" << G4endl;
        if (!fRunAction) fRunAction = (RunAction*)G4RunManager::GetRunManager()->GetUserRunAction();
        fEvent = new T(GetName());
        fOutput = static_cast<FileWriter*>(fRunAction->GetFileWriter());
        fOutput->RegisterSD(fEvent);
      }

      virtual void Initialize(G4HCofThisEvent*) {
        fEvent->Clear();
      }
      virtual inline G4bool ProcessHits(G4Step*, G4TouchableHistory*) { return false; }
      virtual inline void EndOfEvent(G4HCofThisEvent*)
      {
        fOutput->AddSDData<T>(GetName(), fEvent);
      }
    
    protected:
      RunAction* fRunAction;
      FileWriter* fOutput;

      T* fEvent;

      time_t fEventTime;
  };
}

#endif
