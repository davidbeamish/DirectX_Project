////////////////////////////////////////////////////////////////////////////////
// Filename: ObjectClouds.cpp
////////////////////////////////////////////////////////////////////////////////
#include "objectclouds.h"
#include "graphicsmanager.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "clouds.h"
#include "objectterrain.h"
#include "terrain.h"

ObjectClouds::ObjectClouds(D3D* m_D3D, WCHAR* cloudTextureFilename1,  WCHAR* cloudTextureFilename2, WCHAR* perturbTextureFilename)
{
	// Create the clouds object.
	m_Clouds = new Clouds;

	// Initialize the model object.
	m_Clouds->Initialize(m_D3D->GetDevice(), cloudTextureFilename1,  cloudTextureFilename2, perturbTextureFilename);
}


ObjectClouds::ObjectClouds(const ObjectClouds& other)
{
}


ObjectClouds::~ObjectClouds()
{
	m_Clouds->Shutdown();
	delete m_Clouds;
}

void ObjectClouds::Frame()
{
	m_Clouds->Frame();
}

bool ObjectClouds::Render()
{
	return true;
}

bool ObjectClouds::Render(GraphicsManager& graphicsManager, int renderPass)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix;
	D3DXVECTOR3 cameraPosition;
	bool result;
	if (renderPass ==  0)
	{
		// Get the world, view, projection, and ortho matrices.
		worldMatrix = graphicsManager.GetWorldMatrix();
		viewMatrix = graphicsManager.GetViewMatrix();
		projectionMatrix= graphicsManager.GetProjectionMatrix();

		// Get the position of the camera.
		cameraPosition = graphicsManager.GetCamera()->GetPosition();

		// Translate the clouds to be centered around the camera position.
		D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);

		// Turn off the Z buffer.
		graphicsManager.GetD3DObject()->TurnZBufferOff();

		// Enable additive blending so the clouds blend with the sky dome color.
		graphicsManager.GetD3DObject()->TurnOnSecondaryAlphaBlending();

		// Render the clouds using the clouds shader.
		m_Clouds->Render(graphicsManager.GetD3DObject()->GetDeviceContext());
		result = graphicsManager.GetShaderManager()->RenderCloudsShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_Clouds->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
				 m_Clouds->GetCloudTexture1(), m_Clouds->GetCloudTexture2(), m_Clouds->GetPerturbTexture(), m_Clouds->GetTranslation(), m_Clouds->GetScale(), m_Clouds->GetBrightness());
		if(!result)
		{
			return false;
		}

		// Enable additive blending so the clouds blend with the sky dome color.
		graphicsManager.GetD3DObject()->TurnOffAlphaBlending();

		// Turn on the Z buffer.
		graphicsManager.GetD3DObject()->TurnZBufferOn();

		return true;
	}
	else if (renderPass == 2)
	{
		// Turn off back the Z buffer.
		graphicsManager.GetD3DObject()->TurnZBufferOff();

		// Enable additive blending so the clouds blend with the sky dome color.
		graphicsManager.GetD3DObject()->TurnOnSecondaryAlphaBlending();

		// Get the world, reflection, projection matrices.
		worldMatrix = graphicsManager.GetWorldMatrix();
		reflectionMatrix = graphicsManager.GetReflectionMatrix();
		projectionMatrix= graphicsManager.GetProjectionMatrix();

		// Get the position of the camera.
		D3DXVECTOR3 cameraPosition = graphicsManager.GetCamera()->GetPosition();

		// Invert the Y coordinate of the camera around the water plane height for the reflected camera position.
		cameraPosition.y = -cameraPosition.y + (graphicsManager.GetObjectTerrain()->GetMeanTerrainHeight() * 2.0f);

		// Translate the sky dome and clouds to be centered around the reflected camera position.
		D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);

		// Render the clouds using the clouds shader.
		m_Clouds->Render(graphicsManager.GetD3DObject()->GetDeviceContext());
		result = graphicsManager.GetShaderManager()->RenderCloudsShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_Clouds->GetIndexCount(), worldMatrix, reflectionMatrix, projectionMatrix, 
				 m_Clouds->GetCloudTexture1(), m_Clouds->GetCloudTexture2() ,m_Clouds->GetPerturbTexture(), m_Clouds->GetTranslation(), m_Clouds->GetScale(), m_Clouds->GetBrightness());
		if(!result)
		{
			return false;
		}

		graphicsManager.GetD3DObject()->TurnOffAlphaBlending();

		graphicsManager.GetD3DObject()->TurnZBufferOn();

		return true;
	}
	return false;
}