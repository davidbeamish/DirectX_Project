////////////////////////////////////////////////////////////////////////////////
// Filename: objectwater.cpp
////////////////////////////////////////////////////////////////////////////////

#include "objectwater.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "graphicsmanager.h"
#include "lightmanager.h"
#include "water.h"
#include "rendertexture.h"
#include "objectterrain.h"


ObjectWater::ObjectWater(D3D* m_D3D, WCHAR* textureFilename, float waterHeight, float waterRadius)
{
	// Create the model object.
	m_Water = new Water;

	// Initialize the model object.
	m_Water->Initialize(m_D3D->GetDevice(), textureFilename, waterHeight, waterRadius);
}


ObjectWater::ObjectWater(const ObjectWater& other)
{
}


ObjectWater::~ObjectWater()
{
	m_Water->Shutdown();
	delete m_Water;
}

bool ObjectWater::Render(GraphicsManager& graphicsManager, int renderPass)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix;
	D3DXVECTOR4 clipPlane;
	bool result;

	// Get the world, view, and projection matrices from the camera and d3d objects.
	worldMatrix = graphicsManager.GetWorldMatrix();
	viewMatrix = graphicsManager.GetViewMatrix();
	
	reflectionMatrix = graphicsManager.GetReflectionMatrix();

	graphicsManager.GetD3DObject()->GetWorldMatrix(worldMatrix);
	graphicsManager.GetCamera()->GetViewMatrix(viewMatrix);
	graphicsManager.GetD3DObject()->GetProjectionMatrix(projectionMatrix);
	graphicsManager.GetCamera()->GetReflectionViewMatrix(reflectionMatrix);

	// Translate to the location of the water and render it.
	D3DXMatrixTranslation(&worldMatrix, 256.0f, graphicsManager.GetObjectTerrain()->GetMeanTerrainHeight(), 256.0f);

	// Render and shader the water object.
	m_Water->Render(graphicsManager.GetD3DObject()->GetDeviceContext());
	result = graphicsManager.GetShaderManager()->RenderWaterShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_Water->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix, 
		(graphicsManager.GetTerrainRefractionTexture())->GetShaderResourceView(), (graphicsManager.GetTerrainReflectionTexture())->GetShaderResourceView(), m_Water->GetTexture(), 
		graphicsManager.GetCamera()->GetPosition(), m_Water->GetNormalMapTiling(), m_Water->GetWaterTranslation(), m_Water->GetReflectRefractScale(),
		m_Water->GetRefractionTint(), graphicsManager.GetLightManager()->GetDirection(), m_Water->GetSpecularShininess());
	if(!result)
	{
		return false;
	}

	return true;
}

void ObjectWater::Frame()
{
	m_Water->Frame();
}

float ObjectWater::GetWaterHeight()
{
	return m_Water->GetWaterHeight();
}