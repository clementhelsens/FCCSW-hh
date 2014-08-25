#include "VisualizationHandler.h"

static VisualizationHandler mats("Visualization");

VisualizationHandler::VisualizationHandler(std::string s):XMLHandler(s)
{
	AddSupportedHandler("color");
	AddSupportedHandler("visAttributes");
}

void VisualizationHandler::ElementHandle()
{
}
