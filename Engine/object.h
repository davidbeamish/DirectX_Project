////////////////////////////////////////////////////////////////////////////////
// Filename: object.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECT_H_
#define _OBJECT_H_

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
class Model;
class ObjectExplosionParticle;

////////////////////////////////////////////////////////////////////////////////
//  name: object
////////////////////////////////////////////////////////////////////////////////
class Object : public Renderable
{
public:
	Object(D3D* m_D3D, char* modelFilename, WCHAR* textureFilename);
	Object(const Object&);
	~Object();

	bool Render(GraphicsManager& graphicsManager, int renderPass);

	void SetPosition(D3DXVECTOR3 position);
	D3DXVECTOR3 GetPosition() const;

	void SetRotation(D3DXVECTOR3 rotation);
	float GetSphericalBoundingRadius() const;
	float* GetBoundingBoxVertices() const;
	D3DXVECTOR3 *GetBoundingBox() const;

private:
	D3DXMATRIX DoMovement(D3D* d3d);

	Model* m_Model;
	ObjectExplosionParticle * m_ExplosionEffect;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	float m_sphericalBoundingRadius;
	float *m_boundingBoxVertices;
	D3DXVECTOR3 *m_boundingBox;
};

#endif