////////////////////////////////////////////////////////////////////////////////
// Filename: objectskydome.cpp
////////////////////////////////////////////////////////////////////////////////
#include "objectskydome.h"
#include "graphicsmanager.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "skydome.h"
#include "objectterrain.h"
#include "terrain.h"


ObjectSkyDome::ObjectSkyDome(D3D* m_D3D, HWND hwnd, char* modelFilename)
{
	//Create the sky dome object.
	m_SkyDome = new SkyDome;

	// Initialize the sky dome object.
	m_SkyDome->Initialize(m_D3D->GetDevice(), modelFilename);
}

ObjectSkyDome::ObjectSkyDome(const ObjectSkyDome& other)
{
}


ObjectSkyDome::~ObjectSkyDome()
{
	// Release the sky dome object.
	m_SkyDome->Shutdown();
	delete m_SkyDome;
}

bool ObjectSkyDome::Render(GraphicsManager& graphicsManager, int renderPass)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, reflectionMatrix;
	D3DXVECTOR3 cameraPosition;

	if (renderPass == 0)
	{
		// Get the world, view, projection, and ortho matrices.
		worldMatrix = graphicsManager.GetWorldMatrix();
		viewMatrix = graphicsManager.GetViewMatrix();
		projectionMatrix= graphicsManager.GetProjectionMatrix();

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

		// Turn the Z buffer back on.
		graphicsManager.GetD3DObject()->TurnZBufferOn();

		return true;
	}

	else if(renderPass == 2)
	{
		// Turn off back face culling and the Z buffer.
		graphicsManager.GetD3DObject()->TurnOffCulling();
		graphicsManager.GetD3DObject()->TurnZBufferOff();

		// Get the world, reflection, projection matrices.
		worldMatrix = graphicsManager.GetWorldMatrix();
		reflectionMatrix = graphicsManager.GetReflectionMatrix();
		projectionMatrix= graphicsManager.GetProjectionMatrix();

		// Get the position of the camera.
		cameraPosition = graphicsManager.GetCamera()->GetPosition();

		// Invert the Y coordinate of the camera around the water plane height for the reflected camera position.
		cameraPosition.y = -cameraPosition.y + (graphicsManager.GetObjectTerrain()->GetMeanTerrainHeight() * 2.0f);

		// Translate the sky dome and clouds to be centered around the reflected camera position.
		D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);

		// Render the sky dome using the reflection view matrix.
		m_SkyDome->Render(graphicsManager.GetD3DObject()->GetDeviceContext());
		graphicsManager.GetShaderManager()->RenderSkyDomeShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, reflectionMatrix, projectionMatrix, 
			m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

		// Enable back face culling and the z buffer.
		graphicsManager.GetD3DObject()->TurnOnCulling();
		graphicsManager.GetD3DObject()->TurnZBufferOn();

		return true;
	}

	return false;
}