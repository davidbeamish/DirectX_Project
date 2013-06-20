////////////////////////////////////////////////////////////////////////////////
// Filename: lightmanager.cpp
////////////////////////////////////////////////////////////////////////////////
#include "lightmanager.h"


LightManager::LightManager() : m_ambientColor(0.0f, 0.0f, 0.0f, 0.0f),
							m_diffuseColor(0.0f, 0.0f, 0.0f, 0.0f),
							m_direction(0.0f, 0.0f, 0.0f),
							m_specularColor(0.0f, 0.0f, 0.0f, 0.0f),
							m_specularPower(0.0f)
{
}


LightManager::LightManager(const LightManager& other)
{
}


LightManager::~LightManager()
{
}

