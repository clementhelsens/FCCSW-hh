LOCALDIR=$PWD
source /afs/cern.ch/sw/lcg/external/gcc/4.7/x86_64-slc6-gcc47-opt/setup.sh   /afs/cern.ch/sw/lcg/external
cd /afs/cern.ch/sw/lcg/external/geant4/10.0.p02/x86_64-slc6-gcc47-opt-MT/bin
source geant4.sh
cd $LOCALDIR

XERCESClibs=/afs/cern.ch/sw/lcg/external/XercesC/3.1.1p2/x86_64-slc6-gcc47-opt/lib/
Geant4libs=/afs/cern.ch/sw/lcg/external/geant4/10.0.p02/x86_64-slc6-gcc47-opt-MT/lib64/
CLHEPlibs=/afs/cern.ch/sw/lcg/external/clhep/2.1.4.1/x86_64-slc6-gcc47-opt/lib/

ROOTlibs=/afs/cern.ch/exp/fcc/sw/0.1/ROOT/v5-34-00-patches/x86_64-slc6-gcc48-opt/lib

export LD_LIBRARY_PATH=${Geant4libs}:${ROOTlibs}:${CLHEPlibs}:${XERCESClibs}:${LD_LIBRARY_PATH}


cd ${ROOTlibs}/..
. bin/thisroot.sh

cd $LOCALDIR


# cmake -DGEANT4_DIR=/afs/cern.ch/sw/lcg/external/geant4/10.0.p02/x86_64-slc6-gcc47-opt-MT/lib64/Geant4-10.0.2 -DCMAKE_INSTALL_PREFIX=/afs/cern.ch/user/h/helsens/FCCsoft/FCCSOFT/FCC/FCCSW-hh/examples/Containment/install/ ..
