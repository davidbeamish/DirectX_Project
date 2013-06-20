////////////////////////////////////////////////////////////////////////////////
// Filename: particle.h
// Code Adapted from tutorial http://www.rastertek.com/dx11tut39.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _PARTICLE_H_
#define _PARTICLE_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>


///////////////////////
// MY  INCLUDES //
///////////////////////
class Texture;



////////////////////////////////////////////////////////////////////////////////
//  name: Particle
////////////////////////////////////////////////////////////////////////////////
class Particle
{
private:
	struct ParticleType
	{
		float positionX, positionY, positionZ;
		float red, green, blue;
		float velocity;
		bool active;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR4 color;
	};

public:
	Particle();
	Particle(float positionx, float positionY, float positionZ, float particleDeviationX, float particleDeviationY, float particleDeviationZ, 
		          float particleVelocity, float particleVelocityVariation, float particleSize, float particlesPerSecond, int maxParticles, WCHAR* TextureFilename);
	Particle(const Particle&);
	~Particle();

	bool Initialize(ID3D11Device* device, WCHAR* textureFilename, float positionX, float positionY, float positionZ);
	void Shutdown();
	bool Frame(float, ID3D11DeviceContext*);
	void Render(ID3D11DeviceContext* deviceContext);

	ID3D11ShaderResourceView* GetTexture();
	int GetIndexCount();

private:
	bool LoadTexture(ID3D11Device* device, WCHAR* textureFilename);
	void ReleaseTexture();

	bool InitializeParticleSystem();
	void ShutdownParticleSystem();

	bool InitializeBuffers(ID3D11Device* device);
	void ShutdownBuffers();

	void EmitParticles(float);
	void UpdateParticles(float);
	void KillParticles();

	bool UpdateBuffers(ID3D11DeviceContext* deviceContext);

	void RenderBuffers(ID3D11DeviceContext* deviceContext);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_particleDeviationX, m_particleDeviationY, m_particleDeviationZ;
	float m_particleVelocity, m_particleVelocityVariation;
	float m_particleSize, m_particlesPerSecond;
	int m_maxParticles;

	WCHAR* m_TextureFilename;

	int m_currentParticleCount;
	float m_accumulatedTime;

	Texture* m_Texture;
	ParticleType* m_particleList;
	int m_vertexCount, m_indexCount;
	VertexType* m_vertices;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
};

#endif