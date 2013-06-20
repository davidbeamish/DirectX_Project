///////////////////////////////////////////////////////////////////////////////
// Filename: text.cpp
// Code Adapted from tutorial http://www.rastertek.com/dx11tut12.html
///////////////////////////////////////////////////////////////////////////////
#include "text.h"
#include "shadermanager.h"

Text::Text()
{
	m_Font = 0;
	m_ShaderManager = 0;

	m_sentence1 = 0;
	m_sentence2 = 0;
	m_sentence3 = 0;
	m_sentence4 = 0;
	m_sentence5 = 0;
	m_sentence6 = 0;
	m_sentence7 = 0;
	m_sentence8 = 0;
	m_sentence9 = 0;
	m_sentence10 = 0;
	m_sentence11 = 0;
	m_sentence12 = 0;
	m_sentence13 = 0;
	m_sentence14 = 0;
}


Text::Text(const Text& other)
{
}


Text::~Text()
{
}


bool Text::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hwnd, int screenWidth, int screenHeight, 
						   D3DXMATRIX baseViewMatrix)
{
	bool result;


	// Store the screen width and height.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Store the base view matrix.
	m_baseViewMatrix = baseViewMatrix;

	// Create the font object.
	m_Font = new Font;
	if(!m_Font)
	{
		return false;
	}

	// Initialize the font object.
	result = m_Font->Initialize(device, "../Engine/data/fontdata.txt", L"../Engine/data/font.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font object.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManager;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_ShaderManager->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the first sentence.
	result = InitializeSentence(&m_sentence1, 16, device);
	if(!result)
	{
		return false;
	}

	// Initialize the second sentence.
	result = InitializeSentence(&m_sentence2, 16, device);
	if(!result)
	{
		return false;
	}

	// Initialize the third sentence.
	result = InitializeSentence(&m_sentence3, 16, device);
	if(!result)
	{
		return false;
	}

	// Initialize the fourth sentence.
	result = InitializeSentence(&m_sentence4, 16, device);
	if(!result)
	{
		return false;
	}

	// Initialize the fifth sentence.
	result = InitializeSentence(&m_sentence5, 16, device);
	if(!result)
	{
		return false;
	}

	// Initialize the sixth sentence.
	result = InitializeSentence(&m_sentence6, 16, device);
	if(!result)
	{
		return false;
	}

	// Initialize the seventh sentence.
	result = InitializeSentence(&m_sentence7, 16, device);
	if(!result)
	{
		return false;
	}

	// Initialize the eighth sentence.
	result = InitializeSentence(&m_sentence8, 16, device);
	if(!result)
	{
		return false;
	}

	// Initialize the ninth sentence.
	result = InitializeSentence(&m_sentence9, 16, device);
	if(!result)
	{
		return false;
	}

	// Initialize the tenth sentence.
	result = InitializeSentence(&m_sentence10, 16, device);
	if(!result)
	{
		return false;
	}

	// Initialize the eleventh sentence.
	result = InitializeSentence(&m_sentence11, 32, device);
	if(!result)
	{
		return false;
	}

	// Initialize the twelth sentence.
	result = InitializeSentence(&m_sentence12, 16, device);
	if(!result)
	{
		return false;
	}

	// Initialize the thirteenth sentence.
	result = InitializeSentence(&m_sentence13, 16, device);
	if(!result)
	{
		return false;
	}

	// Initialize the fourteenth sentence.
	result = InitializeSentence(&m_sentence14, 32, device);
	if(!result)
	{
		return false;
	}

	return true;
}


void Text::Shutdown()
{
	// Release the sentences.
	ReleaseSentence(&m_sentence1);
	ReleaseSentence(&m_sentence2);
	ReleaseSentence(&m_sentence3);
	ReleaseSentence(&m_sentence4);
	ReleaseSentence(&m_sentence5);
	ReleaseSentence(&m_sentence6);
	ReleaseSentence(&m_sentence7);
	ReleaseSentence(&m_sentence8);
	ReleaseSentence(&m_sentence9);
	ReleaseSentence(&m_sentence10);
	ReleaseSentence(&m_sentence11);

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the font object.
	if(m_Font)
	{
		m_Font->Shutdown();
		delete m_Font;
		m_Font = 0;
	}

	return;
}


bool Text::Render(ID3D11DeviceContext* deviceContext, FontShader* m_FontShader, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix)
{
	bool result;


	// Draw the sentences.
	result = RenderSentence(m_sentence1, deviceContext, m_ShaderManager->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	result = RenderSentence(m_sentence2, deviceContext, m_ShaderManager->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	result = RenderSentence(m_sentence3, deviceContext, m_ShaderManager->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	result = RenderSentence(m_sentence4, deviceContext, m_ShaderManager->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	result = RenderSentence(m_sentence5, deviceContext, m_ShaderManager->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	result = RenderSentence(m_sentence6, deviceContext, m_ShaderManager->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	result = RenderSentence(m_sentence7, deviceContext, m_ShaderManager->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	result = RenderSentence(m_sentence8, deviceContext, m_ShaderManager->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	result = RenderSentence(m_sentence9, deviceContext, m_ShaderManager->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	result = RenderSentence(m_sentence10, deviceContext, m_ShaderManager->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	result = RenderSentence(m_sentence11, deviceContext, m_ShaderManager->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	result = RenderSentence(m_sentence12, deviceContext, m_ShaderManager->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	result = RenderSentence(m_sentence13, deviceContext, m_ShaderManager->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	result = RenderSentence(m_sentence14, deviceContext, m_ShaderManager->GetFontShader(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	return true;
}


bool Text::InitializeSentence(SentenceType** sentence, int maxLength, ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;


	// Create a new sentence object.
	*sentence = new SentenceType;
	if(!*sentence)
	{
		return false;
	}

	// Initialize the sentence buffers to null.
	(*sentence)->vertexBuffer = 0;
	(*sentence)->indexBuffer = 0;

	// Set the maximum length of the sentence.
	(*sentence)->maxLength = maxLength;

	// Set the number of vertices in the vertex array.
	(*sentence)->vertexCount = 6 * maxLength;

	// Set the number of indexes in the index array.
	(*sentence)->indexCount = (*sentence)->vertexCount;

	// Create the vertex array.
	vertices = new VertexType[(*sentence)->vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[(*sentence)->indexCount];
	if(!indices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * (*sentence)->vertexCount));

	// Initialize the index array.
	for(i=0; i<(*sentence)->indexCount; i++)
	{
		indices[i] = i;
	}

	// Set up the description of the dynamic vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * (*sentence)->vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &(*sentence)->vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * (*sentence)->indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &(*sentence)->indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	// Release the index array as it is no longer needed.
	delete [] indices;
	indices = 0;

	return true;
}


bool Text::UpdateSentence(SentenceType* sentence, char* text, int positionX, int positionY, float red, float green, float blue,
							   ID3D11DeviceContext* deviceContext)
{
	int numLetters;
	VertexType* vertices;
	float drawX, drawY;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;


	// Store the color of the sentence.
	sentence->red = red;
	sentence->green = green;
	sentence->blue = blue;

	// Get the number of letters in the sentence.
	numLetters = (int)strlen(text);

	// Check for possible buffer overflow.
	if(numLetters > sentence->maxLength)
	{
		return false;
	}

	// Create the vertex array.
	vertices = new VertexType[sentence->vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * sentence->vertexCount));

	// Calculate the X and Y pixel position on the screen to start drawing to.
	drawX = (float)(((m_screenWidth / 2) * -1) + positionX);
	drawY = (float)((m_screenHeight / 2) - positionY);

	// Use the font  to build the vertex array from the sentence text and sentence draw location.
	m_Font->BuildVertexArray((void*)vertices, text, drawX, drawY);

	// Lock the vertex buffer so it can be written to.
	result = deviceContext->Map(sentence->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (VertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * sentence->vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(sentence->vertexBuffer, 0);

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	return true;
}


void Text::ReleaseSentence(SentenceType** sentence)
{
	if(*sentence)
	{
		// Release the sentence vertex buffer.
		if((*sentence)->vertexBuffer)
		{
			(*sentence)->vertexBuffer->Release();
			(*sentence)->vertexBuffer = 0;
		}

		// Release the sentence index buffer.
		if((*sentence)->indexBuffer)
		{
			(*sentence)->indexBuffer->Release();
			(*sentence)->indexBuffer = 0;
		}

		// Release the sentence.
		delete *sentence;
		*sentence = 0;
	}

	return;
}


bool Text::RenderSentence(SentenceType* sentence, ID3D11DeviceContext* deviceContext, FontShader* FontShader, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix)
{
	unsigned int stride, offset;
	D3DXVECTOR4 pixelColor;
	bool result;


	// Set vertex buffer stride and offset.
    stride = sizeof(VertexType); 
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &sentence->vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(sentence->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create a pixel color vector with the input sentence color.
	pixelColor = D3DXVECTOR4(sentence->red, sentence->green, sentence->blue, 1.0f);

	// Render the text using the font shader.
	result = m_ShaderManager->RenderFontShader(deviceContext, sentence->indexCount, worldMatrix, m_baseViewMatrix, orthoMatrix, m_Font->GetTexture(), pixelColor);
	if(!result)
	{
		false;
	}

	return true;
}

bool Text::SetFps(int fps, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char fpsString[16];
	float red, green, blue;
	bool result;


	// Truncate the fps to below 10,000.
	if(fps > 9999)
	{
		fps = 9999;
	}

	// Convert the fps integer to string format.
	_itoa_s(fps, tempString, 10);

	// Setup the fps string.
	strcpy_s(fpsString, "Fps: ");
	strcat_s(fpsString, tempString);

	// If fps is 60 or above set the fps color to green.
	if(fps >= 60)
	{
		red = 0.0f;
		green = 1.0f;
		blue = 0.0f;
	}

	// If fps is below 60 set the fps color to yellow.
	if(fps < 60)
	{
		red = 1.0f;
		green = 1.0f;
		blue = 0.0f;
	}

	// If fps is below 30 set the fps color to red.
	if(fps < 30)
	{
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f;
	}

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence1, fpsString, 10, 20, red, green, blue, deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}

bool Text::SetCpuManager(int cpumanager, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char cpumanagerString[16];
	bool result;


	// Convert the cpumanager integer to string format.
	_itoa_s(cpumanager, tempString, 10);

	// Setup the cpumanager string.
	strcpy_s(cpumanagerString, "Cpu: ");
	strcat_s(cpumanagerString, tempString);
	strcat_s(cpumanagerString, "%");

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence2, cpumanagerString, 10, 40, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}

bool Text::SetVideoCardInfo(char* videoCardName, int videoCardMemory, ID3D11DeviceContext* deviceContext)
{
	char dataString[150];
	bool result;
	char tempString[16];
	char memoryString[32];


	// Setup the video card name string.
	strcpy_s(dataString, "Video Card: ");
	strcat_s(dataString, videoCardName);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence1, dataString, 10, 10, 1.0f, 1.0f, 1.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	// Truncate the memory value to prevent buffer over flow.
	if(videoCardMemory > 9999999)
	{
		videoCardMemory = 9999999;
	}

	// Convert the video memory integer value to a string format.
	_itoa_s(videoCardMemory, tempString, 10);

	// Setup the video memory string.
	strcpy_s(memoryString, "Video Memory: ");
	strcat_s(memoryString, tempString);
	strcat_s(memoryString, " MB");

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence2, memoryString, 10, 30, 1.0f, 1.0f, 1.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}


bool Text::SetCameraPosition(float posX, float posY, float posZ, ID3D11DeviceContext* deviceContext)
{
	int positionX, positionY, positionZ;
	char tempString[16];
	char dataString[16];
	bool result;


	// Convert the position from floating point to integer.
	positionX = (int)posX;
	positionY = (int)posY;
	positionZ = (int)posZ;

	// Truncate the position if it exceeds either 9999 or -9999.
	if(positionX > 9999) { positionX = 9999; }
	if(positionY > 9999) { positionY = 9999; }
	if(positionZ > 9999) { positionZ = 9999; }

	if(positionX < -9999) { positionX = -9999; }
	if(positionY < -9999) { positionY = -9999; }
	if(positionZ < -9999) { positionZ = -9999; }

	// Setup the X position string.
	_itoa_s(positionX, tempString, 10);
	strcpy_s(dataString, "X: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence5, dataString, 10, 130, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}
	
	// Setup the Y position string.
	_itoa_s(positionY, tempString, 10);
	strcpy_s(dataString, "Y: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence6, dataString, 10, 150, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	// Setup the Z position string.
	_itoa_s(positionZ, tempString, 10);
	strcpy_s(dataString, "Z: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence7, dataString, 10, 170, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}


bool Text::SetCameraRotation(float rotX, float rotY, float rotZ, ID3D11DeviceContext* deviceContext)
{
	int rotationX, rotationY, rotationZ;
	char tempString[16];
	char dataString[16];
	bool result;


	// Convert the rotation from floating point to integer.
	rotationX = (int)rotX;
	rotationY = (int)rotY;
	rotationZ = (int)rotZ;

	// Setup the X rotation string.
	_itoa_s(rotationX, tempString, 10);
	strcpy_s(dataString, "rX: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence8, dataString, 10, 210, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	// Setup the Y rotation string.
	_itoa_s(rotationY, tempString, 10);
	strcpy_s(dataString, "rY: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence9, dataString, 10, 230, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	// Setup the Z rotation string.
	_itoa_s(rotationZ, tempString, 10);
	strcpy_s(dataString, "rZ: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence10, dataString, 10, 250, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}


bool Text::SetMousePosition(int posX, int posY, bool collision, ID3D11DeviceContext* deviceContext)
{
	int positionX, positionY;

	char tempString[16];
	char dataString[16];
	bool result;


	// Convert the position from floating point to integer.
	positionX = (int)posX;
	positionY = (int)posY;

	// Truncate the position if it exceeds either 9999 or -9999.
	if(positionX > 9999) { positionX = 9999; }
	if(positionY > 9999) { positionY = 9999; }

	if(positionX < -9999) { positionX = -9999; }
	if(positionY < -9999) { positionY = -9999; }

	// Setup the X position string.
	_itoa_s(positionX, tempString, 10);
	strcpy_s(dataString, "Mouse X: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence12, dataString, 10, 70, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}
	
	// Setup the Y position string.
	_itoa_s(positionY, tempString, 10);
	strcpy_s(dataString, "Mouse Y: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence13, dataString, 10, 90, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	// Setup the collision position string.
	_itoa_s(collision, tempString, 10);
	strcpy_s(dataString, "Collision: ");
	strcat_s(dataString, tempString);

	result = UpdateSentence(m_sentence14, dataString, 10, 110, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}


bool Text::SetRenderCount(int count, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char renderString[32];
	bool result;


	// Truncate the render count if it gets to large to prevent a buffer overflow.
	if(count > 999999999)
	{
		count = 999999999;
	}

	// Convert the cpumanager integer to string format.
	_itoa_s(count, tempString, 10);

	// Setup the cpumanager string.
	strcpy_s(renderString, "Render Count: ");
	strcat_s(renderString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence11, renderString, 10, 290, 0.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}