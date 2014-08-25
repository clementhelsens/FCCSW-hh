#include "AGDDGeoPrimitiveStore.h"
#include "AGDDGeoPrimitive.h"
#include <iostream>

AGDDGeoPrimitiveStore::AGDDGeoPrimitiveStore()
{
}

void AGDDGeoPrimitiveStore::RegisterGeoPrimitive(AGDDGeoPrimitive *v)
{
	std::string name=v->GetName();
	(*this)[name]=v;
}

bool AGDDGeoPrimitiveStore::Exist(std::string n)
{
	return ((*this).find(n) != (*this).end());
}

AGDDGeoPrimitive* AGDDGeoPrimitiveStore::GetGeoPrimitive(std::string name)
{
	if ((*this).find(name) != (*this).end())
		return (*this)[name];
	else
	{
		std::cout << " GeoPrimitive "<<name<<" not found: returning 0"<<std::endl;
		return 0;
	}
}

AGDDGeoPrimitiveStore* AGDDGeoPrimitiveStore::GetGeoPrimitiveStore()
{
	static AGDDGeoPrimitiveStore* thePointer=new AGDDGeoPrimitiveStore();
	return thePointer;
}
