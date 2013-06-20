////////////////////////////////////////////////////////////////////////////////
// Filename: shadermanager.cpp
// Code Adapted from tutorial http://www.rastertek.com/dx11tut45.html
////////////////////////////////////////////////////////////////////////////////
#include "shadermanager.h"
#include "textureshader.h"
#include "lightshader.h"
#include "purelightshader.h"
#include "fontshader.h"
#include "reflectionshader.h"
#include "terrainshader.h"
#include "skydomeshader.h"
#include "cloudsshader.h"
#include "watershader.h"
#include "terrainreflectionshader.h"
#include "particleshader.h"
#include "horizontalblurshader.h"
#include "verticalblurshader.h"
#include "orthowindow.h"
#include "fireshader.h"
#include "convolutionshader.h"
#include "glowmapshader.h"
#include "glowshader.h"


ShaderManager::ShaderManager()
{

	m_TextureShader = 0;
	m_LightShader = 0;
	m_PureLightShader = 0;
	m_FontShader = 0;
	m_ReflectionShader = 0;
	m_TerrainShader = 0;
	m_SkyDomeShader = 0;
	m_CloudsShader = 0;
	m_WaterShader = 0;
	m_TerrainReflectionShader = 0;
	m_ParticleShader = 0;
	m_HorizontalBlurShader = 0;
	m_VerticalBlurShader = 0;
	m_FireShader = 0;
	m_ConvolutionShader = 0;
	m_GlowShader = 0;
	m_GlowMapShader = 0;
}


ShaderManager::ShaderManager(const ShaderManager& other)
{
}


ShaderManager::~ShaderManager()
{
}


