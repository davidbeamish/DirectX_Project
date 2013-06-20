////////////////////////////////////////////////////////////////////////////////
// Filename: terrainreflectionshader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TERRAINREFLECTIONSHADER_H_
#define _TERRAINREFLECTIONSHADER_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
//  name: TerrainReflectionShader
////////////////////////////////////////////////////////////////////////////////
class TerrainReflectionShader
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct ClipPlaneBufferType
	{
		D3DXVECTOR4 clipPlane;
	};

	struct LightBufferType
	{
		D3DXVECTOR4 lightDiffuseColor;
		D3DXVECTOR3 lightDirection;
		float colorTextureBrightness;
	};

public:
	TerrainReflectionShader();
	TerrainReflectionShader(const TerrainReflectionShader& other);
	~TerrainReflectionShader();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
								   D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, 
								   D3DXVECTOR4 lightDiffuseColor, D3DXVECTOR3 lightDirection, float colorTextureBrightness, D3DXVECTOR4 clipPlane);

private:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
												D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* colorTexture, 
												ID3D11ShaderResourceView* normalTexture, D3DXVECTOR4 lightDiffuseColor, D3DXVECTOR3 lightDirection, 
												float colorTextureBrightness, D3DXVECTOR4 clipPlane);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_clipPlaneBuffer;
	ID3D11Buffer* m_lightBuffer;
};

#endif