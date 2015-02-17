#ifndef IncomingParticle_h
#define IncomingParticle_h

#include "TObject.h"
#include "TLorentzVector.h"

namespace PPS
{
  class IncomingParticle : public TObject
  {
    public:
      IncomingParticle();
      IncomingParticle(int);
      virtual ~IncomingParticle();

      inline void SetPosition(TLorentzVector pos) { fPosition=pos; }
      inline TLorentzVector GetPosition() const { return fPosition; }

      inline void SetMomentum(TLorentzVector mom) { fMomentum=mom; }
      inline TLorentzVector GetMomentum() const { return fMomentum; }

    private:
      int fID;
      TLorentzVector fPosition;
      TLorentzVector fMomentum;

    public:
      ClassDef(IncomingParticle, 1)
  };
}

#endif
