////////////////////////////////////////////////////////////////////////////////
// Filename: orthowindow.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _ORTHOWINDOW_H_
#define _ORTHOWINDOW_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: OrthoWindow
////////////////////////////////////////////////////////////////////////////////
class OrthoWindow
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
	};

public:
	OrthoWindow();
	OrthoWindow(const OrthoWindow&);
	~OrthoWindow();

	bool Initialize(ID3D11Device*, int, int);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	void SetPosition(D3DXVECTOR2 position);
	D3DXVECTOR2 GetPosition() const;

private:
	bool InitializeBuffers(ID3D11Device*, int, int);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	D3DXVECTOR2 m_position;
};

#endif