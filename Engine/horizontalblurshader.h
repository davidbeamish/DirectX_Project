////////////////////////////////////////////////////////////////////////////////
// Filename: horizontalblurshader.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _HORIZONTALBLURSHADER_H_
#define _HORIZONTALBLURSHADER_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Class name: HorizontalBlurShader
////////////////////////////////////////////////////////////////////////////////
class HorizontalBlurShader
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
		float screenWidth;
		D3DXVECTOR3 padding;
	};

	struct BlurWeightingMatrixBufferType
	{
		D3DXVECTOR4 blurWeightingRow1;
		D3DXVECTOR4 blurWeightingRow2;
		D3DXVECTOR4 blurWeightingRow3;
	};

public:
	HorizontalBlurShader();
	HorizontalBlurShader(const HorizontalBlurShader&);
	~HorizontalBlurShader();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, float, D3DXVECTOR4 blurWeightingRow1, D3DXVECTOR4 blurWeightingRow2, D3DXVECTOR4 blurWeightingRow3);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, float, D3DXVECTOR4 blurWeightingRow1, D3DXVECTOR4 blurWeightingRow2, D3DXVECTOR4 blurWeightingRow3);
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