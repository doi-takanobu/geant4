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
   G4double leng_X_World = 2.0*m;         // X-full-length of world 
   G4double leng_Y_World = 2.0*m;         // Y-full-length of world 
   G4double leng_Z_World = 2.0*m;         // Z-full-length of world 
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
   
// Define 'Si Detector====================================================='
   // Define the shape of solid
   G4double leng_X_Si = 5.*cm;
   G4double leng_Y_Si = 5.*cm;
   G4double leng_Z_Si = 0.5*mm;
   //G4Box* solid_Si = new G4Box("Solid_Si",leng_X_Si/2., leng_Y_Si/2.,leng_Z_Si/2.); 

   // Define logical volume (Pad)
   //G4Material* materi_Si = materi_Man->FindOrBuildMaterial("G4_AIR",true);
   //G4LogicalVolume* logVol_Si = 
   //  new G4LogicalVolume( solid_Si, materi_Si, "LogVol_Si", 0, 0, 0 );

// Define Strip of Si Detector===========================================
   // Define the shape of solid
   G4int strip_Num = 10;
   G4double leng_X_Si_str = leng_X_Si/strip_Num;
   G4double leng_Y_Si_str = leng_Y_Si;
   G4double leng_Z_Si_str = leng_Z_Si;
   G4Box* solid_Si_str = new G4Box("Solid_Si_strip",leng_X_Si_str/2.,leng_Y_Si_str/2.,leng_Z_Si_str/2.);

   // Define logical volume
   G4Material* materi_Si_str = materi_Man->FindOrBuildMaterial("G4_Si",true);
   //SensitiveVolume* SV_Si_str = new SensitiveVolume("/Si_str");
   G4LogicalVolume* logVol_Si_str = new G4LogicalVolume(solid_Si_str,materi_Si_str,"LogVol_Si_strip",0,0,0);
   //logVol_Si_str->SetSensitiveDetector(SV_Si_str);
   //SDman->AddNewDetector(SV_Si_str);
   fScoringVol[0] = logVol_Si_str;

   // Make Replica
   //new G4PVReplica("Si_strip",logVol_Si_str,logVol_Si,kXAxis,strip_Num,leng_X_Si_str);
   
   G4double pos_X_LogV = 0.0*cm;           // X-location LogV 
   G4double pos_Y_LogV = 0.0*cm;           // Y-location LogVp
   G4double pos_Z_LogV = 0.0*cm;           // Z-location LogV
   G4ThreeVector threeVect_LogV = G4ThreeVector(pos_X_LogV, pos_Y_LogV, pos_Z_LogV);
   G4RotationMatrix rotMtrx_LogV = G4RotationMatrix();
   G4Transform3D trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV); 
   G4int copyNum_LogV = 1000;                // Set ID number of LogV
   for(G4int ii=0;ii<strip_Num;ii++){
     // Placement of logical volume (Pad)
     pos_X_LogV = -leng_X_Si_str*9/2. + leng_X_Si_str*ii;
     threeVect_LogV = G4ThreeVector(pos_X_LogV,pos_Y_LogV,pos_Z_LogV);
     rotMtrx_LogV = G4RotationMatrix();
     trans3D_LogV = G4Transform3D(rotMtrx_LogV,threeVect_LogV);
     new G4PVPlacement(trans3D_LogV, "PhysVol_Si", logVol_Si_str, physVol_World, false, copyNum_LogV);
   }

// Define 'Crystal Detector'================================================
   // Define the shape of solid
   G4double leng_X_Cry = 1.*cm;
   G4double leng_Y_Cry = 1.*cm;
   G4double leng_Z_Cry = 1.*cm;
   G4Box* solid_Cry = new G4Box("Solid_Cry", leng_X_Cry/2., leng_Y_Cry/2. , leng_Z_Cry/2.); 

   // Define logical volume
   //G4Material* materi_LS = materi_Man->FindOrBuildMaterial("G4_XYLENE");
   G4Material* materi_NaI = materi_Man->FindOrBuildMaterial("G4_SODIUM_IODIDE",true);
   //SensitiveVolume* SV_NaI = new SensitiveVolume("/NaI");
   G4LogicalVolume* logVol_NaI = new G4LogicalVolume(solid_Cry,materi_NaI,"LogVol_NaI",0,0,0);
   fScoringVol[1] = logVol_NaI;
   //logVol_NaI->SetSensitiveDetector(SV_NaI);
   //SDman->AddNewDetector(SV_NaI);
   pos_X_LogV = 0.*mm;
   pos_Y_LogV = -5.*mm;
   pos_Z_LogV = -10.*mm;
   threeVect_LogV = G4ThreeVector(pos_X_LogV,pos_Y_LogV,pos_Z_LogV);
   rotMtrx_LogV = G4RotationMatrix();
   trans3D_LogV = G4Transform3D(rotMtrx_LogV,threeVect_LogV);

   copyNum_LogV = 1001;
   new G4PVPlacement(trans3D_LogV, "PhysVol_NaI",logVol_NaI,physVol_World,false,copyNum_LogV);
   

   //Define GAGG
   G4Element* ele_Gd = new G4Element("Gadolinium","Gd",64,157.25*g/mole);
   G4Element* ele_Al = new G4Element("Aluminium","Al",13,26.98*g/mole);
   G4Element* ele_Ga = new G4Element("Gallium","Ga",31,69.72*g/mole);
   G4Element* ele_O = new G4Element("Oxygen","O",8,16.00*g/mole);
   G4double density = 6.63*g/cm3;
   G4Material* materi_GAGG = new G4Material("GAGG",density,4);
   materi_GAGG->AddElement(ele_Gd,3);
   materi_GAGG->AddElement(ele_Al,2);
   materi_GAGG->AddElement(ele_Ga,3);
   materi_GAGG->AddElement(ele_O,12);
   //SensitiveVolume* SV_GAGG = new SensitiveVolume("/GAGG");
   
   G4LogicalVolume* logVol_GAGG = 
     new G4LogicalVolume( solid_Cry, materi_GAGG, "LogVol_GAGG", 0, 0, 0 );
   fScoringVol[2] = logVol_GAGG;
   //logVol_GAGG->SetSensitiveDetector(SV_GAGG);

   //SDman->AddNewDetector(SV_GAGG);

   // Placement of logical volume
   pos_X_LogV = 0.*mm;           // X-location LogV 
   pos_Y_LogV = 5.*mm;           // Y-location LogV
   pos_Z_LogV = -10.*mm;           // Z-location LogV
   threeVect_LogV = G4ThreeVector(pos_X_LogV, pos_Y_LogV, pos_Z_LogV);
   rotMtrx_LogV = G4RotationMatrix();
   trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);

   copyNum_LogV = 1002;                // Set ID number of LogV
   new G4PVPlacement(trans3D_LogV, "PhysVol_GAGG", logVol_GAGG, physVol_World,false, copyNum_LogV);

// Return the physical world
   return physVol_World;
}
