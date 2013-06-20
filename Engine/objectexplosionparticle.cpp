////////////////////////////////////////////////////////////////////////////////
// Filename: objectparticle.cpp
////////////////////////////////////////////////////////////////////////////////

#include "objectexplosionparticle.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "graphicsManager.h"
#include "particlegenerator.h"
#include "texture.h"

ObjectExplosionParticle::ObjectExplosionParticle(D3D* d3d)
{	
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Create the particle system object.
	//m_FireGenerator = new ParticleGenerator;
	//Initialize the particle system object.
	////Fire.
	//m_FireGenerator->Initialize(d3d->GetDevice(), m_position, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, D3DXVECTOR3(0.0f, 0.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.01f, 0.01f), D3DXVECTOR2(4.0f, 4.0f), D3DXVECTOR2(0.25f, 0.25f), D3DXVECTOR2(0.0f, 0.0f), 4.0f, 50, 3.0f, 2.0f, 0.0f);
	//// Create and initialize the texture object.
	//m_Texture1 = new Texture;
	//m_Texture1->Initialize(d3d->GetDevice(), L"../Engine/data/fire02.dds");
	//// Create and initialize the texture object.
	//m_Texture2 = new Texture;
	//m_Texture2->Initialize(d3d->GetDevice(), L"../Engine/data/noise01.dds");
	//// Create and initialize the texture object.
	//m_Texture3 = new Texture;
	//m_Texture3->Initialize(d3d->GetDevice(), L"../Engine/data/flamealpha01.dds");

	// Create the flash particle system object.
	m_FlashGenerator = new ParticleGenerator;
	m_FlashGenerator->Initialize(d3d->GetDevice(), m_position, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, D3DXVECTOR3(0.0f, 0.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, -0.95f), D3DXVECTOR2(0.01f, 0.01f), D3DXVECTOR2(25.0f, 25.0f), D3DXVECTOR2(200.0f, 200.0f), D3DXVECTOR2(0.0f, 0.0f), 1.0f, 2, 3600.0f);
	// Create and initialize the texture objects.
	m_FlashTexture = new Texture;
	m_FlashTexture->Initialize(d3d->GetDevice(), L"../Engine/data/lensflaretex01.dds");
	m_FlashNoiseTexture = new Texture;
	m_FlashNoiseTexture->Initialize(d3d->GetDevice(), L"../Engine/data/noise01.dds");
	m_FlashAlphaTexture = new Texture;
	m_FlashAlphaTexture->Initialize(d3d->GetDevice(), L"../Engine/data/lensflarealpha03.dds");


	// White hot core
	m_WhiteCoreGenerator = new ParticleGenerator;
	m_WhiteCoreGenerator->Initialize(d3d->GetDevice(), m_position, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, D3DXVECTOR3(-0.5f, 0.5f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, -0.25f), D3DXVECTOR2(0.1f, 0.1f), D3DXVECTOR2(3.0f, 3.0f), D3DXVECTOR2(30.0f, 30.0f), D3DXVECTOR2(0.0f, 0.0f), 1.0f, 2, 3600.0f);
	//m_WhiteCoreGenerator->Initialize(d3d->GetDevice(), m_position, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.25f, D3DXVECTOR3(-0.5f, 0.5f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, -0.25f), D3DXVECTOR2(0.1f, 0.1f), D3DXVECTOR2(0.1f, 0.1f), D3DXVECTOR2(2.0f, 2.0f), D3DXVECTOR2(0.0f, 0.0f), 20.0f, 20, 5.0f);
	// Create and initialize the texture objects.
	m_WhiteCoreTexture = new Texture;
	m_WhiteCoreTexture->Initialize(d3d->GetDevice(), L"../Engine/data/whitehotcoretex01.dds");
	m_WhiteCoreNoiseTexture = new Texture;
	m_WhiteCoreNoiseTexture->Initialize(d3d->GetDevice(), L"../Engine/data/noise01.dds");
	m_WhiteCoreAlphaTexture = new Texture;
	m_WhiteCoreAlphaTexture->Initialize(d3d->GetDevice(), L"../Engine/data/cloudalpha02.dds");

	// Fireball
	m_FireballGenerator = new ParticleGenerator;
	m_FireballGenerator->Initialize(d3d->GetDevice(), m_position, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, D3DXVECTOR3(-0.5f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, -0.25f), D3DXVECTOR2(0.1f, 0.1f), D3DXVECTOR2(3.0f, 3.0f), D3DXVECTOR2(25.0f, 25.0f), D3DXVECTOR2(0.0f, 0.0f), 1.0f, 2, 3600.0f);
	//m_FireballGenerator->Initialize(d3d->GetDevice(), m_position, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.1f, D3DXVECTOR3(0.0f, 0.0f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.8f, 0.8f, 0.8f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, -0.25f), D3DXVECTOR2(0.01f, 0.01f), D3DXVECTOR2(0.05f, 0.05f), D3DXVECTOR2(5.0f, 5.0f), D3DXVECTOR2(0.0f, 0.0f), 60.0f, 50, 10.0f);
	// Create and initialize the texture object.
	m_FireballTexture = new Texture;
	m_FireballTexture->Initialize(d3d->GetDevice(), L"../Engine/data/fire02.dds");
	// Create and initialize the texture object.
	m_FireballNoiseTexture = new Texture;
	m_FireballNoiseTexture->Initialize(d3d->GetDevice(), L"../Engine/data/noise01.dds");
	// Create and initialize the texture object.
	m_FireballAlphaTexture = new Texture;
	//m_FireballAlphaTexture3->Initialize(d3d->GetDevice(), L"../Engine/data/whitehotcore01.dds");
	m_FireballAlphaTexture->Initialize(d3d->GetDevice(), L"../Engine/data/cloudalpha01.dds");

	// Smoke
	m_SmokeGenerator = new ParticleGenerator;
	m_SmokeGenerator->Initialize(d3d->GetDevice(), m_position, D3DXVECTOR3(0.01f, 0.001f, 0.01f), 0.1f, D3DXVECTOR3(-0.75f, 0.75f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),  D3DXVECTOR3(-0.05f, -0.05f, 0.0f), D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, -0.25f), D3DXVECTOR2(0.01f, 0.01f), D3DXVECTOR2(0.5f, 0.5f), D3DXVECTOR2(0.1f, 0.1f), D3DXVECTOR2(0.0f, 0.0f), 50.0f, 500, 8.0f);
	// Create and initialize the texture object.
	m_SmokeTexture = new Texture;
	m_SmokeTexture->Initialize(d3d->GetDevice(), L"../Engine/data/smoketex02.dds");
	// Create and initialize the texture object.
	m_SmokeNoiseTexture = new Texture;
	m_SmokeNoiseTexture->Initialize(d3d->GetDevice(), L"../Engine/data/noise01.dds");
	// Create and initialize the texture object.
	m_SmokeAlphaTexture = new Texture;
	//m_SmokeAlphaTexture->Initialize(d3d->GetDevice(), L"../Engine/data/whitehotcore01.dds");
	m_SmokeAlphaTexture->Initialize(d3d->GetDevice(), L"../Engine/data/cloudalpha01.dds");

	////Debris
	//m_DebrisGenerator = new ParticleGenerator;
	//m_DebrisGenerator->Initialize(d3d->GetDevice(), m_position, D3DXVECTOR3(0.01f, 0.001f, 0.01f), 0.0f, D3DXVECTOR3(0.0f, 0.25f, 0.075f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),  D3DXVECTOR3(0.0f, -0.05f, 0.0f), D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.01f, 0.01f), D3DXVECTOR2(0.5f, 0.5f), D3DXVECTOR2(0.1f, 0.1f), D3DXVECTOR2(0.0f, 0.0f), 50.0f, 20, 2.0f);
	////m_DebrisGenerator->Initialize(d3d->GetDevice(), m_position, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.1f, D3DXVECTOR3(0.0f, 0.0f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.8f, 0.8f, 0.8f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, -0.25f), D3DXVECTOR2(0.01f, 0.01f), D3DXVECTOR2(0.05f, 0.05f), D3DXVECTOR2(5.0f, 5.0f), D3DXVECTOR2(0.0f, 0.0f), 60.0f, 50, 10.0f);
	//// Create and initialize the texture object.
	//m_DebrisTexture = new Texture;
	//m_DebrisTexture->Initialize(d3d->GetDevice(), L"../Engine/data/explosiontex03.dds");
	//// Create and initialize the texture object.
	//m_DebrisNoiseTexture = new Texture;
	//m_DebrisNoiseTexture->Initialize(d3d->GetDevice(), L"../Engine/data/noise01.dds");
	//// Create and initialize the texture object.
	//m_DebrisAlphaTexture3 = new Texture;
	////m_DebrisAlphaTexture->Initialize(d3d->GetDevice(), L"../Engine/data/whitehotcore01.dds");
	//m_DebrisAlphaTexture->Initialize(d3d->GetDevice(), L"../Engine/data/cloudalpha01.dds");

	//// Create the texture object.
	//m_Texture2 = new Texture;
	//// Initialize the texture object.
	//m_Texture2->Initialize(d3d->GetDevice(), L"../Engine/data/noise01.dds");
	////m_Texture2->Initialize(d3d->GetDevice(), L"../Engine/data/cloud003.dds");
	//// Create the texture object.
	//m_Texture3 = new Texture;
	//// Initialize the texture object.
	////m_Texture3->Initialize(d3d->GetDevice(), L"../Engine/data/cloud004.dds");
	////m_Texture3->Initialize(d3d->GetDevice(), L"../Engine/data/lensflarealpha02.dds");
	////m_Texture3->Initialize(d3d->GetDevice(), L"../Engine/data/alpha01.dds");
	//m_Texture3->Initialize(d3d->GetDevice(), L"../Engine/data/lensflare01.dds");
	////m_Texture3->Initialize(d3d->GetDevice(), L"../Engine/data/star.dds");
	//// Create the texture object.
	//m_Texture4 = new Texture;
	//// Initialize the texture object.
	//m_Texture4->Initialize(d3d->GetDevice(), L"../Engine/data/star.dds");
}


