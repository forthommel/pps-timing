#include "IncomingParticle.h"

ClassImp(PPS::IncomingParticle)

namespace PPS
{
  IncomingParticle::IncomingParticle() :
    fID(-1), fPosition(new TLorentzVector()), fMomentum(new TLorentzVector())
  {}

  IncomingParticle::IncomingParticle(int id) :
    fID(id), fPosition(new TLorentzVector()), fMomentum(new TLorentzVector())
  {}

  IncomingParticle::~IncomingParticle()
  {}
}
