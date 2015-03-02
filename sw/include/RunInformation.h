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

      inline void AddIncomingParticle(IncomingParticle* ip) { fIPCollection->push_back(ip); }
      inline IncomingParticle* GetIncomingParticle(size_t i) { return fIPCollection->at(i); }

      inline size_t GetNumberOfIncomingParticles() const { return fIPCollection->size(); }
      inline double GetMeanIncomingParticlesEnergy() const {
	double esum = 0.;
	for (std::vector<IncomingParticle*>::const_iterator it=fIPCollection->begin(); it!=fIPCollection->end(); it++) {
	  esum += (*it)->GetMomentum()->E();
	}
	return esum/GetNumberOfIncomingParticles();
      }

    private:
      IncomingParticlesRef* fIPCollection; //!

    public:
      ClassDef(RunInformation, 1)
  };
}

#endif
