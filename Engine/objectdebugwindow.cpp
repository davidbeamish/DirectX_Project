////////////////////////////////////////////////////////////////////////////////
// Filename: objectdebugwindow.cpp
////////////////////////////////////////////////////////////////////////////////
#include "objectdebugwindow.h"
#include "graphicsmanager.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "debugwindow.h"
#include "rendertexture.h"

ObjectDebugWindow::ObjectDebugWindow(D3D* m_D3D, int screenWidth, int screenHeight, int bitmapWidth, int bitmapHeight)
{
	// Create the debug window object.
	m_DebugWindow = new DebugWindow;

	// Initialize the debug window object.
	m_DebugWindow->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, bitmapWidth, bitmapHeight);
}

ObjectDebugWindow::ObjectDebugWindow(const ObjectDebugWindow& other)
{
}

ObjectDebugWindow::~ObjectDebugWindow()
{
	delete m_DebugWindow;
}

bool ObjectDebugWindow::Render(GraphicsManager& graphicsManager, int renderPass)
{
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	bool result;

	// Turn off the Z buffer to begin all 2D rendering.
	graphicsManager.GetD3DObject()->TurnZBufferOff();

	// Get the world, view, and ortho matrices from the camera and d3d objects.
	graphicsManager.GetD3DObject()->GetWorldMatrix(worldMatrix);
	viewMatrix = graphicsManager.GetViewMatrix();
	graphicsManager.GetD3DObject()->GetOrthoMatrix(orthoMatrix);

	// Put the debug window vertex and index buffers on the graphicsmanager pipeline to prepare them for drawing.
	result = m_DebugWindow->Render(graphicsManager.GetD3DObject()->GetDeviceContext(), 50, 50);
	if(!result)
	{
		return false;
	}

	// Render the debug window using the texture shader.
	result = graphicsManager.GetShaderManager()->RenderTextureShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_DebugWindow->GetIndexCount(), worldMatrix, viewMatrix,
					 orthoMatrix, m_RenderTexture->GetShaderResourceView());
	if(!result)
	{
		return false;
	}
	
	// Turn the Z buffer back on now that all 2D rendering has completed.
	graphicsManager.GetD3DObject()->TurnZBufferOn();

	return true;
}