ObjectExplosionParticle::ObjectExplosionParticle(const ObjectExplosionParticle& other)
{
}


ObjectExplosionParticle::~ObjectExplosionParticle()
{
	m_FlashGenerator->Shutdown();
	delete m_FlashGenerator;

	m_WhiteCoreGenerator->Shutdown();
	delete m_WhiteCoreGenerator;
	
	m_FireballGenerator->Shutdown();
	delete m_FireballGenerator;

	m_SmokeGenerator->Shutdown();
	delete m_SmokeGenerator;

	//m_DebrisGenerator->Shutdown();
	//delete m_DebrisGenerator;

}


void ObjectExplosionParticle::Frame(D3D* d3d, float time)
{
	m_FlashGenerator->Frame(time, d3d->GetDeviceContext());
	m_WhiteCoreGenerator->Frame(time, d3d->GetDeviceContext());
	m_FireballGenerator->Frame(time, d3d->GetDeviceContext());
	m_SmokeGenerator->Frame(time, d3d->GetDeviceContext());
}


bool ObjectExplosionParticle::Render(GraphicsManager& graphicsManager, int renderPass)
{
	static float frameTime = 0.0f;

	// Render Scene.
	if(renderPass == 0)
	{
		// Turn on the alpha blending.
		//graphicsManager.GetD3DObject()->TurnOnSecondaryAlphaBlending();
		graphicsManager.GetD3DObject()->TurnOnAlphaBlending();
		//graphicsManager.GetD3DObject()->TurnZBufferOff();
		//graphicsManager.GetD3DObject()->TurnOffCulling();

		// Increment the frame time counter.
		frameTime += 0.016666f;


		// Render Explosion.
		RenderFlash(graphicsManager, frameTime);
		if (frameTime > 0.5f)
			RenderWhiteCore(graphicsManager, frameTime);
		if (frameTime > 0.55f)
			RenderFireball(graphicsManager, frameTime);

		// Turn off blending.
		graphicsManager.GetD3DObject()->TurnOffAlphaBlending();
		//graphicsManager.GetD3DObject()->TurnOnCulling();
		//graphicsManager.GetD3DObject()->TurnZBufferOn();


		return true;
	}

	return true;
}

