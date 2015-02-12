#include "MBP.hh"

MBP::MBP(window_type window_material_, G4bool only_window_) :
  fScoringVolume(0),
  fOnlyWindow(only_window_)
{
  env_sizeXY = 1.*m;
  env_sizeZ = 1.*m;

  mbp_z_size = 600.*mm;
  mbp_outer_radius = 96.4*mm/2.;
    
  mbp_cone_extrusion_depth = 229.51*mm;
  mbp_cone_extrusion_angle = 22.*deg;
  
  mbp_beampipe_radius = 61.*mm/2.;
  mbp_beampipe_extrusion_x_offset = 13.*mm;
  mbp_beampipe_sqrextrusion_x_offset = 28.5*mm;
  mbp_beampipe_sqrextrusion_y_size = 25.*mm;

  mbp_taper_angle = 11.*deg;
  mbp_taper_y_size = 150.*mm; // whatever...
  mbp_traptaper_z_size_small = 250.*mm; //FIXME FIXME FIXME FIXME
  mbp_traptaper_z_size_large = 500.*mm;
  
  mbp_lateral_extrusion_x_size = 40.*mm; // whatever...
  mbp_lateral_extrusion_y_offset = 45.*mm;
  
  mbp_window_thickness = .3*mm;
  mbp_window_x_offset = 37.5*mm;
  mbp_window_y_size = 30.*mm;
  mbp_window_extrusion_x_size = 20.67*mm;
  
  switch (window_material_) {
    case ALBEMET: fWindowMaterial = fMaterial->AlBeMet; break;
    case BERYLLIUM: fWindowMaterial = fMaterial->Beryllium; break;
    case STAINLESS_STEEL: default: fWindowMaterial = fMaterial->StainlessSteel; break;
  }
}

MBP::~MBP()
{ }

