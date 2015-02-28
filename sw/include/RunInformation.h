#ifndef RunInformation_h
#define RunInformation_h

#include "IncomingParticle.h"

#include "TObject.h"
#include "TList.h"
#include "TLorentzVector.h"

namespace PPS
{
  class RunInformation : public TObject
  {
    public:
      RunInformation();
      virtual ~RunInformation();
      void Clear(Option_t*);

      inline void AddIncomingParticle(IncomingParticle* ip) { fIPCollection->Add(ip); }
      inline size_t GetNumberOfIncomingParticles() const { return fIPCollection->GetSize(); }
      inline double GetMeanIncomingParticlesEnergy() const {
	double esum = 0.;
	for (size_t i=0; i<GetNumberOfIncomingParticles(); i++) {
	  esum += ((IncomingParticle*)fIPCollection->At(i))->GetMomentum()->E();
	}
	return esum/GetNumberOfIncomingParticles();
      }

    private:
      TList* fIPCollection;

    public:
      ClassDef(RunInformation, 1)
  };
}

#endif
