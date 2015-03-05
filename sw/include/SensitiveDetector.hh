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
   * General handler class for an active detector readout. This enables to simplify
   * sub-detectors' simulation work while providing the required information and letting
   * the developper fill the remaining quantities.
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
      
      inline virtual ~SensitiveDetector() {
        delete fEvent;
      }

      /**
       * Placeholder method to register the event content(s) into the output stream. 
       */
      virtual void RegisterEvent()
      {
        G4cout << __PRETTY_FUNCTION__ << " new sensitive detector with name \"" << GetName() << "\" added to the output stream !" << G4endl;
        if (!fRunAction) fRunAction = (RunAction*)G4RunManager::GetRunManager()->GetUserRunAction();
        fEvent = new T(GetName());
        fOutput = static_cast<FileWriter*>(fRunAction->GetFileWriter());
        fOutput->RegisterSD(fEvent);
      }

      /**
       * Method called at the beginning of every new event. This can be used to reset
       * the content of the event object to work with.
       */
      virtual void Initialize(G4HCofThisEvent*) {
        fEvent->Clear();
      }
      virtual inline G4bool ProcessHits(G4Step*, G4TouchableHistory*) { return false; }
      /**
       * Method called at the end of each event. This can be used to store the event
       * into the output stream.
       */
      virtual inline void EndOfEvent(G4HCofThisEvent*)
      {
        fOutput->AddSDData<T>(GetName(), fEvent);
      }
    
    protected:
      /// User-defined run object
      RunAction* fRunAction;
      /// Output stream handler
      FileWriter* fOutput;
      /// Templated event object
      T* fEvent;
      /// Event generation time
      time_t fEventTime;
  };
}

#endif
