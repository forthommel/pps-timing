#include "QuartLPhotonHit.h"

ClassImp(PPS::QuartLPhotonHit)

PPS::QuartLPhotonHit::QuartLPhotonHit() :
  fParentID(-1)
{}

PPS::QuartLPhotonHit::QuartLPhotonHit(int par_id) :
  fParentID(par_id)
{}

PPS::QuartLPhotonHit::~QuartLPhotonHit()
{}
