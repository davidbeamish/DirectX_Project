////////////////////////////////////////////////////////////////////////////////
// Filename: camera.h
// Adapted from a variety of tutorials on http://www.rastertek.com
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERA_H_
#define _CAMERA_H_


//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>


////////////////////////////////////////////////////////////////////////////////
//  name: Camera
////////////////////////////////////////////////////////////////////////////////
class Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();	

	void Render();
	void RenderReflection(const float height);

	void GetViewMatrix(D3DXMATRIX& viewMatrix) const {viewMatrix = m_viewMatrix;}
	void GetReflectionViewMatrix(D3DXMATRIX& viewMatrix) const {viewMatrix = m_reflectionViewMatrix;}
	void GetBillboardedWorldMatrix(D3DXMATRIX & out, D3DXVECTOR3 position) const;

	void SetPosition(const float x, const float y, const float z) {m_positionX = x;	m_positionY = y; m_positionZ = z;}
	D3DXVECTOR3 GetPosition() const {return D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);}
	

	void SetRotation(const float x, const float y, const float z) {m_rotationX = x;	m_rotationY = y; m_rotationZ = z;}
	D3DXVECTOR3 GetRotation() const {return D3DXVECTOR3(m_rotationX, m_rotationY, m_rotationZ);} 

private:
	float m_positionX, m_positionY, m_positionZ, m_rotationX, m_rotationY, m_rotationZ;
	D3DXVECTOR3 m_up, m_position, m_lookAt;
	D3DXMATRIX m_viewMatrix, m_reflectionViewMatrix, m_mapViewMatrix;
};

#endif //_CAMERA_H_