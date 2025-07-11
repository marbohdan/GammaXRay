#include "PhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "BreitWheeler.hh"
#include "BlackBody.hh"
#include "G4Gamma.hh"

#include "G4SystemOfUnits.hh"      
#include "G4ProcessManager.hh"     

PhysicsList::PhysicsList()
{
    defaultCutValue = 0.1*mm;

    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4DecayPhysics());

    // 10 keV (kT = 0.01 MeV) black-body photon field
    auto field = new BlackBody(0.01, 1e-3, 100., 200, 100);
    auto bw    = new BreitWheeler(field);

    G4Gamma::Gamma()->GetProcessManager()->AddDiscreteProcess(bw);
}
