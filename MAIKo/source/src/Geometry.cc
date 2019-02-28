//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geometry.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Geometry.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4Element.hh"
#include "G4SystemOfUnits.hh"
#include "SensitiveVolume.hh"
#include "G4SDManager.hh"


//------------------------------------------------------------------------------
Geometry::Geometry() {}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
Geometry::~Geometry() {}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
G4VPhysicalVolume* Geometry::Construct()
//------------------------------------------------------------------------------
{
  return ConstructDetector();
}

//------------------------------------------------------------------------------
G4VPhysicalVolume* Geometry::ConstructDetector()
//------------------------------------------------------------------------------
{
  // Get pointer to 'Material Manager'
   G4NistManager* materi_Man = G4NistManager::Instance();
   //   G4SDManager* SDman = G4SDManager::GetSDMpointer();

// Define 'World Volume'====================================================
   // Define the shape of solid
   G4double leng_X_World = 1.0*m;         // X-full-length of world 
   G4double leng_Y_World = 1.0*m;         // Y-full-length of world 
   G4double leng_Z_World = 1.0*m;         // Z-full-length of world 
   G4Box* solid_World = 
     new G4Box("Solid_World", leng_X_World/2.0, leng_Y_World/2.0, leng_Z_World/2.0);

   // Define logical volume
   G4Material* materi_World = materi_Man->FindOrBuildMaterial("G4_Galactic",true);
   G4LogicalVolume* logVol_World = 
     new G4LogicalVolume(solid_World, materi_World, "LogVol_World");
   logVol_World->SetVisAttributes (G4VisAttributes::Invisible);

   // Placement of logical volume
   G4int copyNum_World = 0;               // Set ID number of world
   G4PVPlacement* physVol_World  = 
     new G4PVPlacement(G4Transform3D(), "PhysVol_World", logVol_World, 0, 
                       false, copyNum_World);

// Define 'Lead-Glass Detector'===========================================
   // Define the shape of solid
   G4double leng_X_MAIKo = 102.4*mm;
   G4double leng_Y_MAIKo = 140.*mm;
   G4double leng_Z_MAIKo = 102.4*mm;
   G4Box* solid_MAIKo = new G4Box("Solid_MAIKo", leng_X_MAIKo/2., leng_Y_MAIKo/2. , leng_Z_MAIKo/2.); 

   // Define logical volume
   //G4Material* materi_LS = materi_Man->FindOrBuildMaterial("G4_XYLENE");
   //G4Material* materi_LG = materi_Man->FindOrBuildMaterial("G4_GLASS_LEAD",true);
   
   G4double exp_Pressure = 500*0.00986923*atmosphere;
   //Define CO2 gas
   G4Element* elC = materi_Man->FindOrBuildElement("C",true);
   G4Element* elO = materi_Man->FindOrBuildElement("O",true);
   G4double exp_Pressure_CO2 = 0.04*exp_Pressure;
   G4double denCO2 = 0.001977*g/cm3*exp_Pressure_CO2/CLHEP::STP_Pressure;
   G4Material* CO2 = new G4Material("CO2",denCO2,2,kStateGas,CLHEP::STP_Temperature,exp_Pressure_CO2);
   CO2->AddElement(elC,1);
   CO2->AddElement(elO,2);

   // Define He gas
   G4Element* elHe = materi_Man->FindOrBuildElement("He",true);
   G4double exp_Pressure_He = 0.96*exp_Pressure;
   G4double denHe = 0.0001786*g/cm3*exp_Pressure_He/CLHEP::STP_Pressure;
   G4Material* He = new G4Material("He",denHe,1,kStateGas,CLHEP::STP_Temperature,exp_Pressure_He);
   He->AddElement(elHe,1);

   //Define He + CO2 mixture
   G4double density = denHe*0.96 + denCO2*0.04;
   G4Material* materi_MAIKo =
     new G4Material("materi_MAIKo",density,2,kStateGas,CLHEP::STP_Temperature,exp_Pressure);
   materi_MAIKo->AddMaterial(He,96*perCent);
   materi_MAIKo->AddMaterial(CO2,4*perCent);
   
   G4cout << "check" << G4endl;
   //SensitiveVolume* SV_LG = new SensitiveVolume("/LG");
   //G4LogicalVolume* logVol_LG = new G4LogicalVolume(solid_LG,materi_LG,"LogVol_LG",0,0,0);
   //fScoringVol[0] = logVol_LG;
   G4LogicalVolume* logVol_MAIKo = new G4LogicalVolume(solid_MAIKo,materi_MAIKo,"LogVol_MAIKo",0,0,0);
   //logVol_LG->SetSensitiveDetector(SV_LG);
   //SDman->AddNewDetector(SV_LG);
   G4double pos_X_LogV = 0.*mm;
   G4double pos_Y_LogV = 0.*mm;
   G4double pos_Z_LogV = 0.*mm;
   G4ThreeVector threeVect_LogV = G4ThreeVector(pos_X_LogV,pos_Y_LogV,pos_Z_LogV);
   G4RotationMatrix rotMtrx_LogV = G4RotationMatrix();
   G4Transform3D trans3D_LogV = G4Transform3D(rotMtrx_LogV,threeVect_LogV);

   G4int copyNum_LogV = 1000;
   new G4PVPlacement(trans3D_LogV, "PhysVol_MAIKo",logVol_MAIKo,physVol_World,false,copyNum_LogV);

   //G4LogicalBorderSurface("World-LG",physVol_World,physVol_LG,

// Return the physical world
   return physVol_World;
}
