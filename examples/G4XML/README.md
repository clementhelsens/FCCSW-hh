FCCSW-hh FCC example G4XML
==================

This is a modified version of the Geant4 example B1 which was modified to support an XML driven
geometry interface. the original detector description class was replaced with a totally generic
XMLDetectorDescription class which does nothing more than fetching a World volume as described 
in an XML file. the example comes with three XML files that show how to define materials
(material.xml), how to define a totally bogus geometry (geometry.xml) and how to set visualization
attributes (visualization.xml). To run the example (from the build directory), provide a 
colon-spearated list of XML files from the command line (-XML_files option)

./exampleB1 -XML_files material.xml:geometry.xml:visualization.xml

The example comes with predifined build and install directories. To build it just: 

Source the setup script:

    source setup.sh

    cd build

Compile and install:

    cmake -DGEANT4_DIR=/afs/cern.ch/sw/lcg/external/geant4/10.0.p02/x86_64-slc6-gcc47-opt-MT/lib64/Geant4-10.0.2 -DCMAKE_INSTALL_PREFIX=/afs/cern.ch/user/h/helsens/FCCsoft/FCCSOFT/FCC/FCCSW-hh/examples/Containment/install/ -DXERCESC_ROOT_DIR=/afs/cern.ch/sw/lcg/external/XercesC/3.1.1p2/x86_64-slc6-gcc47-opt/  ..
    make -j 4
    make install
    
to visualize the geometry I use FreeWRL on an iMac but any other Geant4-supported graphics system 
can be used. An interface to Root via GDML is being envisaged.

ADA 2015-08-25
