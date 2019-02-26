//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geometry.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Geometry.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"


#include "G4SDManager.hh"

/* use for MultiFumctionalDetector and PrimitiveScorer 使わ無い
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
//#include "G4PSTrackLength.hh"
//#include "G4SDChargedFilter.hh"
*/

//------------------------------------------------------------------------------
  Geometry::Geometry() : G4VUserDetectorConstruction(),fScoringVol(0){}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
  Geometry::~Geometry() {}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
  G4VPhysicalVolume* Geometry::Construct()
//------------------------------------------------------------------------------
{
// Get pointer to 'Material Manager'
   G4NistManager* materi_Man = G4NistManager::Instance();

// Define 'World Volume'
   // Define the shape of solid
   G4double leng_X_World = 2.0*m;         // X-full-length of world 
   G4double leng_Y_World = 2.0*m;         // Y-full-length of world 
   G4double leng_Z_World = 2.0*m;         // Z-full-length of world 
   G4Box* solid_World = 
     new G4Box("Solid_World", leng_X_World/2.0, leng_Y_World/2.0, leng_Z_World/2.0);

   // Define logical volume
   G4Material* materi_World = materi_Man->FindOrBuildMaterial("G4_AIR");
   G4LogicalVolume* logVol_World = 
     new G4LogicalVolume(solid_World, materi_World, "LogVol_World");
   logVol_World->SetVisAttributes (G4VisAttributes::Invisible);

   // Placement of logical volume
   G4int copyNum_World = 0;               // Set ID number of world
   G4PVPlacement* physVol_World  = 
     new G4PVPlacement(G4Transform3D(), "PhysVol_World", logVol_World, 0, 
                       false, copyNum_World);

// Define 'BGO Detector'
   // Define the shape of solid
   G4double radius_BGO = 5.0*cm;
   G4double leng_Z_BGO = 20.0*cm;
   G4Tubs* solid_BGO = new G4Tubs("Solid_BGO", 0., radius_BGO, leng_Z_BGO/2.0, 0., 360.*deg); 

   // Define logical volume
   G4Material* materi_BGO = materi_Man->FindOrBuildMaterial("G4_BGO");
   G4LogicalVolume* logVol_BGO = 
     new G4LogicalVolume( solid_BGO, materi_BGO, "LogVol_BGO", 0, 0, 0 );

// define my sensitive volume BGO論理物体を有感としてSteppingActionでチェックする
    fScoringVol = logVol_BGO;


// Placement of logical volume BGO with another constructor
    

   G4double pos_X_LogV = 0.0*cm;           // X-location LogV
   G4double pos_Y_LogV = 0.0*cm;           // Y-location LogV
   G4double pos_Z_LogV = 0.0*cm;
    
  
   G4ThreeVector threeVect_LogV = G4ThreeVector(pos_X_LogV, pos_Y_LogV, pos_Z_LogV);
   new G4PVPlacement(0,   // no rotation
                     threeVect_LogV, // translation
                     logVol_BGO,     //logical vol
                     "PhysVol_BGO", //name
                     logVol_World, // mother logical
                     false,0);  // no Boolean, default copy no.

// Return the physical world
   return physVol_World;
}
