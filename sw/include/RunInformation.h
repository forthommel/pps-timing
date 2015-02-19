#ifndef RunInformation_h
#define RunInformation_h

#include "IncomingParticle.h"

#include "TObject.h"
#include "TLorentzVector.h"

#include <vector>

namespace PPS
{
  class RunInformation : public TObject
  {
    public:
      RunInformation();
      virtual ~RunInformation();

      inline void AddIncomingParticle(IncomingParticle ip) { fIPCollection.push_back(ip); }
      inline size_t GetNumberOfIncomingParticles() const { return fIPCollection.size(); }
      inline double GetMeanIncomingParticlesEnergy() const {
	double esum = 0.;
	for (std::vector<IncomingParticle>::const_iterator ip=fIPCollection.begin(); ip!=fIPCollection.end(); ip++) {
	  esum += ip->GetMomentum().E();
	}
	return esum/GetNumberOfIncomingParticles();
      }

    private:
      std::vector<IncomingParticle> fIPCollection;

    public:
      ClassDef(RunInformation, 1)
  };
}

#endif
