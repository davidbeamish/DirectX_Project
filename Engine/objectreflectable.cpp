////////////////////////////////////////////////////////////////////////////////
// Filename: objectreflectable.cpp
////////////////////////////////////////////////////////////////////////////////
#include "objectreflectable.h"
#include "graphicsmanager.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "model.h"
#include "rendertexture.h"

ObjectReflectable ::ObjectReflectable (D3D* m_D3D, HWND hwnd, char* modelFilename, WCHAR* textureFilename)
{
	// Create the model object.
	m_Model = new Model;

	// Initialize the model object.
	m_Model->Initialize(m_D3D->GetDevice(), modelFilename, textureFilename);

	m_RenderTexture = 0;

	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}


ObjectReflectable ::ObjectReflectable (const ObjectReflectable & other)
{
}


ObjectReflectable ::~ObjectReflectable ()
{
	m_Model->Shutdown();
	delete m_Model;
}

bool ObjectReflectable ::Render()
{
	return true;
}

bool ObjectReflectable ::Render(GraphicsManager& graphicsManager, int renderPass)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix;
	bool result;
	
	// Get the world, view, and projection matrices from the camera and d3d objects.
	viewMatrix = graphicsManager.GetViewMatrix();
	graphicsManager.GetD3DObject()->GetWorldMatrix(worldMatrix);
	graphicsManager.GetD3DObject()->GetProjectionMatrix(projectionMatrix);
	
	reflectionMatrix = graphicsManager.GetReflectionMatrix();

	// Put the model vertex and index buffers on the graphicsmanager pipeline to prepare them for drawing.
	m_Model->Render(graphicsManager.GetD3DObject()->GetDeviceContext());

	// Render the model using the reflection shader, reflection texture, and reflection view matrix.
	result = graphicsManager.GetShaderManager()->RenderReflectionShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix,
					    projectionMatrix, m_Model->GetTexture(), m_RenderTexture->GetShaderResourceView(), reflectionMatrix);
	if(!result)
	{
		return false;
	}

	return true;
}