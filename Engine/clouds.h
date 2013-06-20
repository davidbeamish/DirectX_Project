////////////////////////////////////////////////////////////////////////////////
// Filename: clouds.h
// Code Adapted from tutorial http://www.rastertek.com/tertut11.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _CLOUDS_H_
#define _CLOUDS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>


///////////////////////
// MY  INCLUDES //
///////////////////////
#include "texture.h"
class Texture;


////////////////////////////////////////////////////////////////////////////////
//  name: Clouds
////////////////////////////////////////////////////////////////////////////////
class Clouds
{
private:
	struct CloudsType
	{
		float x, y, z;
		float tu, tv;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	Clouds();
	Clouds(const Clouds&);
	~Clouds();

	bool Initialize(ID3D11Device* device, WCHAR* cloudTextureFilename, WCHAR* cloudTextureFilename2, WCHAR* perturbTextureFilename);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	void Frame();

	int GetIndexCount();
	ID3D11ShaderResourceView* GetCloudTexture1();
	ID3D11ShaderResourceView* GetCloudTexture2();
	ID3D11ShaderResourceView* GetPerturbTexture();
	
	D3DXVECTOR2 GetBrightness();
	D3DXVECTOR2 GetTranslation();
	D3DXVECTOR2 GetScale();
private:
	bool InitializeClouds(int, float, float, float, int);
	void ShutdownClouds();

	bool InitializeBuffers(ID3D11Device*, int);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTextures(ID3D11Device* device, WCHAR* cloudTextureFilename1,  WCHAR* cloudTextureFilename2, WCHAR* perturbTextureFilename);
	void ReleaseTextures();

private:
	CloudsType* m_clouds;
	int m_vertexCount, m_indexCount;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	Texture *m_CloudTexture1, *m_CloudTexture2, *m_PerturbTexture;
	D3DXVECTOR2 m_scale, m_brightness, m_translation;
};

#endif