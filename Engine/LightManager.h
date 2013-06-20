////////////////////////////////////////////////////////////////////////////////
// Filename: lightmanager.h
// Code Adapted from http://www.rastertek.com/dx11tut10.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _LIGHTMANAGER_H_
#define _LIGHTMANAGER_H_


//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>

////////////////////////////////////////////////////////////////////////////////
//  name: LightManager
////////////////////////////////////////////////////////////////////////////////
class LightManager
{
public:
	LightManager();
	LightManager(const LightManager&);
	~LightManager();

	void SetAmbientColor(const D3DXVECTOR4& ambientColor) {m_ambientColor = ambientColor;}
	void SetDiffuseColor(const D3DXVECTOR4& diffuseColor) {m_diffuseColor = diffuseColor;}
	void SetDirection(const D3DXVECTOR3& direction) {m_direction = direction;}
	void SetSpecularColor(const D3DXVECTOR4& ambientColor) {m_ambientColor = ambientColor;}
	void SetSpecularPower(const float specularPower) {m_specularPower = specularPower;}

	const D3DXVECTOR4 GetAmbientColor() const {return m_ambientColor;}
	const D3DXVECTOR4 GetDiffuseColor() const {return m_diffuseColor;}
	const D3DXVECTOR3 GetDirection() const {return m_direction;}
	const D3DXVECTOR4 GetSpecularColor() const {return m_specularColor;}
	const float GetSpecularPower() const {return m_specularPower;}

private:
	D3DXVECTOR4 m_ambientColor, m_diffuseColor, m_specularColor;
	D3DXVECTOR3 m_direction;
	float m_specularPower;
};

#endif