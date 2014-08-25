#ifndef XMLHandler_H
#define XMLHandler_H

#include <string>
#include <xercesc/dom/DOM.hpp>

#include "ExpressionEvaluator.h"

#include <iostream>
#include <vector>

using namespace xercesc;

class XMLHandlerStore;

class XMLHandler {
public:
	XMLHandler(std::string n);
	virtual ~XMLHandler() {}
	std::string GetName() {return _name;}
	
	// Setting ElementHandle to be not fully virtual for testing purposes
	//virtual void ElementHandle()=0;
	virtual void ElementHandle() {std::cout<<"Running default Handle() for "<<_name<<std::endl;}
	virtual void Handle(DOMNode *t) 
	{
		SetCurrentElement(t);
		ElementHandle();
	}
	void StopLoop(bool);
	bool IsLoopToBeStopped();
	
	static void handlerPush(XMLHandler *h) {handlerChain.push_back(h);}
	static void handlerPop() {handlerChain.pop_back();}
	
	std::vector<std::string> supportedHandlers;
	void AddSupportedHandler(std::string s) {supportedHandlers.push_back(s);}
	int NoSupportedHandlers() const {return supportedHandlers.size();}
	std::vector<std::string>::iterator SupportedHandlersBegin() {return supportedHandlers.begin();}
	std::vector<std::string>::iterator SupportedHandlersEnd()   {return supportedHandlers.end();}
	bool FindSupportedHandler(std::string n)
	{
		if (!NoSupportedHandlers()) return true;
		std::vector<std::string>::iterator it=find(supportedHandlers.begin(),supportedHandlers.end(),n);
		return it!=supportedHandlers.end();
	}
	
protected:

	std::string _name;
	bool stopLoop;
	static DOMNode *currentElement;
	static void SetCurrentElement(DOMNode *t) {currentElement=t;}
	static DOMNode *GetCurrentElement() {return currentElement;}
	
	bool isAttribute(const std::string) const;
	
	static std::vector<XMLHandler*> handlerChain;
	
	ExpressionEvaluator& Evaluator() const {static ExpressionEvaluator e; return e;}

	std::string getAttribute(const std::string, bool&) const;
        std::string getAttributeAsString(const std::string) const;
        double getAttributeAsDouble(const std::string) const;
        int getAttributeAsInt(const std::string) const;
        std::vector<double> getAttributeAsVector(const std::string) const;
	std::vector<int> getAttributeAsIntVector(const std::string) const;
	std::string getAttributeAsString(const std::string, bool&) const;
	double getAttributeAsDouble(const std::string, bool&) const;
	int getAttributeAsInt(const std::string, bool&) const;
	std::vector<double> getAttributeAsVector(const std::string, bool&) const;
        std::vector<int> getAttributeAsIntVector(const std::string, bool&) const;
	std::string getAttributeAsString(const std::string, const std::string) const;
	double getAttributeAsDouble(const std::string, const double) const;
	int getAttributeAsInt(const std::string, const int) const;
	std::vector<double> getAttributeAsVector(const std::string, const std::vector<double>) const;
        std::vector<int> getAttributeAsIntVector(const std::string, const std::vector<int>) const;
	static bool printFlag;
private:
	void RegisterToStore();
};

#endif
