////////////////////////////////////////////////////////////////////////////////
// Filename: camera.cpp
// Adapted from a variety of tutorials on http://www.rastertek.com
////////////////////////////////////////////////////////////////////////////////
#include "camera.h"


Camera::Camera()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_up = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_lookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


Camera::Camera(const Camera& other)
{
}


Camera::~Camera()
{
}



void Camera::Render()
{
	// Setup the vector that points upwards.
	m_up.x = 0.0f;
	m_up.y = 1.0f;
	m_up.z = 0.0f;

	// Setup the position of the camera in the world.
	m_position.x = m_positionX;
	m_position.y = m_positionY;
	m_position.z = m_positionZ;

	// Setup where the camera is looking by default.
	m_lookAt.x = 0.0f;
	m_lookAt.y = 0.0f;
	m_lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	float pitch = m_rotationX * 0.0174532925f;
	float yaw   = m_rotationY * 0.0174532925f;
	float roll  = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&m_lookAt, &m_lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&m_up, &m_up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	m_lookAt = m_position + m_lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &m_lookAt, &m_up);

	GenerateMapViewMatrix();

	return;
}



void Camera::RenderReflection(float height)
{
	// Setup the vector that points upwards.
	m_up.x = 0.0f;
	m_up.y = 1.0f;
	m_up.z = 0.0f;

	// Setup the position of the camera in the world.  For planar reflection invert the Y position of the camera.
	m_position.x = m_positionX;
	m_position.y = -m_positionY + (height * 2.0f);
	m_position.z = m_positionZ;

	// Setup where the camera is looking by default.
	m_lookAt.x = 0.0f;
	m_lookAt.y = 0.0f;
	m_lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.  Invert the X rotation for reflection.
	float pitch = -m_rotationX * 0.0174532925f;
	float yaw   = m_rotationY * 0.0174532925f;
	float roll  = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&m_lookAt, &m_lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&m_up, &m_up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	m_lookAt = m_position + m_lookAt;

	// Finally create the reflection view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_reflectionViewMatrix, &m_position, &m_lookAt, &m_up);

	return;
}


void Camera::GenerateBaseViewMatrix()
{
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	m_up.x = 0.0f;
	m_up.y = 1.0f;
	m_up.z = 0.0f;

	// Setup the position of the camera in the world.
	m_position.x = m_positionX;
	m_position.y = m_positionY;
	m_position.z = m_positionZ;

	// Setup where the camera is looking by default.
	m_lookAt.x = 0.0f;
	m_lookAt.y = 0.0f;
	m_lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw   = m_rotationY * 0.0174532925f;
	roll  = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&m_lookAt, &m_lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&m_up, &m_up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	m_lookAt = m_position + m_lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_baseViewMatrix, &m_position, &m_lookAt, &m_up);

	return;
}

void Camera::GenerateMapViewMatrix()
{
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	m_up.x = 1.0f;
	m_up.y = 0.0f;
	m_up.z = 0.0f;

	// Setup the position of the camera in the world.
	m_position.x = m_positionX;
	m_position.y = m_positionY;
	m_position.z = m_positionZ;

	// Setup where the camera is looking by default.
	m_lookAt.x = 0.0f;
	m_lookAt.y = -1.0f;
	m_lookAt.z = 0.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw   = m_rotationY * 0.0174532925f;
	roll  = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&m_lookAt, &m_lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&m_up, &m_up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	m_lookAt = m_position + m_lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_mapViewMatrix, &m_position, &m_lookAt, &m_up);
}



void Camera::GetBillboardAlign(D3DXMATRIX& out)
{
	D3DXVECTOR3 right;

	D3DXVec3Normalize(&m_lookAt, &m_lookAt);

	D3DXVec3Cross(&right, &m_up, &m_lookAt);

	D3DXVec3Normalize(&right, &right);
	
	out = D3DXMATRIX(right.x,		right.y,	right.z, 0,
					 m_up.x ,		m_up.y ,	m_up.z, 0,
					 m_lookAt.x , m_lookAt.y , m_lookAt.z, 0,
					 0,				0,		0,			1);
}

void Camera::GetBillboardMatrix(D3DXMATRIX& out, D3DXVECTOR3 position)
{
	D3DXVECTOR3 direction, right, up;
	direction = D3DXVECTOR3(m_positionX, m_positionY, m_positionZ) - position;
	D3DXVec3Normalize(&direction, &direction);

	D3DXVec3Cross(&right, &m_up, &direction);
	D3DXVec3Normalize(&right, &right);

	D3DXVec3Cross(&up, &direction, &right);

	out = D3DXMATRIX(right.x, right.y, right.z, 0,
					up.x, up.y, up.z, 0,
					direction.x, direction.y, direction.z, 0,
					position.x, position.y, position.z, 1);
}

void Camera::GetBillboardedWorldMatrix(D3DXMATRIX & out, D3DXVECTOR3 position)
{
	D3DXMATRIX rotationMatrix, translationMatrix;
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 direction = D3DXVECTOR3(position.x - m_positionX, position.y - m_positionY, position.z - m_positionZ);
	//D3DXVECTOR3 direction = D3DXVECTOR3(m_positionX - position.x, m_positionY - position.y , m_positionZ - position.z);
	D3DXVECTOR3 right;
	D3DXVec3Cross(&right, &direction, &up);

	float magnitude = D3DXVec3Length(&direction);
	float yaw = atan2(direction.x, direction.z);
	float pitch = float(D3DX_PI/2 - acos(-direction.y / magnitude));

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, 0.0f);
	D3DXMatrixTranslation(&translationMatrix, position.x, position.y, position.z);

	out = rotationMatrix * translationMatrix;
}


void Camera::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}

void Camera::GetMapViewMatrix(D3DXMATRIX& mapViewMatrix)
{
	m_mapViewMatrix = mapViewMatrix;
	return;
}

void Camera::GetReflectionViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_reflectionViewMatrix;
	return;
}

void Camera::GetBaseViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_baseViewMatrix;
	return;
}

D3DXVECTOR3 Camera::GetPosition()
{
	return D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
}

void Camera::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void Camera::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}



D3DXVECTOR3 Camera::GetRotation()
{
	return D3DXVECTOR3(m_rotationX, m_rotationY, m_rotationZ);
}