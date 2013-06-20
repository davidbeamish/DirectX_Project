////////////////////////////////////////////////////////////////////////////////
// Filename: glowshader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GLOWSHADER_H_
#define _GLOWSHADER_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Class name: GlowShader
////////////////////////////////////////////////////////////////////////////////
class GlowShader
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct GlowBufferType
	{
		float glowStrength;
		D3DXVECTOR3 padding;
	};

public:
	GlowShader();
	GlowShader(const GlowShader&);
	~GlowShader();

	bool Initialize(ID3D11Device* device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
			     D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* glowTexture, 
			     float glowStrength);

private:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
					  D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* colorTexture, 
					  ID3D11ShaderResourceView* glowTexture, float glowStrength);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_glowBuffer;
	ID3D11SamplerState* m_sampleState;
};

#endif