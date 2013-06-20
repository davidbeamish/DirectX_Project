////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsmanager.h
// Adapted from a variety of tutorials on http://www.rastertek.com
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSMANAGER_H_
#define _GRAPHICSMANAGER_H_


///////////////////////
// MY  INCLUDES //
///////////////////////
#include "d3d.h"
#include <vector>

///////////////////////
// Forward declarations
///////////////////////

class Camera;
class ShaderManager;
class LightManager;
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
class ObjectExplosionParticle;
class ObjectFireParticle;
class Input;


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
//  name: GraphicsManager
////////////////////////////////////////////////////////////////////////////////
class GraphicsManager
{
public:
	GraphicsManager();
	GraphicsManager(const GraphicsManager&);
	~GraphicsManager();

	bool Initialize(Camera* cam, int screenWidth, int screenHeight, HWND hwnd);
	void Shutdown();
	bool Frame(Camera* cam, Input* input, int fps, int cpumanager, float frameTime, int mouseX, int mouseY);

	D3D *GetD3DObject() const;
	ShaderManager * GetShaderManager() const;
	LightManager * GetLightManager() const;
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
	float GetFrameTime() const {return m_frameTime;}
	

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
	bool ApplyConvolutionTexture(Camera* cam, RenderTexture* renderTexture, D3DXVECTOR4 kernelRow1, D3DXVECTOR4 kernelRow2, D3DXVECTOR4 kernelRow3);
	bool CreateGlowMap(Camera* cam, RenderTexture* renderTexture, D3DXVECTOR4 tint);
	bool GlowTexture(Camera* cam, RenderTexture* renderTexture, float glowStrength);
	bool BlurTextureHorizontally(Camera* cam, RenderTexture* renderTexture);
	bool BlurTextureVertically(Camera* cam, RenderTexture* renderTexture);
	bool UpSampleTexture(Camera* cam, RenderTexture* renderTexture);
	bool Render2DTextureScene(Camera* cam, RenderTexture* renderTexture);

	bool RenderTestToTexture(Camera* cam, RenderTexture* renderTexture);

	bool TestPickingCollision(int mouseX, int mouseY, Object * object);
	bool TestSphericalRadiusCollision(Object* object, Object* object2);
	bool TestBoundingBoxCollision(Object* object, Object* object2);
	bool RaySphereIntersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDirection, float radius);
	

private:
	D3D* m_D3D;
	ShaderManager* m_ShaderManager;
	Camera* m_Camera;
	LightManager * m_LightManager;

	Object* m_ObjectSphere;
	Object* m_ObjectSphere2;
	Object* m_Object3;
	Object* m_Object4;
	ObjectReflectable* m_ObjectFloor;
	ObjectBitmap* m_ObjectCursor;
	ObjectText* m_ObjectText1;
	ObjectDebugWindow* m_ObjectDebugWindow1;
	ObjectTerrain* m_ObjectTerrain;
	ObjectSkyDome* m_ObjectSkyDome;
	ObjectClouds* m_ObjectClouds;
	ObjectWorld* m_ObjectWorld;
	ObjectWater* m_ObjectWater;

	RenderTexture* m_TerrainRefractionTexture, *m_TerrainReflectionTexture;

	RenderTexture *m_RenderTexture, * m_ConvolutionTexture, *m_DownSampleTexture, *m_GlowMapTexture, *m_GlowTexture, *m_HorizontalBlurTexture, *m_VerticalBlurTexture, *m_UpSampleTexture, *m_MiniMapTexture;
	OrthoWindow *m_SmallWindow, *m_FullScreenWindow, *m_MiniMapWindow;


	int m_ScreenWidth, m_ScreenHeight;
	int renderPass;
	int m_MouseX, m_MouseY;

	D3DXMATRIX worldMatrix, viewMatrix, m_InitialViewMatrix, projectionMatrix, reflectionMatrix, orthoMatrix;
	D3DXVECTOR4 clipPlane;
	D3DXVECTOR4 m_convolutionRow1, m_convolutionRow2, m_convolutionRow3;
	int convolutionCheck;

	float m_frameTime;

	
	bool m_collisionCheck, m_collisionCheck2;

	std::vector<Object*>  m_collidables;
	std::vector<ObjectExplosionParticle*> m_ExplosionParticles;
	std::vector<ObjectFireParticle*> m_FireParticles;
};

#endif