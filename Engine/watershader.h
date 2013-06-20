////////////////////////////////////////////////////////////////////////////////
// Filename: watershader.h
// Adapted from http://www.rastertek.com/tertut16.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _WATERSHADER_H_
#define _WATERSHADER_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
//  name: WaterShader
////////////////////////////////////////////////////////////////////////////////
class WaterShader
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
		D3DXMATRIX reflection;
	};

	struct CamNormBufferType
	{
		D3DXVECTOR3 cameraPosition;
		float padding1;
		D3DXVECTOR2 normalMapTiling;
		D3DXVECTOR2 padding2;
	};

	struct WaterBufferType
	{
		D3DXVECTOR4 refractionTint;
		D3DXVECTOR3 lightDirection;
		float waterTranslation;
		float reflectRefractScale;
		float specularShininess;
		D3DXVECTOR2 padding;
	};

public:
	WaterShader();
	WaterShader(const WaterShader&);
	~WaterShader();

	bool Initialize(ID3D11Device* device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
							  D3DXMATRIX projectionMatrix, D3DXMATRIX reflectionMatrix, ID3D11ShaderResourceView* refractionTexture, 
							  ID3D11ShaderResourceView* reflectionTexture, ID3D11ShaderResourceView* normalTexture, D3DXVECTOR3 cameraPosition, 
							  D3DXVECTOR2 normalMapTiling, float waterTranslation, float reflectRefractScale, D3DXVECTOR4 refractionTint, 
							  D3DXVECTOR3 lightDirection, float specularShininess);

private:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix,
										   D3DXMATRIX reflectionMatrix, ID3D11ShaderResourceView* refractionTexture, ID3D11ShaderResourceView* reflectionTexture, 
										   ID3D11ShaderResourceView* normalTexture, D3DXVECTOR3 cameraPosition, D3DXVECTOR2 normalMapTiling, 
										   float waterTranslation, float reflectRefractScale, D3DXVECTOR4 refractionTint, D3DXVECTOR3 lightDirection, float specularShininess);
	
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_camNormBuffer;
	ID3D11Buffer* m_waterBuffer;
};

#endif