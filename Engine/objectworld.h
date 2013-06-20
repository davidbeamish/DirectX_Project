////////////////////////////////////////////////////////////////////////////////
// Filename: objectworld.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTWORLD_H_
#define _OBJECTWORLD_H_


///////////////////////
// MY  INCLUDES //
///////////////////////

#include "renderable.h"

class Graphic;
class D3D;
class Camera;
class ShaderManager;
class Terrain;
class Clouds;
class SkyDome;

/////////////
// GLOBALS //
/////////////

////////////////////////////////////////////////////////////////////////////////
//  name: objectworld
////////////////////////////////////////////////////////////////////////////////
class ObjectWorld : public Renderable
{
public:
	ObjectWorld(D3D* m_D3D, HWND hwnd);
	ObjectWorld(const ObjectWorld&);
	~ObjectWorld();

	void Frame();

	bool Render();
	bool Render(GraphicsManager& graphicsManager, int renderPass);

private:
	/*ObjectTerrain* m_ObjectTerrain;
	ObjectSkyDome* m_ObjectSkyDome;
	ObjectClouds* m_ObjectClouds;*/

	Terrain* m_Terrain;
	SkyDome* m_SkyDome;
	Clouds* m_Clouds;
};

#endif