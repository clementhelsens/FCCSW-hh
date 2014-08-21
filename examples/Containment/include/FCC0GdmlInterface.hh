#ifndef FCC0GdmlInterface_H
#define FCC0GdmlInterface_H

#include <string>

class FCC0GdmlInterface {
public:
	FCC0GdmlInterface();
	void WriteGDML(std::string fileName="",std::string volName="");
};

#endif
