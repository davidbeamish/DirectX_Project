////////////////////////////////////////////////////////////////////////////////
// Filename: objectexplosionparticle.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTEXPLOSIONPARTICLE_H_
#define _OBJECTEXPLOSIONPARTICLE_H_

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
//  name: objectexplosionparticle
////////////////////////////////////////////////////////////////////////////////
class ObjectExplosionParticle : public Renderable
{
public:
	ObjectExplosionParticle(D3D* m_D3D);
	ObjectExplosionParticle(const ObjectExplosionParticle&);
	~ObjectExplosionParticle();

	bool Render(GraphicsManager& graphicsManager, int renderPass);
	void Frame(D3D* m_D3D, float frameTime);

	void SetPosition(D3DXVECTOR3 position);
	void SetRotation(D3DXVECTOR3 rotation);

	D3DXVECTOR3 GetPosition() const {return m_position;}

private:
	bool RenderFlash(GraphicsManager& graphicsManager, float frameTime);
	bool RenderWhiteCore(GraphicsManager& graphicsManager, float frameTime);
	bool RenderFireball(GraphicsManager& graphicsManager, float frameTime);
	bool RenderSmoke(GraphicsManager& graphicsManager, float frameTime);
	bool RenderDebris(GraphicsManager& graphicsManager, float frameTime);

	ParticleGenerator * m_FlashGenerator, * m_WhiteCoreGenerator, * m_FireballGenerator, * m_SmokeGenerator, * m_DebrisGenerator;
	Texture * m_FlashTexture, * m_FlashNoiseTexture, * m_FlashAlphaTexture, * m_WhiteCoreTexture, * m_WhiteCoreNoiseTexture, * m_WhiteCoreAlphaTexture, * m_FireballTexture, * m_FireballNoiseTexture, * m_FireballAlphaTexture, * m_SmokeTexture, * m_SmokeNoiseTexture, * m_SmokeAlphaTexture;

	float m_lifeTime;

	D3DXVECTOR3 m_position, m_rotation;
};

#endif //_OBJECTEXPLOSIONPARTICLE_H_