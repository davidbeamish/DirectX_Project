////////////////////////////////////////////////////////////////////////////////
// Filename: objectparticle.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTPARTICLE_H_
#define _OBJECTPARTICLE_H_

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
class Light;
class Texture;

////////////////////////////////////////////////////////////////////////////////
//  name: objectparticle
////////////////////////////////////////////////////////////////////////////////
class ObjectParticle : public Renderable
{
public:
	ObjectParticle(D3D* m_D3D, WCHAR* textureFilename);
	ObjectParticle(const ObjectParticle&);
	~ObjectParticle();

	bool Render(GraphicsManager& m_GraphicsManager, int renderPass);
	void Frame(D3D* m_D3D, float frameTime);

	void SetPosition(D3DXVECTOR3 position);
	void SetRotation(D3DXVECTOR3 rotation);

	D3DXVECTOR3 GetPosition();

private:
	D3DXMATRIX BillboardWorldMatrix(D3DXMATRIX & worldMatrix, D3DXVECTOR3 position);

	Light* m_Light;
	ParticleGenerator * m_FlashGenerator, * m_WhiteCoreGenerator, * m_FireballGenerator, * m_SmokeGenerator, * m_DebrisGenerator;
	Texture * m_FlashTexture, * m_FlashNoiseTexture, * m_FlashAlphaTexture, * m_WhiteCoreTexture, * m_WhiteCoreNoiseTexture, * m_WhiteCoreAlphaTexture, * m_FireTexture, * m_FireNoiseTexture, * FireAlphaTexture, * m_SmokeTexture, * m_SmokeNoiseTexture, * SmokeAlphaTexture;

	D3DXVECTOR3 m_position, m_rotation;
};

#endif