bool ObjectExplosionParticle::RenderFlash(GraphicsManager& graphicsManager, float frameTime)
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
	m_FlashGenerator->Render(graphicsManager.GetD3DObject()->GetDeviceContext());
	// Render the model using the light shader.
	//result = graphicsManager.GetShaderManager()->RenderParticleShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_FlashGenerator->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Texture3->GetTexture() );
	//result = graphicsManager.GetShaderManager()->RenderTextureShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_FlashGenerator->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_FlashGenerator->GetTexture() );
	result = graphicsManager.GetShaderManager()->RenderFireShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_FlashGenerator->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_FlashTexture->GetTexture(), m_FlashNoiseTexture->GetTexture(), m_FlashAlphaTexture->GetTexture(), frameTime, scrollSpeeds, scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ObjectExplosionParticle::RenderWhiteCore(GraphicsManager& graphicsManager, float frameTime)
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
	m_WhiteCoreGenerator->Render(graphicsManager.GetD3DObject()->GetDeviceContext());

	// Render the model using the light shader.
	result = graphicsManager.GetShaderManager()->RenderFireShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_WhiteCoreGenerator->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_WhiteCoreTexture->GetTexture(), m_WhiteCoreNoiseTexture->GetTexture(), m_WhiteCoreAlphaTexture->GetTexture(), frameTime, scrollSpeeds, scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if(!result)
	{
		return false;
	}

	return true;

}

