#ifndef AGDDGeoPrimitive_H
#define AGDDGeoPrimitive_H

#include <string>
#include <vector>


class AGDDGeoPrimitive {
public:
	AGDDGeoPrimitive(std::string s):_name(s) {}
	virtual ~AGDDGeoPrimitive() {}
	void SetName(std::string s) {_name=s;}
	std::string GetName() {return _name;}
        virtual void* Create() =0;
protected:
	std::string _name;
	void* thePrimitive;
};

#endif
