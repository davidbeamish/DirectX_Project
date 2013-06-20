////////////////////////////////////////////////////////////////////////////////
// Filename: ObjectWorld.cpp
////////////////////////////////////////////////////////////////////////////////
#include "objectworld.h"
#include "graphicsmanager.h"
#include "lightmanager.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "skydome.h"
#include "clouds.h"

#include "terrain.h"

ObjectWorld::ObjectWorld(D3D* m_D3D, HWND hwnd)
{
	// Create the terrain object.
	m_Terrain = new Terrain;

	// Initialize the model object.
	m_Terrain->Initialize(m_D3D->GetDevice(), "../Engine/data/heightmap02.bmp", L"../Engine/data/dirt01.dds", L"../Engine/data/slope.dds", L"../Engine/data/rock.dds", "../Engine/data/colorm01.bmp", L"../Engine/data/detail001.dds", L"../Engine/data/normal.dds");

	//Create the sky dome object.
	m_SkyDome = new SkyDome;

	// Initialize the sky dome object.
	m_SkyDome->Initialize(m_D3D->GetDevice(), "../Engine/data/skydome.txt");
	
	// Create the clouds object.
	m_Clouds = new Clouds;

	// Initialize the model object.
	m_Clouds->Initialize(m_D3D->GetDevice(), L"../Engine/data/cloud001.dds", L"../Engine/data/cloud002.dds",L"../Engine/data/perturb001.dds");


}


ObjectWorld::ObjectWorld(const ObjectWorld& other)
{
}


ObjectWorld::~ObjectWorld()
{
	m_Clouds->Shutdown();
	delete m_Clouds;

	m_SkyDome->Shutdown();
	delete m_SkyDome;
		
	m_Terrain->Shutdown();
	delete m_Terrain;
}

void ObjectWorld::Frame()
{
	m_Clouds->Frame();

	return;
}

bool ObjectWorld::Render()
{
	return true;
}

bool ObjectWorld::Render(GraphicsManager& graphicsManager, int renderPass)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, translateMatrix;
	D3DXVECTOR3 cameraPosition;

	bool result;
	
// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	graphicsManager.GetD3DObject()->GetWorldMatrix(worldMatrix);
	graphicsManager.GetCamera()->GetViewMatrix(viewMatrix);
	graphicsManager.GetD3DObject()->GetProjectionMatrix(projectionMatrix);
	graphicsManager.GetD3DObject()->GetOrthoMatrix(orthoMatrix);

	// Get the position of the camera.
	cameraPosition = graphicsManager.GetCamera()->GetPosition();

	// Translate the sky dome to be centered around the camera position.
	D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Turn off back face culling.
	graphicsManager.GetD3DObject()->TurnOffCulling();

	// Turn off the Z buffer.
	graphicsManager.GetD3DObject()->TurnZBufferOff();

	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(graphicsManager.GetD3DObject()->GetDeviceContext());
	graphicsManager.GetShaderManager()->RenderSkyDomeShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
				m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

	// Turn back face culling back on.
	graphicsManager.GetD3DObject()->TurnOnCulling();

	// Enable additive blending so the clouds blend with the sky dome color.
	graphicsManager.GetD3DObject()->TurnOnSecondaryAlphaBlending();

	// Render the clouds using the clouds shader.
	m_Clouds->Render(graphicsManager.GetD3DObject()->GetDeviceContext());
	graphicsManager.GetShaderManager()->RenderCloudsShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_Clouds->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
				 m_Clouds->GetCloudTexture1(), m_Clouds->GetCloudTexture2(), m_Clouds->GetPerturbTexture(), m_Clouds->GetTranslation(), m_Clouds->GetScale(), 
				 m_Clouds->GetBrightness());

	// Turn off blending.
	graphicsManager.GetD3DObject()->TurnOffAlphaBlending();

	// Turn the Z buffer back on.
	graphicsManager.GetD3DObject()->TurnZBufferOn();

	// Reset the world matrix.
	graphicsManager.GetD3DObject()->GetWorldMatrix(worldMatrix);
	
	// Render the terrain using the terrain shader.
	m_Terrain->Render(graphicsManager.GetD3DObject()->GetDeviceContext());
	result = graphicsManager.GetShaderManager()->RenderTerrainShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
					 graphicsManager.GetLightManager()->GetAmbientColor(), graphicsManager.GetLightManager()->GetDiffuseColor(), graphicsManager.GetLightManager()->GetDirection(), m_Terrain->GetGrassTexture(),
					 m_Terrain->GetSlopeTexture(), m_Terrain->GetRockTexture(), m_Terrain->GetDetailMapTexture());
	if(!result)
	{
		return false;
	}

	return true;
}