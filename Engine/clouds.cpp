////////////////////////////////////////////////////////////////////////////////
// Filename: clouds.cpp
// Code Adapted from tutorial http://www.rastertek.com/tertut11.html
////////////////////////////////////////////////////////////////////////////////
#include "clouds.h"
#include "texture.h"

Clouds::Clouds()
{
	m_clouds = 0;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_CloudTexture1 = 0;
	m_CloudTexture2 = 0;
	m_PerturbTexture = 0;
}


Clouds::Clouds(const Clouds& other)
{
}


Clouds::~Clouds()
{
}


bool Clouds::Initialize(ID3D11Device* device, WCHAR* cloudTextureFilename1, WCHAR* cloudTextureFilename2, WCHAR* perturbTextureFilename)
{
	int cloudsResolution, textureRepeat;
	float cloudsWidth, cloudsTop, cloudsBottom;
	bool result;


	// Set the clouds parameters.
	cloudsResolution = 25;
	cloudsWidth = 5.0f;
	cloudsTop = 0.5f;
	cloudsBottom = -0.25f;
	textureRepeat = 2;

	// Set the brightness and scales of the clouds.
	m_brightness.x = 0.2f;
	m_brightness.y = 0.15f;
	m_scale.x = 0.8f;
	m_scale.y = 0.4f;

	// Initialize the texture translation values.
	m_translation.x = 0.0f;
	m_translation.y = 0.0f;
	// Create the clouds.
	result = InitializeClouds(cloudsResolution, cloudsWidth, cloudsTop, cloudsBottom, textureRepeat);
	if(!result)
	{
		return false;
	}

	// Create the vertex and index buffer for the clouds.
	result = InitializeBuffers(device, cloudsResolution);
	if(!result)
	{
		return false;
	}

	// Load the clouds textures.
	result = LoadTextures(device, cloudTextureFilename1, cloudTextureFilename2, perturbTextureFilename);
	if(!result)
	{
		return false;
	}

	return true;
}


void Clouds::Shutdown()
{
	// Release the clouds textures.
	ReleaseTextures();

	// Release the vertex and index buffer that were used for rendering the clouds.
	ShutdownBuffers();

	// Release the clouds array.
	ShutdownClouds();

	return;
}


void Clouds::Render(ID3D11DeviceContext* deviceContext)
{
	// Render the clouds.
	RenderBuffers(deviceContext);

	return;
}


void Clouds::Frame()
{
	// Increment the texture translation value each frame.
	m_translation.x += 0.00015f;
	if(m_translation.x > 1.0f)
	{
		m_translation.x -= 1.0f;
	}

	m_translation.y += 0.00005f;
	if(m_translation.y > 1.0f)
	{
		m_translation.y -= 1.0f;
	}

	return;
}

int Clouds::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* Clouds::GetCloudTexture1()
{
	return m_CloudTexture1->GetTexture();
}

ID3D11ShaderResourceView* Clouds::GetCloudTexture2()
{
	return m_CloudTexture2->GetTexture();
}


ID3D11ShaderResourceView* Clouds::GetPerturbTexture()
{
	return m_PerturbTexture->GetTexture();
}

D3DXVECTOR2 Clouds::GetScale()
{
	return m_scale;
}

D3DXVECTOR2 Clouds::GetBrightness()
{
	return m_brightness;
}


D3DXVECTOR2 Clouds::GetTranslation()
{
	return m_translation;
}

bool Clouds::InitializeClouds(int cloudsResolution, float cloudsWidth, float cloudsTop, float cloudsBottom, int textureRepeat)
{
	float quadSize, radius, constant, textureDelta;
	int i, j, index;
	float positionX, positionY, positionZ, tu, tv;


	// Create the array to hold the clouds coordinates.
	m_clouds = new CloudsType[(cloudsResolution + 1) * (cloudsResolution + 1)];
	if(!m_clouds)
	{
		return false;
	}

	// Determine the size of each quad on the clouds.
	quadSize = cloudsWidth / (float)cloudsResolution;

	// Calculate the radius of the clouds based on the width.
	radius = cloudsWidth / 2.0f;

	// Calculate the height constant to increment by.
	constant = (cloudsTop - cloudsBottom) / (radius * radius);

	// Calculate the texture coordinate increment value.
	textureDelta = (float)textureRepeat / (float)cloudsResolution;

	// Loop through the clouds and build the coordinates based on the increment values given.
	for(j=0; j<=cloudsResolution; j++)
	{
		for(i=0; i<=cloudsResolution; i++)
		{
			// Calculate the vertex coordinates.
			positionX = (-0.5f * cloudsWidth) + ((float)i * quadSize);
			positionZ = (-0.5f * cloudsWidth) + ((float)j * quadSize);
			positionY = cloudsTop - (constant * ((positionX * positionX) + (positionZ * positionZ)));

			// Calculate the texture coordinates.
			tu = (float)i * textureDelta;
			tv = (float)j * textureDelta;

			// Calculate the index into the clouds array to add this coordinate.
			index = j * (cloudsResolution + 1) + i;

			// Add the coordinates to the clouds array.
			m_clouds[index].x = positionX;
			m_clouds[index].y = positionY;
			m_clouds[index].z = positionZ;
			m_clouds[index].tu = tu;
			m_clouds[index].tv = tv;
		}
	}

	return true;
}


