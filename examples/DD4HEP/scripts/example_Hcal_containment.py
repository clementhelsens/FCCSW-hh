#!/usr/bin/env python
#
# DD4hep example setup using the python configuration
#
# Carlos.Solans@cern.ch
# Based on the example by M.Frank
# 
################################################################
 
import os
import time
import DDG4
from SystemOfUnits import *
import argparse

# Parse arguments
parser = argparse.ArgumentParser()
#parser.add_argument("--compactpath", help="path to compact files", default=".:./compact")
parser.add_argument("--outputfile", default="FCC_HCAL_"+time.strftime("%Y-%m-%d_%H-%M")+".root")
args = parser.parse_args()

# Load DDG4
kernel = DDG4.Kernel()
kernel.UI = "UI"
kernel.loadGeometry("file:./compact/FCCDectOpt02.xml")
kernel.loadGeometry("file:./compact/HCal_Barrel.xml")
kernel.loadGeometry("file:./compact/HCal_Barrel_Shell.xml")
kernel.loadXML("file:%s/examples/DDG4/examples/DDG4_field.xml" %os.environ['DD4hepINSTALL'])
kernel.printProperties()
lcdd = kernel.lcdd()

# Configure UI
ui = DDG4.Action(kernel,"Geant4UIManager/UI")
ui.HaveVIS = True
ui.HaveUI = True
ui.SessionType = 'csh'
kernel.registerGlobalAction(ui)

# Configure I/O
evt_root = DDG4.EventAction(kernel,'Geant4Output2ROOT/RootOutput')
evt_root.Control = True
evt_root.Output = args.outputfile
evt_root.enableUI()
kernel.eventAction().add(evt_root)

# Setup particle gun
gun = DDG4.GeneratorAction(kernel,"Geant4ParticleGun/Gun")
gun.energy   = 100*GeV
gun.particle = 'pi-'
gun.multiplicity = 1
gun.position = (0*mm,0*mm,0*mm)
gun.isotrop = True
gun.enableUI()
kernel.generatorAction().add(gun)

# Setup global filters fur use in sensntive detectors
f1 = DDG4.Filter(kernel,'GeantinoRejectFilter/GeantinoRejector')
f2 = DDG4.Filter(kernel,'EnergyDepositMinimumCut')
f2.Cut = 1e-14*keV
f2.enableUI()
kernel.registerGlobalFilter(f1)
kernel.registerGlobalFilter(f2)

# Now the calorimeters
seq = DDG4.SensitiveSequence(kernel,'Geant4SensDetActionSequence/HcalBarrel')
act = DDG4.SensitiveAction(kernel,'Geant4SimpleCalorimeterAction/HcalBarrelHandler','HcalBarrel')
seq.add(f1)  # ignore geantinos
#seq.add(f2)  # ignore particles below threshold
seq.add(act)

# Containment shell to detect escaping particles
seq = DDG4.SensitiveSequence(kernel,'Geant4SensDetActionSequence/HcalBarrelShell')
act = DDG4.SensitiveAction(kernel,'Geant4EscapeCounter/ShellHandler','HcalBarrelShell')
seq.add(act)

# Now build the physics list:
phys = kernel.physicsList()
phys.extends = 'QGSP_BERT'
#phys.transportation = True
#phys.decays  = True

phys.enableUI()

  
ph = DDG4.PhysicsList(kernel,'Geant4PhysicsList/Myphysics')
ph.addParticleConstructor('G4BosonConstructor')
ph.addParticleConstructor('G4LeptonConstructor')
ph.addParticleConstructor('G4MesonConstructor')
ph.addParticleConstructor('G4BaryonConstructor')
ph.addParticleProcess('e[+-]','G4eMultipleScattering',-1,1,1)
#ph.addParticleProcess('e[+-]','G4eIonisation',-1,2,2)
ph.addParticleProcess('mu[+-]','G4MuMultipleScattering',-1,1,1)
#ph.addParticleProcess('mu[+-]','G4MuIonisation',-1,2,2)
ph.addParticleProcess('pi[+-]','G4hMultipleScattering',-1,2,2)
#ph.addParticleProcess('pi[+-]','G4hIonisation',-1,2,2)
ph.addParticleProcess('pi[+-]','G4hBremsstrahlung',-1,3,3)
ph.addParticleProcess('proton','G4hMultipleScattering',-1,2,2)
#ph.addParticleProcess('proton','G4hIonisation',-1,2,2)
ph.addParticleProcess('proton','G4hBremsstrahlung',-1,3,3)
ph.enableUI()
phys.add(ph)


phys.dump()

kernel.configure()
kernel.initialize()
kernel.run()
kernel.terminate()

