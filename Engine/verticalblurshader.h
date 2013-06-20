////////////////////////////////////////////////////////////////////////////////
// Filename: verticalblurshader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _VERTICALBLURSHADER_H_
#define _VERTICALBLURSHADER_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Class name: VerticalBlurShader
////////////////////////////////////////////////////////////////////////////////
class VerticalBlurShader
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct ScreenSizeBufferType
	{
		float screenHeight;
		D3DXVECTOR3 padding;
	};

	struct BlurWeightingMatrixBufferType
	{
		D3DXVECTOR4 blurWeightingRow1;
		D3DXVECTOR4 blurWeightingRow2;
		D3DXVECTOR4 blurWeightingRow3;
	};

public:
	VerticalBlurShader();
	VerticalBlurShader(const VerticalBlurShader&);
	~VerticalBlurShader();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, float screenHeight, D3DXVECTOR4 blurWeightingRow1, D3DXVECTOR4 blurWeightingRow2, D3DXVECTOR4 blurWeightingRow3);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, float screenHeight, D3DXVECTOR4 blurWeightingRow1, D3DXVECTOR4 blurWeightingRow2, D3DXVECTOR4 blurWeightingRow3);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_screenSizeBuffer;
	ID3D11Buffer* m_blurWeightingBuffer;
};

#endif