////////////////////////////////////////////////////////////////////////////////
// Filename: particle.cpp
// Code Adapted from tutorial http://www.rastertek.com/dx11tut39.html
////////////////////////////////////////////////////////////////////////////////
#include "particle.h"
#include "texture.h"

Particle::Particle()
{
	m_positionX = 0; 
	m_positionY = 0;
	m_positionZ = 0;
	m_particleDeviationX = 0; 
	m_particleDeviationY = 0; 
	m_particleDeviationZ = 0; 
	m_particleVelocity = 0; 
	m_particleVelocityVariation = 0; 
	m_particleSize = 0; 
	m_particlesPerSecond = 0; 
	m_maxParticles = 0;
	WCHAR* m_TextureFilename = L"../Engine/data/star.dds";
}

Particle::Particle(float positionX, float positionY, float positionZ, float particleDeviationX, float particleDeviationY, float particleDeviationZ, 
		          float particleVelocity, float particleVelocityVariation, float particleSize, float particlesPerSecond, int maxParticles, WCHAR* TextureFilename)
{
	m_positionX = positionX; 
	m_positionY = positionY;
	m_positionZ = positionZ;
	m_particleDeviationX = particleDeviationX; 
	m_particleDeviationY = particleDeviationY; 
	m_particleDeviationZ = particleDeviationZ; 
	m_particleVelocity = particleVelocity; 
	m_particleVelocityVariation = particleVelocityVariation; 
	m_particleSize = particleSize; 
	m_particlesPerSecond = particlesPerSecond; 
	m_maxParticles = maxParticles;
	m_TextureFilename = TextureFilename;
}


Particle::Particle(const Particle& other)
{
}


Particle::~Particle()
{
}

