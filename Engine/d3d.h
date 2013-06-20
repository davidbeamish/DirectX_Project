////////////////////////////////////////////////////////////////////////////////
// Filename: d3d.h
// Code Adapted from a variety of tutorials on http://www.rastertek.com
////////////////////////////////////////////////////////////////////////////////
#ifndef _D3D_H_
#define _D3D_H_


/////////////
// LINKING //
/////////////
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")


//////////////
// INCLUDES //
//////////////
#include "d3d.h"
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>


////////////////////////////////////////////////////////////////////////////////
//  name: D3D
////////////////////////////////////////////////////////////////////////////////
 class D3D
{
public:
	D3D();
	D3D(const D3D&);
	~D3D();

	bool Initialize(const int screenWidth, const int screenHeight, const bool vsync, const HWND hwnd, const bool fullscreen, 
						 const float screenDepth, const float screenNear);
	void Shutdown();
	
	void BeginScene(const float red, const float green, const float blue, const float alpha);
	void EndScene();

	ID3D11Device* GetDevice() const {return m_device;}
	ID3D11DeviceContext* GetDeviceContext() const {return m_deviceContext;}
	ID3D11DepthStencilView* GetDepthStencilView() const {m_depthStencilView;}

	void GetProjectionMatrix(D3DXMATRIX& projectionMatrix) const {projectionMatrix = m_projectionMatrix;}
	void GetWorldMatrix(D3DXMATRIX& worldMatrix) const {worldMatrix = m_worldMatrix;}
	void GetOrthoMatrix(D3DXMATRIX& orthoMatrix) const {orthoMatrix = m_orthoMatrix;}

	void GetVideoCardInfo(char* cardName, int& memory);

	void TurnZBufferOn();
	void TurnZBufferOff();
	void TurnOnAlphaBlending();
	void TurnOffAlphaBlending();
	void TurnOnCulling();
	void TurnOffCulling();
	void TurnOnSecondaryAlphaBlending();
	
	void SetBackBufferRenderTarget();
	void ResetViewport();

private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState, * m_depthDisabledStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState, * m_rasterStateNoCulling;
	D3DXMATRIX m_projectionMatrix, m_worldMatrix, m_orthoMatrix;
	ID3D11BlendState* m_alphaEnableBlendingState, * m_alphaDisableBlendingState, * m_alphaBlendState2;
	D3D11_VIEWPORT viewport;
};

#endif