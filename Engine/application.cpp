////////////////////////////////////////////////////////////////////////////////
// Filename: application.cpp
//// Code Adapted from a variety of tutorials on http://www.rastertek.com
////////////////////////////////////////////////////////////////////////////////
#include "application.h"
#include "InputManager.h"
#include "camera.h"
#include "position.h"
#include "timer.h"
#include "Fps.h"
#include "cpumanager.h"
#include "sound.h"

Application::Application()
{
	m_GraphicsManager = 0;

	m_Input = 0;
	m_Camera = 0;
	m_Position = 0;
	
	m_Timer = 0;
	m_Fps = 0;
	m_CpuManager = 0;
}


Application::Application(const Application& other)
{
}


Application::~Application()
{
}


bool Application::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	D3DXMATRIX baseViewMatrix;
	float cameraX, cameraY, cameraZ;

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new Input;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}


	// Create the camera object.
	m_Camera = new Camera;
	if(!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Set the initial position of the camera.
	cameraX = 128.0f;
	cameraY = 20.0f;
	cameraZ = 128.0f;

	//m_Camera->SetPosition(cameraX, cameraY, cameraZ);
	

	// Create the graphicsmanager object.  This object will handle rendering all the graphicsmanager for this application.
	m_GraphicsManager = new GraphicsManager;
	if(!m_GraphicsManager)
	{
		return false;
	}

	// Initialize the graphicsmanager object.
	result = m_GraphicsManager->Initialize(m_Camera, screenWidth, screenHeight, hwnd);
	if(!result)
	{
		return false;
	}

	// Create the timer object.
	m_Timer = new Timer;
	if(!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new Position();
	if(!m_Position)
	{
		return false;
	}

	// Set the initial position of the viewer to the same as the initial camera position.
	m_Position->SetPosition(cameraX, cameraY, cameraZ);

	// Create the fps object.
	m_Fps = new Fps();
	if(!m_Fps)
	{
		return false;
	}

	// Create the cpumanager object.
	m_CpuManager = new CpuManager;
	if(!m_CpuManager)
	{
		return false;
	}

	// Initialize the cpumanager object.
	m_CpuManager->Initialize();

	//	// Create the sound object.
	//m_Sound = new Sound;
	//if(!m_Sound)
	//{
	//	return false;
	//}
 //
	//// Initialize the sound object.
	//result = m_Sound->Initialize(hwnd);
	//if(!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
	//	return false;
	//}

	return true;
}


void Application::Shutdown()
{
	//// Release the sound object.
	//if(m_Sound)
	//{
	//	m_Sound->Shutdown();
	//	delete m_Sound;
	//	m_Sound = 0;
	//}

	// Release the cpumanager object.
	if(m_CpuManager)
	{
		m_CpuManager->Shutdown();
		delete m_CpuManager;
		m_CpuManager = 0;
	}

	// Release the fps object.
	if(m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Release the position object.
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the timer object.
	if(m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the graphicsmanager object.
	if(m_GraphicsManager)
	{
		m_GraphicsManager->Shutdown();
		delete m_GraphicsManager;
		m_GraphicsManager = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool Application::Frame()
{
	bool result;


	// Read the user input.
	result = m_Input->Frame();
	if(!result)
	{
		return false;
	}
	
	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Update the system stats.
	m_Timer->Update();
	m_Fps->Update();
	m_CpuManager->Update();

	// Do the frame input processing.
	result = HandleInput(m_Timer->GetTime());
	if(!result)
	{
		return false;
	}
	int mouseX, mouseY;
	m_Input->GetMouseLocation(mouseX, mouseY);

	// Do the frame processing for the graphicsmanager object.
	result = m_GraphicsManager->Frame(m_Camera, m_Input, m_Fps->GetFps(), m_CpuManager->GetCpuUsage(), m_Timer->GetTime(), mouseX, mouseY);
	if(!result)
	{
		return false;
	}

	return result;
}


bool Application::HandleInput(float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;


	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Position based movement.
	keyDown = m_Input->IsWKeyPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsSKeyPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsAKeyPressed();
	m_Position->StrafeLeft(keyDown);

	keyDown = m_Input->IsDKeyPressed();
	m_Position->StrafeRight(keyDown);

	keyDown = m_Input->IsSpacePressed();
	m_Position->MoveUpward(keyDown);
	
	keyDown = m_Input->IsLShiftPressed();
	m_Position->MoveDownward(keyDown);

	// Rotation based movement.
	keyDown = m_Input->IsUpArrowPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsDownArrowPressed();
	m_Position->LookDownward(keyDown);

	keyDown = m_Input->IsLeftArrowPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightArrowPressed();
	m_Position->TurnRight(keyDown);
	
	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);


	return true;
}