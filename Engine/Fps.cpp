///////////////////////////////////////////////////////////////////////////////
// Filename: fps.cpp
// Code Adapted from tutorial http://www.rastertek.com/dx11tut15.html
///////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <windows.h>
#include <mmsystem.h>
#include "fps.h"

Fps::Fps() : m_fps(0),
	m_count(0),
	m_startTime(timeGetTime())
{}


Fps::Fps(const Fps& other)
{}


Fps::~Fps()
{}

void Fps::Update()
{
	m_count++;

	if(timeGetTime() >= (m_startTime + 1000))
	{
		m_fps = m_count;
		m_count = 0;
		
		m_startTime = timeGetTime();
	}
}

int Fps::GetFps() const
{
	return m_fps;
}