bool ShaderManager::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	// Create the texture shader object.
	m_TextureShader = new TextureShader;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShader;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the pure light shader object.
	m_PureLightShader = new PureLightShader;
	if(!m_PureLightShader)
	{
		return false;
	}

	// Initialize the pure light shader object.
	result = m_PureLightShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the pure light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the font shader object.
	m_FontShader = new FontShader;
	if(!m_PureLightShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the reflection light shader object.
	m_ReflectionShader = new ReflectionShader;
	if(!m_ReflectionShader)
	{
		return false;
	}

	// Initialize the reflection light shader object.
	result = m_ReflectionShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object.
	m_TerrainShader = new TerrainShader;
	if(!m_TerrainShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_TerrainShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky dome shader object.
	m_SkyDomeShader = new SkyDomeShader;
	if(!m_SkyDomeShader)
	{
		return false;
	}

	// Initialize the sky dome shader object.
	result = m_SkyDomeShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the clouds shader object.
	m_CloudsShader = new CloudsShader;
	if(!m_CloudsShader)
	{
		return false;
	}

	// Initialize the clouds shader object.
	result = m_CloudsShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the clouds shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the water shader object.
	m_WaterShader = new WaterShader;
	if(!m_WaterShader)
	{
		return false;
	}

	// Initialize the water shader object.
	result = m_WaterShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the water shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain reflection light shader object.
	m_TerrainReflectionShader = new TerrainReflectionShader;
	if(!m_TerrainReflectionShader)
	{
		return false;
	}

	// Initialize the terrain reflection light shader object.
	result = m_TerrainReflectionShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain reflection shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the particle shader object.
	m_ParticleShader = new ParticleShader;
	if(!m_ParticleShader)
	{
		return false;
	}

	// Initialize the particle shader object.
	result = m_ParticleShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the horizontal blur shader object.
	m_HorizontalBlurShader = new HorizontalBlurShader;
	if(!m_HorizontalBlurShader)
	{
		return false;
	}

	// Initialize the horizontal blur shader object.
	result = m_HorizontalBlurShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the horizontal blur shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the vertical blur shader object.
	m_VerticalBlurShader = new VerticalBlurShader;
	if(!m_VerticalBlurShader)
	{
		return false;
	}

	// Initialize the vertical blur shader object.
	result = m_VerticalBlurShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the vertical blur shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the convolution shader object.
	m_ConvolutionShader = new ConvolutionShader;
	if(!m_ConvolutionShader)
	{
		return false;
	}

	// Initialize the vertical blur shader object.
	result = m_ConvolutionShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the convolution shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the fire shader object.
	m_FireShader = new FireShader;
	if(!m_FireShader)
	{
		return false;
	}

	// Initialize the fire shader object.
	result = m_FireShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the glow map shader object.
	m_GlowMapShader = new GlowMapShader;
	if(!m_GlowMapShader)
	{
		return false;
	}

	// Initialize the glow map shader object.
	result = m_GlowMapShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the glow map shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the glow shader object.
	m_GlowShader = new GlowShader;
	if(!m_GlowShader)
	{
		return false;
	}

	// Initialize the glow shader object.
	result = m_GlowShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the glow shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void ShaderManager::Shutdown()
{
	// Release the glow shader object.
	if(m_GlowShader)
	{
		m_GlowShader->Shutdown();
		delete m_GlowShader;
		m_GlowShader = 0;
	}

	// Release the glow map shader object.
	if(m_GlowMapShader)
	{
		m_GlowMapShader->Shutdown();
		delete m_GlowMapShader;
		m_GlowMapShader = 0;
	}

	// Release the fire shader object.
	if(m_FireShader)
	{
		m_FireShader->Shutdown();
		delete m_FireShader;
		m_FireShader = 0;
	}

	// Release the convolution blur shader object.
	if(m_ConvolutionShader)
	{
		m_ConvolutionShader->Shutdown();
		delete m_ConvolutionShader;
		m_ConvolutionShader = 0;
	}


	// Release the vertical blur shader object.
	if(m_VerticalBlurShader)
	{
		m_VerticalBlurShader->Shutdown();
		delete m_VerticalBlurShader;
		m_VerticalBlurShader = 0;
	}

	// Release the horizontal blur shader object.
	if(m_HorizontalBlurShader)
	{
		m_HorizontalBlurShader->Shutdown();
		delete m_HorizontalBlurShader;
		m_HorizontalBlurShader = 0;
	}

	// Release the particle shader object.
	if(m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}

	// Release the terrain reflection shader object.
	if(m_TerrainReflectionShader)
	{
		m_TerrainReflectionShader->Shutdown();
		delete m_TerrainReflectionShader;
		m_TerrainReflectionShader = 0;
	}

	// Release the water shader object.
	if(m_WaterShader)
	{
		m_WaterShader->Shutdown();
		delete m_WaterShader;
		m_WaterShader = 0;
	}

	// Release the clouds shader object.
	if(m_CloudsShader)
	{
		m_CloudsShader->Shutdown();
		delete m_CloudsShader;
		m_CloudsShader = 0;
	}

	// Release the sky dome shader object.
	if(m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = 0;
	}

	// Release the terrain shader object.
	if(m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	// Release the reflection shader object.
	if(m_ReflectionShader)
	{
		m_ReflectionShader->Shutdown();
		delete m_ReflectionShader;
		m_ReflectionShader = 0;
	}

	// Release the font shader object.
	if(m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}
	
	// Release the pure light shader object.
	if(m_PureLightShader)
	{
		m_PureLightShader->Shutdown();
		delete m_PureLightShader;
		m_PureLightShader = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	return;
}


bool ShaderManager::RenderTextureShader(ID3D11DeviceContext* device, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, 
					     ID3D11ShaderResourceView* texture)
{
	bool result;

	// Render the model using the texture shader.
	result = m_TextureShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if(!result)
	{
		return false;
	}

	return true;
}


bool ShaderManager::RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
							  D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientColor,
							  D3DXVECTOR4 diffuseColor, D3DXVECTOR3 cameraPosition, D3DXVECTOR4 specularColor, float specularPower)
{
	bool result;

	// Render the model using the light shader.
	result = m_LightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambientColor,
							  diffuseColor, cameraPosition, specularColor, specularPower);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderPureLightShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
							  D3DXMATRIX projectionMatrix , D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor, D3DXVECTOR3 cameraPosition, D3DXVECTOR4 specularColor, float specularPower, float deltavalue)
{
	bool result;

	// Render the model using the light shader.
	result = m_PureLightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, 
		                               lightDirection, ambientColor, diffuseColor, cameraPosition, specularColor, specularPower, deltavalue);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderReflectionShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, 
				   D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture,
				   ID3D11ShaderResourceView* reflectionTexture, D3DXMATRIX reflectionMatrix)
{
	bool result;

	// Render the model using the light shader.
	result = m_ReflectionShader->Render(deviceContext, indexCount, worldMatrix, 
				   viewMatrix, projectionMatrix, texture, reflectionTexture, reflectionMatrix);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderFontShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
			     D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, D3DXVECTOR4 pixelColor)
{
	bool result;
	
	// Render using the font shader.
	m_TerrainShader;
	result = m_FontShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, pixelColor);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderTerrainShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
	                     D3DXMATRIX projectionMatrix, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor, D3DXVECTOR3 lightDirection, ID3D11ShaderResourceView* grassTexture, ID3D11ShaderResourceView* slopeTexture, ID3D11ShaderResourceView* rockTexture, ID3D11ShaderResourceView* detailTexture)
{
	bool result;

	// Render using the terrain shader.
	result = m_TerrainShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, ambientColor, diffuseColor, lightDirection, grassTexture, slopeTexture, rockTexture, detailTexture);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderSkyDomeShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
								D3DXMATRIX projectionMatrix, D3DXVECTOR4 apexColor, D3DXVECTOR4 centerColor)
{
	bool result;

	// Render using the sky dome shader.
	result = m_SkyDomeShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, apexColor, centerColor);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderCloudsShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
				 D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* cloudTexture1, ID3D11ShaderResourceView* cloudTexture2, ID3D11ShaderResourceView* perturbTexture, 
				 D3DXVECTOR2 translation, D3DXVECTOR2 scale, D3DXVECTOR2 brightness)
{
	bool result;

	// Render using the clouds shader.
	result = m_CloudsShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, cloudTexture1, cloudTexture2, perturbTexture, translation, scale, brightness);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderTerrainReflectionShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
								   D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, 
								   D3DXVECTOR4 lightDiffuseColor, D3DXVECTOR3 lightDirection, float colorTextureBrightness, D3DXVECTOR4 clipPlane)
{
	bool result;

	// Render using the terrain reflection shader.
	result = m_TerrainReflectionShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, 
								   lightDiffuseColor, lightDirection, colorTextureBrightness, clipPlane);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderWaterShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
							  D3DXMATRIX projectionMatrix, D3DXMATRIX reflectionMatrix, ID3D11ShaderResourceView* refractionTexture, 
							  ID3D11ShaderResourceView* reflectionTexture, ID3D11ShaderResourceView* normalTexture, D3DXVECTOR3 cameraPosition, 
							  D3DXVECTOR2 normalMapTiling, float waterTranslation, float reflectRefractScale, D3DXVECTOR4 refractionTint, 
							  D3DXVECTOR3 lightDirection, float specularShininess)
{
	bool result;

	// Render using the water shader.
	result = m_WaterShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix, refractionTexture, 
							  reflectionTexture, normalTexture, cameraPosition, normalMapTiling, waterTranslation, reflectRefractScale, refractionTint, 
							  lightDirection, specularShininess);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderParticleShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
								D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
	bool result;

	// Render using the particle shader.
	result = m_ParticleShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderHorizontalBlurShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
									 D3DXMATRIX orthoMatrix, ID3D11ShaderResourceView* texture, float screenWidth, D3DXVECTOR4 blurWeightingRow1, D3DXVECTOR4 blurWeightingRow2, D3DXVECTOR4 blurWeightingRow3)
{
	bool result;

	// Render using the horizontal blur shader.

	result = m_HorizontalBlurShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, orthoMatrix, texture, screenWidth, blurWeightingRow1, blurWeightingRow2, blurWeightingRow3);
	if(!result)
	{
		return false;
	}

	return true;
}


