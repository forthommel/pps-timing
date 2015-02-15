#ifndef QuartLEvent_h
#define QuartLEvent_h

#include <vector>

#include "QuartLPhotonHit.h"

#include "TObject.h"
#include "TLorentzVector.h"

namespace PPS
{
  class QuartLEvent : public TObject
  {
    public:
      QuartLEvent(); // Default constructor for ROOT not to complain in TTree readout...
      QuartLEvent(TString);
      virtual ~QuartLEvent();
      virtual void Clear(Option_t* opt="");
      
      inline TString GetSDName() const { return fName; }
      inline size_t GetNumberOfPhotons() const { return fHitsCollection.size(); }
      inline QuartLPhotonHit GetHit(size_t i) const { return fHitsCollection.at(i);  }

      void AddPhoton(TLorentzVector pos, TLorentzVector mom);
            
    private:
      TString fName;
      
      std::vector<QuartLPhotonHit> fHitsCollection;

    public:
      ClassDef(QuartLEvent, 1)
  };
}

#endif
