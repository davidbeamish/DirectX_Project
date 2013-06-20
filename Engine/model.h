////////////////////////////////////////////////////////////////////////////////
// Filename: model.h
// Adapted from a variety of tutorials on http://www.rastertek.com
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODEL_H_
#define _MODEL_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include "texture.h"
using namespace std;

////////////////////////////////////////////////////////////////////////////////
//  name: Model
////////////////////////////////////////////////////////////////////////////////
class Model
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	Model();
	Model(const Model&);
	~Model();

	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	ID3D11ShaderResourceView* GetTexture();

	int GetIndexCount();
	float GetSphericalBoundingRadius() const;
	D3DXVECTOR3* GetBoundingBox() const;
	float* GetBoundingBoxVertices() const;

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadModel(char*);
	void ReleaseModel();
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	void CreateBoundingSphere(VertexType* vertices);
	void CreateBoundingBox(VertexType* vertices);
	

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	ModelType* m_model;
	Texture* m_Texture;
	
	float m_sphericalBoundingRadius;
	float* m_boundingBoxVertices;
	D3DXVECTOR3* m_boundingBox;
	
};

#endif