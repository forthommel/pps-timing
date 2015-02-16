#ifndef RunInformation_h
#define RunInformation_h

#include <vector>

#include "TObject.h"
#include "TLorentzVector.h"

class RunInformation : public TObject
{
  public:
    RunInformation();
    virtual ~RunInformation();

  private:
    std::vector<float> fProtonEnergies;
    std::vector<TLorentzVector> fProtonStarts;

  public:
    ClassDef(RunInformation, 1)
};

#endif
