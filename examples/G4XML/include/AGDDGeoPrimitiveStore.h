#ifndef AGDDGeoPrimitiveStore_H
#define AGDDGeoPrimitiveStore_H

class AGDDGeoPrimitive;

#include <map>
#include <string>

typedef std::map<std::string,AGDDGeoPrimitive* > AGDDGeoPrimitiveMap;

class AGDDGeoPrimitiveStore: public AGDDGeoPrimitiveMap {
public:
	AGDDGeoPrimitiveStore();
	void RegisterGeoPrimitive(AGDDGeoPrimitive *);
	AGDDGeoPrimitive* GetGeoPrimitive(std::string);
	bool Exist(std::string);
	static AGDDGeoPrimitiveStore* GetGeoPrimitiveStore();
private:

};

#endif
