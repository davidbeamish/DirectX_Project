////////////////////////////////////////////////////////////////////////////////
// Filename: particlegenerator.cpp
// Code Adapted from tutorial http://www.rastertek.com/dx11tut39.html
////////////////////////////////////////////////////////////////////////////////
#include "particlegenerator.h"
#include "texture.h"
#include <algorithm>

ParticleGenerator::ParticleGenerator()
{
	m_Texture = 0;
	m_particleList = 0;
	m_vertices = 0;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_positionDeviation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_positionRadius = 0.0f;
	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_velocityDeviation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_acceleration = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	m_colorVelocity = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	m_colorAcceleration = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_maxSize = D3DXVECTOR2(0.0f, 0.0f);
	m_sizeVelocity = D3DXVECTOR2(0.0f, 0.0f);
	m_sizeAcceleration = D3DXVECTOR2(0.0f, 0.0f);	
	m_particlesPerSecond = 0.0f;
	m_maxParticleCount = 0;
	m_lifeTime = 0.0f;
	m_particleVector = NULL;

	m_emissionState = true;
}


ParticleGenerator::ParticleGenerator(const ParticleGenerator& other)
{
}


ParticleGenerator::~ParticleGenerator()
{
}


bool ParticleGenerator::Initialize(ID3D11Device* device, D3DXVECTOR3 position, D3DXVECTOR3 positionDeviation, float positionRadius,  D3DXVECTOR3 velocity, D3DXVECTOR3 velocityDeviation, D3DXVECTOR3 acceleration, D3DXVECTOR4 color, D3DXVECTOR4 colorVelocity, D3DXVECTOR4 colorAcceleration, D3DXVECTOR2 size, D3DXVECTOR2 maxSize, D3DXVECTOR2 sizeVelocity, D3DXVECTOR2 sizeAcceleration, float particlesPerSecond, int maxParticleCount, float lifeTime) 
{
	bool result;


	//// Load the texture that is used for the particles.
	//result = LoadTexture(device, textureFilename);
	//if(!result)
	//{
	//	return false;
	//}
	// Set initial position and random deviation of the position of the particles.
	m_position =  position;
	m_positionDeviation = positionDeviation;
	m_positionRadius = positionRadius;

	// Set the velocity, speed, speed variation and acceleration of particles.
	m_velocity = velocity;
	m_velocityDeviation = velocityDeviation;
	m_acceleration = acceleration;

	// Set the colour of the particles.
	m_color = color;
	m_colorVelocity = colorVelocity;
	m_colorAcceleration = colorAcceleration;

	// Set the physical size, max size, size scaling velocity and acceleration of the particles.
	m_size = size;
	m_maxSize = maxSize;
	m_sizeVelocity = sizeVelocity;
	m_sizeAcceleration = sizeAcceleration;
	
	// Set the number of particles to emit per second and the max number of particles.
	m_particlesPerSecond = particlesPerSecond;
	m_maxParticleCount = maxParticleCount;

	//Set the maximum life time of particles.
	m_lifeTime = lifeTime;

	// Initialize the particle system.
	result = InitializeParticleGenerator();
	if(!result)
	{
		return false;
	}

	// Create the buffers that will be used to render the particles with.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	return true;
}


void ParticleGenerator::Shutdown()
{
	// Release the buffers.
	ShutdownBuffers();

	// Release the particle system.
	ShutdownParticleGenerator();

	// Release the texture used for the particles.
	ReleaseTexture();

	return;
}


