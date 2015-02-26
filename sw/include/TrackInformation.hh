#ifndef TrackInformation_h
#define TrackInformation_h

#include "G4Track.hh"

namespace PPS
{
  /**
   * \date Feb 2015
   * \author Laurent Forthomme <laurent.forthomme>
   */
  class TrackInformation : public G4VUserTrackInformation
  {
    public:
      TrackInformation();
      /**
       * \brief Track definition (called at the track object creation)
       */
      TrackInformation(const G4Track*);
      /**
       * \brief Track propagation
       */
      TrackInformation(const TrackInformation*);
      virtual ~TrackInformation();

      inline void *operator new(size_t);
      inline void operator delete(void *aTrackInfo);
      inline int operator ==(const TrackInformation& right) const { return (this==&right); }

      void Print() const;

      inline G4int GetOriginalTrackID() const { return fOriginalTrackID; };
      inline G4ParticleDefinition* GetOriginalParticle() const { return fParticleDefinition; };

      inline G4ThreeVector GetOriginalPosition() const { return fOriginalPosition; };
      inline G4double GetOriginalTime() const { return fOriginalTime; };

      inline G4ThreeVector GetOriginalMomentum() const { return fOriginalMomentum; };
      inline G4double GetOriginalEnergy() const { return fOriginalEnergy; };

    private:
      G4int fOriginalTrackID;
      G4ParticleDefinition* fParticleDefinition;
      G4ThreeVector fOriginalPosition;
      G4double fOriginalTime;
      G4ThreeVector fOriginalMomentum;
      G4double fOriginalEnergy;
  };

  extern G4Allocator<TrackInformation> aTrackInformationAllocator;

  inline void* TrackInformation::operator new(size_t) {
    void* aTrackInfo;
    aTrackInfo = (void*)aTrackInformationAllocator.MallocSingle();
    return aTrackInfo;
  }

  inline void TrackInformation::operator delete(void *aTrackInfo)
  {
    aTrackInformationAllocator.FreeSingle((TrackInformation*)aTrackInfo);
  }
}

#endif
