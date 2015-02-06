#include "DetectorSD.hh"

using namespace CLHEP;

DetectorSD::DetectorSD(G4String name) :
  G4VSensitiveDetector(name), runAction(0), analyzer(0)
{
  runAction = (QuartLRunAction*)G4RunManager::GetRunManager()->GetUserRunAction();
  analyzer = (QuartLAnalyzer*)runAction->GetAnalyzer();
}

DetectorSD::~DetectorSD()
{}

void
DetectorSD::Initialize(G4HCofThisEvent*)
{
  //  Reset
  detEnergy = 0;
  firstPh = 100.;
}

G4bool
DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  //  Energy deposited from each step
  //  is summarized in detEnergy
  G4double edep = step->GetTotalEnergyDeposit();
  detEnergy += edep;
  
  analyzer->AddHitInEvent(step);
  //
  // Time of the Track
  //
  G4double time = step->GetPreStepPoint()->GetGlobalTime();
  detTime = time;
  if (detTime < firstPh) firstPh = detTime;
  
  G4ThreeVector wc = step->GetPreStepPoint()->GetPosition();
  
  //G4double yw = wc.y();
  //G4double zw = wc.z();
  
  //------------------------------------------------------  
  //  G4cout << "Track Time " << time << G4endl;
  //---------------------------------------------------------------  
  
  if (step->GetTrack()->GetDefinition()==G4OpticalPhoton::OpticalPhotonDefinition()) {
    // particle is optical photon ; was
    //    G4cout <<" step->Tack is Optical Photon " <<   G4endl;
    //    G4int idpar = step->GetTrack()->GetParentID();	//19.02.2012
    //    G4cout << " Parent ID " << idpar << G4endl;
    //    if(step->GetTrack()->GetParentID()>0)  G4cout << " Parent ID>0 " << G4endl;
    //    if(step->GetTrack()->GetParentID()>0) {             // particle is secondary  
    //      gammaCounter++;
    //      G4cout<<" Secondary " << G4endl;
    //      runAction->FillArrivalHist(time);
    //    }
    //G4int i = step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo();  
    time = step->GetPreStepPoint()->GetGlobalTime();
    
    //G4double timeloc = step->GetPreStepPoint()->GetLocalTime();
    //not work    G4double timepro = step->GetPreStepPoint()->GetProperTime();    

    //G4double lentr = step->GetTrack()->GetTrackLength();
    
    G4ThreeVector vertr = step->GetTrack()->GetVertexPosition();
    // G4cout << "Vertex " << vertr.x()/mm<<" " << vertr.y()/mm 
    //        << " " << vertr.z()/mm  << G4endl;
    
    //G4double ecer = step->GetPreStepPoint()->GetTotalEnergy(); 

    // G4cout << "Bar N " << i <<"  Time " << time/ns << G4endl;
    // was G4cout <<  i << " " << time/ns << G4endl;
    //	if (i == 0) {
    //	Now, 21.01.2015
    // --> display : G4cout <<  i <<" " << time/ns << " " << ecer/eV << G4endl; 
    //------------------------------------------------------------------------------------
    // was, 21.01.2015       G4cout <<  i <<" " << time/ns << " " << timeloc/ns
    //-----------------------------------------------
    // was  <<" "<< lentr/mm << " " << vertr.z()/mm<< " " << ecer/eV << G4endl;  //19.02
    //      <<" "<< lentr/mm << " " << zw/mm<< " " <<yw/mm <<' ' <<ecer/eV << G4endl;  //24.02
    // was, 9.06.2014 << " " << lentr/mm << " " << vertr.z()/mm << " " << yw/mm <<' ' << ecer/eV << G4endl;  //27.02 
    // was 21.01.2015 <<" "<< lentr/mm << " " << ecer/eV << G4endl; 	         //17.0
    //--------------------------------------------------------------------------------------	
    ///////////////////////////////////////////////      
    G4Track* track = step->GetTrack(); 
    
    track->SetTrackStatus(fStopAndKill); // One kills the particle after its arrival in the sensitive detector
  }
  //------------------------------------------- 
 
  return true;
}

void
DetectorSD::EndOfEvent(G4HCofThisEvent*)
{
  // Filling the tree with kinematic information...
  analyzer->Store();
}

