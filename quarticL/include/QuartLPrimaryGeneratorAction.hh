#ifndef QuartLPrimaryGeneratorAction_h
#define QuartLPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "Randomize.hh"
#include "globals.hh"

#include "QuartLPrimaryGeneratorMessenger.hh"

class G4ParticleGun;
class G4Event;
class QuartLPrimaryGeneratorMessenger;


class QuartLPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    QuartLPrimaryGeneratorAction();
   ~QuartLPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event*);

    void SetOptPhotonPolar();
    void SetOptPhotonPolar(G4double);

  private:
    G4ParticleGun* particleGun;
    QuartLPrimaryGeneratorMessenger* gunMessenger;
};

#endif /*QuartLPrimaryGeneratorAction_h*/
