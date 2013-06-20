////////////////////////////////////////////////////////////////////////////////
// Filename: objectrendertexture.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTRENDERTEXTURE_H_
#define _OBJECTRENDERTEXTURE_H_

///////////////////////
// MY  INCLUDES //
///////////////////////
#include "renderable.h"

///////////////////////////
// FORWARD DECLARATIONS //
//////////////////////////
class Graphic;
class D3D;
class Camera;
class ShaderManager;
class RenderTexture;


////////////////////////////////////////////////////////////////////////////////
//  Name: ObjectRenderTexture
////////////////////////////////////////////////////////////////////////////////
class ObjectRenderTexture : public Renderable
{
public:
	ObjectRenderTexture(D3D* d3d, int textureWidth, int textureHeight, float screenDepth, float screenNear);
	ObjectRenderTexture(const ObjectRenderTexture&);
	~ObjectRenderTexture();

	bool Render(GraphicsManager& graphicsmanagermanager, int renderPass);

private:
	RenderTexture* m_RenderTexture;

	virtual bool RenderObjectsToTexture(GraphicsManager& graphicsmanager, int renderPass);
};

#endif