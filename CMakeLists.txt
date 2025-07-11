cmake_minimum_required(VERSION 3.16)
project(GammaXRayProject)

find_package(Geant4 REQUIRED ui_all vis_all)
find_package(PhotonProcess REQUIRED)

include(${Geant4_USE_FILE})

add_executable(GammaXRay
    src/main.cc
    src/DetectorConstruction.cc
    src/PhysicsList.cc
    src/PrimaryGeneratorAction.cc
    src/ActionInitialization.cc)

target_include_directories(GammaXRay PUBLIC src)          # include
target_link_libraries(GammaXRay
    PUBLIC ${Geant4_LIBRARIES} PhotonProcess::PhotonProcess)

install(TARGETS GammaXRay DESTINATION bin)
