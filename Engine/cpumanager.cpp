///////////////////////////////////////////////////////////////////////////////
// Filename: cpumanager.cpp
// Code Adapted from tutorial http://www.rastertek.com/dx11tut15.html
///////////////////////////////////////////////////////////////////////////////
#include "CpuManager.h"


CpuManager::CpuManager()
{
}


CpuManager::CpuManager(const CpuManager& other)
{
}


CpuManager::~CpuManager()
{
}

void CpuManager::Initialize()
{
	// Initialize the flag indicating whether this object can read the system cpumanager usage or not.
	m_canReadCpu = true;

	// Create a query object to poll cpumanager usage.
	PDH_STATUS status = PdhOpenQuery(NULL, 0, &m_queryHandle);
	if(status != ERROR_SUCCESS)
	{
		m_canReadCpu = false;
	}

	// Set query object to poll all cpumanagers in the system.
	status = PdhAddCounter(m_queryHandle, TEXT("\\Processor(_Total)\\% processor time"), 0, &m_counterHandle);
	if(status != ERROR_SUCCESS)
	{
		m_canReadCpu = false;
	}

	m_lastSampleTime = GetTickCount(); 

	m_cpuUsage = 0;
}

void CpuManager::Shutdown()
{
	if(m_canReadCpu)
	{
		PdhCloseQuery(m_queryHandle);
	}
}

void CpuManager::Update()
{
	PDH_FMT_COUNTERVALUE value; 

	if(m_canReadCpu)
	{
		if((m_lastSampleTime + 1000) < GetTickCount())
		{
			m_lastSampleTime = GetTickCount(); 

			PdhCollectQueryData(m_queryHandle);
        
			PdhGetFormattedCounterValue(m_counterHandle, PDH_FMT_LONG, NULL, &value);

			m_cpuUsage = value.longValue;
		}
	}
}

int CpuManager::GetCpuUsage() const
{
	int usage = 0;

	if(m_canReadCpu)
	{
		usage = (int)m_cpuUsage;
	}
	else
	{
		usage = 0;
	}

	return usage;
}