#include "XMLHandlerStore.h"
#include "XMLHandler.h"

#include <iostream>

XMLHandlerStore* XMLHandlerStore::theStore=0;

XMLHandlerStore::XMLHandlerStore()
{
}

XMLHandlerStore* XMLHandlerStore::GetHandlerStore()
{
	if (!theStore) theStore=new XMLHandlerStore;
	return theStore;
}

void XMLHandlerStore::RegisterHandler(XMLHandler* handler)
{
	std::string name=handler->GetName();
	if (this->find(name)!=this->end()) 
		std::cout<<" handler "<<name<<" already defined!"<<std::cout;
	else
		(*this)[name]=handler;
}

void XMLHandlerStore::Handle(DOMNode *element)
{
	char* temp=XMLString::transcode(element->getNodeName());
	std::string name=temp;
	XMLString::release(&temp);
	if (this->find(name)!=this->end()) 
		((*this)[name])->Handle(element);
	else
		std::cout<<" Handler for "<<name<<" not found! continuing"<<std::endl;
}

XMLHandler* XMLHandlerStore::GetHandler(DOMNode *element)
{
        char* temp=XMLString::transcode(element->getNodeName());
        std::string name=temp;
        XMLString::release(&temp);
	if (this->find(name)!=this->end()) 
		return (*this)[name];
	else
	{
		std::cout<<" Handler for "<<name<<" not found! continuing"<<std::endl;
		return 0;
	}
}

