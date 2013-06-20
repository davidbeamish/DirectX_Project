////////////////////////////////////////////////////////////////////////////////
// Filename: input.cpp
// Code Adapted from tutorial http://www.rastertek.com/dx11tut13.html
////////////////////////////////////////////////////////////////////////////////
#include "InputManager.h"


Input::Input(const HINSTANCE hinstance, const HWND hwnd, const int screenWidth, const int screenHeight)
{
	// Store the screen size which will be used for positioning the mouse cursor.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Initialize the location of the mouse on the screen.
	m_mouseX = 0,
	m_mouseY = 0;

	// Initialize the main direct input interface.
	DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);

	// Initialize the direct input interface for the keyboard.
	m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	
	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	
	// Set the cooperative level of the keyboard to not share with other programs and acquire the keyboard.
	m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	m_keyboard->Acquire();
	
	// Initialize the direct input interface for the mouse.
	m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);

	// Set the data format for the mouse using the pre-defined mouse data format.
	m_mouse->SetDataFormat(&c_dfDIMouse);

	// Set the cooperative level of the mouse to share with other programs and acquire the mouse.
	m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_mouse->Acquire();
}


Input::Input(const Input& other)
{
}


Input::~Input()
{
	// Release the mouse.
	if(m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	// Release the keyboard.
	if(m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	// Release the main interface to direct input.
	if(m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}
}


//bool Input::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
//{
//	// Store the screen size which will be used for positioning the mouse cursor.
//	m_screenWidth = screenWidth;
//	m_screenHeight = screenHeight;
//
//	// Initialize the location of the mouse on the screen.
//	m_mouseX = 0;
//	m_mouseY = 0;
//
//	// Initialize the main direct input interface.
//	HRESULT result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
//	if(FAILED(result))
//	{
//		return false;
//	}
//
//	// Initialize the direct input interface for the keyboard.
//	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
//	if(FAILED(result))
//	{
//		return false;
//	}
//
//	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
//	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
//	if(FAILED(result))
//	{
//		return false;
//	}
//
//	// Set the cooperative level of the keyboard to not share with other programs.
//	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
//	if(FAILED(result))
//	{
//		return false;
//	}
//
//	// Now acquire the keyboard.
//	result = m_keyboard->Acquire();
//	if(FAILED(result))
//	{
//		return false;
//	}
//
//	// Initialize the direct input interface for the mouse.
//	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
//	if(FAILED(result))
//	{
//		return false;
//	}
//
//	// Set the data format for the mouse using the pre-defined mouse data format.
//	result = m_mouse->SetDataFormat(&c_dfDIMouse);
//	if(FAILED(result))
//	{
//		return false;
//	}
//
//	// Set the cooperative level of the mouse to share with other programs.
//	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
//	if(FAILED(result))
//	{
//		return false;
//	}
//
//	// Acquire the mouse.
//	result = m_mouse->Acquire();
//	if(FAILED(result))
//	{
//		return false;
//	}
//
//	return true;
//}


//void Input::Shutdown()
//{
//	// Release the mouse.
//	if(m_mouse)
//	{
//		m_mouse->Unacquire();
//		m_mouse->Release();
//		m_mouse = NULL;
//	}
//
//	// Release the keyboard.
//	if(m_keyboard)
//	{
//		m_keyboard->Unacquire();
//		m_keyboard->Release();
//		m_keyboard = NULL;
//	}
//
//	// Release the main interface to direct input.
//	if(m_directInput)
//	{
//		m_directInput->Release();
//		m_directInput = NULL;
//	}
//}


bool Input::Update()
{
	// Read the current state of the keyboard.
	bool result = ReadKeyboard();
	if(!result)
	{
		return false;
	}

	// Read the current state of the mouse.
	result = ReadMouse();
	if(!result)
	{
		return false;
	}

	// Process the changes in the mouse and keyboard.
	ProcessInput();

	return true;
}


bool Input::ReadKeyboard()
{
	// Read the keyboard device.
	HRESULT result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if(FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
		
	return true;
}


bool Input::ReadMouse()
{
	// Read the mouse device.
	HRESULT result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if(FAILED(result))
	{
		// If the mouse lost focus or was not acquired then try to get control back.
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

void Input::ProcessInput()
{
	// Update the location of the mouse cursor based on the change of the mouse location during the frame.
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	// Ensure the mouse location doesn't exceed the screen width or height.
	if(m_mouseX < 0) 
		m_mouseX = 0; 
	if(m_mouseY < 0)  
		m_mouseY = 0;
	if(m_mouseX > m_screenWidth) 
		m_mouseX = m_screenWidth;
	if(m_mouseY > m_screenHeight) 
		m_mouseY = m_screenHeight;
	
	return;
}

bool Input::IsLeftMousePressed()
{
	// Check if the left mouse button is currently pressed.
	if(m_mouseState.rgbButtons[0] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsRightMousePressed()
{
	// Check if the left mouse button is currently pressed.
	if(m_mouseState.rgbButtons[1] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsEscapePressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsUpArrowPressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_UP] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsDownArrowPressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_DOWN] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsLeftArrowPressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_LEFT] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsRightArrowPressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_RIGHT] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsWKeyPressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_W] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsSKeyPressed()
	{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_S] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsAKeyPressed()
	{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_A] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsDKeyPressed()
	{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_D] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsQKeyPressed()
	{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_Q] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsEKeyPressed()
	{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_E] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsRKeyPressed()
	{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_R] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsFKeyPressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_F] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsTKeyPressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_T] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsSpacePressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_SPACE] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsLShiftPressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_LSHIFT] & 0x80)
	{
		return true;
	}

	return false;
}

void Input::GetMouseLocation(int& mouseX, int& mouseY) const
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;
	return;
}

