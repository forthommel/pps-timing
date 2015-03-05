#include "QuartLPhotonHit.h"

ClassImp(Quartic::QuartLPhotonHit)

namespace Quartic
{
  QuartLPhotonHit::QuartLPhotonHit() :
    fPosition(0), fMomentum(0), fIP(0)
  {
    fPosition = new TLorentzVector;
    fMomentum = new TLorentzVector;
  }
  
  QuartLPhotonHit::~QuartLPhotonHit()
  {
    if (fPosition) delete fPosition;
    if (fMomentum) delete fMomentum;
  }
}
