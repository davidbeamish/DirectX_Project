////////////////////////////////////////////////////////////////////////////////
// Filename: objectbitmap.cpp
////////////////////////////////////////////////////////////////////////////////
#include "objectbitmap.h"
#include "graphicsmanager.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "bitmap.h"
#include "rendertexture.h"

ObjectBitmap::ObjectBitmap(D3D* m_D3D, int screenWidth, int screenHeight, WCHAR* textureFilename1, int bitmapWidth, int bitmapHeight, int positionX, int positionY, D3DXMATRIX viewMatrix)
{
	// Create the new bitmap object.
	m_Bitmap = new Bitmap;

	// Initialize the bitmap object.
	m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, textureFilename1, bitmapWidth, bitmapHeight);

	m_positionX = positionX;
	m_positionY = positionY;

	m_viewMatrix = viewMatrix;

}

ObjectBitmap::ObjectBitmap(const ObjectBitmap& other)
{
}

ObjectBitmap::~ObjectBitmap()
{
	delete m_Bitmap;
}

bool ObjectBitmap::Render(GraphicsManager& graphicsmanager, int renderPass)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, translateMatrix;
	D3DXVECTOR3 cameraPosition;
	bool result;
	
	// Get the world, view, and projection matrices from the camera and d3d objects.
	graphicsmanager.GetD3DObject()->GetWorldMatrix(worldMatrix);
	//viewMatrix = graphicsmanager.GetViewMatrix();
	graphicsmanager.GetD3DObject()->GetProjectionMatrix(projectionMatrix);
	graphicsmanager.GetD3DObject()->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	graphicsmanager.GetD3DObject()->TurnZBufferOff();

	// Turn on alpha blending.
	graphicsmanager.GetD3DObject()->TurnOnSecondaryAlphaBlending();
	
	//// Get the position of the camera.
	//cameraPosition =graphicsmanager.GetCamera()->GetPosition();

	//// Calculate the rotation that needs to be applied to the billboard model to face the current camera position using the arc tangent function.
	//angle = atan2(m_positionX - cameraPosition.x, m_positionY - cameraPosition.z) * (180.0 / D3DX_PI);

	//// Convert rotation into radians.
	//rotation = (float)angle * 0.0174532925f;

	//// Setup the rotation the billboard at the origin using the world matrix.
	//D3DXMatrixRotationY(&worldMatrix, rotation);

	////// Setup the translation matrix from the billboard model.
	////D3DXMatrixTranslation(&translateMatrix, modelPosition.x, modelPosition.


	// Put the bitmap vertex and index buffers on the graphicsmanager pipeline to prepare them for drawing.
	result = m_Bitmap->Render(graphicsmanager.GetD3DObject()->GetDeviceContext(), m_positionX, m_positionY);
	if(!result)
	{
		return false;
	}
	// Render the bitmap with the texture shader.
	result = graphicsmanager.GetShaderManager()->RenderTextureShader(graphicsmanager.GetD3DObject()->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, m_viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if(!result)
	{
		return false;
	}

	// Turn of alpha blending.
	graphicsmanager.GetD3DObject()->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	graphicsmanager.GetD3DObject()->TurnZBufferOn();

	return true;
}

void ObjectBitmap::SetPosition(int posX, int posY)
{
	m_positionX = posX;
	m_positionY = posY;
}

