////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
// Code Adapted from tutorial http://www.rastertek.com/dx11tut02.html
////////////////////////////////////////////////////////////////////////////////
#include "system.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	System* system;
	bool result;
	
	
	// Create the system object.
	system = new System;
	if(!system)
	{
		return 0;
	}

	// Initialize and run the system object.
	result = system->Initialize();
	if(result)
	{
		system->Run();
	}

	// Shutdown and release the system object.
	system->Shutdown();
	delete system;
	system = 0;

	return 0;
}