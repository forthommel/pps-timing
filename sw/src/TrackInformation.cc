#include "TrackInformation.hh"

namespace PPS
{
  G4Allocator<TrackInformation> aTrackInformationAllocator;
  
  TrackInformation::TrackInformation() :
    fOriginalTrackID(0), fParticleDefinition(0),
    fOriginalPosition(G4ThreeVector()), fOriginalTime(0.),
    fOriginalMomentum(G4ThreeVector()), fOriginalEnergy(0.)
  {}
  
  TrackInformation::TrackInformation(const G4Track* aTrack) :
    fOriginalTrackID(aTrack->GetTrackID()), fParticleDefinition(aTrack->GetDefinition()),
    fOriginalPosition(aTrack->GetPosition()), fOriginalTime(aTrack->GetGlobalTime()),
    fOriginalMomentum(aTrack->GetMomentum()), fOriginalEnergy(aTrack->GetTotalEnergy())
  {}
  
  TrackInformation::TrackInformation(const TrackInformation* aTrackInfo) :
    fOriginalTrackID(aTrackInfo->fOriginalTrackID), fParticleDefinition(aTrackInfo->fParticleDefinition),
    fOriginalPosition(aTrackInfo->fOriginalPosition), fOriginalTime(aTrackInfo->fOriginalTime),
    fOriginalMomentum(aTrackInfo->fOriginalMomentum), fOriginalEnergy(aTrackInfo->fOriginalEnergy)
  {}
  
  TrackInformation::~TrackInformation()
  {}
  
  void
  TrackInformation::Print() const
  {
    G4cout << "Original track ID " << fOriginalTrackID << " at " << fOriginalPosition << G4endl;
  }
}
