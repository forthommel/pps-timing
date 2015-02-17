#include "IncomingParticle.h"

ClassImp(PPS::IncomingParticle)

namespace PPS
{
  IncomingParticle::IncomingParticle() :
    fID(-1), fPosition(TLorentzVector()), fMomentum(TLorentzVector())
  {}

  IncomingParticle::IncomingParticle(int id) :
    fID(id), fPosition(TLorentzVector()), fMomentum(TLorentzVector())
  {}

  IncomingParticle::~IncomingParticle()
  {}
}
