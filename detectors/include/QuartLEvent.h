#ifndef QuartLEvent_h
#define QuartLEvent_h

#include <vector>

#include "QuartLPhotonHit.h"

#include "TObject.h"
#include "TLorentzVector.h"
#include "TH2.h"

namespace Quartic
{
  typedef std::vector<QuartLPhotonHit*> HitsCollection;  
  /**
   * Class containing all kinematic information on the photon tracks in each QUARTIC event
   *
   * \date Feb 2015
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   */
  class QuartLEvent : public TObject
  {
    public:
      QuartLEvent(); // Default constructor for ROOT not to complain in TTree readout...
      QuartLEvent(TString);
      virtual ~QuartLEvent();
      /**
       * \brief Reset the event after its storage to the output file
       */
      virtual void Clear(Option_t* opt="");
      
      inline TString GetSDName() const { return fName; }
      /**
       * \brief Total number of photon hits collected in one single event
       */
      inline size_t GetNumberOfPhotons() const { return (!fHitsCollection) ? -1 : fHitsCollection->size(); }
      /**
       * \brief Retrieve one photon hit from the collection
       */
      inline QuartLPhotonHit* GetHit(size_t i) const { return (!fHitsCollection) ? 0 : fHitsCollection->at(i); }

      /**
       * \brief Add a new photon hit on the PMT in the events' collection.
       * \param[in] hit A pointer to the QuartLPhotonHit object containing all the photon
       *  kinematics.
       */
      void AddPhoton(QuartLPhotonHit*);
            
    private:
      TString fName;
      
      HitsCollection* fHitsCollection;
      TH2D* fHitMap;

    public:
      ClassDef(QuartLEvent, 1)
  };
}

#endif
