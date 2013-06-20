////////////////////////////////////////////////////////////////////////////////
// Filename: objectterrain.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTTERRAIN_H_
#define _OBJECTTERRAIN_H_


///////////////////////
// MY  INCLUDES //
///////////////////////

#include "renderable.h"

class Graphic;
class D3D;
class Camera;
class ShaderManager;
class Terrain;
class RenderTexture;

/////////////
// GLOBALS //
/////////////

////////////////////////////////////////////////////////////////////////////////
//  name: objectterrain
////////////////////////////////////////////////////////////////////////////////
class ObjectTerrain : public Renderable
{
public:
	ObjectTerrain(D3D* m_D3D, char* heightMapFilename, WCHAR* grassTextureFilename, WCHAR* slopeTextureFilename, WCHAR* rockTextureFilename, 
		               char* colorMapFilename, WCHAR* detailMapFilename, WCHAR* normalFilename);
	ObjectTerrain(D3D* m_D3D, int terrainWidth, int terrainHeight, WCHAR* grassTextureFilename, WCHAR* slopeTextureFilename, WCHAR* rockTextureFilename, 
		char* colorMapFilename, WCHAR* detailMapFilename, WCHAR* normalFilename);
	ObjectTerrain(const ObjectTerrain&);
	~ObjectTerrain();

	bool Render(GraphicsManager& graphicsManager, int renderPass);

	void SetPosition(float x, float y, float z);

	Terrain* GetTerrain() const;
	float GetMeanTerrainHeight() const;

private:
	Terrain* m_Terrain;
};

#endif