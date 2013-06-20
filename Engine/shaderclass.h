////////////////////////////////////////////////////////////////////////////////
// Filename: shaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHADERCLASS_H_
#define _SHADERCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderClass
////////////////////////////////////////////////////////////////////////////////
class ShaderClass
{
private:

public:
	ShaderClass();
	ShaderClass(const ShaderClass&);
	~ShaderClass();

	bool Initialize();
	void Shutdown();
	bool Render();

private:
	bool InitializeShader(ID3D11Device*, HWND,);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);
	void RenderShader(ID3D11DeviceContext*, int);


