////////////////////////////////////////////////////////////////////////////////
// Filename: objectclouds.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTCLOUDS_H_
#define _OBJECTCLOUDS_H_


///////////////////////
// MY  INCLUDES //
///////////////////////

#include "renderable.h"

class Graphic;
class D3D;
class Camera;
class ShaderManager;
class Clouds;





/////////////
// GLOBALS //
/////////////

////////////////////////////////////////////////////////////////////////////////
//  name: objectclouds
////////////////////////////////////////////////////////////////////////////////
class ObjectClouds : public Renderable
{
public:
	ObjectClouds(D3D* m_D3D, WCHAR* textureFilename1, WCHAR* textureFilename2);
	ObjectClouds(const ObjectClouds&);
	~ObjectClouds();

	void Frame();

	bool Render();
	bool Render(Graphics& m_Graphics, int renderPass);


private:
	Clouds* m_Clouds;
};

#endif