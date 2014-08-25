#include "MaterialsHandler.h"

static MaterialsHandler mats("Materials");

MaterialsHandler::MaterialsHandler(std::string s):XMLHandler(s)
{
	AddSupportedHandler("element");
	AddSupportedHandler("mixture");
}

void MaterialsHandler::ElementHandle()
{
}
