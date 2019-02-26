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
#include "G4MaterialPropertiesTable.hh"


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
   G4MaterialPropertiesTable* MatPropTab = new  G4MaterialPropertiesTable();
   //   G4SDManager* SDman = G4SDManager::GetSDMpointer();

// Define 'World Volume'====================================================
   // Define the shape of solid
   G4double leng_X_World = 2.0*m;         // X-full-length of world 
   G4double leng_Y_World = 2.0*m;         // Y-full-length of world 
   G4double leng_Z_World = 2.0*m;         // Z-full-length of world 
   G4Box* solid_World = 
     new G4Box("Solid_World", leng_X_World/2.0, leng_Y_World/2.0, leng_Z_World/2.0);

   // Define logical volume
   G4Material* materi_World = materi_Man->FindOrBuildMaterial("G4_Galactic",true);
   G4int nEntries = 1;
   G4double PhotonEnergy[nEntries] = {3.*eV};
   G4double RefractiveIndex[nEntries] = {1.};
   G4double Absorption[nEntries] = {1000000*m};
   MatPropTab->AddProperty("RINDEX",PhotonEnergy,RefractiveIndex,nEntries);
   MatPropTab->AddProperty("ABSLENGTH",PhotonEnergy,Absorption,nEntries);
   MatPropTab->AddConstProperty("RESOLUTIONSCALE",1.);
   materi_World->SetMaterialPropertiesTable(MatPropTab);
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
   G4double leng_X_LG = 160.*mm;
   G4double leng_Y_LG = 122.*mm;
   G4double leng_Z_LG = 135.*mm;
   G4Box* solid_LG = new G4Box("Solid_LG", leng_X_LG/2., leng_Y_LG/2. , leng_Z_LG/2.); 

   // Define logical volume
   //G4Material* materi_LS = materi_Man->FindOrBuildMaterial("G4_XYLENE");
   G4Material* materi_LG = materi_Man->FindOrBuildMaterial("G4_GLASS_LEAD",true);
   
   PhotonEnergy[nEntries] = {3.*eV};
   RefractiveIndex[nEntries] = {1.8};
   Absorption[nEntries] = {1.69*cm};
   MatPropTab->AddProperty("RINDEX",PhotonEnergy,RefractiveIndex,nEntries);
   MatPropTab->AddProperty("ABSLENGTH",PhotonEnergy,Absorption,nEntries);
   MatPropTab->AddConstProperty("RESOLUTIONSCALE",1.);
   materi_LG->SetMaterialPropertiesTable(MatPropTab);
   //SensitiveVolume* SV_LG = new SensitiveVolume("/LG");
   G4LogicalVolume* logVol_LG = new G4LogicalVolume(solid_LG,materi_LG,"LogVol_LG",0,0,0);
   fScoringVol[0] = logVol_LG;
   //logVol_LG->SetSensitiveDetector(SV_LG);
   //SDman->AddNewDetector(SV_LG);
   G4double pos_X_LogV = 0.*mm;
   G4double pos_Y_LogV = 0.*mm;
   G4double pos_Z_LogV = 0.*mm;
   G4ThreeVector threeVect_LogV = G4ThreeVector(pos_X_LogV,pos_Y_LogV,pos_Z_LogV);
   G4RotationMatrix rotMtrx_LogV = G4RotationMatrix();
   G4Transform3D trans3D_LogV = G4Transform3D(rotMtrx_LogV,threeVect_LogV);

   G4int copyNum_LogV = 1000;
   G4PVPlacement* physVol_LG = new G4PVPlacement(trans3D_LogV, "PhysVol_LG",logVol_LG,physVol_World,false,copyNum_LogV);

   //G4LogicalBorderSurface("World-LG",physVol_World,physVol_LG,

// Return the physical world
   return physVol_World;
}
