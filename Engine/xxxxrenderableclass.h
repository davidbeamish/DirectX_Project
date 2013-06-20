////////////////////////////////////////////////////////////////////////////////
// Filename: renderableclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _RENDERABLECLASS_H_
#define _RENDERABLECLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////

#include "modelclass.h"
#include "shadermanagerclass.h"
#include "lightclass.h"
#include "cameraclass.h"

/////////////
// GLOBALS //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: RenderableClass
////////////////////////////////////////////////////////////////////////////////
class RenderableClass
{
public:
	RenderableClass();
	RenderableClass(const RenderableClass&);
	~RenderableClass();

	bool Initialize(D3DClass* m_D3D, HWND hwnd);
	void Shutdown();
	bool Render(D3DClass* m_D3D, CameraClass* m_Camera, float, float);

	//bool Frame(int fps, int cpu, float frameTime, float rotationY);

private:
	

private:
	ModelClass* m_Model;
	ShaderManagerClass* m_ShaderManager;
	LightClass* m_Light;
};

#endif