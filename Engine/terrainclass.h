////////////////////////////////////////////////////////////////////////////////
// Filename: terrainclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TERRAINCLASS_H_
#define _TERRAINCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <stdio.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: TerrainClass
////////////////////////////////////////////////////////////////////////////////
class TerrainClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
	};

	struct HeightMapType 
	{ 
		float x, y, z;
		float nx, ny, nz;
	};

	struct VectorType 
	{ 
		float x, y, z;
	};

public:
	TerrainClass();
	TerrainClass(const TerrainClass&);
	~TerrainClass();

	bool Initialize(ID3D11Device *device, char *heightFilename);
	bool InitializeTerrain(ID3D11Device*, int terrainWidth, int terrainHeight);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	bool GenerateHeightMap(ID3D11Device* device, bool keydown);
	bool FlattenTerrain(ID3D11Device* device, bool keyDown);

	bool ErodeHeightMap(ID3D11Device* device, bool keyDown, float smoothness);
	bool SmoothTerrain(ID3D11Device* device, bool keyDown);

	bool GenerateNewSeed(bool keydown);
	int  GetIndexCount();

private:
	bool LoadHeightMap(char*);
	void NormalizeHeightMap();
	bool CalculateNormals();
	void ShutdownHeightMap();
	void GenerateHeightField();

	void DoMidpointDisplacement(int size, float rough);
	void DoFaultFormation(int size, int iterations, float minDelta, float maxDelta, int iterationsPerFilter, float filter);
	void DoParticleDeposition(int jumps, int peakWalk, int minParticlesPerJump, int maxParticlesPerJump, float caldera);
	void GenerateSphere(int size);
	void GenerateMultiFractal(int size);

	void NormalizeTerrain(int size);
	float GenerateRndNum(float min, float max);
	void Erode(float* heightMap, int index, int count, float smoothness);

	float GenerateMultifractal(float x, float y, float octaves, float amplitude, float frequency, float height, float offset);
	float GenerateRandomNumber(int x, int y);
	float SmoothRandomNumber(int x, int y);
	float DoInterpolation(float num1, float num2, float x);
	float GenerateNoise(float x, float y);

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	bool m_terrainInitializedToggle, m_terrainGeneratedToggle, m_terrainFlattenedToggle, m_terrainErodedToggle, m_terrainSmoothedToggle, m_seedGeneratedToggle;
	int m_terrainWidth, m_terrainHeight;
	int m_vertexCount, m_indexCount;
	int m_rndNumSeed;
	int m_IterationCount;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	HeightMapType* m_heightMap;
};

#endif