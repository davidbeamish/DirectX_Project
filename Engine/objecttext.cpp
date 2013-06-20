////////////////////////////////////////////////////////////////////////////////
// Filename: objecttext.cpp
////////////////////////////////////////////////////////////////////////////////
#include "objecttext.h"
#include "graphicsmanager.h"
#include "d3d.h"
#include "camera.h"
#include "shadermanager.h"
#include "text.h"
ObjectText::ObjectText(D3D* m_D3D, Camera* m_Camera, HWND hwnd, int screenWidth, int screenHeight)
{
	D3DXMATRIX baseViewMatrix;
	
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new Text;

	// Initialize the text object.
	m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
}

ObjectText::ObjectText(const ObjectText& other)
{
}

ObjectText::~ObjectText()
{
	delete m_Text;
}

bool ObjectText::Render()
{
	return true;
}

bool ObjectText::Render(GraphicsManager& graphicsManager, int renderPass)
{
	D3DXMATRIX worldMatrix, orthoMatrix; 
	bool result;

	// Update the position values in the text object.
	D3DXMATRIX cameraPositionMatrix = graphicsManager.GetCamera()->GetPosition();
	result = m_Text->SetCameraPosition(cameraPositionMatrix._11, cameraPositionMatrix._12,cameraPositionMatrix._13, graphicsManager.GetD3DObject()->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Update the rotation values in the text object.
	D3DXMATRIX cameraRotationMatrix = graphicsManager.GetCamera()->GetRotation();
	result = m_Text->SetCameraRotation(cameraRotationMatrix._11, cameraRotationMatrix._12, cameraRotationMatrix._13, graphicsManager.GetD3DObject()->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Turn off the Z buffer to begin all 2D rendering.
	graphicsManager.GetD3DObject()->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	graphicsManager.GetD3DObject()->TurnOnSecondaryAlphaBlending();

	worldMatrix = graphicsManager.GetWorldMatrix();
	orthoMatrix = graphicsManager.GetOrthoMatrix();

	D3DXMatrixTranslation(&worldMatrix, -5.0f, -5.0f, 0.0f);

	// Render the text strings.
	result = m_Text->Render(graphicsManager.GetD3DObject()->GetDeviceContext(), graphicsManager.GetShaderManager()->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	graphicsManager.GetD3DObject()->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	graphicsManager.GetD3DObject()->TurnZBufferOn();

	return true;
}


bool ObjectText::Frame(D3D* m_D3D, int fps, int cpumanager, int mouseX, int mouseY, bool collision)
{
	bool result; 

	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Set the cpumanager usage.
	result = m_Text->SetCpuManager(cpumanager, m_D3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Set the mouse and collision info.
	result = m_Text->SetMousePosition(mouseX, mouseY, collision, m_D3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}



	return true;
}

//
//bool ObjectText::SetFps(int fps, ID3D11DeviceContext* deviceContext)
//{
//	char tempString[16];
//	char fpsString[16];
//	float red, green, blue;
//	bool result;
//
//
//	// Truncate the fps to below 10,000.
//	if(fps > 9999)
//	{
//		fps = 9999;
//	}
//
//	// Convert the fps integer to string format.
//	_itoa_s(fps, tempString, 10);
//
//	// Setup the fps string.
//	strcpy_s(fpsString, "Fps: ");
//	strcat_s(fpsString, tempString);
//
//	// If fps is 60 or above set the fps color to green.
//	if(fps >= 60)
//	{
//		red = 0.0f;
//		green = 1.0f;
//		blue = 0.0f;
//	}
//
//	// If fps is below 60 set the fps color to yellow.
//	if(fps < 60)
//	{
//		red = 1.0f;
//		green = 1.0f;
//		blue = 0.0f;
//	}
//
//	// If fps is below 30 set the fps color to red.
//	if(fps < 30)
//	{
//		red = 1.0f;
//		green = 0.0f;
//		blue = 0.0f;
//	}
//
//	// Update the sentence vertex buffer with the new string information.
//	result = m_Text->UpdateSentence(m_Text->m_sentence1, fpsString, 10, 20, red, green, blue, deviceContext);
//	if(!result)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//
//bool ObjectText::SetCpuManager(int cpumanager, ID3D11DeviceContext* deviceContext)
//{
//	char tempString[16];
//	char cpumanagerString[16];
//	bool result;
//
//
//	// Convert the cpumanager integer to string format.
//	_itoa_s(cpumanager, tempString, 10);
//
//	// Setup the cpumanager string.
//	strcpy_s(cpumanagerString, "CpuManager: ");
//	strcat_s(cpumanagerString, tempString);
//	strcat_s(cpumanagerString, "%");
//
//	// Update the sentence vertex buffer with the new string information.
//	result = UpdateSentence(m_sentence2, cpumanagerString, 10, 40, 0.0f, 1.0f, 0.0f, deviceContext);
//	if(!result)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//
//bool ObjectText::SetCameraPosition(float posX, float posY, float posZ, ID3D11DeviceContext* deviceContext)
//{
//	int positionX, positionY, positionZ;
//	char tempString[16];
//	char dataString[16];
//	bool result;
//
//
//	// Convert the position from floating point to integer.
//	positionX = (int)posX;
//	positionY = (int)posY;
//	positionZ = (int)posZ;
//
//	// Truncate the position if it exceeds either 9999 or -9999.
//	if(positionX > 9999) { positionX = 9999; }
//	if(positionY > 9999) { positionY = 9999; }
//	if(positionZ > 9999) { positionZ = 9999; }
//
//	if(positionX < -9999) { positionX = -9999; }
//	if(positionY < -9999) { positionY = -9999; }
//	if(positionZ < -9999) { positionZ = -9999; }
//
//	// Setup the X position string.
//	_itoa_s(positionX, tempString, 10);
//	strcpy_s(dataString, "X: ");
//	strcat_s(dataString, tempString);
//
//	result = UpdateSentence(m_sentence5, dataString, 10, 130, 0.0f, 1.0f, 0.0f, deviceContext);
//	if(!result)
//	{
//		return false;
//	}
//	
//	// Setup the Y position string.
//	_itoa_s(positionY, tempString, 10);
//	strcpy_s(dataString, "Y: ");
//	strcat_s(dataString, tempString);
//
//	result = UpdateSentence(m_sentence6, dataString, 10, 150, 0.0f, 1.0f, 0.0f, deviceContext);
//	if(!result)
//	{
//		return false;
//	}
//
//	// Setup the Z position string.
//	_itoa_s(positionZ, tempString, 10);
//	strcpy_s(dataString, "Z: ");
//	strcat_s(dataString, tempString);
//
//	result = UpdateSentence(m_sentence7, dataString, 10, 170, 0.0f, 1.0f, 0.0f, deviceContext);
//	if(!result)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//
//bool ObjectText::SetCameraRotation(float rotX, float rotY, float rotZ, ID3D11DeviceContext* deviceContext)
//{
//	int rotationX, rotationY, rotationZ;
//	char tempString[16];
//	char dataString[16];
//	bool result;
//
//
//	// Convert the rotation from floating point to integer.
//	rotationX = (int)rotX;
//	rotationY = (int)rotY;
//	rotationZ = (int)rotZ;
//
//	// Setup the X rotation string.
//	_itoa_s(rotationX, tempString, 10);
//	strcpy_s(dataString, "rX: ");
//	strcat_s(dataString, tempString);
//
//	result = UpdateSentence(m_sentence8, dataString, 10, 210, 0.0f, 1.0f, 0.0f, deviceContext);
//	if(!result)
//	{
//		return false;
//	}
//
//	// Setup the Y rotation string.
//	_itoa_s(rotationY, tempString, 10);
//	strcpy_s(dataString, "rY: ");
//	strcat_s(dataString, tempString);
//
//	result = UpdateSentence(m_sentence9, dataString, 10, 230, 0.0f, 1.0f, 0.0f, deviceContext);
//	if(!result)
//	{
//		return false;
//	}
//
//	// Setup the Z rotation string.
//	_itoa_s(rotationZ, tempString, 10);
//	strcpy_s(dataString, "rZ: ");
//	strcat_s(dataString, tempString);
//
//	result = UpdateSentence(m_sentence10, dataString, 10, 250, 0.0f, 1.0f, 0.0f, deviceContext);
//	if(!result)
//	{
//		return false;
//	}
//
//	return true;
//}
//