G4VPhysicalVolume*
MBP::Construct()
{  
  // Envelope parameters
  //

  G4double traptaper_x_size, sqrtaper_x_size;
  G4double leg_x_size, leg_y_size, leg_length;
  G4double extrusion_length;
  G4double center_to_beampipe_cut_x_distance = (mbp_beampipe_sqrextrusion_x_offset-mbp_beampipe_extrusion_x_offset);
  G4double taper_x_position;
  
  traptaper_x_size = (mbp_traptaper_z_size_large-mbp_traptaper_z_size_small)/2.*tan(mbp_taper_angle);
  sqrtaper_x_size = mbp_outer_radius-center_to_beampipe_cut_x_distance-traptaper_x_size-mbp_window_thickness+1.*mm;
  taper_x_position = center_to_beampipe_cut_x_distance+traptaper_x_size/2.;
  leg_x_size = (mbp_window_x_offset-center_to_beampipe_cut_x_distance);
  leg_y_size = leg_x_size/tan(mbp_taper_angle);
  leg_length = leg_x_size/sin(mbp_taper_angle);
  extrusion_length = 50.*mm;    
  mbp_window_leg_length = leg_length;

  rot_taper = new G4RotationMatrix();
  rot_taper->rotateY(-90.*deg);
  rot_extrusion1 = new G4RotationMatrix();
  rot_extrusion2 = new G4RotationMatrix();
  rot_extrusion2->rotateY(180.*deg);
  rot_window_leg1 = new G4RotationMatrix();
  rot_window_leg1->rotateX(mbp_taper_angle);
  rot_window_leg2 = new G4RotationMatrix();
  rot_window_leg2->rotateX(-mbp_taper_angle);
  rot_window = new G4RotationMatrix();
  rot_window->rotateZ(90.*deg);
  
  //
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  G4VPhysicalVolume* physEnv;
  
  //     
  // Envelope
  //  
  solidEnv = new G4Box("Envelope", env_sizeXY/2., env_sizeXY/2., env_sizeZ/2.);
  logicEnv = new G4LogicalVolume(solidEnv, fMaterial->Air, "Envelope");
  physEnv = new G4PVPlacement(0, fPosition, logicEnv, "Envelope", fParentLog, false, 0, checkOverlaps);
  
  solidWindowCentre = new G4Box("Window_Centre", mbp_window_y_size/2., mbp_window_thickness/2., mbp_traptaper_z_size_small/2.);
  solidWindowLeg = new G4Box("Window_Leg", mbp_window_y_size/2., mbp_window_thickness/2., mbp_window_leg_length/2.);
  solidWindowOneLeg = new G4UnionSolid("Window_OneLeg", solidWindowCentre, solidWindowLeg, rot_window_leg1,
    G4ThreeVector(0., leg_x_size/2., mbp_traptaper_z_size_small/2.+leg_y_size/2.)
  );
  solidWindow = new G4UnionSolid("Window", solidWindowOneLeg, solidWindowLeg, rot_window_leg2,
    G4ThreeVector(0., leg_x_size/2., -(mbp_traptaper_z_size_small/2.+leg_y_size/2.))
  );

  if (!fOnlyWindow) {
    solidBeamLineCylExtrusion = new G4Tubs("Beamline_Extrusion2", 0., mbp_beampipe_radius, mbp_z_size/2., 0.*deg, 360.*deg);
    solidBeamLineSqrExtrusion = new G4Box("Beamline_Flat_Extrusion", extrusion_length/2., mbp_beampipe_sqrextrusion_y_size/2., mbp_z_size/2.);
    solidBeamLineExtrusion = new G4UnionSolid("Beamline_Extrusion_", solidBeamLineCylExtrusion, solidBeamLineSqrExtrusion, new G4RotationMatrix,
      G4ThreeVector(center_to_beampipe_cut_x_distance+mbp_window_extrusion_x_size-extrusion_length/2., 0., 0.)
    );
      
    solidConeExtrusion = new G4Cons("Cone_Extrusion", 0., 0., 0., mbp_cone_extrusion_depth*tan(mbp_cone_extrusion_angle/2.), mbp_cone_extrusion_depth/2., 0., 360.*deg);
    solidWindowExtrusion = new G4Box("Window_Extrusion", mbp_window_extrusion_x_size/2., mbp_window_y_size/2., mbp_z_size/2.);
    solidLateralExtrusion = new G4Box("Lateral_Extrusion", mbp_lateral_extrusion_x_size/2., extrusion_length/2., mbp_traptaper_z_size_large/2.);
    
    solidTubeNoExtrusion = new G4Tubs("Tube_NoExtrusion", 0., mbp_outer_radius, mbp_z_size/2., 0.*deg, 360.*deg);
    solidTubeBeamLineExtrusion = new G4SubtractionSolid("Tube_ThreeExtrusions", solidTubeNoExtrusion, solidBeamLineExtrusion, new G4RotationMatrix,
      G4ThreeVector(-mbp_beampipe_extrusion_x_offset, 0., 0.));
    solidTubeOneConeExtrusion = new G4SubtractionSolid("Tube_OneExtrusion", solidTubeBeamLineExtrusion, solidConeExtrusion, rot_extrusion1,
      G4ThreeVector(0., 0., (mbp_z_size-mbp_cone_extrusion_depth)/2.)
    );
    solidTubeTwoConeExtrusions = new G4SubtractionSolid("Tube_TwoExtrusions", solidTubeOneConeExtrusion, solidConeExtrusion, rot_extrusion2,
      G4ThreeVector(0., 0., (-mbp_z_size+mbp_cone_extrusion_depth)/2.)
    );
    
    solidTrapTaper = new G4Trap("Taper_Trap", mbp_traptaper_z_size_small/2., mbp_traptaper_z_size_large/2., mbp_taper_y_size/2., mbp_taper_y_size/2., traptaper_x_size/2.);
    solidSqrTaper = new G4Box("Taper_Sqr", mbp_traptaper_z_size_large/2., mbp_taper_y_size/2., sqrtaper_x_size/2.);
    solidTaper = new G4UnionSolid("Taper", solidTrapTaper, solidSqrTaper, new G4RotationMatrix,
      G4ThreeVector(0., 0., (traptaper_x_size+sqrtaper_x_size)/2.)
    );
      
    solidMBPNoWindowExtrusion = new G4SubtractionSolid("Tube_FourExtrusions", solidTubeTwoConeExtrusions, solidTaper, rot_taper,
      G4ThreeVector(taper_x_position, 0., 0.)
    );
    solidMBPNoLateralExtrusions = new G4SubtractionSolid("Tube_FiveExtrusions", solidMBPNoWindowExtrusion, solidWindowExtrusion, new G4RotationMatrix,
      G4ThreeVector(mbp_window_x_offset-mbp_window_extrusion_x_size/2., 0., 0.)
    );
    solidMBPOneLateralExtrusion = new G4SubtractionSolid("Tube_SixExtrusions", solidMBPNoLateralExtrusions, solidLateralExtrusion, new G4RotationMatrix,
      G4ThreeVector(0., +(mbp_lateral_extrusion_y_offset+extrusion_length/2.), 0.)
    );
    solidMBPTwoLateralExtrusions = new G4SubtractionSolid("Tube_SevenExtrusions", solidMBPOneLateralExtrusion, solidLateralExtrusion, new G4RotationMatrix,
      G4ThreeVector(0., -(mbp_lateral_extrusion_y_offset+extrusion_length/2.), 0.)
    );
    //solidMBPNoWindow = new G4SubtractionSolid("MBP_NoWindow", solidMBPTwoLateralExtrusions, solidWindow, rot_window,
    //  G4ThreeVector(center_to_beampipe_cut_x_distance-mbp_window_thickness/2., 0., 0.)
    //);
    //logicTube = new G4LogicalVolume(solidMBPNoWindow, fMaterial->StainlessSteel, "logic_Tube");
    
    logicTube = new G4LogicalVolume(solidMBPTwoLateralExtrusions, fMaterial->StainlessSteel, "logic_Tube");
    physTube = new G4PVPlacement(0, G4ThreeVector(), logicTube, "phys_Tube", logicEnv, false, 0, checkOverlaps);
  }
  logicWindow = new G4LogicalVolume(solidWindow, fWindowMaterial, "logic_Window");
  logicWindow->SetVisAttributes(new G4VisAttributes(G4Colour(1., 0., 0.))); // we paint the glass with red
  
  physWindow = new G4PVPlacement(rot_window, 
    G4ThreeVector(center_to_beampipe_cut_x_distance-mbp_window_thickness/2., 0., 0.),
    logicWindow, "phys_Window", logicEnv, false, 0, checkOverlaps);

  /*G4LogicalVolume *logicTest = new G4LogicalVolume(solidTaper, fMaterial->StainlessSteel, "test");
  new G4PVPlacement(rot_taper, G4ThreeVector(taper_x_position, 0., 0.), logicTest, "test_phys", logicEnv, false, 0, false);
  logicTest->SetVisAttributes(new G4VisAttributes(G4Colour(0., 1., 0.)));*/
  /*G4LogicalVolume *logicTest = new G4LogicalVolume(solidBeamLineExtrusion, fMaterial->StainlessSteel, "test");
  new G4PVPlacement(0, G4ThreeVector(20.*cm, 0., 0.), logicTest, "test_phys", logicEnv, false, 0, false);
  logicTest->SetVisAttributes(new G4VisAttributes(G4Colour(0., 1., 0.)));*/
  // Set scoring volume
  //
  //fScoringVolume = logicTube;
  fScoringVolume = fParentLog;

  //
  //always return the physical World
  //
  return physEnv;
}
