////////////////////////////////////////////////////////////////////////////////
// Filename: objectcursor.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTCURSOR_H_
#define _OBJECTCURSOR_H_


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
//  name: objectcursor
////////////////////////////////////////////////////////////////////////////////
class ObjectCursor : public Renderable
{
public:
	ObjectCursor(D3D* m_D3D, int screenWidth, int screenHeight, WCHAR* textureFilename1, int bitmapWidth, int bitmapHeight, int positionX, int positionY, D3DXMATRIX viewMatrix);
	ObjectCursor(const ObjectCursor&);
	~ObjectCursor();

	bool Render(GraphicsManager& graphicsManager, int renderPass);
	void SetPosition(int x, int y);

private:
	Bitmap* m_Bitmap;
	D3DXMATRIX m_viewMatrix;
	int m_positionX, m_positionY;

};

#endif //_OBJECTCURSOR_H_