////////////////////////////////////////////////////////////////////////////////
// Filename: position.cpp
// Code Adapted from tutorial http://www.rastertek.com/tertut01.html
////////////////////////////////////////////////////////////////////////////////
#include "position.h"

Position::Position() : m_positionX(0.0f), m_positionY(0.0f), m_positionZ(0.0f),	m_rotationX(0.0f), m_rotationY(0.0f), m_rotationZ(0.0f), 
	m_forwardSpeed(0.0f), m_backwardSpeed(0.0f), m_upwardSpeed(0.0f), m_downwardSpeed(0.0f), m_leftTurnSpeed(0.0f), m_rightTurnSpeed(0.0f), 
	m_strafeLeftSpeed(0.0f), m_strafeRightSpeed(0.0f),	m_lookUpSpeed(0.0f), m_lookDownSpeed(0.0f), m_frameTime(0.0f)
{}


Position::Position(const Position& other)
{}


Position::~Position()
{}

// If the key is pressed the camera accelerates until max speed is reached.  Similarly if the key is released the camera decelerates.
void Position::MoveForward(bool keydown)
{
	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_forwardSpeed += m_frameTime * 0.001f;

		if(m_forwardSpeed > (m_frameTime * 0.03f))
		{
			m_forwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_forwardSpeed -= m_frameTime * 0.0007f;

		if(m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	float radians = m_rotationY * 0.0174532925f;

	// Update the position.
	m_positionX += sinf(radians) * m_forwardSpeed;
	m_positionZ += cosf(radians) * m_forwardSpeed;
}

void Position::MoveBackward(bool keydown)
{
	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_backwardSpeed += m_frameTime * 0.001f;

		if(m_backwardSpeed > (m_frameTime * 0.03f))
		{
			m_backwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_backwardSpeed -= m_frameTime * 0.0007f;

		if(m_backwardSpeed < 0.0f)
		{
			m_backwardSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	float radians = m_rotationY * 0.0174532925f;

	// Update the position.
	m_positionX -= sinf(radians) * m_backwardSpeed;
	m_positionZ -= cosf(radians) * m_backwardSpeed;
}

void Position::MoveUpward(bool keydown)
{
	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_upwardSpeed += m_frameTime * 0.003f;

		if(m_upwardSpeed > (m_frameTime * 0.03f))
		{
			m_upwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_upwardSpeed -= m_frameTime * 0.002f;

		if(m_upwardSpeed < 0.0f)
		{
			m_upwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY += (m_upwardSpeed*0.5f);
}

void Position::MoveDownward(bool keydown)
{
	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_downwardSpeed += m_frameTime * 0.003f;

		if(m_downwardSpeed > (m_frameTime * 0.03f))
		{
			m_downwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_downwardSpeed -= m_frameTime * 0.002f;

		if(m_downwardSpeed < 0.0f)
		{
			m_downwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY -= (m_downwardSpeed*0.5f);
}

void Position::TurnLeft(bool keydown)
{
	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_leftTurnSpeed += m_frameTime * 0.01f;

		if(m_leftTurnSpeed > (m_frameTime * 0.15f))
		{
			m_leftTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime* 0.005f;

		if(m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationY -= m_leftTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if(m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}
}

void Position::TurnRight(bool keydown)
{
	// Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_rightTurnSpeed += m_frameTime * 0.01f;

		if(m_rightTurnSpeed > (m_frameTime * 0.15f))
		{
			m_rightTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime* 0.005f;

		if(m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationY += m_rightTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if(m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}
}

void Position::LookUpward(bool keydown)
{
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookUpSpeed += m_frameTime * 0.01f;

		if(m_lookUpSpeed > (m_frameTime * 0.15f))
		{
			m_lookUpSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_lookUpSpeed -= m_frameTime* 0.005f;

		if(m_lookUpSpeed < 0.0f)
		{
			m_lookUpSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX -= m_lookUpSpeed;

	// Keep the rotation maximum 90 degrees.
	if(m_rotationX > 90.0f)
	{
		m_rotationX = 90.0f;
	}
}

void Position::LookDownward(bool keydown)
{
	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookDownSpeed += m_frameTime * 0.01f;

		if(m_lookDownSpeed > (m_frameTime * 0.15f))
		{
			m_lookDownSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_lookDownSpeed -= m_frameTime* 0.005f;

		if(m_lookDownSpeed < 0.0f)
		{
			m_lookDownSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX += m_lookDownSpeed;

	// Keep the rotation maximum 90 degrees.
	if(m_rotationX < -90.0f)
	{
		m_rotationX = -90.0f;
	}
}

void Position::StrafeLeft(bool keydown)
{
	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_strafeLeftSpeed += m_frameTime * 0.001f;

		if(m_strafeLeftSpeed > (m_frameTime * 0.03f))
		{
			m_strafeLeftSpeed  = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_strafeLeftSpeed -= m_frameTime * 0.0007f;

		if(m_strafeLeftSpeed < 0.0f)
		{
			m_strafeLeftSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	float radians = m_rotationY * 0.0174532925f;

	// Update the position.
	m_positionX -= cosf(radians) * m_strafeLeftSpeed;
	m_positionZ -= sinf(-radians) * m_strafeLeftSpeed;
}

void Position::StrafeRight(bool keydown)
{
	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_strafeRightSpeed += m_frameTime * 0.001f;

		if(m_strafeRightSpeed > (m_frameTime * 0.03f))
		{
			m_strafeRightSpeed  = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_strafeRightSpeed -= m_frameTime * 0.0007f;

		if(m_strafeRightSpeed < 0.0f)
		{
			m_strafeRightSpeed = 0.0f;
		}
	}

	// Convert degrees to radians.
	float radians = m_rotationY * 0.0174532925f;

	// Update the position.
	m_positionX += cosf(radians) * m_strafeRightSpeed;
	m_positionZ += sinf(-radians) * m_strafeRightSpeed;
}

// Sets the position of the camera.
void Position::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
}

void Position::GetPosition(float& x, float& y, float& z) const
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;
}

// Sets the rotation of the camera.
void Position::SetRotation(float x, float y, float z) 
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
}



void Position::GetRotation(float& x, float& y, float& z) const
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;
}

// Stores the current frame time for the use of movement calculation functions.
void Position::SetFrameTime(float time)
{
	m_frameTime = time;
}