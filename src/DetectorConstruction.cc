#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    DefineMaterials();
    auto nist = G4NistManager::Instance();

    // ---------------- World ----------------
    auto worldMat  = nist->FindOrBuildMaterial("G4_Galactic");
    auto worldSize = 1.0*m;

    auto solidWorld = new G4Box("World", worldSize, worldSize, worldSize);
    auto logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
    auto physWorld  = new G4PVPlacement(nullptr, {}, logicWorld,
                                        "World", nullptr, false, 0);

    // -------- Spherical photon field -------
    auto radius = 5.*cm;
    auto solidSrc = new G4Sphere("XRaySource", 0., radius,
                                 0., twopi, 0., pi);

    auto vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    auto mpt = new G4MaterialPropertiesTable;
    mpt->AddConstProperty("Radiation", 1.0);  // Photon-Process flag
    vacuum->SetMaterialPropertiesTable(mpt);

    auto logicSrc = new G4LogicalVolume(solidSrc, vacuum, "XRaySource");
    new G4PVPlacement(nullptr, {}, logicSrc, "XRaySource",
                      logicWorld, false, 0);

    return physWorld;
}

void DetectorConstruction::DefineMaterials()
{
    // Nothing custom – rely on NIST manager
}
