#ifndef XMLHandlerStore_H
#define XMLHandlerStore_H

class XMLHandler;

#include <map>
#include <string>

#include <xercesc/dom/DOM.hpp>

using namespace xercesc;

typedef std::map<std::string,XMLHandler*,std::less<std::string> > handlerStore;

class XMLHandlerStore:public handlerStore {
public:
	static XMLHandlerStore* GetHandlerStore();
	void RegisterHandler(XMLHandler*);
	XMLHandler* GetHandler(DOMNode *);
	void Handle(DOMNode *);
private:
	XMLHandlerStore();
	static XMLHandlerStore *theStore;
};

#endif
