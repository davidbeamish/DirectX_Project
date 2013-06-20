////////////////////////////////////////////////////////////////////////////////
// Filename: ObjectClouds.cpp
////////////////////////////////////////////////////////////////////////////////
#include "objectclouds.h"
#include "graphics.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "clouds.h"

ObjectClouds::ObjectClouds(D3D* m_D3D, WCHAR* textureFilename1, WCHAR* textureFilename2)
{
	// Create the sky plane object.
	m_Clouds = new Clouds;

	// Initialize the model object.
	m_Clouds->Initialize(m_D3D->GetDevice(), textureFilename1, textureFilename2);
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

bool ObjectClouds::Render(Graphics& m_Graphics, int renderPass)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix;
	D3DXVECTOR3 cameraPosition;
	bool result;
	if (renderPass ==  0)
	{
		// Get the world, view, projection, and ortho matrices.
		worldMatrix = m_Graphics.GetWorldMatrix();
		viewMatrix = m_Graphics.GetViewMatrix();
		projectionMatrix= m_Graphics.GetProjectionMatrix();

		// Get the position of the camera.
		cameraPosition = m_Graphics.GetCamera()->GetPosition();

		// Translate the sky plane to be centered around the camera position.
		D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);

		// Turn off the Z buffer.
		m_Graphics.GetD3DObject()->TurnZBufferOff();

		// Enable additive blending so the clouds blend with the sky dome color.
		m_Graphics.GetD3DObject()->TurnOnSecondaryAlphaBlending();

		// Render the sky plane using the sky plane shader.
		m_Clouds->Render(m_Graphics.GetD3DObject()->GetDeviceContext());
		result = m_Graphics.GetShaderManager()->RenderCloudsShader(m_Graphics.GetD3DObject()->GetDeviceContext(), m_Clouds->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
				 m_Clouds->GetCloudTexture(), m_Clouds->GetPerturbTexture(), m_Clouds->GetTranslation(), m_Clouds->GetScale(), 
				 m_Clouds->GetBrightness());
		if(!result)
		{
			return false;
		}

		// Enable additive blending so the clouds blend with the sky dome color.
		m_Graphics.GetD3DObject()->TurnOffAlphaBlending();

		// Turn on the Z buffer.
		m_Graphics.GetD3DObject()->TurnZBufferOn();

		return true;
	}
	else if (renderPass == 2)
	{
		// Turn off back the Z buffer.
		m_Graphics.GetD3DObject()->TurnZBufferOff();

		// Enable additive blending so the clouds blend with the sky dome color.
		m_Graphics.GetD3DObject()->TurnOnSecondaryAlphaBlending();

		// Get the world, reflection, projection matrices.
		worldMatrix = m_Graphics.GetWorldMatrix();
		reflectionMatrix = m_Graphics.GetReflectionMatrix();
		projectionMatrix= m_Graphics.GetProjectionMatrix();

		// Get the position of the camera.
		D3DXVECTOR3 cameraPosition = m_Graphics.GetCamera()->GetPosition();

		// Invert the Y coordinate of the camera around the water plane height for the reflected camera position.
		cameraPosition.y = -cameraPosition.y + (3.75f * 2.0f);

		// Translate the sky dome and sky plane to be centered around the reflected camera position.
		D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);

		// Render the sky plane using the sky plane shader.
		m_Clouds->Render(m_Graphics.GetD3DObject()->GetDeviceContext());
		result = m_Graphics.GetShaderManager()->RenderCloudsShader(m_Graphics.GetD3DObject()->GetDeviceContext(), m_Clouds->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
				 m_Clouds->GetCloudTexture(), m_Clouds->GetPerturbTexture(), m_Clouds->GetTranslation(), m_Clouds->GetScale(), m_Clouds->GetBrightness());
		if(!result)
		{
			return false;
		}

		m_Graphics.GetD3DObject()->TurnOffAlphaBlending();

		m_Graphics.GetD3DObject()->TurnZBufferOn();

		return true;
	}
	return false;
}