bool ShaderManager::RenderVerticalBlurShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
									 D3DXMATRIX orthoMatrix, ID3D11ShaderResourceView* texture, float screenHeight, D3DXVECTOR4 blurWeightingRow1, D3DXVECTOR4 blurWeightingRow2, D3DXVECTOR4 blurWeightingRow3)
{
	bool result;

	// Render using the vertical blur shader.
	result = m_VerticalBlurShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, orthoMatrix, texture, screenHeight, blurWeightingRow1, blurWeightingRow2, blurWeightingRow3);
	if(!result)
	{
		return false;
	}

	return true;
}


bool ShaderManager::RenderConvolutionShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
	D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, float screenWidth, D3DXVECTOR4 kernelRow1, D3DXVECTOR4 kernelRow2, D3DXVECTOR4 kernelRow3)
{
	bool result;

	// Render using the convolution shader.
	result = m_ConvolutionShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, screenWidth, kernelRow1, kernelRow2, kernelRow3);
	if(!result)
	{
		return false;
	}

	return true;
}


bool ShaderManager::RenderFireShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
							 D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* fireTexture, 
							 ID3D11ShaderResourceView* noiseTexture, ID3D11ShaderResourceView* alphaTexture, float frameTime,
							 D3DXVECTOR3 scrollSpeeds, D3DXVECTOR3 scales, D3DXVECTOR2 distortion1, D3DXVECTOR2 distortion2,
							 D3DXVECTOR2 distortion3, float distortionScale, float distortionBias)
{
	bool result;

	// Render using the fire shader.
	result = m_FireShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, fireTexture, noiseTexture,	
									alphaTexture, frameTime, scrollSpeeds, scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderGlowMapShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
				D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, D3DXVECTOR4 tint)
{
	bool result;

	result = m_GlowMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture,  tint);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManager::RenderGlowShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
			     D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* glowTexture, 
			     float glowStrength)
{
	bool result;

	result = m_GlowShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, glowTexture, glowStrength);
	if(!result)
	{
		return false;
	}

	return true;
}

FontShader* ShaderManager::GetFontShader()
{
	return m_FontShader;
}