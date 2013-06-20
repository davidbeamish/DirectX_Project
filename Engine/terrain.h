////////////////////////////////////////////////////////////////////////////////
// Filename: terrain.h
// Code Adapted from a variety of terrain tutorials on http://www.rastertek.com
////////////////////////////////////////////////////////////////////////////////
#ifndef _TERRAIN_H_
#define _TERRAIN_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <stdio.h>


///////////////////////
// MY  INCLUDES //
///////////////////////
class Texture;

/////////////
// GLOBALS //
/////////////
const int TEXTURE_REPEAT = 8;


////////////////////////////////////////////////////////////////////////////////
//  name: Terrain
////////////////////////////////////////////////////////////////////////////////
class Terrain
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 texture;
	    D3DXVECTOR3 normal;
		D3DXVECTOR4 color;
	};

	struct HeightMapType 
	{ 
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float red, green, blue;
	};

	struct VectorType 
	{ 
		float x, y, z;
	};

public:
	Terrain();
	Terrain(const Terrain&);
	~Terrain();

	bool Initialize(ID3D11Device* device, char* heightMapFilename, WCHAR* grassTextureFilename, WCHAR* slopeTextureFilename, 
			      WCHAR* rockTextureFilename, char* colorMapFilename, WCHAR* detailMapFilename, WCHAR* normalTextureFilename);
	bool InitializeTerrain(ID3D11Device* device, int terrainWidth, int terrainHeight, WCHAR* grassTextureFilename, WCHAR* slopeTextureFilename, 
			      WCHAR* rockTextureFilename, char* colorMapFilename, WCHAR* detailTexture, WCHAR* normalTextureFilename);

	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	bool GenerateHeightMap(ID3D11Device* device, bool keyDown);
	bool FlattenTerrain(ID3D11Device* device, bool keyDown);
	void DoMidpointDisplacement(int mapSize, float roughness, float smoothness);
	void DoFaultFormation(int mapSize, int iterations, float minDelta, float maxDelta, float smoothness);
	void DoParticleDeposition(int jumps, int peakWalk, int minParticlesPerJump, int maxParticlesPerJump, float caldera, float smoothness);
	bool SmoothTerrain(ID3D11Device* device, bool keyDown);
	bool SmoothTerrain(float smoothness);

	ID3D11ShaderResourceView* GetGrassTexture() const;
	ID3D11ShaderResourceView* GetSlopeTexture() const;
	ID3D11ShaderResourceView* GetRockTexture() const;
	ID3D11ShaderResourceView* GetDetailMapTexture() const;
	ID3D11ShaderResourceView* GetColorTexture() const;
	ID3D11ShaderResourceView* GetNormalTexture() const;

	float GetMeanTerrainHeight() const;
	float GetHeightAtPosition(float, float);

private:
	bool LoadHeightMap(char*);
	void NormalizeHeightMap();
	bool CalculateNormals();
	void ShutdownHeightMap();
	void NormalizeTerrain(int size, float smoothness);
	void CalculateTextureCoordinates();
	bool LoadTextures(ID3D11Device* device, WCHAR* grassTexturefilename, WCHAR* slopeTexturefilename, WCHAR* rockTexturefilename, WCHAR* detailMapFilename, WCHAR* normalTextureFilename);
	void ReleaseTexture();

	float GenerateRndNum(float x, float y);
	bool InitializeBuffers(ID3D11Device* device);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContext);

	bool LoadColorMap(char* colorMapFilename);

	void CalculateMeanTerrainHeight();
	
private:
	bool m_terrainInitializedToggle, m_terrainGeneratedToggle, m_terrainFlattenedToggle, m_terrainErodedToggle, m_terrainSmoothedToggle, m_seedGeneratedToggle;
	int m_terrainWidth, m_terrainHeight;
	int m_vertexCount, m_indexCount;
	int m_IterationCount;

	float m_meanTerrainHeight;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	HeightMapType* m_heightMap;
	Texture *m_GrassTexture, *m_SlopeTexture, *m_RockTexture, *m_DetailTexture, *m_ColorTexture, *m_NormalTexture;
};

#endif