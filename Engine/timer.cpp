///////////////////////////////////////////////////////////////////////////////
// Filename: timer.cpp
// Code Adapted from tutorial http://www.rastertek.com/dx11tut15.html
///////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <windows.h>
#include "timer.h"


Timer::Timer()
{
}


Timer::Timer(const Timer& other)
{
}


Timer::~Timer()
{
}

bool Timer::Initialize()
{
	// Check to see if this system supports high performance timers.
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if(m_frequency == 0)
	{
		return false;
	}

	// Find out how many times the frequency counter ticks every millisecond.
	m_ticksPerMs = static_cast<float>(m_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;
}

void Timer::Update()
{
	INT64 currentTime;

	QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

	float timeDifference = static_cast<float>(currentTime - m_startTime);

	m_frameTime = timeDifference / m_ticksPerMs;

	m_startTime = currentTime;
}
