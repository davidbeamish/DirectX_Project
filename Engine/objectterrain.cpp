////////////////////////////////////////////////////////////////////////////////
// Filename: objectterrain.cpp
////////////////////////////////////////////////////////////////////////////////
#include "objectterrain.h"
#include "graphicsmanager.h"
#include "lightmanager.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "terrain.h"
#include "rendertexture.h"

ObjectTerrain::ObjectTerrain(D3D* m_D3D, char* heightMapFilename, WCHAR* grassTextureFilename, WCHAR* slopeTextureFilename, 
	WCHAR* rockTextureFilename, char* colorMapFilename, WCHAR* detailMapFilename, WCHAR* normalFilename)
{
	// Create the terrain object.
	m_Terrain = new Terrain;

	// Initialize the model object.
	m_Terrain->Initialize(m_D3D->GetDevice(), heightMapFilename, grassTextureFilename, slopeTextureFilename, rockTextureFilename, colorMapFilename, detailMapFilename, normalFilename);
}

ObjectTerrain::ObjectTerrain(D3D* m_D3D, int terrainWidth, int terrainHeight, WCHAR* grassTextureFilename, WCHAR* slopeTextureFilename, WCHAR* rockTextureFilename, 
		char* colorMapFilename, WCHAR* detailMapFilename, WCHAR* normalFilename)
{
	// Create the terrain object.
	m_Terrain = new Terrain;

	// Initialize the model object.
	m_Terrain->InitializeTerrain(m_D3D->GetDevice(), terrainWidth, terrainHeight, grassTextureFilename, slopeTextureFilename, rockTextureFilename, colorMapFilename, detailMapFilename, normalFilename);
}


ObjectTerrain::ObjectTerrain(const ObjectTerrain& other)
{
}


ObjectTerrain::~ObjectTerrain()
{
	m_Terrain->Shutdown();
	delete m_Terrain;
}

bool ObjectTerrain::Render(GraphicsManager& graphicsManager, int renderPass)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix;
	D3DXVECTOR4 clipPlane;
	bool result;

	// Render Scene.
	if(renderPass == 0)
	{
		// Get the world, view, and projection matrices from the camera and d3d objects.
		worldMatrix = graphicsManager.GetWorldMatrix();
		viewMatrix = graphicsManager.GetViewMatrix();
		projectionMatrix= graphicsManager.GetProjectionMatrix();

		// Put the model vertex and index buffers on the graphicsmanager pipeline to prepare them for drawing.
		m_Terrain->Render(graphicsManager.GetD3DObject()->GetDeviceContext());

		// Render the model using the light shader.
		result = graphicsManager.GetShaderManager()->RenderTerrainShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
			graphicsManager.GetLightManager()->GetAmbientColor(), graphicsManager.GetLightManager()->GetDiffuseColor(), graphicsManager.GetLightManager()->GetDirection(), m_Terrain->GetGrassTexture(),
			m_Terrain->GetSlopeTexture(), m_Terrain->GetRockTexture(), m_Terrain->GetDetailMapTexture());
		if(!result)
		{
			return false;
		}



		return true;
	}
	// Render Refraction.
	else if(renderPass == 1)
	{
		// Get clipping plane based on the height of the water to clip everything above it to create a refraction.
		clipPlane = graphicsManager.GetClipPlane();

		// Get the world, view, and projection matrices from the camera and d3d objects.
		worldMatrix = graphicsManager.GetWorldMatrix();
		viewMatrix = graphicsManager.GetViewMatrix();
		projectionMatrix= graphicsManager.GetProjectionMatrix();

		// Render the terrain using the reflection shader and the refraction clip plane to produce the refraction effect.
		m_Terrain->Render(graphicsManager.GetD3DObject()->GetDeviceContext());
		//result = graphicsManager.GetShaderManager()->RenderTerrainReflectionShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Terrain->GetGrassTexture(), m_Terrain->GetNormalTexture(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), 2.0f, clipPlane);
		result  = graphicsManager.GetShaderManager()->RenderReflectionShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Terrain->GetGrassTexture(), (graphicsManager.GetTerrainRefractionTexture())->GetShaderResourceView(), reflectionMatrix);
		
		if(!result)
		{
			return false;
		}

		return true;
	}
	// Render Reflection
	if (renderPass == 2)
	{
		// Get clipping plane based on the height of the water to clip everything above it to create a refraction.
		clipPlane = graphicsManager.GetClipPlane();

		// Get the world, view, and projection matrices from the camera and d3d objects.
		worldMatrix = graphicsManager.GetWorldMatrix();
		viewMatrix = graphicsManager.GetViewMatrix();
		reflectionMatrix = graphicsManager.GetReflectionMatrix();
		projectionMatrix= graphicsManager.GetProjectionMatrix();

		graphicsManager.GetD3DObject()->GetWorldMatrix(worldMatrix);
		// Render the terrain using the reflection view matrix and reflection clip plane.
		m_Terrain->Render(graphicsManager.GetD3DObject()->GetDeviceContext());
		result = graphicsManager.GetShaderManager()->RenderTerrainReflectionShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, reflectionMatrix, projectionMatrix, m_Terrain->GetGrassTexture(), m_Terrain->GetNormalTexture(), graphicsManager.GetLightManager()->GetDiffuseColor(), graphicsManager.GetLightManager()->GetDirection(), 2.0f, clipPlane);
		//result  = graphicsManager.GetShaderManager()->RenderReflectionShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Terrain->GetGrassTexture(), (graphicsManager.GetTerrainReflectionTexture())->GetShaderResourceView(), reflectionMatrix);
			
		if(!result)
		{
			return false;
		}


		return true;
	}
	return false;
}

Terrain* ObjectTerrain::GetTerrain() const
{
	return m_Terrain;
}

float ObjectTerrain::GetMeanTerrainHeight() const
{
	return this->m_Terrain->GetMeanTerrainHeight();
}