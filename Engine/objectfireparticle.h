////////////////////////////////////////////////////////////////////////////////
// Filename: objectfireparticle.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTFIREPARTICLE_H_
#define _OBJECTFIREPARTICLE_H_

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
//  name: objectfireparticle
////////////////////////////////////////////////////////////////////////////////
class ObjectFireParticle : public Renderable
{
public:
	ObjectFireParticle(D3D* m_D3D);
	ObjectFireParticle(const ObjectFireParticle&);
	~ObjectFireParticle();

	bool Render(GraphicsManager& graphicsManager, int renderPass);
	void Frame(D3D* m_D3D, float frameTime);

	void SetPosition(D3DXVECTOR3 position);
	void SetRotation(D3DXVECTOR3 rotation);

	D3DXVECTOR3 GetPosition() const {return m_position;}

private:
	bool RenderFire(GraphicsManager& graphicsManager, float frameTime);

	ParticleGenerator * m_FireGenerator;
	Texture * m_FireTexture, * m_FireNoiseTexture, * m_FireAlphaTexture;

	D3DXVECTOR3 m_position, m_rotation;
};

#endif //_OBJECTFIREPARTICLE_H_