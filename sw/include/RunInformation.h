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

    private:
      std::vector<IncomingParticle> fIPCollection;

    public:
      ClassDef(RunInformation, 1)
  };
}

#endif
