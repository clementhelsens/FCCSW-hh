FCCSW-hh FCC example 0
==================

Source the setup script:

    source setup.sh


Create build and install directories:

    mkdir build
    mkdir install
    cd build

Compile and install

    cmake -DGEANT4_DIR=/afs/cern.ch/sw/lcg/external/geant4/10.0.p02/x86_64-slc6-gcc47-opt-MT/lib64/Geant4-10.0.2 -DCMAKE_INSTALL_PREFIX=/afs/cern.ch/user/h/helsens/FCCsoft/FCCSOFT/FCC/FCCSW-hh/examples/Containment/install/ -DXERCESC_ROOT_DIR=/afs/cern.ch/sw/lcg/external/XercesC/3.1.1p2/x86_64-slc6-gcc47-opt/  ..
    make -j 4
    make install