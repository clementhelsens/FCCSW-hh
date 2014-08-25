#include <iostream>
#include "GdmlInterface.h"

#include "G4TransportationManager.hh"
#include "G4GDMLParser.hh"
#include "G4PhysicalVolumeStore.hh"
#include <stdexcept>

GdmlInterface::GdmlInterface()
{
    std::cout<<" Creating the GdmlInterface "<<std::endl;
}

void GdmlInterface::WriteGDML(std::string fileName,std::string volName)
{
	G4VPhysicalVolume *g4wv;
	if (volName.empty())
		g4wv=G4TransportationManager::GetTransportationManager()
				->GetNavigatorForTracking()->GetWorldVolume();
	else
	{
		G4PhysicalVolumeStore *pvs=G4PhysicalVolumeStore::GetInstance();
		g4wv=pvs->GetVolume(volName);
	}
	if (g4wv)
	{
		if (fileName.empty()) fileName="World.gdml";
		G4GDMLParser gdml;
                
		gdml.Write(fileName,g4wv);
	}
	else
		std::cout<<" Invalid pointer to world volume! "<<std::endl;
}

