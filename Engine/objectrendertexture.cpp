////////////////////////////////////////////////////////////////////////////////
// Filename: objectrendertexture.cpp
////////////////////////////////////////////////////////////////////////////////

#include "objectrendertexture.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "graphicsmanager.h"
#include "rendertexture.h"


ObjectRenderTexture::ObjectRenderTexture(D3D* d3d, int textureWidth, int textureHeight, float screenDepth, float screenNear)
{
	// Create the render to texture object.
	m_RenderTexture = new RenderTexture;
	
	// Initialize the render to texture object.
	m_RenderTexture->Initialize(d3d->GetDevice(), textureWidth, textureHeight, screenDepth, screenNear);
}


ObjectRenderTexture::ObjectRenderTexture(const ObjectRenderTexture& other)
{
}


ObjectRenderTexture::~ObjectRenderTexture()
{

}

bool ObjectRenderTexture::Render(GraphicsManager& graphicsmanager, int renderPass)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, translateMatrix;

	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(graphicsmanager.GetD3DObject()->GetDeviceContext());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(graphicsmanager.GetD3DObject()->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	//// Generate the view matrix based on the camera's position.
	//graphicsmanager.GetCamera()->Render();

	viewMatrix = graphicsmanager.GetViewMatrix();
	graphicsmanager.GetD3DObject()->GetWorldMatrix(worldMatrix);
	graphicsmanager.GetD3DObject()->GetProjectionMatrix(projectionMatrix);
	// Get the ortho matrix from the render to texture since texture has different dimensions.
	m_RenderTexture->GetOrthoMatrix(orthoMatrix);

	RenderObjectsToTexture(graphicsmanager, renderPass);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	graphicsmanager.GetD3DObject()->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	graphicsmanager.GetD3DObject()->ResetViewport();

	return true;
}

bool ObjectRenderTexture::RenderObjectsToTexture(GraphicsManager& graphicsmanager, int renderPass)
{
	//// Turn off the Z buffer to begin all 2D rendering.
	//m_D3D->TurnZBufferOff();
	//

	//// Put the model vertex and index buffers on the graphicsmanager pipeline to prepare them for drawing.
	//m_Model->Render(graphicsmanager.GetD3DObject()->GetDeviceContext());

	//// Render the model using the light shader.
	//result = graphicsmanager.GetShaderManager()->RenderLightShader(graphicsmanager.GetD3DObject()->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
	//					    m_Model->GetTexture(), graphicsManager.GetLightManager()->GetDirection(), graphicsManager.GetLightManager()->GetAmbientColor(), graphicsManager.GetLightManager()->GetDiffuseColor(), 
	//					    graphicsmanager.GetCamera()->GetPosition(), graphicsManager.GetLightManager()->GetSpecularColor(), graphicsManager.GetLightManager()->GetSpecularPower());
	//if(!result)
	//{
	//	return false;
	//}

	//// Turn the Z buffer back on now that all 2D rendering has completed.
	//graphicsmanager.GetD3DObject()->TurnZBufferOn();

	return true;
}