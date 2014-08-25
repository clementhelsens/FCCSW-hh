#include "msgHandler.h"
#include <iostream>

static msgHandler msg("msg");

msgHandler::msgHandler(std::string s):XMLHandler(s)
{
//	std::cout<<"Creating handler for msg"<<std::endl;
}

void msgHandler::ElementHandle()
{
//	std::cout<<"handling for msg";
	std::string text=getAttributeAsString("text");
	std::string expression=getAttributeAsString("expression");
	std::cout<<" msg: "<<text<<std::endl;
}
