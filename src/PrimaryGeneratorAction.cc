#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    fGun = new G4ParticleGun(1);

    auto gamma = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
    fGun->SetParticleDefinition(gamma);
    fGun->SetParticleEnergy(100.*MeV);
    fGun->SetParticleMomentumDirection({0.,0.,1.});
    fGun->SetParticlePosition({0.,0.,-50.*cm});
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() { delete fGun; }

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* evt)
{
    fGun->GeneratePrimaryVertex(evt);
}

