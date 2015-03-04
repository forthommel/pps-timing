#ifndef IncomingParticle_h
#define IncomingParticle_h

#include "TObject.h"
#include "TLorentzVector.h"
#include <vector>

namespace PPS
{
  /**
   * Class holding all the kinematic information on the incoming particles to appear in a run
   *
   * \date Feb 2015
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   */
  class IncomingParticle : public TObject
  {
    public:
      IncomingParticle();
      IncomingParticle(int);
      virtual ~IncomingParticle();

      inline void SetPosition(TLorentzVector pos) { *fPosition=pos; }
      inline TLorentzVector* GetPosition() const { return fPosition; }

      inline void SetMomentum(TLorentzVector mom) { *fMomentum=mom; }
      inline TLorentzVector* GetMomentum() const { return fMomentum; }

    private:
      int fID;
      TLorentzVector* fPosition;
      TLorentzVector* fMomentum;

    public:
      ClassDef(IncomingParticle, 1)
  };
  typedef std::vector<IncomingParticle> IncomingParticles;
  typedef std::vector<IncomingParticle*> IncomingParticlesRef;
}

#endif
