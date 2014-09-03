export DD4hepINSTALL=`dirname $DD4hepLibs`
export CLHEP_DIR=`dirname $CLHEPlibs`
export G4INSTALL=`dirname $Geant4libs`
export PYTHONPATH=$MYLOCALDIR/scripts:${DD4hepINSTALL}/python/DDG4/python:$PYTHONPATH
export LD_LIBRARY_PATH=$MYLOCALDIR/install/lib:$LD_LIBRARY_PATH
export PATH=$MYLOCALDIR/install/bin:$PATH
