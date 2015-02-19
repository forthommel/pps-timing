#ifndef QuartLPhotonHit_h
#define QuartLPhotonHit_h

#include "TObject.h"
#include "TLorentzVector.h"

namespace PPS
{
  class QuartLPhotonHit : public TObject
  {
    public:
      QuartLPhotonHit();
      QuartLPhotonHit(int);
      virtual ~QuartLPhotonHit();
      
      inline void SetPosition(TLorentzVector pos) { fPosition=pos; }
      inline TLorentzVector Position() const { return fPosition; }
      
      inline void SetMomentum(TLorentzVector mom) { fMomentum=mom; }
      inline TLorentzVector Momentum() const { return fMomentum; }

      inline void SetParentID(int par_id) { fParentID=par_id; }
      inline int GetParentID() const { return fParentID; }

      inline void SetCellID(int cell_id) { fCellID=cell_id; }
      inline int GetCellID() const { return fCellID; }
    
    private:
      TLorentzVector fPosition;
      TLorentzVector fMomentum;
      int fParentID;
      int fCellID;
      
    public:
      ClassDef(QuartLPhotonHit, 1)
  };
}

#endif
