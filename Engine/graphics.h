////////////////////////////////////////////////////////////////////////////////
// Filename: graphics.h
// Adapted from a variety of tutorials on http://www.rastertek.com
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_


///////////////////////
// MY  INCLUDES //
///////////////////////
#include "d3d.h"

///////////////////////
// Forward declarations
///////////////////////

class Camera;
class ShaderManager;
class D3D;
class OrthoWindow;
class RenderTexture;

class Object;
class ObjectBitmap;
class ObjectText;
class ObjectDebugWindow;
class ObjectReflectable;
class ObjectTerrain;
class ObjectSkyDome;
class ObjectClouds;
class ObjectWorld;
class ObjectWater;
class ObjectParticle;

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
//  name: Graphics
////////////////////////////////////////////////////////////////////////////////
class Graphics
{
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	bool Initialize(Camera* cam, int screenWidth, int screenHeight, HWND hwnd);
	void Shutdown();
	bool Frame(Camera* cam, int fps, int cpu, float frameTime, int mouseX, int mouseY);

	D3D *GetD3DObject() const;
	ShaderManager *GetShaderManager() const;
	Camera *GetCamera();
	RenderTexture* GetTerrainRefractionTexture() const;
	RenderTexture* GetTerrainReflectionTexture() const;
	ObjectTerrain* GetObjectTerrain();

	D3DXMATRIX GetWorldMatrix() const;
	D3DXMATRIX GetViewMatrix() const;
	D3DXMATRIX GetProjectionMatrix() const;
	D3DXMATRIX GetReflectionMatrix() const;
	D3DXMATRIX GetOrthoMatrix() const;
	D3DXMATRIX GetReflectionViewMatrix() const;
	D3DXVECTOR4 GetClipPlane() const;
	D3DXVECTOR3 GetCameraPosition() const;

	void GetMouseLocation(int&, int&);
	

private:
	bool Render(Camera* cam);
	bool RenderPreProcessing(Camera* cam);
	bool RenderPostProcessing(Camera* cam);
	bool RenderScene(Camera* cam, int renderPass);
	//bool RenderToTexture(Camera* m_Camera, int renderPass);
	//bool RenderReflection(Camera* m_Camera, int renderPass);
	bool RenderReflectionToTexture(Camera* cam, int renderPass);
	bool RenderRefractionToTexture(Camera* cam, int renderPass);

	bool RenderSceneToTexture(Camera* cam);
	bool DownSampleTexture(Camera* cam, RenderTexture* renderTexture);
	bool RenderConvolutionToTexture(Camera* cam, RenderTexture* renderTexture, D3DXVECTOR4 kernelRow1, D3DXVECTOR4 kernelRow2, D3DXVECTOR4 kernelRow3);
	bool RenderHorizontalBlurToTexture(Camera* cam, RenderTexture* renderTexture);
	bool RenderVerticalBlurToTexture(Camera* cam, RenderTexture* renderTexture);
	bool UpSampleTexture(Camera* cam, RenderTexture* renderTexture);
	bool Render2DTextureScene(Camera* cam, RenderTexture* renderTexture);

	bool RenderTestToTexture(Camera* cam, RenderTexture* renderTexture);

	void TestIntersection(int mouseX, int mouseY);
	bool TestSphericalRadiusCollision();
	bool TestBoundingBoxCollision();
	bool RaySphereIntersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDirection, float radius);
	

private:
	D3D* m_D3D;
	ShaderManager* m_ShaderManager;
	Camera* m_Camera;

	Object* m_ObjectSphere;
	Object* m_ObjectSphere2;
	Object* m_Object3;
	Object* m_Object4;
	ObjectReflectable* m_ObjectFloor;
	ObjectBitmap* m_ObjectCursor;
	ObjectBitmap* m_ObjectBitmap1;
	ObjectText* m_ObjectText1;
	ObjectDebugWindow* m_ObjectDebugWindow1;
	ObjectTerrain* m_ObjectTerrain;
	ObjectSkyDome* m_ObjectSkyDome;
	ObjectClouds* m_ObjectClouds;
	ObjectWorld* m_ObjectWorld;
	ObjectWater* m_ObjectWater;
	ObjectParticle* m_ObjectParticle;

	RenderTexture* m_TerrainRefractionTexture, *m_TerrainReflectionTexture;

	RenderTexture *m_RenderTexture, * m_ConvolutionTexture, *m_DownSampleTexture, *m_HorizontalBlurTexture, *m_VerticalBlurTexture, *m_UpSampleTexture, *m_MiniMapTexture;
	OrthoWindow *m_SmallWindow, *m_FullScreenWindow, *m_MiniMapWindow;


	int m_ScreenWidth, m_ScreenHeight;
	int renderPass;
	int m_MouseX, m_MouseY;

	D3DXMATRIX worldMatrix, viewMatrix, m_InitialViewMatrix, projectionMatrix, reflectionMatrix, orthoMatrix;
	D3DXVECTOR4 clipPlane;

	bool m_collisionCheck, m_collisionCheck2;
};

#endif