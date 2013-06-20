////////////////////////////////////////////////////////////////////////////////
// Filename: particlesystem.h
// Code Adapted from tutorial http://www.rastertek.com/dx11tut39.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <vector>

///////////////////////
// MY  INCLUDES //
///////////////////////

class Texture;


////////////////////////////////////////////////////////////////////////////////
//  name: ParticleSystem
////////////////////////////////////////////////////////////////////////////////
class ParticleSystem
{
private:
	struct ParticleType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 velocity;
		D3DXVECTOR3 acceleration;
		D3DXVECTOR4 color;
		D3DXVECTOR4 colorVelocity;
		D3DXVECTOR4 colorAcceleration;
		float lifeTime;
		float lifeSpeed;
		float lifeAcceleration;
		D3DXVECTOR2 size;
		D3DXVECTOR2 sizeVelocity;
		D3DXVECTOR2 sizeAcceleration;
		bool active;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR4 color;
	};

	enum State
	{
		OFF = 0,
		ON = 1,
	};

public:
	ParticleSystem();
	ParticleSystem(const ParticleSystem&);
	~ParticleSystem();

	bool Initialize(ID3D11Device* device, WCHAR* textureFilename, D3DXVECTOR3 position, D3DXVECTOR3 positionDeviation, float positionRadius, D3DXVECTOR3 velocity, D3DXVECTOR3 velocityDeviation, D3DXVECTOR3 acceleration, D3DXVECTOR4 color, D3DXVECTOR4 colorVelocity, D3DXVECTOR4 colorAcceleration, D3DXVECTOR2 size, D3DXVECTOR2 maxSize, D3DXVECTOR2 sizeVelocity, D3DXVECTOR2 sizeAcceleration, float particlesPerSecond, int maxParticleCount, float lifeTime, float lifeSpeed, float lifeAcceleration);
	void Shutdown();
	bool Frame(float, ID3D11DeviceContext* deviceContext);
	void Render(ID3D11DeviceContext* deviceContext);

	ID3D11ShaderResourceView* GetTexture();

	void SetInitializationVariables(D3DXVECTOR3 position, D3DXVECTOR3 positionDeviation, float positionRadius, D3DXVECTOR3 velocity, D3DXVECTOR3 velocityDeviation, D3DXVECTOR3 acceleration, D3DXVECTOR4 color, D3DXVECTOR4 colorVelocity, D3DXVECTOR4 colorAcceleration, D3DXVECTOR2 size, D3DXVECTOR2 maxSize, D3DXVECTOR2 sizeVelocity, D3DXVECTOR2 sizeAcceleration, float particlesPerSecond, int maxParticleCount, float lifeTime, float lifeSpeed, float lifeAcceleration);

	int GetIndexCount();

	int GetCurrentParticleCount() const;

	void SetPosition(D3DXVECTOR3 position);
	D3DXVECTOR3 GetPosition() const;

	void SetVelocity(D3DXVECTOR3 velocity);
	void SetAcceleration(D3DXVECTOR3 acceleration);
	
	void SetLifeTime(float lifeTime);
	void SetLifeSpeed(float lifeSpeed);

	void SetColor(D3DXVECTOR4 color);
	void SetColorVelocity(D3DXVECTOR4 colorVelocity);
	void SetColorAcceleration(D3DXVECTOR4 colorAcceleration);

	void SetSize(D3DXVECTOR2 size);
	void SetMaxSize(D3DXVECTOR2 maxSize);
	void SetSizeVelocity(D3DXVECTOR2 sizeVelocity);
	void SetSizeAcceleration(D3DXVECTOR2 sizeAcceleration);
	

	void SetParticlesPerSecond(float particlesPerSecond);
	void SetMaxParticleCount(int maxParticleCount);

	void SetEmissionState(const bool state);
	bool GetEmissionState() const;




private:
	bool LoadTexture(ID3D11Device* device, WCHAR* textureFilename);
	void ReleaseTexture();

	bool InitializeParticleSystem();
	void ShutdownParticleSystem();

	bool InitializeBuffers(ID3D11Device* device);
	void ShutdownBuffers();

	void EmitParticles(float time);
	void UpdateParticles(float time);
	void KillParticles(float time);

	bool UpdateBuffers(ID3D11DeviceContext* deviceContext);
	void RenderBuffers(ID3D11DeviceContext* deviceContext);

	
private:
	D3DXVECTOR3 m_position, m_positionDeviation, m_velocity, m_velocityDeviation, m_acceleration;
	D3DXVECTOR4 m_color, m_colorVelocity, m_colorAcceleration;
	D3DXVECTOR2 m_size, m_maxSize, m_sizeVelocity, m_sizeAcceleration;
	float m_positionRadius, m_particlesPerSecond;
	int m_currentParticleCount, m_maxParticleCount;

	float m_lifeTime, m_lifeSpeed, m_lifeAcceleration;
	float m_accumulatedTime;

	Texture* m_Texture;
	ParticleType* m_particleList;

	std::vector<ParticleType> * m_particleVector;

	int m_vertexCount, m_indexCount;
	VertexType* m_vertices;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;

	bool m_emissionState;
};

#endif