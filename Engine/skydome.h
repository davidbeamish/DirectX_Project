////////////////////////////////////////////////////////////////////////////////
// Filename: skydome.h
// Code Adapted from tutorial http://www.rastertek.com/tertut10.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _SKYDOME_H_
#define _SKYDOME_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
//  name: SkyDome
////////////////////////////////////////////////////////////////////////////////
class SkyDome
{
private:
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
	};

public:
	SkyDome();
	SkyDome(const SkyDome&);
	~SkyDome();

	bool Initialize(ID3D11Device* device, char* modelFilename);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount();
	D3DXVECTOR4 GetApexColor();
	D3DXVECTOR4 GetCenterColor();

private:
	bool LoadSkyDomeModel(char*);
	void ReleaseSkyDomeModel();

	bool InitializeBuffers(ID3D11Device* device);
	void ReleaseBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContext);

private:
	ModelType* m_model;
	int m_vertexCount, m_indexCount;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	D3DXVECTOR4 m_apexColor, m_centerColor;
};

#endif