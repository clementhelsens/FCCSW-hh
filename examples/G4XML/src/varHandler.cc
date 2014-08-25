#include "varHandler.h"
#include "XMLHandler.h"
#include "XercesParser.h"
#include <iostream>

static varHandler var("var");

varHandler::varHandler(std::string s):XMLHandler(s)
{
}

void varHandler::ElementHandle()
{
	bool bres;
	std::string name=getAttributeAsString("name",bres);
	double res=getAttributeAsDouble("value",bres);
	Evaluator().RegisterConstant(name,res);
	//std::cout<<" var name "<<name<<" calculated value="<<res<<std::endl;
}
