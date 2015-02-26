#ifndef QuartLPhotonHit_h
#define QuartLPhotonHit_h

#include "TObject.h"
#include "TLorentzVector.h"

namespace Quartic
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

      /**
       * Set the incoming proton unique identifier giving rise to this photon hit
       * \param[in] par_id Unique identifier of the incoming proton
       */
      inline void SetParentID(int par_id) { fParentID=par_id; }
      /**
       * Return the incoming proton unique identifier giving rise to this photon hit
       * \return Unique identifier of the incoming proton
       */
      inline int GetParentID() const { return fParentID; }

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
      TLorentzVector fPosition;
      TLorentzVector fMomentum;
      int fParentID;
      int fCellID;
      int fCellRowID;
      int fCellColID;
      
    public:
      ClassDef(QuartLPhotonHit, 1)
  };
}

#endif
