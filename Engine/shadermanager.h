////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderManager.h
// Code Adapted from tutorial http://www.rastertek.com/dx11tut45.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHADERMANAGER_H_
#define _SHADERMANAGER_H_


///////////////////////
// MY  INCLUDES //
///////////////////////
#include "d3d.h"

class ColorShader;
class TextureShader;
class LightShader;
class PureLightShader;
class FontShader;
class ReflectionShader;
class TerrainShader;
class SkyDomeShader;
class CloudsShader;
class WaterShader;
class TerrainReflectionShader;
class ParticleShader;
class FireShader;
class ConvolutionShader;
class HorizontalBlurShader;
class VerticalBlurShader;
class GlowMapShader;
class GlowShader;


////////////////////////////////////////////////////////////////////////////////
//  name: ShaderManager
////////////////////////////////////////////////////////////////////////////////
class ShaderManager
{
public:
	ShaderManager();
	ShaderManager(const ShaderManager&);
	~ShaderManager();

	bool Initialize(ID3D11Device* device, HWND hwnd);
	void Shutdown();


	bool RenderTextureShader(ID3D11DeviceContext* device, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, 
					     ID3D11ShaderResourceView* texture);

	bool RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
							  D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientColor,
							  D3DXVECTOR4 diffuseColor, D3DXVECTOR3 cameraPosition, D3DXVECTOR4 specularColor, float specularPower);

	bool RenderPureLightShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
							  D3DXMATRIX projectionMatrix , D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor, D3DXVECTOR3 cameraPosition, D3DXVECTOR4 specularColor, float specularPower, float deltavalue);

	bool RenderFontShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
			     D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, D3DXVECTOR4 pixelColor);

	bool RenderReflectionShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, 
				   D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture,
				   ID3D11ShaderResourceView* reflectionTexture, D3DXMATRIX reflectionMatrix);

	bool RenderTerrainShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
								D3DXMATRIX projectionMatrix, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor, D3DXVECTOR3 lightDirection, ID3D11ShaderResourceView* grassTexture, ID3D11ShaderResourceView* slopeTexture, ID3D11ShaderResourceView* rockTexture, ID3D11ShaderResourceView* detailTexture);

	bool RenderSkyDomeShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
								D3DXMATRIX projectionMatrix, D3DXVECTOR4 apexColor, D3DXVECTOR4 centerColor);

	bool RenderCloudsShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
				 D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* cloudTexture1, ID3D11ShaderResourceView* cloudTexture2, ID3D11ShaderResourceView* perturbTexture, 
				 D3DXVECTOR2 translation, D3DXVECTOR2 scale, D3DXVECTOR2 brightness);
	
	bool RenderTerrainReflectionShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
								   D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, 
								   D3DXVECTOR4 lightDiffuseColor, D3DXVECTOR3 lightDirection, float colorTextureBrightness, D3DXVECTOR4 clipPlane);

	bool RenderWaterShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
							  D3DXMATRIX projectionMatrix, D3DXMATRIX reflectionMatrix, ID3D11ShaderResourceView* refractionTexture, 
							  ID3D11ShaderResourceView* reflectionTexture, ID3D11ShaderResourceView* normalTexture, D3DXVECTOR3 cameraPosition, 
							  D3DXVECTOR2 normalMapTiling, float waterTranslation, float reflectRefractScale, D3DXVECTOR4 refractionTint, 
							  D3DXVECTOR3 lightDirection, float specularShininess);

	bool RenderParticleShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
								D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture);

	bool RenderHorizontalBlurShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
									   D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, float screenWidth, D3DXVECTOR4 blurWeightingRow1, D3DXVECTOR4 blurWeightingRow2, D3DXVECTOR4 blurWeightingRow3);

	bool RenderVerticalBlurShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
									 D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, float screenHeight, D3DXVECTOR4 blurWeightingRow1, D3DXVECTOR4 blurWeightingRow2, D3DXVECTOR4 blurWeightingRow3);

	bool RenderFireShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
							 D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* fireTexture, 
							 ID3D11ShaderResourceView* noiseTexture, ID3D11ShaderResourceView* alphaTexture, float frameTime,
							 D3DXVECTOR3 scrollSpeeds, D3DXVECTOR3 scales, D3DXVECTOR2 distortion1, D3DXVECTOR2 distortion2,
							 D3DXVECTOR2 distortion3, float distortionScale, float distortionBias);
	
	bool RenderConvolutionShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
									   D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, float screenWidth, D3DXVECTOR4 kernelRow1, D3DXVECTOR4 kernelRow2, D3DXVECTOR4 kernelRow3);

	bool RenderGlowMapShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
				D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, D3DXVECTOR4 tint);

	bool RenderGlowShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
			     D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* glowTexture, 
			     float glowStrength);

	FontShader* GetFontShader();
private:
	TextureShader* m_TextureShader;
	LightShader* m_LightShader;
	PureLightShader* m_PureLightShader;
	FontShader* m_FontShader;
	ReflectionShader* m_ReflectionShader;
	TerrainShader* m_TerrainShader;
	SkyDomeShader* m_SkyDomeShader;
	CloudsShader* m_CloudsShader;
	TerrainReflectionShader* m_TerrainReflectionShader;
	WaterShader* m_WaterShader;
	ParticleShader* m_ParticleShader;
	HorizontalBlurShader* m_HorizontalBlurShader;
	VerticalBlurShader* m_VerticalBlurShader;
	FireShader* m_FireShader;
	ConvolutionShader * m_ConvolutionShader;
	GlowMapShader * m_GlowMapShader;
	GlowShader * m_GlowShader;
};

#endif //_SHADERMANAGER_H_
