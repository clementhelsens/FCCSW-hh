#ifndef GdmlInterface_H
#define GdmlInterface_H

#include <string>

class GdmlInterface {
public:
	GdmlInterface();
	void WriteGDML(std::string fileName="",std::string volName="");
};

#endif
