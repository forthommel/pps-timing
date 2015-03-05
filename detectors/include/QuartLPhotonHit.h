#ifndef QuartLPhotonHit_h
#define QuartLPhotonHit_h

#include "IncomingParticle.h"

#include "TObject.h"
#include "TLorentzVector.h"

namespace Quartic
{
  class QuartLPhotonHit : public TObject
  {
    public:
      QuartLPhotonHit();
      virtual ~QuartLPhotonHit();
      
      inline void SetPosition(TLorentzVector pos) { *fPosition=pos; }
      inline TLorentzVector* GetPosition() const { return fPosition; }
      
      inline void SetMomentum(TLorentzVector mom) { *fMomentum=mom; }
      inline TLorentzVector* GetMomentum() const { return fMomentum; }

      inline void SetIncomingParticle(PPS::IncomingParticle* ip) { fIP=ip; }
      inline PPS::IncomingParticle* GetIncomingParticle() const { return fIP; }

      // Cells mapping (downstream from the beam) :
      // -------------------------
      // |  3  |  7  | 11  | 15  | 
      // -------------------------
      // |  2  |  6  | 10  | 14  | 
      // -------------------------
      // |  1  |  5  |  9  | 13  | 
      // -------------------------
      // |  0  |  4  |  8  | 12  | 
      // -------------------------
      inline void SetCellID(int cell_id) {
        fCellID = cell_id;
        fCellRowID =  fCellID%4;
        fCellColID = (fCellID-fCellRowID)/4;
      }
      inline int GetCellID() const { return fCellID; }
      int GetCellRowID() const { return fCellRowID; } //!
      int GetCellColumnID() const { return fCellColID; } //!
    
    private:
      TLorentzVector* fPosition;
      TLorentzVector* fMomentum;
      PPS::IncomingParticle* fIP;
      int fCellID;
      int fCellRowID;
      int fCellColID;
      
    public:
      ClassDef(QuartLPhotonHit, 1)
  };
}

#endif
