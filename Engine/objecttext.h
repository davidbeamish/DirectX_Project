////////////////////////////////////////////////////////////////////////////////
// Filename: objecttext.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTTEXT_H_
#define _OBJECTTEXT_H_


///////////////////////
// MY  INCLUDES //
///////////////////////

#include "renderable.h"

class Graphic;
class D3D;
class Camera;
class ShaderManager;
class Text;


/////////////
// GLOBALS //
/////////////

////////////////////////////////////////////////////////////////////////////////
//  name: objecttext
////////////////////////////////////////////////////////////////////////////////
class ObjectText : public Renderable
{
public:
	ObjectText(D3D* m_D3D, Camera* m_Camera, HWND hwnd, int screenWidth, int screenHeight);
	ObjectText(const ObjectText&);
	~ObjectText();

	bool Render();
	bool Render(GraphicsManager& graphicsManager, int renderPass);
	bool Frame(D3D* m_D3D, int fps, int cpumanager, int mouseX, int mouseY, bool collision);

	void SetPosition(float x, float y, float z);

private:
	bool SetFps(int fps, ID3D11DeviceContext* deviceContext);
	bool SetCpuManager(int cpumanager, ID3D11DeviceContext* deviceContext);
	bool SetCameraPosition(float posX, float posY, float posZ, ID3D11DeviceContext* deviceContext);
	bool SetCameraRotation(float rotX, float rotY, float rotZ, ID3D11DeviceContext* deviceContext);

	Text* m_Text;
	float m_positionX, m_positionY, m_positionZ;

};

#endif