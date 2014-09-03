FCCSW-hh Example DD4HEP
==================

### GeoDisplay (DD4HEP)

Source the setup script:

    source /afs/cern.ch/exp/fcc/sw/0.1/setup.sh

Export the absolute path to the installation directory 

    export MYLOCALDIR=`dirname $PWD`
    export MYINSTALLDIR=`dirname $PWD`/install

Create build and install directories:

    mkdir build
    mkdir install
    cd build

Compile and install

    cmake -DCMAKE_INSTALL_PREFIX=${MYINSTALLDIR}  -DDD4HEP_USE_BOOST=ON -DDD4HEP_USE_XERCESC=ON -DXERCESC_ROOT_DIR=${location}/XercesC/3.1.1p1/x86_64-slc6-gcc48-opt -DROOTSYS=${location}/ROOT/v5-34-00-patches/x86_64-slc6-gcc48-opt -DDD4HEP_WITH_GEANT4=ON -DCMAKE_PREFIX_PATH=${location}/Geant4/9.6.p03/x86_64-slc6-gcc48-opt -DCMAKE_MODULE_PATH=${location}/DD4hep/v00-06/x86_64-slc6-gcc48-opt ..
    make -j 12
    make install

Export install dir to LD_LIBRARY_PATH and PATH

    export LD_LIBRARY_PATH=${MYINSTALLDIR}/lib:${LD_LIBRARY_PATH}
    export PATH=${MYINSTALLDIR}/bin:${PATH}


At this stage one can run geoDisplay to visualize the geometry being used. Always have the top file FCCDectOpt02.xml first, then just happend any detector (here only HCal_Barrel)

    geoDisplay -compact file:../compact/FCCDectOpt02.xml -compact file:../compact/HCal_Barrel.xml


Or alternatively run the GUI

    python ../script/gui.py

Do not forget to quit the ROOT window (.q) before running an other display


### Simulation (Geant4)

at this point one can run FCChh_sim in batch mode:

    FCChh_sim file:../compact/FCCDectOpt02.xml file:../Hcal_Barrel.xml file:../compact/geant4.xml ../scripts/FCChh.in

or in (Geant4-like) interactive mode:

    FCChh_sim -i file:../compact/FCCDectOpt02.xml file:../Hcal_Barrel.xml file:../compact/geant4.xml ../scripts/FCChh.in

### Simulation with DD4hep

Setup the environment for DDG4

    source scripts/setup_DDG4.sh

Run the DDG4 example

    python scripts/example_Hcal_containment.py

Browse the file in ROOT, (load library and Open the ROOT file)

    root -l
    gSystem->Load("./scripts/DDG4Dict_C")
    TFile *_file0 = TFile::Open("FILENAME.root")       
