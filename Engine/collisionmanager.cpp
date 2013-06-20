#include "collisionmanager.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::CollisionManager(const CollisionManager& other)
{
}

CollisionManager::~CollisionManager()
{

}




//bool CollisionManager::TestPickingCollision(int mouseX, int mouseY)
//{
//	float pointX, pointY;
//	D3DXMATRIX projectionMatrix, viewMatrix, inverseViewMatrix, worldMatrix, translateMatrix, inverseWorldMatrix;
//	D3DXVECTOR3 direction, origin, rayOrigin, rayDirection;
//	bool intersect;
//	//bool result;
//
//
//	// Change the mouse cursor coordinates into the -1 to +1 range in both x and y axes.
//	pointX = ((2.0f * (float)mouseX) / (float)m_ScreenWidth) - 1.0f;
//	pointY = (((2.0f * (float)mouseY) / (float)m_ScreenHeight) - 1.0f) * -1.0f;
//		
//	// Adjust the points using the projection matrix to account for the aspect ratio of the viewport.
//	m_D3D->GetProjectionMatrix(projectionMatrix);
//	pointX = pointX / projectionMatrix._11;
//	pointY = pointY / projectionMatrix._22;
//
//	// Get the inverse of the view matrix since a 2D point is being transformed into 3D space.
//	m_Camera->GetViewMatrix(viewMatrix);
//	D3DXMatrixInverse(&inverseViewMatrix, NULL, &viewMatrix);
//
//	// Calculate the direction vector of the picking ray in view space for the mouse cursor.
//	direction.x = (pointX * inverseViewMatrix._11) + (pointY * inverseViewMatrix._21) + inverseViewMatrix._31;
//	direction.y = (pointX * inverseViewMatrix._12) + (pointY * inverseViewMatrix._22) + inverseViewMatrix._32;
//	direction.z = (pointX * inverseViewMatrix._13) + (pointY * inverseViewMatrix._23) + inverseViewMatrix._33;
//
//	// Set the origin of the picking ray to be the position of the camera.
//	origin = m_Camera->GetPosition();
//
//	// Get the world matrix and translate to the location of the sphere.
//	m_D3D->GetWorldMatrix(worldMatrix);
//
//	D3DXMatrixTranslation(&translateMatrix, m_ObjectSphere->GetPosition().x, m_ObjectSphere->GetPosition().y, m_ObjectSphere->GetPosition().z);
//	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix); 
//
//	// Now get the inverse of the translated world matrix.
//	D3DXMatrixInverse(&inverseWorldMatrix, NULL, &worldMatrix);
//
//	// Now transform the ray origin and the ray direction from view space to world space.
//	D3DXVec3TransformCoord(&rayOrigin, &origin, &inverseWorldMatrix);
//	D3DXVec3TransformNormal(&rayDirection, &direction, &inverseWorldMatrix);
//
//	// Normalize the ray direction.
//	D3DXVec3Normalize(&rayDirection, &rayDirection);
//
//	// Now perform the ray-sphere intersection test.
//	intersect = RaySphereIntersect(rayOrigin, rayDirection, 1.0f);
//	
//	if(intersect == true)
//	{
//		// If it does intersect then set the intersection to "yes" in the text string that is displayed to the screen.
//		//result = m_Text->SetIntersection(true, m_D3D->GetDeviceContext());
//		m_collisionCheck = true;
//	}
//	else
//	{
//		// If not then set the intersection to "No".
//		//result = m_Text->SetIntersection(false, m_D3D->GetDeviceContext());
//		m_collisionCheck = false;
//	}
//
//	return intersect;
//}
//
//
//bool CollisionManager::RaySphereIntersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDirection, float radius)
//{
//	float a, b, c, discriminant;
//
//	// Calculate the a, b, and c coefficients.
//	a = (rayDirection.x * rayDirection.x) + (rayDirection.y * rayDirection.y) + (rayDirection.z * rayDirection.z);
//	b = ((rayDirection.x * rayOrigin.x) + (rayDirection.y * rayOrigin.y) + (rayDirection.z * rayOrigin.z)) * 2.0f;
//	c = ((rayOrigin.x * rayOrigin.x) + (rayOrigin.y * rayOrigin.y) + (rayOrigin.z * rayOrigin.z)) - (radius * radius);
//
//	// Find the discriminant.
//	discriminant = (b * b) - (4 * a * c);
//
//	// if discriminant is negative the picking ray missed the sphere, otherwise it intersected the sphere.
//	if (discriminant < 0.0f)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//
//bool CollisionManager::TestSphericalRadiusCollision()
//{
//	
//	float distance = 0.0f;
//
//	D3DXVECTOR3 pos1 = m_ObjectSphere->GetPosition();
//	D3DXVECTOR3 pos2= m_ObjectSphere2->GetPosition();
//
//	float distX = pos2.x - pos1.x;
//	float distY = pos2.y - pos1.y;
//	float distZ = pos2.z - pos1.z;	
//
//	distance = sqrt(distX*distX + distY*distY + distZ*distZ);
//
//	if( distance <= (m_ObjectSphere->GetSphericalBoundingRadius() + m_ObjectSphere2->GetSphericalBoundingRadius() ) )
//	{
//
//		////This is where we will do something if the objects have collided. What we do here is move the object we have collided with, then check to see if the object we just moved has collided with another object, by calling the DetectCollision() function again. First we get the objects position that we want to move. The distX, distY, and distZ together are basically the vector that explains the angle the two objects have collided at. We can use this vector to "push back" the object we are colliding with, in the right direction, which is what we do, we add the negative distX and distZ, times the "speed" which we want to move at, to the objects x and z position values. Then we transform the local space matrix of the object, call DetectCollision() to see if it has collided with another object, then finally return true, and as you can see below that, if we did not collide with anything, we return false.
//		//D3DXVECTOR3 objPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//D3DXVec3TransformCoord(&objPos, &objPos, &SphereLocalSpace[i]);
//
//		//objPos.x += -distX * 0.075f;
//		//objPos.z += -distZ * 0.075f;
//
//		//D3DXMatrixScaling( &Scale, 2.0f, 2.0f, 2.0f );
//		//D3DXMatrixTranslation( &Translation, objPos.x, 1.0f, objPos.z );
//
//		//SphereLocalSpace[i] = Scale * Translation;
//
//		//DetectCollision(SphereLocalSpace[i]);
//		return true;
//	}
//	return false;
//}
//
//
//bool CollisionManager::TestBoundingBoxCollision()
//{
//	float* bbVertices =	m_ObjectSphere->GetBoundingBoxVertices();
//	float* bbVertices2 = m_ObjectSphere2->GetBoundingBoxVertices();
//
//	// Check if object 1's maxX is greater than object 2's minX.  Else object 1 is left of object 2.
//	if (bbVertices[1] > bbVertices2[0])
//		// Check if object 1's minX is less than object 2's maxX.  Else object 1 is right of object 2.
//		if (bbVertices[0] < bbVertices2[1])
//			// Check if object 1's maxY is greater than object 2's minY.  Else object 1 is under object 2.
//			if(bbVertices[3] > bbVertices2[2])
//				// Check if object 1's minY is less than object 2's maxY.  Else object 1 is above object 2.
//				if(bbVertices[2] < bbVertices2[3])
//					// Check if object 1's maxZ is greater than object 2's minZ.  Else object 1 is in front of object 2.
//					if (bbVertices[5] > bbVertices2[4])
//						// Check if object 1's minZ is less than object 2's maxZ.  Else object 1 is behind object 2.
//						if(bbVertices[4] < bbVertices2[5])
//							//The two bounding boxes intersect.
//							return true;
//	//Bounding boxes do not intersect
//	return false;
//}