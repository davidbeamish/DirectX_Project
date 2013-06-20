////////////////////////////////////////////////////////////////////////////////
// Filename: objectbitmap.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTBITMAP_H_
#define _OBJECTBITMAP_H_


///////////////////////
// MY  INCLUDES //
///////////////////////

#include "renderable.h"

class GraphicsManager;
class D3D;
class Camera;
class ShaderManager;
class Bitmap;

/////////////
// GLOBALS //
/////////////

////////////////////////////////////////////////////////////////////////////////
//  name: objectbitmap
////////////////////////////////////////////////////////////////////////////////
class ObjectBitmap : public Renderable
{
public:
	ObjectBitmap(D3D* m_D3D, int screenWidth, int screenHeight, WCHAR* textureFilename1, int bitmapWidth, int bitmapHeight, int positionX, int positionY, D3DXMATRIX viewMatrix);
	ObjectBitmap(const ObjectBitmap&);
	~ObjectBitmap();

	bool Render(GraphicsManager& graphicsManager, int renderPass);
	void SetPosition(int posX, int posY);

private:
	Bitmap* m_Bitmap;

	int m_positionX, m_positionY;
	D3DXMATRIX m_viewMatrix;

};

#endif