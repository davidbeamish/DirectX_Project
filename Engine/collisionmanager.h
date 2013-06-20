////////////////////////////////////////////////////////////////////////////////
// Filename: collisionmanager.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _COLLISIONMANAGER_H_
#define _COLLISIONMANAGER_H_


///////////////////////
// MY  INCLUDES //
///////////////////////
#include "d3d.h"
#include <vector>
#include <iterator>

///////////////////////
// Forward declarations
///////////////////////

/////////////
// GLOBALS //
/////////////


////////////////////////////////////////////////////////////////////////////////
//  name: CollisionManager
////////////////////////////////////////////////////////////////////////////////
class CollisionManager
{
public:
	CollisionManager();
	CollisionManager(const CollisionManager&);
	~CollisionManager();

	bool Initialize();
	void Shutdown();
	bool Frame();

	void GetMouseLocation(int&, int&);

private:
	bool TestPickingCollision(int mouseX, int mouseY);
	bool TestSphericalRadiusCollision();
	bool TestBoundingBoxCollision();
	bool RaySphereIntersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDirection, float radius);
	

private:
	bool m_collisionCheck, m_collisionCheck2;
};

#endif