bool ParticleGenerator::Frame(float frameTime, ID3D11DeviceContext* deviceContext)
{
	bool result;

	static float time = 0.0f;

	time += (frameTime * 0.016666f);

	// Release old particles.
	KillParticles(time);

	if (m_emissionState == true)
	{
		// Emit new particles.
		EmitParticles(time);
	}	
	// Update the position of the particles.
	UpdateParticles(time);

	// Update the dynamic vertex buffer with the new position of each particle.
	result = UpdateBuffers(deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}


void ParticleGenerator::EmitParticles(float time)
{
	bool emitParticle, found;
	float red, green, blue, theta, rndNum, radius;
	int index, i, j;

	static float emitTime = 0.0f;

	// Increment the frame time.
	m_accumulatedTime += 0.016666f;

	// Set emit particle to false for now.
	emitParticle = false;
	
	// Check if it is time to emit a new particle or not.
	if(m_accumulatedTime > (1.0f / m_particlesPerSecond))
	{
		m_accumulatedTime = 0.0f;
		emitParticle = true;
	}

	// If there are particles to emit then emit one per frame.
	//if((emitParticle == true) && (m_currentParticleCount < (m_maxParticleCount - 1)))
	while((emitParticle == true) && (m_currentParticleCount < (m_maxParticleCount - 1)))
	{
		m_currentParticleCount++;

		// Now generate the randomized particle properties.
		m_position.x += (((float)rand()-(float)rand())/RAND_MAX) * m_positionDeviation.x;
		m_position.y += (((float)rand()-(float)rand())/RAND_MAX) * m_positionDeviation.y;
		m_position.z += (((float)rand()-(float)rand())/RAND_MAX) * m_positionDeviation.z;

		m_velocity.x += (((float)rand()-(float)rand())/RAND_MAX) * m_velocityDeviation.x;
		m_velocity.y += (((float)rand()-(float)rand())/RAND_MAX) * m_velocityDeviation.y;
		m_velocity.z += (((float)rand()-(float)rand())/RAND_MAX) * m_velocityDeviation.z;

		red   = (((float)rand()-(float)rand())/RAND_MAX) + 0.5f;
		green = (((float)rand()-(float)rand())/RAND_MAX) + 0.5f;
		blue  = (((float)rand()-(float)rand())/RAND_MAX) + 0.5f;

		// Now since the particles need to be rendered from back to front for blending we have to sort the particle array.
		// We will sort using Z depth so we need to find where in the list the particle should be inserted.
		index = 0;
		found = false;
		while(!found)
		{
			if((m_particleList[index].active == false) || (m_particleList[index].position.z < m_position.z))
			{
				found = true;
			}
			else
			{
				index++;
			}
		}

		// Now that we know the location to insert into we need to copy the array over by one position from the index to make room for the new particle.
		i = m_currentParticleCount;
		j = i - 1;

		while(i != index)
		{
			m_particleList[i].position			= m_particleList[j].position;
			m_particleList[i].velocity			= m_particleList[j].velocity;
			m_particleList[i].acceleration		= m_particleList[j].acceleration;
			m_particleList[i].color				= m_particleList[j].color;
			m_particleList[i].colorVelocity		= m_particleList[j].colorVelocity;
			m_particleList[i].colorAcceleration	= m_particleList[j].colorAcceleration;
			m_particleList[i].lifeTime			= m_particleList[j].lifeTime;
			m_particleList[i].size				= m_particleList[j].size;
			m_particleList[i].sizeVelocity		= m_particleList[j].sizeVelocity;
			m_particleList[i].sizeAcceleration	= m_particleList[j].sizeAcceleration;
			m_particleList[i].active			= m_particleList[j].active;
			i--;
			j--;
		}

		// Generate random angle for placing particle using polar coords.
		rndNum = float(rand() % m_maxParticleCount);
		theta = float((2.0f * D3DX_PI * (rand() % m_maxParticleCount)) / m_maxParticleCount);
		radius = float(rand() % (int(m_positionRadius * 10.0f) + 1)) / 10.0f;

		// Now insert it into the particle array in the correct depth order with initial values.
		m_particleList[index].position.x		= m_position.x + radius * sin(theta);
		m_particleList[index].position.y		= m_position.y + radius * cos(theta);
		m_particleList[index].position.z		= m_position.z;
		m_particleList[index].velocity			= m_velocity;
		m_particleList[index].acceleration		= m_acceleration;
		m_particleList[index].color				= m_color;
		m_particleList[index].colorVelocity		= m_colorVelocity;
		m_particleList[index].colorAcceleration	= m_colorAcceleration;
		m_particleList[index].lifeTime			= m_lifeTime;
		m_particleList[index].size				= m_size;
		m_particleList[index].sizeVelocity		= m_sizeVelocity;
		m_particleList[index].sizeAcceleration  = m_sizeAcceleration;
		m_particleList[index].active			= true;
	}

	return;
}


void ParticleGenerator::UpdateParticles(float time)
{
	int i;


	// Each frame we update all the particles by making them move downwards using their position, speed, and the frame time.
	for(i=0; i<m_currentParticleCount; i++)
	{
		m_particleList[i].velocity.x += m_particleList[i].acceleration.x *  0.016666f;
		m_particleList[i].velocity.y += m_particleList[i].acceleration.y *  0.016666f;
		m_particleList[i].velocity.z += m_particleList[i].acceleration.z *  0.016666f;

		m_particleList[i].position.x += m_particleList[i].velocity.x * 0.016666f;
		m_particleList[i].position.y += m_particleList[i].velocity.y * 0.016666f;
		m_particleList[i].position.z += m_particleList[i].velocity.z * 0.016666f;

		m_particleList[i].lifeTime -= 0.016666f;

		if (m_particleList[i].size.x < m_maxSize.x )
		{
			m_particleList[i].sizeVelocity.x += m_particleList[i].acceleration.x * 0.016666f;
			m_particleList[i].size.x += m_particleList[i].sizeVelocity.x * 0.016666f;
		}
		if (m_particleList[i].size.y < m_maxSize.y )
		{
			m_particleList[i].sizeVelocity.y += m_particleList[i].acceleration.y * 0.016666f;
			m_particleList[i].size.y += m_particleList[i].sizeVelocity.y * 0.016666f;
		}



		if (m_particleList[i].color.w > 0.0f)
		{
			m_particleList[i].colorVelocity += m_particleList[i].colorAcceleration * 0.016666f;
			m_particleList[i].color += m_particleList[i].colorVelocity * 0.016666f;
		}
	}

	return;
}


void ParticleGenerator::KillParticles(float time)
{
	int i, j;

	// Kill all the particles whose life time is up or who are invisible.
	for(i = 0; i < m_maxParticleCount; i++)
	{
		if( (m_particleList[i].active == true) && ( (m_particleList[i].lifeTime < 0.0f) ))
		{
			m_particleList[i].active = false;
			m_currentParticleCount--;

			// Now shift all the live particles back up the array to erase the destroyed particle and keep the array sorted correctly.
			for(j=i; j<m_maxParticleCount-1; j++)
			{
				m_particleList[j].position			= m_particleList[j+1].position;
				m_particleList[j].velocity			= m_particleList[j+1].velocity;
				m_particleList[j].acceleration		= m_particleList[j+1].acceleration;
				m_particleList[i].color				= m_particleList[j+1].color;
				m_particleList[j].colorVelocity		= m_particleList[j+1].colorVelocity;
				m_particleList[j].colorAcceleration	= m_particleList[j+1].colorAcceleration;
				m_particleList[j].lifeTime			= m_particleList[j+1].lifeTime;
				m_particleList[j].size				= m_particleList[j+1].size;
				m_particleList[j].sizeVelocity		= m_particleList[j+1].sizeVelocity;
				m_particleList[j].sizeAcceleration	= m_particleList[j+1].sizeAcceleration;
				m_particleList[j].active			= m_particleList[j+1].active;

			}
		}
	}

	return;
}


bool ParticleGenerator::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
	int index, i;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;


	// Initialize vertex array to zeros at first.
	memset(m_vertices, 0, (sizeof(VertexType) * m_vertexCount));

	// Now build the vertex array from the particle list array.  Each particle is a quad made out of two triangles.
	index = 0;

	for( i= 0; i < m_currentParticleCount; i++)
	{
		// Bottom left.
		m_vertices[index].position = D3DXVECTOR3(m_particleList[i].position.x - m_particleList[i].size.x, m_particleList[i].position.y - m_particleList[i].size.y, m_particleList[i].position.z);
		m_vertices[index].texture = D3DXVECTOR2(0.0f, 1.0f);
		m_vertices[index].color = D3DXVECTOR4(m_particleList[i].color.x, m_particleList[i].color.y, m_particleList[i].color.z, m_particleList[i].color.w);
		index++;

		// Top left.
		m_vertices[index].position = D3DXVECTOR3(m_particleList[i].position.x - m_particleList[i].size.x, m_particleList[i].position.y + m_particleList[i].size.y , m_particleList[i].position.z);
		m_vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
		m_vertices[index].color = D3DXVECTOR4(m_particleList[i].color.x, m_particleList[i].color.y, m_particleList[i].color.z, m_particleList[i].color.w);
		index++;

		// Bottom right.
		m_vertices[index].position = D3DXVECTOR3(m_particleList[i].position.x + m_particleList[i].size.x, m_particleList[i].position.y - m_particleList[i].size.y, m_particleList[i].position.z);
		m_vertices[index].texture = D3DXVECTOR2(1.0f, 1.0f);
		m_vertices[index].color = D3DXVECTOR4(m_particleList[i].color.x, m_particleList[i].color.y, m_particleList[i].color.z, m_particleList[i].color.w);
		index++;

		// Bottom right.
		m_vertices[index].position = D3DXVECTOR3(m_particleList[i].position.x + m_particleList[i].size.x, m_particleList[i].position.y - m_particleList[i].size.y, m_particleList[i].position.z);
		m_vertices[index].texture = D3DXVECTOR2(1.0f, 1.0f);
		m_vertices[index].color = D3DXVECTOR4(m_particleList[i].color.x, m_particleList[i].color.y, m_particleList[i].color.z, m_particleList[i].color.w);
		index++;

		// Top left.
		m_vertices[index].position = D3DXVECTOR3(m_particleList[i].position.x - m_particleList[i].size.x, m_particleList[i].position.y + m_particleList[i].size.y, m_particleList[i].position.z);
		m_vertices[index].texture = D3DXVECTOR2(0.0f, 0.0f);
		m_vertices[index].color = D3DXVECTOR4(m_particleList[i].color.x, m_particleList[i].color.y, m_particleList[i].color.z, m_particleList[i].color.w);
		index++;

		// Top right.
		m_vertices[index].position = D3DXVECTOR3(m_particleList[i].position.x + m_particleList[i].size.x, m_particleList[i].position.y + m_particleList[i].size.y, m_particleList[i].position.z);
		m_vertices[index].texture = D3DXVECTOR2(1.0f, 0.0f);
		m_vertices[index].color = D3DXVECTOR4(m_particleList[i].color.x, m_particleList[i].color.y, m_particleList[i].color.z, m_particleList[i].color.w);
		index++;
	}
	
	// Lock the vertex buffer.
	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (VertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)m_vertices, (sizeof(VertexType) * m_vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(m_vertexBuffer, 0);

	return true;
}



void ParticleGenerator::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphicsmanager pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


bool ParticleGenerator::InitializeParticleGenerator()
{
	int i;

	// Create the particle list.
	m_particleList = new ParticleType[m_maxParticleCount];
	if(!m_particleList)
	{
		return false;
	}

	// Initialize the particle list.
	for(i=0; i<m_maxParticleCount; i++)
	{
		m_particleList[i].active = false;
	}

	// Initialize the current particle count to zero since none are emitted yet.
	m_currentParticleCount = 0;

	// Clear the initial accumulated time for the particle per second emission rate.
	m_accumulatedTime = 0.0f;

	return true;
}


void ParticleGenerator::ShutdownParticleGenerator()
{
	// Release the particle list.
	if(m_particleList)
	{
		delete [] m_particleList;
		m_particleList = 0;
	}

	return;
}


void ParticleGenerator::ReleaseTexture()
{
	// Release the texture object.
	if(m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}


bool ParticleGenerator::InitializeBuffers(ID3D11Device* device)
{
	unsigned long* indices;
	int i;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;


	// Set the maximum number of vertices in the vertex array.
	m_vertexCount = m_maxParticleCount * 6;

	// Set the maximum number of indices in the index array.
	m_indexCount = m_vertexCount;

	// Create the vertex array for the particles that will be rendered.
	m_vertices = new VertexType[m_vertexCount];
	if(!m_vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(m_vertices, 0, (sizeof(VertexType) * m_vertexCount));

	// Initialize the index array.
	for(i=0; i<m_indexCount; i++)
	{
		indices[i] = i;
	}

	// Set up the description of the dynamic vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = m_vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now finally create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
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

	// Release the index array since it is no longer needed.
	delete [] indices;
	indices = 0;

	return true;
}


void ParticleGenerator::ShutdownBuffers()
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


void ParticleGenerator::RenderBuffers(ID3D11DeviceContext* deviceContext)
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

    // Set the type of primitive that should be rendered from this vertex buffer.
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


ID3D11ShaderResourceView* ParticleGenerator::GetTexture()
{
	return m_Texture->GetTexture();
}


int ParticleGenerator::GetIndexCount()
{
	return m_indexCount;
}


bool ParticleGenerator::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new Texture;
	if(!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if(!result)
	{
		return false;
	}

	return true;
}

void ParticleGenerator::SetInitializationVariables(D3DXVECTOR3 position, D3DXVECTOR3 positionDeviation, float positionRadius, D3DXVECTOR3 velocity, D3DXVECTOR3 velocityDeviation, D3DXVECTOR3 acceleration, D3DXVECTOR4 color, D3DXVECTOR4 colorVelocity, D3DXVECTOR4 colorAcceleration, D3DXVECTOR2 size, D3DXVECTOR2 maxSize, D3DXVECTOR2 sizeVelocity, D3DXVECTOR2 sizeAcceleration, float particlesPerSecond, int maxParticleCount, float lifeTime)
{
	// Set initial position and random deviation of the position of the particles.
	m_position =  position;
	m_positionDeviation = positionDeviation;
	m_positionRadius = positionRadius;

	// Set the velocity, speed, speed variation and acceleration of particles.
	m_velocity = velocity;
	m_velocityDeviation = velocityDeviation;
	m_acceleration = acceleration;

	// Set the colour of the particles.
	m_color = color;
	m_colorVelocity = colorVelocity;
	m_colorAcceleration = colorAcceleration;

	// Set the physical size, max size, size scaling velocity and acceleration of the particles.
	m_size = size;
	m_maxSize = maxSize;
	m_sizeVelocity = sizeVelocity;
	m_sizeAcceleration = sizeAcceleration;
	
	// Set the number of particles to emit per second and the max number of particles.
	m_particlesPerSecond = particlesPerSecond;
	m_maxParticleCount = maxParticleCount;

	//Set the life time of particles.

	m_lifeTime = lifeTime;
}

int ParticleGenerator::GetCurrentParticleCount() const
{
	return m_currentParticleCount;
}

void ParticleGenerator::SetPosition(D3DXVECTOR3 position)
{
	m_position = position;
}

D3DXVECTOR3 ParticleGenerator::GetPosition() const
{
	return m_position;
}

void ParticleGenerator::SetVelocity(D3DXVECTOR3 velocity)
{
	m_velocity = velocity;
}

void ParticleGenerator::SetAcceleration(D3DXVECTOR3 acceleration)
{
	m_acceleration = acceleration;
}

void ParticleGenerator::SetColor(D3DXVECTOR4 color)
{
	m_color = color;
}

void ParticleGenerator::SetColorVelocity(D3DXVECTOR4 colorVelocity)
{
	m_colorVelocity = colorVelocity;
}

void ParticleGenerator::SetColorAcceleration(D3DXVECTOR4 colorAcceleration)
{
	m_colorAcceleration = colorAcceleration;
}


void ParticleGenerator::SetLifeTime(float lifeTime)
{
	m_lifeTime = lifeTime;
}

void ParticleGenerator::SetSize(D3DXVECTOR2 size)
{
	m_size = size;
}

void ParticleGenerator::SetMaxSize(D3DXVECTOR2 maxSize)
{
	m_maxSize = maxSize;
}


void ParticleGenerator::SetSizeVelocity(D3DXVECTOR2 sizeVelocity)
{
	m_sizeVelocity = sizeVelocity;
}

void ParticleGenerator::SetSizeAcceleration(D3DXVECTOR2 sizeAcceleration)
{
	m_sizeAcceleration = sizeAcceleration;
}


void ParticleGenerator::SetMaxParticleCount(int maxParticleCount)
{
	m_maxParticleCount = maxParticleCount;
}


void ParticleGenerator::SetParticlesPerSecond(float particlesPerSecond)
{
	m_particlesPerSecond = particlesPerSecond;
}

void ParticleGenerator::SetEmissionState(const bool emissionState)
{
	m_emissionState = emissionState;
}

bool ParticleGenerator::GetEmissionState() const
{
	return m_emissionState;
}