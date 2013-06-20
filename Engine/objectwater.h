////////////////////////////////////////////////////////////////////////////////
// Filename: objectwater.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTWATER_H_
#define _OBJECTWATER_H_

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
class Water;
class RenderTexture;


////////////////////////////////////////////////////////////////////////////////
//  name: objectwater
////////////////////////////////////////////////////////////////////////////////
class ObjectWater : public Renderable
{
public:
	ObjectWater(D3D* m_D3D, WCHAR* textureFilename, float waterHeight, float waterRadius);
	ObjectWater(const ObjectWater&);
	~ObjectWater();

	bool Render(GraphicsManager& graphicsManager, int renderPass);
	void Frame();

	float GetWaterHeight();
private:
	Water* m_Water;
	RenderTexture* m_ReflectionTexture, * m_RefractionTexture;

	float m_positionX, m_positionY, m_positionZ;

};

#endif