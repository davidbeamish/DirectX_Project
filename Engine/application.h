////////////////////////////////////////////////////////////////////////////////
// Filename: application.h
// Adapted from a variety of tutorials on http://www.rastertek.com/dx11tut13.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATION_H_
#define _APPLICATION_H_


/////////////
// GLOBALS //
/////////////

///////////////////////
// MY  INCLUDES //
///////////////////////
#include "graphicsmanager.h"

///////////////////////
// Forward declarations
///////////////////////
//class GraphicsManager;
class Input;
class Camera;
class Position;
class Timer;
class Fps;
class CpuManager;
class Sound;

////////////////////////////////////////////////////////////////////////////////
//  name: Application
////////////////////////////////////////////////////////////////////////////////
class Application
{
public:
	Application();
	Application(const Application&);
	~Application();

	bool Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight);
	void Shutdown();
	bool Frame();

private:
	bool HandleInput(float frameTime);
	bool RenderGraphicsManager();

private:
	GraphicsManager* m_GraphicsManager;
	Input* m_Input;
	Camera* m_Camera;
	Position* m_Position;

	Timer* m_Timer;
	Fps* m_Fps;
	CpuManager* m_CpuManager;

	Sound* m_Sound;

};

#endif