void Clouds::ShutdownClouds()
{
	// Release the clouds array.
	if(m_clouds)
	{
		delete [] m_clouds;
		m_clouds = 0;
	}

	return;
}


bool Clouds::InitializeBuffers(ID3D11Device* device, int cloudsResolution)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i, j, index, index1, index2, index3, index4;


	// Calculate the number of vertices in the clouds mesh.
	m_vertexCount = (cloudsResolution + 1) * (cloudsResolution + 1) * 6;

	// Set the index count to the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// Initialize the index into the vertex array.
	index = 0;

	// Load the vertex and index array with the clouds array data.
	for(j=0; j<cloudsResolution; j++)
	{
		for(i=0; i<cloudsResolution; i++)
		{
			index1 = j * (cloudsResolution + 1) + i;
			index2 = j * (cloudsResolution + 1) + (i+1);
			index3 = (j+1) * (cloudsResolution + 1) + i;
			index4 = (j+1) * (cloudsResolution + 1) + (i+1);

			// Triangle 1 - Upper Left
			vertices[index].position = D3DXVECTOR3(m_clouds[index1].x, m_clouds[index1].y, m_clouds[index1].z);
			vertices[index].texture = D3DXVECTOR2(m_clouds[index1].tu, m_clouds[index1].tv);
			indices[index] = index;
			index++;

			// Triangle 1 - Upper Right
			vertices[index].position = D3DXVECTOR3(m_clouds[index2].x, m_clouds[index2].y, m_clouds[index2].z);
			vertices[index].texture = D3DXVECTOR2(m_clouds[index2].tu, m_clouds[index2].tv);
			indices[index] = index;
			index++;

			// Triangle 1 - Bottom Left
			vertices[index].position = D3DXVECTOR3(m_clouds[index3].x, m_clouds[index3].y, m_clouds[index3].z);
			vertices[index].texture = D3DXVECTOR2(m_clouds[index3].tu, m_clouds[index3].tv);
			indices[index] = index;
			index++;

			// Triangle 2 - Bottom Left
			vertices[index].position = D3DXVECTOR3(m_clouds[index3].x, m_clouds[index3].y, m_clouds[index3].z);
			vertices[index].texture = D3DXVECTOR2(m_clouds[index3].tu, m_clouds[index3].tv);
			indices[index] = index;
			index++;

			// Triangle 2 - Upper Right
			vertices[index].position = D3DXVECTOR3(m_clouds[index2].x, m_clouds[index2].y, m_clouds[index2].z);
			vertices[index].texture = D3DXVECTOR2(m_clouds[index2].tu, m_clouds[index2].tv);
			indices[index] = index;
			index++;

			// Triangle 2 - Bottom Right
			vertices[index].position = D3DXVECTOR3(m_clouds[index4].x, m_clouds[index4].y, m_clouds[index4].z);
			vertices[index].texture = D3DXVECTOR2(m_clouds[index4].tu, m_clouds[index4].tv);
			indices[index] = index;
			index++;
		}
	}

	// Set up the description of the vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now finally create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void Clouds::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void Clouds::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


bool Clouds::LoadTextures(ID3D11Device* device, WCHAR* cloudTextureFilename1, WCHAR* cloudTextureFilename2, WCHAR* perturbTextureFilename)
{

	bool result;


	// Create the first cloud texture object.
	m_CloudTexture1 = new Texture;
	if(!m_CloudTexture1)
	{
		return false;
	}

	// Initialize the first cloud texture object.
	result = m_CloudTexture1->Initialize(device, cloudTextureFilename1);
	if(!result)
	{
		return false;
	}

	// Create the second cloud texture object.
	m_CloudTexture2 = new Texture;
	if(!m_CloudTexture2)
	{
		return false;
	}

	// Initialize the second cloud texture object.
	result = m_CloudTexture2->Initialize(device, cloudTextureFilename2);
	if(!result)
	{
		return false;
	}

	// Create the perturb texture object.
	m_PerturbTexture = new Texture;
	if(!m_PerturbTexture)
	{
		return false;
	}

	// Initialize the perturb texture object.
	result = m_PerturbTexture->Initialize(device, perturbTextureFilename);
	if(!result)
	{
		return false;
	}

	return true;
}


void Clouds::ReleaseTextures()
{
	// Release the texture objects.
	if(m_PerturbTexture)
	{
		m_PerturbTexture->Shutdown();
		delete m_PerturbTexture;
		m_PerturbTexture = 0;
	}

	if(m_CloudTexture2)
	{
		m_CloudTexture2->Shutdown();
		delete m_CloudTexture2;
		m_CloudTexture2 = 0;
	}

	if(m_CloudTexture1)
	{
		m_CloudTexture1->Shutdown();
		delete m_CloudTexture1;
		m_CloudTexture1 = 0;
	}

	return;
}