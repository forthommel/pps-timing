#include "QuartLPrimaryGeneratorAction.hh"

using namespace CLHEP;

QuartLPrimaryGeneratorAction::QuartLPrimaryGeneratorAction()
{
  G4int n_particle = 1;
  
  //G4double z_mv = G4UniformRand() * 0.1*cm;  
  //G4double y_mv = G4UniformRand() * 0.1*cm;  
  
  particleGun = new G4ParticleGun(n_particle);
  
  //create a messenger for this class
  gunMessenger = new QuartLPrimaryGeneratorMessenger(this);
  
  //default kinematic
  //
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  // G4ParticleDefinition* particle = particleTable->FindParticle("e+");
  //   G4ParticleDefinition* particle = particleTable->FindParticle("e-");  
  G4ParticleDefinition* particle = particleTable->FindParticle("proton");   
  
  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleTime(0.0*ns);
  //  particleGun->SetParticlePosition(G4ThreeVector(-10.0*cm,0.0*cm,0.0*cm));
  //    particleGun->SetParticlePosition(G4ThreeVector(-5.0*cm,0.0*cm,0.0*cm));  
  //    particleGun->SetParticlePosition(G4ThreeVector(-5.0*cm, 0.0*cm, 0.0*cm)); //was Z=0.0 
  //    particleGun->SetParticlePosition(G4ThreeVector(-5.0*cm, y_mv,   z_mv)); 	//was Z=0.0 
  //------------------------was ^ now --------------------
  //
  //    was    particleGun->SetParticlePosition(G4ThreeVector(0*cm, 0*cm ,    -5.0*cm)); 
  particleGun->SetParticlePosition(G4ThreeVector(1*mm, 1*mm, -5.0*cm));
  //
  //	Beam under Angle, 26.04
  //
  //was 2 jun        particleGun->SetParticlePosition(G4ThreeVector(-0.1*cm, 0*cm ,    -5.0*cm)); 	
  
  
  //Run39 particleGun->SetParticlePosition(G4ThreeVector(0.1*cm,0.1*cm , -5.0*cm)); 
  //Run41 particleGun->SetParticlePosition(G4ThreeVector(-0.1*cm,0.1*cm , -5.0*cm)); 
  
  
  //  particleGun->SetParticlePosition(G4ThreeVector(-5.0*cm, 0.0*cm,-1.0*cm)); 	//was Z=0.0 
  //  particleGun->SetParticlePosition(G4ThreeVector(-5.0*cm, 0.0*cm, 1.0*cm)); 	//was Z=0.0         
  
  //  particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
  //---------------------was now ^----------------------  
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));  
  //  
  //	Beam under Angle, 26.04. 2012  
  //  
  //Run82  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.025,0.,0.9994));  
  //           particleGun->SetParticleMomentumDirection(G4ThreeVector(0.0,0.025,0.9994)); //Run85  
  //was 2 jun  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.025,0.0,0.9994)); //Run86  	 
  
  particleGun->SetParticleEnergy(2000.*GeV);
  //  particleGun->SetParticleEnergy(2500.0*keV); 
}

QuartLPrimaryGeneratorAction::~QuartLPrimaryGeneratorAction()
{
  delete particleGun;
  delete gunMessenger;
}

void
QuartLPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  particleGun->GeneratePrimaryVertex(anEvent);
}

void
QuartLPrimaryGeneratorAction::SetOptPhotonPolar()
{
 G4double angle = G4UniformRand() * 360.0*deg;
 SetOptPhotonPolar(angle);
}

void
QuartLPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
  if (particleGun->GetParticleDefinition()->GetParticleName()!="opticalphoton") {
    G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
      "the particleGun is not an opticalphoton" << G4endl;
    return;
  }
  
  G4ThreeVector normal (1., 0., 0.);
  G4ThreeVector kphoton = particleGun->GetParticleMomentumDirection();
  G4ThreeVector product = normal.cross(kphoton); 
  G4double modul2       = product*product;
  
  G4ThreeVector e_perpend (0., 0., 1.);
  if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product; 
  G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
  
  G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
  particleGun->SetParticlePolarization(polar);
}
