////////////////////////////////////////////////////////////////////////////////
// Filename: cloudsshader.h
// Code Adapted from tutorial http://www.rastertek.com/tertut11.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _CLOUDSSHADER_H_
#define _CLOUDSSHADER_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
//  name: CloudsShader
////////////////////////////////////////////////////////////////////////////////
class CloudsShader
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct SkyBufferType
	{
		D3DXVECTOR2 translation;
		D3DXVECTOR2 brightness;
		D3DXVECTOR2 scale;
		D3DXVECTOR2 padding;
	};

public:
	CloudsShader();
	CloudsShader(const CloudsShader&);
	~CloudsShader();

	bool Initialize(ID3D11Device* device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
				 D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* cloudTexture1, ID3D11ShaderResourceView* cloudTexture2, ID3D11ShaderResourceView* perturbTexture, 
				 D3DXVECTOR2 translation, D3DXVECTOR2 scale, D3DXVECTOR2 brightness);

private:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
				 D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* cloudTexture1, ID3D11ShaderResourceView* cloudTexture2, ID3D11ShaderResourceView* perturbTexture, 
				 D3DXVECTOR2 translation, D3DXVECTOR2 scale, D3DXVECTOR2 brightness);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_skyBuffer;
};

#endif