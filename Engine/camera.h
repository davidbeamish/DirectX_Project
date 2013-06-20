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

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void Render();
	void GetViewMatrix(D3DXMATRIX& viewMatrix);

	void GenerateBaseViewMatrix();
	void GetBaseViewMatrix(D3DXMATRIX& baseViewMatrix);

	void GenerateMapViewMatrix();
	void GetMapViewMatrix(D3DXMATRIX& mapViewMatrix);	

	void RenderReflection(float height);
	void GetReflectionViewMatrix(D3DXMATRIX& viewMatrix);

	void GetBillboardedWorldMatrix(D3DXMATRIX & out, D3DXVECTOR3 position);

	void GetBillboardAlign(D3DXMATRIX& out);
	void GetBillboardMatrix(D3DXMATRIX& out, D3DXVECTOR3 position);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	D3DXVECTOR3 m_up, m_position, m_lookAt;

	D3DXMATRIX m_viewMatrix, m_baseViewMatrix, m_reflectionViewMatrix, m_mapViewMatrix;
};

#endif //_CAMERA_H_