////////////////////////////////////////////////////////////////////////////////
// Filename: objectdebugwindow.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTDEBUGWINDOW_H_
#define _OBJECTDEBUGWINDOW_H_


///////////////////////
// MY  INCLUDES //
///////////////////////
#include "renderable.h"

/////////////
// GLOBALS //
/////////////
class Graphic;
class D3D;
class Camera;
class ShaderManager;
class DebugWindow;
class RenderTexture;

////////////////////////////////////////////////////////////////////////////////
//  name: objectdebugwindow
////////////////////////////////////////////////////////////////////////////////
class ObjectDebugWindow : public Renderable
{
public:
	ObjectDebugWindow(D3D* m_D3D, int screenWidth, int screenHeight, int bitmapWidth, int bitmapHeight);
	ObjectDebugWindow(const ObjectDebugWindow&);
	~ObjectDebugWindow();

	bool Render(GraphicsManager& graphicsManager, int renderPass);

	void SetPosition(float x, float y, float z);

private:

	DebugWindow* m_DebugWindow;
	RenderTexture* m_RenderTexture;

	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
};

#endif