////////////////////////////////////////////////////////////////////////////////
// Filename: objectweatherparticle.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTWEATHERPARTICLE_H_
#define _OBJECTWEATHERPARTICLE_H_

///////////////////////
// MY  INCLUDES //
///////////////////////
#include "renderable.h"

/////////////
// GLOBALS //
/////////////
class Graphic;
class D3D;
class Camera;
class ShaderManager;
class ParticleGenerator;
class Texture;

////////////////////////////////////////////////////////////////////////////////
//  name: objectweatherparticle
////////////////////////////////////////////////////////////////////////////////
class ObjectWeatherParticle : public Renderable
{
public:
	ObjectWeatherParticle(D3D* m_D3D);
	ObjectWeatherParticle(const ObjectWeatherParticle&);
	~ObjectWeatherParticle();

	bool Render(GraphicsManager& graphicsManager, int renderPass);
	void Frame(D3D* m_D3D, float frameTime);

	void SetPosition(D3DXVECTOR3 position);
	void SetRotation(D3DXVECTOR3 rotation);

	D3DXVECTOR3 GetPosition() const {return m_position;}

private:
	bool RenderRain(GraphicsManager& graphicsManager, float frameTime);
	//bool RenderWhiteCore(GraphicsManager& graphicsManager, float frameTime);
	//bool RenderFireball(GraphicsManager& graphicsManager, float frameTime);
	//bool RenderSmoke(GraphicsManager& graphicsManager, float frameTime);
	//bool RenderDebris(GraphicsManager& graphicsManager, float frameTime);

	ParticleGenerator * m_RainGenerator;
	Texture * m_RainTexture, * m_RainNoiseTexture, * m_RainAlphaTexture;

	D3DXVECTOR3 m_position, m_rotation;
};

#endif //_OBJECTWEATHERPARTICLE_H_