////////////////////////////////////////////////////////////////////////////////
// Filename: renderableclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "renderableclass.h"


RenderableClass::RenderableClass()
{
	m_Model = 0;
	m_ShaderManager = 0;
	m_Light = 0;
}


RenderableClass::RenderableClass(const RenderableClass& other)
{
}


RenderableClass::~RenderableClass()
{
}


bool RenderableClass::Initialize(D3DClass* m_D3D, HWND hwnd)
{
	bool result;

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the model object.
	m_Model = new ModelClass;
	if(!m_Model)
	{
		return false;
	}
	
	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/dirt01.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.1f, 0.0f, 0.1f, 0.2f);
	m_Light->SetDiffuseColor(0.7f, 0.1f, 0.11f, 0.3f);
	m_Light->SetDirection(-1.0f, -1.0, 0.2f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(64.0f);

	return true;
}

void RenderableClass::Shutdown()
{
	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}
	
	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}
	
	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}
}

bool RenderableClass::Render(D3DClass* m_D3D, CameraClass* m_Camera, float rotation, float deltavalue)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, translateMatrix;
	bool result;
	
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	
	// Setup movement of the model.
	D3DXMatrixRotationY(&worldMatrix, rotation);
	D3DXMatrixTranslation(&translateMatrix, 0.0f, 2.5f, 0.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix); 

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
						    m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
						    m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	return true;
}