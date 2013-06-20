////////////////////////////////////////////////////////////////////////////////
// Filename: water.h
// Adapted from http://www.rastertek.com/tertut16.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _WATER_H_
#define _WATER_H_

// INCLUDES //
#include <d3d11.h>
#include <d3dx10math.h>



// Forward Declarations //

class Texture;


////////////////////////////////////////////////////////////////////////////////
//  name: Water
////////////////////////////////////////////////////////////////////////////////
class Water
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	Water();
	Water(const Water&);
	~Water();

	bool Initialize(ID3D11Device* device, WCHAR* textureFilename, float waterHeight, float waterRadius);
	void Shutdown();
	void Frame();
	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
	
	float GetWaterHeight();
	D3DXVECTOR2 GetNormalMapTiling();
	float GetWaterTranslation();
	float GetReflectRefractScale();
	D3DXVECTOR4 GetRefractionTint();
	float GetSpecularShininess();

private:
	bool InitializeBuffers(ID3D11Device* device, float waterRadius);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContex);

	bool LoadTexture(ID3D11Device* device, WCHAR* filename);
	void ReleaseTexture();

private:
	float m_waterHeight;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	Texture* m_Texture;
	D3DXVECTOR2 m_normalMapTiling;
	float m_waterTranslation;
	float m_reflectRefractScale;
	D3DXVECTOR4 m_refractionTint;
	float m_specularShininess;
};

#endif