bool ObjectExplosionParticle::RenderFireball(GraphicsManager& graphicsManager, float frameTime)
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
	scrollSpeeds = D3DXVECTOR3(1.3f, 2.1f, 2.3f);
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
	m_FireballGenerator->Render(graphicsManager.GetD3DObject()->GetDeviceContext());
	// Render the model using the light shader.
	result = graphicsManager.GetShaderManager()->RenderFireShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_FireballGenerator->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_FireballTexture->GetTexture(), m_FireballNoiseTexture->GetTexture(), m_FireballAlphaTexture->GetTexture(), frameTime, scrollSpeeds, scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if(!result)
	{
		return false;
	}

	return true;
}
bool ObjectExplosionParticle::RenderSmoke(GraphicsManager& graphicsManager, float frameTime)
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
	distortion1 = D3DXVECTOR2(0.1f, 0.5f);
	distortion2 = D3DXVECTOR2(0.1f, 0.3f);
	distortion3 = D3DXVECTOR2(0.1f, 0.1f);

	// Set the scale and bias of the texture coordinate sampling perturbation.
	distortionScale = 0.8f;
	distortionBias = 0.5f;

	graphicsManager.GetCamera()->GetBillboardedWorldMatrix(worldMatrix, m_position);
	m_SmokeGenerator->Render(graphicsManager.GetD3DObject()->GetDeviceContext());
	// Render the model using the light shader.
	result = graphicsManager.GetShaderManager()->RenderFireShader(graphicsManager.GetD3DObject()->GetDeviceContext(), m_SmokeGenerator->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_SmokeTexture->GetTexture(), m_SmokeNoiseTexture->GetTexture(), m_SmokeAlphaTexture->GetTexture(), frameTime, scrollSpeeds, scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ObjectExplosionParticle::RenderDebris(GraphicsManager& graphicsManager, float frameTime)
{


	return true;
}

void ObjectExplosionParticle::SetPosition(D3DXVECTOR3 position)
{
	m_position = position;
}

void ObjectExplosionParticle::SetRotation(D3DXVECTOR3 rotation)
{
	m_rotation = rotation;
}