export MYPATH=/afs/cern.ch/user/s/solans/FCC/fccsw-hh

export DD4hepINSTALL=`dirname $DD4hepLibs`
export CLHEP_DIR=`dirname $CLHEPlibs`
export G4INSTALL=`dirname $Geant4libs`
export G4LEDATA=${G4INSTALL}/share/Geant4-9.6.3/data/G4EMLOW6.32
export G4LEVELGAMMADATA=${G4INSTALL}/share/Geant4-9.6.3/data/PhotonEvaporation2.3
export G4SAIDXSDATA=${G4INSTALL}/share/Geant4-9.6.3/data/G4SAIDDATA1.1  
export PYTHONPATH=$MYPATH/scripts:${DD4hepINSTALL}/python/DDG4/python:$PYTHONPATH
export LD_LIBRARY_PATH=$MYPATH/install/lib:$LD_LIBRARY_PATH
export PATH=$MYPATH/install/bin:$PATH
