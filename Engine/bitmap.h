////////////////////////////////////////////////////////////////////////////////
// Filename: bitmap.h
// Adapted from http://www.rastertek.com/dx11tut11.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _BITMAP_H_
#define _BITMAP_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>


///////////////////////
// MY  INCLUDES //
///////////////////////
//#include "text.h"
class Texture;

////////////////////////////////////////////////////////////////////////////////
//  name: Bitmap
////////////////////////////////////////////////////////////////////////////////
class Bitmap
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	Bitmap();
	Bitmap(const Bitmap&);
	~Bitmap();

	bool Initialize(ID3D11Device*, int, int, WCHAR*, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, int);

	int GetIndexCount();

	ID3D11ShaderResourceView* GetTexture();
	/*ID3D11ShaderResourceView** GetTextureArray();*/

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*, int, int);
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	/*bool LoadTextures(ID3D11Device*, WCHAR*, WCHAR*);
	void ReleaseTextures();*/

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	Texture* m_Texture;
	/*TextureArray* m_TextureArray;*/

	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;
	int m_previousPosX, m_previousPosY;
};

#endif