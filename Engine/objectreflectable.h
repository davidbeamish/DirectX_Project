////////////////////////////////////////////////////////////////////////////////
// Filename: objectreflectable.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTREFLECTABLE_H_
#define _OBJECTREFLECTABLE_H_


///////////////////////
// MY  INCLUDES //
///////////////////////

#include "renderable.h"


class Graphic;
class D3D;
class Camera;
class ShaderManager;
class Model;
class RenderTexture;
/////////////
// GLOBALS //
/////////////

////////////////////////////////////////////////////////////////////////////////
//  name: objectreflectable
////////////////////////////////////////////////////////////////////////////////
class ObjectReflectable : public Renderable
{
public:
	ObjectReflectable (D3D* m_D3D, HWND hwnd, char* modelFilename, WCHAR* textureFilename);
	ObjectReflectable (const ObjectReflectable &);
	~ObjectReflectable ();

	bool Render();
	bool Render(GraphicsManager& graphicsManager, int renderPass);

	void SetPosition(float x, float y, float z);
	D3DXVECTOR3 GetPosition();

	void SetRotation(float rotationX, float rotationY, float rotationZ);

private:

	Model* m_Model;
	RenderTexture* m_RenderTexture;

	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
};

#endif