////////////////////////////////////////////////////////////////////////////////
// Filename: objectweatherparticle.cpp
////////////////////////////////////////////////////////////////////////////////

#include "objectweatherparticle.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "graphicsManager.h"
#include "particlegenerator.h"
#include "texture.h"

ObjectWeatherParticle::ObjectWeatherParticle(D3D* d3d)
{	
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Create the rain particle generator.
	m_RainGenerator = new ParticleGenerator;
	m_RainGenerator->Initialize(d3d->GetDevice(), m_position, D3DXVECTOR3(128.0f, 0.0f, 128.0f), 0.0f, D3DXVECTOR3(0.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), D3DXVECTOR2(2.0f, 2.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 100.0f, 100, 2.0f);
	// Create and initialize the texture objects.
	m_RainTexture = new Texture;
	m_RainTexture->Initialize(d3d->GetDevice(), L"../Engine/data/star.dds");
	m_RainNoiseTexture = new Texture;
	m_RainNoiseTexture->Initialize(d3d->GetDevice(), L"../Engine/data/noise01.dds");
	m_RainAlphaTexture = new Texture;
	m_RainAlphaTexture->Initialize(d3d->GetDevice(), L"../Engine/data/lensflarealpha03.dds");
}


ObjectWeatherParticle::ObjectWeatherParticle(const ObjectWeatherParticle& other)
{
}


ObjectWeatherParticle::~ObjectWeatherParticle()
{
	m_RainGenerator->Shutdown();
	delete m_RainGenerator;
}


void ObjectWeatherParticle::Frame(D3D* d3d, float time)
{
	m_RainGenerator->Frame(time, d3d->GetDeviceContext());
}


bool ObjectWeatherParticle::Render(GraphicsManager& graphicsManager, int renderPass)
{
	static float frameTime = 0.0f;

	// Render Scene.
	if(renderPass == 0)
	{
		// Turn on the alpha blending.
		graphicsManager.GetD3DObject()->TurnOnSecondaryAlphaBlending();
		//graphicsManager.GetD3DObject()->TurnOnAlphaBlending();
		//graphicsManager.GetD3DObject()->TurnZBufferOff();
		//graphicsManager.GetD3DObject()->TurnOffCulling();

		// Increment the frame time counter.
		frameTime += 0.016666f;

		// Render Rain.
		RenderRain(graphicsManager, frameTime);		
		
		// Turn off blending.
		graphicsManager.GetD3DObject()->TurnOffAlphaBlending();
		//graphicsManager.GetD3DObject()->TurnOnCulling();
		//graphicsManager.GetD3DObject()->TurnZBufferOn();


		return true;
	}

	return true;
}

bool ObjectWeatherParticle::RenderRain(GraphicsManager& graphicsManager, float frameTime)
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
	scrollSpeeds = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// Set the three scales which will be used to create the three different noise octave textures.
	scales = D3DXVECTOR3(1.0f, 2.0f, 3.0f);
	// Set the three different x and y distortion factors for the three different noise textures.
	distortion1 = D3DXVECTOR2(0.0f, 0.0f);
	distortion2 = D3DXVECTOR2(0.0f, 0.0f);
	distortion3 = D3DXVECTOR2(0.0f, 0.0f);

	// Set the scale and bias of the texture coordinate sampling perturbation.
	distortionScale = 0.8f;
	distortionBias = 0.5f;

	graphicsManager.GetCamera()->GetBillboardedWorldMatrix(worldMatrix, m_position);
	m_RainGenerator->Render(graphicsManager.GetD3DObject()->GetDeviceContext());
	// Render the model using the light shader.
	//result = graphicsManager.GetShaderManager()->RenderParticleShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_RainGenerator->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_RainTexture->GetTexture());
	//result = graphicsManager.GetShaderManager()->RenderTextureShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_RainGenerator->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_RainGenerator->GetTexture() );
	result = graphicsManager.GetShaderManager()->RenderFireShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_RainGenerator->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_RainTexture->GetTexture(), m_RainNoiseTexture->GetTexture(), m_RainAlphaTexture->GetTexture(), frameTime, scrollSpeeds, scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if(!result)
	{
		return false;
	}

	return true;
}

void ObjectWeatherParticle::SetPosition(D3DXVECTOR3 position)
{
	m_position = position;
}

void ObjectWeatherParticle::SetRotation(D3DXVECTOR3 rotation)
{
	m_rotation = rotation;
}