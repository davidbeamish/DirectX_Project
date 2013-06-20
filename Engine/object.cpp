////////////////////////////////////////////////////////////////////////////////
// Filename: object.cpp
////////////////////////////////////////////////////////////////////////////////

#include "object.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "graphicsmanager.h"
#include "lightmanager.h"
#include "model.h"
#include "objectexplosionparticle.h"

Object::Object(D3D* d3d, char* modelFilename, WCHAR* textureFilename)
{
	// Create the model object.
	m_Model = new Model;

	// Initialize the model object.
	m_Model->Initialize(d3d->GetDevice(), modelFilename, textureFilename);

	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_sphericalBoundingRadius = m_Model->GetSphericalBoundingRadius();
	m_boundingBox = m_Model->GetBoundingBox();
	m_boundingBoxVertices = m_Model->GetBoundingBoxVertices();

	m_ExplosionEffect = new ObjectExplosionParticle(d3d);
}


Object::Object(const Object& other)
{
}


Object::~Object()
{
	m_Model->Shutdown();
	delete m_Model;
}

bool Object::Render(GraphicsManager& graphicsManager, int renderPass)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, reflectionMatrix, translateMatrix;
	bool result;

	// Render Scene.
	if(renderPass == 0)
	{
		// Get the world, view, and projection matrices from the camera and d3d objects.
		viewMatrix = graphicsManager.GetViewMatrix();
		graphicsManager.GetD3DObject()->GetWorldMatrix(worldMatrix);
		graphicsManager.GetD3DObject()->GetProjectionMatrix(projectionMatrix);

		// Turn off blending.
		//graphicsManager.GetD3DObject()->TurnOffAlphaBlending();
		graphicsManager.GetD3DObject()->TurnOffCulling();
		//worldMatrix = DoMovement(graphicsManager.GetD3DObject());
		//D3DXMatrixTranslation(&worldMatrix, m_positionX, m_positionY, m_positionZ);
		worldMatrix = DoMovement(graphicsManager.GetD3DObject());
		// Put the model vertex and index buffers on the graphicsmanager pipeline to prepare them for drawing.
		m_Model->Render(graphicsManager.GetD3DObject()->GetDeviceContext());

		// Render the model using the light shader.
		result = graphicsManager.GetShaderManager()->RenderLightShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
			m_Model->GetTexture(), graphicsManager.GetLightManager()->GetDirection(), graphicsManager.GetLightManager()->GetAmbientColor(), graphicsManager.GetLightManager()->GetDiffuseColor(), 
			graphicsManager.GetCamera()->GetPosition(), graphicsManager.GetLightManager()->GetSpecularColor(), graphicsManager.GetLightManager()->GetSpecularPower());
		if(!result)
		{
			return false;
		}

		// Turn on the alpha blending before rendering the text.
		//graphicsManager.GetD3DObject()->TurnOnAlphaBlending();

		// Turn back face culling back on.
		graphicsManager.GetD3DObject()->TurnOnCulling();
	}
	// Render Reflection
	if (renderPass == 2)
	{
		// Get clipping plane based on the height of the water to clip everything above it to create a refraction.
		//clipPlane = graphicsManager.GetClipPlane();

		// Get the world, view, and projection matrices from the camera and d3d objects.
		worldMatrix = graphicsManager.GetWorldMatrix();
		viewMatrix = graphicsManager.GetViewMatrix();
		reflectionMatrix = graphicsManager.GetReflectionMatrix();
		projectionMatrix= graphicsManager.GetProjectionMatrix();		
		worldMatrix = DoMovement(graphicsManager.GetD3DObject());

		// Get the position of the camera.
		D3DXVECTOR3 cameraPosition = graphicsManager.GetCamera()->GetPosition();

		// Translate the sky dome and clouds to be centered around the reflected camera position.
		D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);
		//D3DXMatrixTranslation(&worldMatrix, m_positionX, m_positionY, m_positionZ);
		// Put the model vertex and index buffers on the graphicsmanager pipeline to prepare them for drawing.
		m_Model->Render(graphicsManager.GetD3DObject()->GetDeviceContext());

		// Render the model using the light shader.
		result = graphicsManager.GetShaderManager()->RenderLightShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, reflectionMatrix, projectionMatrix, 
			m_Model->GetTexture(), graphicsManager.GetLightManager()->GetDirection(), graphicsManager.GetLightManager()->GetAmbientColor(), graphicsManager.GetLightManager()->GetDiffuseColor(), 
			graphicsManager.GetCamera()->GetPosition(), graphicsManager.GetLightManager()->GetSpecularColor(), graphicsManager.GetLightManager()->GetSpecularPower());
		if(!result)
		{
			return false;
		}

		return true;
	}

	return true;
}

D3DXMATRIX Object::DoMovement(D3D* d3d)
{
	D3DXMATRIX worldMatrix, translateMatrix;

	// Get world matrix form the D3D object.
	d3d->GetWorldMatrix(worldMatrix);

	// Setup movement of the model.
	m_rotation.x += (float)D3DX_PI * 0.005f;
	if(m_rotation.x > 360.0f)
	{
		m_rotation.x -= 360.0f;
	}

	m_rotation.y += (float)D3DX_PI * 0.005f;
	if(m_rotation.y> 360.0f)
	{
		m_rotation.y -= 360.0f;
	}

	D3DXMatrixRotationYawPitchRoll(&worldMatrix, m_rotation.x, m_rotation.y, m_rotation.z);
	D3DXMatrixTranslation(&translateMatrix, m_position.x, m_position.y, m_position.z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

	return worldMatrix;
}

void Object::SetPosition(D3DXVECTOR3 position)
{
	m_position = position;
}

D3DXVECTOR3 Object::GetPosition() const
{
	return m_position;
}

void Object::SetRotation(D3DXVECTOR3 rotation)
{
	m_rotation = rotation;
}

float Object::GetSphericalBoundingRadius() const
{
	return m_sphericalBoundingRadius;
}

D3DXVECTOR3* Object::GetBoundingBox() const
{
	return m_boundingBox;
} 

float* Object::GetBoundingBoxVertices() const
{
	return m_boundingBoxVertices;
}