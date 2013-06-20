////////////////////////////////////////////////////////////////////////////////
// Filename: position.h
// Code Adapted from tutorial http://www.rastertek.com/tertut01.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _POSITION_H_
#define _POSITION_H_


//////////////
// INCLUDES //
//////////////
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
//  name: Position
////////////////////////////////////////////////////////////////////////////////
class Position
{
public:
	Position();
	Position(const Position&);
	~Position();

	void SetPosition(float x, float y, float z);
	void GetPosition(float& x, float&, float&) const;
	void SetRotation(float x, float y, float z);	
	void GetRotation(float& x, float& y, float& z) const;
	void SetFrameTime(float time);
	void MoveForward(bool keydown);
	void MoveBackward(bool keydown);
	void MoveUpward(bool keydown);
	void MoveDownward(bool keydown);

	void TurnLeft(bool keydown);
	void TurnRight(bool keydown);
	void LookUpward(bool keydown);
	void LookDownward(bool keydown);

	void StrafeLeft(bool keydown);
	void StrafeRight(bool keydown);

private:
	float m_positionX, m_positionY, m_positionZ, m_rotationX, m_rotationY, m_rotationZ,
		m_forwardSpeed, m_backwardSpeed, m_upwardSpeed, m_downwardSpeed, m_leftTurnSpeed, m_rightTurnSpeed, 
		m_strafeLeftSpeed, m_strafeRightSpeed, m_lookUpSpeed, m_lookDownSpeed, m_frameTime;
};

#endif