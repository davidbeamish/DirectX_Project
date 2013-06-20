////////////////////////////////////////////////////////////////////////////////
// Filename: InputManager.h
// Code Adapted from tutorial http://www.rastertek.com/dx11tut13.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUT_H_
#define _INPUT_H_

//---------------------------------------------------------------------------//
//                          Pre-Processing Directives						 //
//---------------------------------------------------------------------------//
#define DIRECTINPUT_VERSION 0x0800


//---------------------------------------------------------------------------//
//									Linking									 //
//---------------------------------------------------------------------------//
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


//---------------------------------------------------------------------------//
//								   Includes									 //
//---------------------------------------------------------------------------//
#include <dinput.h>


//---------------------------------------------------------------------------//
//                               Class: Input								 //
//---------------------------------------------------------------------------//
class Input
{
public:
	Input(const HINSTANCE hinstance, const HWND hwnd, const int screenWidth, const int screenHeight);
	Input(const Input&);
	~Input();

	bool Update();

	bool IsEscapePressed();
	bool IsUpArrowPressed();
	bool IsDownArrowPressed();
	bool IsLeftArrowPressed();
	bool IsRightArrowPressed();
	bool IsWKeyPressed();
	bool IsSKeyPressed();
	bool IsAKeyPressed();
	bool IsDKeyPressed();
	bool IsQKeyPressed();
	bool IsEKeyPressed();
	bool IsRKeyPressed();
	bool IsFKeyPressed();
	bool IsTKeyPressed();
	bool IsSpacePressed();
	bool IsLShiftPressed();
	bool IsLeftMousePressed();
	bool IsRightMousePressed();
	
	void GetMouseLocation(int&, int&) const;

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};

#endif