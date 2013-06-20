////////////////////////////////////////////////////////////////////////////////
// Filename: objectfireparticle.cpp
////////////////////////////////////////////////////////////////////////////////

#include "objectfireparticle.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "graphicsManager.h"
#include "particlegenerator.h"
#include "texture.h"

ObjectFireParticle::ObjectFireParticle(D3D* d3d)
{	
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Create the rain particle generator.
	m_FireGenerator = new ParticleGenerator;
	m_FireGenerator->Initialize(d3d->GetDevice(), m_position, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, D3DXVECTOR3(-0.5f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, -0.1f), D3DXVECTOR2(0.1f, 0.1f), D3DXVECTOR2(3.0f, 3.0f), D3DXVECTOR2(40.0f, 40.0f), D3DXVECTOR2(0.0f, 0.0f), 1.0f, 2, 3600.0f);;
	// Create and initialize the texture objects.
	m_FireTexture = new Texture;
	m_FireTexture->Initialize(d3d->GetDevice(), L"../Engine/data/fire02.dds");
	m_FireNoiseTexture = new Texture;
	m_FireNoiseTexture->Initialize(d3d->GetDevice(), L"../Engine/data/noise01.dds");
	m_FireAlphaTexture = new Texture;
	m_FireAlphaTexture->Initialize(d3d->GetDevice(), L"../Engine/data/cloudalpha02.dds");
}


ObjectFireParticle::ObjectFireParticle(const ObjectFireParticle& other)
{
}


ObjectFireParticle::~ObjectFireParticle()
{
	m_FireGenerator->Shutdown();
	delete m_FireGenerator;
}


void ObjectFireParticle::Frame(D3D* d3d, float time)
{
	m_FireGenerator->Frame(time, d3d->GetDeviceContext());
}


bool ObjectFireParticle::Render(GraphicsManager& graphicsManager, int renderPass)
{
	static float frameTime = 0.0f;

	// Render Scene.
	if(renderPass == 0)
	{
		// Turn on the alpha blending.
		graphicsManager.GetD3DObject()->TurnOnAlphaBlending();

		// Increment the frame time counter.
		frameTime += 0.016666f;

		// Render Fire.
		RenderFire(graphicsManager, frameTime);		
		
		// Turn off blending.
		graphicsManager.GetD3DObject()->TurnOffAlphaBlending();

		return true;
	}

	return true;
}

bool ObjectFireParticle::RenderFire(GraphicsManager& graphicsManager, float frameTime)
{
	D3DXMATRIX worldMatrix, viewMatrix, newViewMatrix, projectionMatrix, reflectionMatrix, translateMatrix, rotationMatrix;
	D3DXVECTOR3 scrollSpeeds, scales;
	D3DXVECTOR2 distortion1, distortion2, distortion3;
	bool result;
	float distortionScale, distortionBias;

	// Get the world, view, and projection matrices from the camera and d3d objects.
	worldMatrix = graphicsManager.GetWorldMatrix();
	viewMatrix = graphicsManager.GetViewMatrix();
	projectionMatrix= graphicsManager.GetProjectionMatrix();

	// Set the three scrolling speeds for the three different noise textures.
	scrollSpeeds = D3DXVECTOR3(0.3f, 0.5f, 0.8f);

	// Set the three scales which will be used to create the three different noise octave textures.
	scales = D3DXVECTOR3(1.0f, 2.0f, 3.0f);

	// Set the three different x and y distortion factors for the three different noise textures.
	distortion1 = D3DXVECTOR2(0.1f, 0.2f);
	distortion2 = D3DXVECTOR2(0.1f, 0.3f);
	distortion3 = D3DXVECTOR2(0.1f, 0.1f);

	// The the scale and bias of the texture coordinate sampling perturbation.
	distortionScale = 0.8f;
	distortionBias = 0.5f;

	graphicsManager.GetCamera()->GetBillboardedWorldMatrix(worldMatrix, m_position);
	m_FireGenerator->Render(graphicsManager.GetD3DObject()->GetDeviceContext());
	// Render the model using the light shader.
	//result = graphicsManager.GetShaderManager()->RenderParticleShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_FireGenerator->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_FireTexture->GetTexture());
	//result = graphicsManager.GetShaderManager()->RenderTextureShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_FireGenerator->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_FireGenerator->GetTexture() );
	result = graphicsManager.GetShaderManager()->RenderFireShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_FireGenerator->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_FireTexture->GetTexture(), m_FireNoiseTexture->GetTexture(), m_FireAlphaTexture->GetTexture(), frameTime, scrollSpeeds, scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if(!result)
	{
		return false;
	}

	return true;
}

void ObjectFireParticle::SetPosition(D3DXVECTOR3 position)
{
	m_position = position;
}

void ObjectFireParticle::SetRotation(D3DXVECTOR3 rotation)
{
	m_rotation = rotation;
}