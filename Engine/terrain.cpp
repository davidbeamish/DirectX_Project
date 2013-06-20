////////////////////////////////////////////////////////////////////////////////
// Filename: terrain.cpp
// Code Adapted from a variety of terrain tutorials on http://www.rastertek.com
// Terrain generation algorithms based on:
//Shankel. J. Fractal Terrain Generation - Fault Formation. 2000. Game Programming Gems. Charles River Media. pp. 499-503
//Shankel. J. Fractal Terrain Generation - Midpoint Displacement. 2000. Game Programming Gems.  Charles River Media. pp. 503-507.
//Shankel. J. Fractal Terrain Generation - Particle Deposition. 2000. Game Programming Gems.  Charles River Media. pp. 507-511.
////////////////////////////////////////////////////////////////////////////////
#include "terrain.h"
#include "texture.h"
#include <ctime>
#include <cmath>

Terrain::Terrain()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_heightMap = 0;
	m_GrassTexture = 0;
	m_SlopeTexture = 0;
	m_RockTexture = 0;
	m_DetailTexture = 0;
	m_ColorTexture = 0;
	m_NormalTexture = 0;
	m_meanTerrainHeight = 0;
}


Terrain::Terrain(const Terrain& other)
{
}


Terrain::~Terrain()
{
}


bool Terrain::Initialize(ID3D11Device* device, char* heightMapFilename, WCHAR* grassTextureFilename, WCHAR* slopeTextureFilename, WCHAR* rockTextureFilename, char* colorMapFilename, WCHAR* detailMapFilename, WCHAR* normalTextureFilename)
{
	bool result;

	// Load in the height map for the terrain.
	result = LoadHeightMap(heightMapFilename);
	if(!result)
	{
		return false;
	}

	// Normalize the height of the height map.
	NormalizeHeightMap();

	// Calculate the normals for the terrain data.
	result = CalculateNormals();
	if(!result)
	{
		return false;
	}

	// Calculate the texture coordinates.
	CalculateTextureCoordinates();

	// Load the textures.
	result = LoadTextures(device, grassTextureFilename, slopeTextureFilename, rockTextureFilename, detailMapFilename, normalTextureFilename);
	if(!result)
	{
		return false;
	}

	// Load in the color map for the terrain.
	result = LoadColorMap(colorMapFilename);
	if(!result)
	{
		return false;
	}

	// Initialize the vertex and index buffer that hold the geometry for the terrain.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	return true;
}


bool Terrain::InitializeTerrain(ID3D11Device* device, int terrainWidth, int terrainHeight, WCHAR* grassTextureFilename, WCHAR* slopeTextureFilename, 
			      WCHAR* rockTextureFilename, char* colorMapFilename, WCHAR* detailMapFilename, WCHAR* normalTextureFilename)
{
	int index;
	float height = 0.0;
	bool result;
	// Save the dimensions of the terrain.
	m_terrainWidth = terrainWidth;
	m_terrainHeight = terrainHeight;
	// srand(time(NULL));
	// Create the structure to hold the terrain data.
	m_heightMap = new HeightMapType[m_terrainWidth * m_terrainHeight];
	if(!m_heightMap)
	{
		return false;
	}

	// Initialise the data in the height map (flat).
	for(int j=0; j<m_terrainHeight; j++)
	{
		for(int i=0; i<m_terrainWidth; i++)
		{			
			index = (m_terrainHeight * j) + i;

			m_heightMap[index].x = (float)i;
			m_heightMap[index].y = (float)height;
			m_heightMap[index].z = (float)j;
		}
	}
	srand(time(NULL));
	
	DoParticleDeposition(3, 10, 50000, 80000, 1.0f, 0.6f);
	DoMidpointDisplacement(m_terrainHeight, GenerateRndNum(0.6f, 2.0f), 0.5f);
	DoFaultFormation(m_terrainHeight, 100, -2.0f, 2.0f, 0.8f);
	//even though we are generating a flat terrain, we still need to normalise it. 
	// Calculate the normals for the terrain data.
	result = CalculateNormals();
	if(!result)
	{
		return false;
	}

	// Calculate the texture coordinates.
	CalculateTextureCoordinates();

	// Load the textures.
	result = LoadTextures(device, grassTextureFilename, slopeTextureFilename, rockTextureFilename, detailMapFilename, normalTextureFilename);
	if(!result)
	{
		return false;
	}

	// Load in the color map for the terrain.
	result = LoadColorMap(colorMapFilename);
	if(!result)
	{
		return false;
	}

	// Initialize the vertex and index buffer that hold the geometry for the terrain.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	CalculateMeanTerrainHeight();
	return true;
}


void Terrain::Shutdown()
{
	// Release the texture.
	ReleaseTexture();

	// Release the vertex and index buffer.
	ShutdownBuffers();

	// Release the height map data.
	ShutdownHeightMap();

	return;
}


bool Terrain::GenerateHeightMap(ID3D11Device* device, bool keyDown)
{

	bool result;
	//the toggle is just a bool that I use to make sure this is only called ONCE when you press a key
	//until you release the key and start again. We dont want to be generating the terrain 500
	//times per second. 
	if(keyDown&&(!m_terrainGeneratedToggle))
	{
		//srand(time(NULL));
		m_IterationCount++;
		DoFaultFormation(m_terrainHeight, 1000, -0.2f, 0.2f, 0.5f);
		DoMidpointDisplacement(m_terrainHeight, GenerateRndNum(0.6f,2.0f), 0.5f);
		//GenerateSphere(m_terrainHeight);
		//ErodeHeightMap(1.0f);

		//GenerateMultiFractal(m_terrainHeight);

		result = CalculateNormals();
		if(!result)
		{
			return false;
		}

		// Initialize the vertex and index buffer that hold the geometry for the terrain.
		result = InitializeBuffers(device);
		if(!result)
		{
			return false;
		}

		m_terrainGeneratedToggle = true;
	}
	else
	{
		m_terrainGeneratedToggle = false;
	}



	return true;
}


bool Terrain::FlattenTerrain(ID3D11Device* device, bool keyDown)
{
	float height = 0.0f;
	int index;
	bool result;

	if (keyDown&&(!m_terrainFlattenedToggle))
	{
		// Flatten the height.
		for(int j=0; j<m_terrainHeight; j++)
		{
			for(int i=0; i<m_terrainWidth; i++)
			{			
				index = (m_terrainHeight * j) + i;

				m_heightMap[index].x = (float)i;
				m_heightMap[index].y = (float)height;
				m_heightMap[index].z = (float)j;

			}
		}

		result = CalculateNormals();
		if(!result)
		{
			return false;
		}

		// Initialize the vertex and index buffer that hold the geometry for the terrain.
		result = InitializeBuffers(device);
		if(!result)
		{
			return false;
		}

		m_terrainFlattenedToggle = true;
	}
	else
	{
		m_terrainFlattenedToggle = false;
	}

	return true;
}


void Terrain::DoParticleDeposition(int jumps, int particleOffset, int minParticlesPerJump, int maxParticlesPerJump, float caldera, float smoothness)
{
	int xPos, yPos, m, px, py, sx, sy, numParticles, tx, ty, done;
	int dx[] = {0 ,1 ,0 , m_terrainHeight-1 , 1 ,1 , m_terrainHeight-1, m_terrainHeight-1};
	int dy[] = {1, 0, m_terrainHeight-1, 0, m_terrainHeight-1, 1 , m_terrainHeight-1, 1};


	for (int p = 0; p < jumps; p++)
	{
		//Pick a random spot.
		xPos = rand() % m_terrainHeight;
		yPos = rand() % m_terrainHeight;

		//Determine the number of particles to drop.
		numParticles = int(GenerateRndNum( float(minParticlesPerJump), float(maxParticlesPerJump) ) );

		for (int i = 0; i < numParticles; i++)
		{
			//Determine whether to move the drop point and move it in a random direction.
			if (particleOffset != 0 && (i % particleOffset) == 0)
			{
				m = rand() % 8;
				xPos = (xPos + dx[m] + m_terrainHeight) % m_terrainHeight;
				yPos = (yPos + dy[m] + m_terrainHeight) % m_terrainHeight;
			}

			//Drop the particle.
			m_heightMap[xPos + yPos * m_terrainHeight].y += GenerateRndNum(-1.0f, 2.0f);

			// Agitate the particle until it settles.

			sx = xPos;
			sy = yPos;
			done = 0;

			while (done == 0)
			{
				done = 1;

				//Check a random neighbour of the particle.
				m = rand();
				for (int j = 0; j < 8; j++)
				{
					tx = (sx + dx[(j + m) % 8]) % m_terrainHeight;
					ty = (sy + dy[(j + m) % 8]) % m_terrainHeight;

					// Compare height of the particle with neightbour and move to it if possible.
					if ( m_heightMap[tx + ty * m_terrainHeight].y + 1.0f < m_heightMap[sx + sy].y)
					{
						m_heightMap[tx + ty * m_terrainHeight].y += GenerateRndNum(0.0f, 0.2f);
						m_heightMap[sx + sy  *m_terrainHeight].y -= GenerateRndNum(0.0f, 0.2f);
						sx = tx;
						sy = ty;
						done = 0;
						break;
					}
				}
			}
		}	
	}
	NormalizeTerrain(m_terrainHeight, smoothness);
}



void Terrain::DoMidpointDisplacement(int mapSize, float roughness, float smoothness)
{
	int ni, nj, mi, mj, pmi, pmj;
	int rectSize = mapSize;
	float deltaHeight = float(rectSize/2);
	float r = float( pow(2,(-1*roughness)) );

	m_heightMap[0].x = 0;
	m_heightMap[0].y = 0;
	m_heightMap[0].z = 0;

	while(rectSize > 0)
	{
		// Diamond Step.
		for (int i=0; i<mapSize; i+=rectSize)
		{
			for (int j=0; j<mapSize; j+=rectSize)
			{
				ni = (i + rectSize) % mapSize;
				nj = (j + rectSize) % mapSize;

				mi = (i + rectSize ) / 2;
				mj = (j + rectSize) / 2;

				//m_heightMap[mi+mj*mapSize].x = float( radius * sin ( theta ) * cos ( phi ) );
				m_heightMap[mi+mj*mapSize].y = (m_heightMap[i+j*mapSize].y + m_heightMap[ni+j*mapSize].y+m_heightMap[i+nj*mapSize].y + m_heightMap[ni+nj*mapSize].y)/4+GenerateRndNum(-deltaHeight/2, deltaHeight/2);
				//m_heightMap[mi+mj*mapSize].z = float( radius * sin ( theta ) * sin ( phi ) );

				//m_heightMap[mi+mj*mapSize].x = (float)i;
				m_heightMap[mi+mj*mapSize].y = (m_heightMap[i+j*mapSize].y + m_heightMap[ni+j*mapSize].y+m_heightMap[i+nj*mapSize].y + m_heightMap[ni+nj*mapSize].y)/4+GenerateRndNum(-deltaHeight/2, deltaHeight/2);
				//m_heightMap[mi+mj*mapSize].z = (float)j;
			}
		}

		// Square Step
		for (int i = 0; i < mapSize; i += rectSize)
		{
			for(int j = 0; j < mapSize; j += rectSize)
			{
				ni = (i + rectSize) % mapSize;
				nj = (j + rectSize) % mapSize;

				mi = (i + rectSize / 2);
				mj = (j + rectSize / 2);

				pmi = (i - rectSize / 2 + mapSize) % mapSize;
				pmj = (j - rectSize / 2 + mapSize) % mapSize;

				// Calcuate the square value for the top side of the rectangle.
				//m_heightMap[mi+j*mapSize].x = (float)i;
				m_heightMap[mi+j*mapSize].y = (m_heightMap[i+j*mapSize].y + m_heightMap[ni+j*mapSize].y + m_heightMap[mi+pmj*mapSize].y + m_heightMap[mi+mj*mapSize].y)/4 + GenerateRndNum(-deltaHeight / 2, deltaHeight / 2);
				//m_heightMap[mi+j*mapSize].z = (float)j;

				// Calculate the square value for the left side of the rectangle.
				//m_heightMap[i+mj*mapSize].x = (float)i;
				m_heightMap[i+mj*mapSize].y = (m_heightMap[i+j*mapSize].y + m_heightMap[i+nj*mapSize].y + m_heightMap[pmi+mj*mapSize].y + m_heightMap[mi+mj*mapSize].y)/4 + GenerateRndNum(-deltaHeight / 2, deltaHeight / 2);
				//m_heightMap[i+mj*mapSize].z = (float)j;
			}
		}
		rectSize /= 2;
		deltaHeight*=r;
	}
	NormalizeTerrain(mapSize, smoothness);
}


void Terrain::DoFaultFormation(int mapSize, int iterations, float minDelta, float maxDelta, float smoothness)
{
	int firstXPos, firstYPos, secondXPos, secondYPos, firstDirectionX, firstDirectionY, secondDirectionX, secondDirectionY;
	float deltaHeight;

	for (int i = 0; i < iterations; i++)
	{
		// Perform linear interpolation from maxDelta to minDelta by calculating the difference for this iteration.
		deltaHeight = maxDelta - ( ( maxDelta - minDelta )  *i )/ float( iterations );

		//Choose a random point on the height map.
		firstXPos = rand() % mapSize;
		firstYPos = rand() % mapSize;

		// Choose a second random point not equal to the first.
		do
		{
			secondXPos = rand() % mapSize;
			secondYPos = rand() % mapSize;
		} while (secondXPos == firstXPos && secondYPos == firstYPos);

		// Calculate the direction of the line between both points
		firstDirectionX = secondXPos - firstXPos;
		firstDirectionY = secondYPos - firstYPos;

		//Iterate through each point on one side of the line.  
		for (secondXPos = 0; secondXPos < mapSize; secondXPos++)
		{
			for (secondYPos = 0; secondYPos < mapSize; secondYPos++)
			{
				//Calculate the direction between the first random point and the new point
				secondDirectionX = secondXPos - firstXPos;
				secondDirectionY = secondYPos - firstYPos;

				//Check if cross product of both points is positive and if so, increase height of point.
				if (secondDirectionX * firstDirectionY - firstDirectionX * secondDirectionY > 0)
				{
					m_heightMap[secondXPos + mapSize * secondYPos].y += deltaHeight;
				}
			}
		}
	}
	NormalizeTerrain(mapSize, smoothness);
}


void Terrain::NormalizeTerrain(int mapSize, float smoothness)
{
	float min, max;
	float deltaHeight;

	min = m_heightMap[0].y;
	max = m_heightMap[0].y;

	for (int i = 1; i < mapSize * mapSize ;i++)
	{
		if(m_heightMap[i].y > max) 
		{ 
			max = m_heightMap[i].y; 
		} 
		else if(m_heightMap[i].y < min) 
		{ 
			min = m_heightMap[i].y;
		}
	}

	if(max <= min) 
	{ 
		return; 
	} 
	deltaHeight = max - min;

	for (int i = 0; i < mapSize; i++) 
	{
		m_heightMap[i].y = (m_heightMap[i].y - min) / deltaHeight;
	}

	for (int i = 0; i < 4; i++)
	{
		SmoothTerrain(smoothness);
	}
}


bool Terrain::SmoothTerrain(float smoothness)
{
	int index;

	// Left to right smooth pass
	for(int j = 1; j < m_terrainHeight; j++)
	{
		for(int i = 1; i < m_terrainWidth; i++)
		{			
			index = (m_terrainHeight * i) + j;
			m_heightMap[index].y = (((1-smoothness)*m_heightMap[index-1].y) + (smoothness*m_heightMap[index].y));
		}
	}

	// Right to left smooth pass
	for(int j = (m_terrainHeight - 1); j > -1; j--)
	{
		for(int i=(m_terrainWidth-1); i> -1; i--)
		{			
			index = (m_terrainHeight * i) + j;
			m_heightMap[index].y = ((smoothness*m_heightMap[index].y) + ((1-smoothness)*m_heightMap[index+1].y));
		}
	}

	//Bottom to top smooth pass
	for(int i = 0; i < (m_terrainWidth); i++)
	{
		for (int j = m_terrainHeight; j < (m_terrainHeight-1) * (m_terrainHeight-1); j += m_terrainHeight)
		{
			index = j + i;
			m_heightMap[index].y = ( ( (1-smoothness)*m_heightMap[index-m_terrainHeight].y) + (smoothness*m_heightMap[index].y) );

		}
	}

	//Top to bottom smooth pass
	for(int i = (m_terrainWidth-1); i > -1; i--)
	{
		for (int j = (m_terrainHeight-1) * (m_terrainHeight-1); j > -1; j -= m_terrainHeight)
		{
			index = j + i;
			m_heightMap[index].y = ( (smoothness*m_heightMap[index].y) + ((1-smoothness)*m_heightMap[index+m_terrainHeight].y) );

		}
	}

	return true;
}


bool Terrain::SmoothTerrain(ID3D11Device* device, bool keyDown)
{
	bool result;
	int index;
	float smoothness = 0.5f;

	// Horizontal smooth pass
	for(int j=0; j<m_terrainHeight; j++)
		{
			for(int i=0; i<m_terrainWidth; i++)
			{			
				index = (m_terrainHeight * i) + j;
				m_heightMap[index].y = (m_heightMap[index-2].y +m_heightMap[index-1].y + m_heightMap[index].y + m_heightMap[index+1].y +m_heightMap[index+2].y )/5;
				/*m_heightMap[index].y = ((smoothness*m_heightMap[index-1].y) + ((1-smoothness)*m_heightMap[index].y));*/
			}
	}

	//Vertical smooth pass
	for(int i = 0; i < m_terrainWidth; i++)
	{
		for (int j = 0; j < m_terrainHeight * (m_terrainHeight - 1); j += m_terrainHeight)
		{
			float total = 0.0f;
			int count = 0;
			index = i + j;

			for (int k = -2; k < 3; k++)
			{
				int index2 = index + (k*m_terrainHeight);
				if ( m_heightMap[index2].y > -200 )
				{
					total += m_heightMap[index2].y;
					count++;
				}
			}
			if ( count != 0 )
			{
				m_heightMap[index].y = total / count;
			}
		}
	}
	result = CalculateNormals();
	if(!result)
	{
		return false;
	}

	// Initialize the vertex and index buffer that hold the geometry for the terrain.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	m_terrainSmoothedToggle = true;
	//}
	//else
	//{
	//	m_terrainSmoothedToggle = false;
	//}

	return true;
}


float Terrain::GenerateRndNum(float min, float max)
{
	return min+(max-min)*((float)((rand() % 1000 + 1))/1000);
}


void Terrain::CalculateMeanTerrainHeight()
{
	float total = 0.0f;
	int index = 0;
	for (int i = 0; i < m_terrainHeight; i++)
	{
		for (int j = 0; j < m_terrainWidth; j++)
		{
			index = (m_terrainHeight * i) + j;
			total += m_heightMap[index].y;
		}
	}
	m_meanTerrainHeight = total / (m_terrainWidth * m_terrainHeight);
}


void Terrain::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphicsmanager pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


bool Terrain::LoadHeightMap(char* filename)
{
	FILE* filePtr;
	int error;
	unsigned int count;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	int imageSize, i, j, k, index;
	unsigned char* bitmapImage;
	unsigned char height;


	// Open the height map file in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if(error != 0)
	{
		return false;
	}

	// Read in the file header.
	count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	if(count != 1)
	{
		return false;
	}

	// Read in the bitmap info header.
	count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	if(count != 1)
	{
		return false;
	}

	// Save the dimensions of the terrain.
	m_terrainWidth = bitmapInfoHeader.biWidth;
	m_terrainHeight = bitmapInfoHeader.biHeight;

	// Calculate the size of the bitmap image data.
	imageSize = m_terrainWidth * m_terrainHeight * 3;

	// Allocate memory for the bitmap image data.
	bitmapImage = new unsigned char[imageSize];
	if(!bitmapImage)
	{
		return false;
	}

	// Move to the beginning of the bitmap data.
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// Read in the bitmap image data.
	count = fread(bitmapImage, 1, imageSize, filePtr);
	if(count != imageSize)
	{
		return false;
	}

	// Close the file.
	error = fclose(filePtr);
	if(error != 0)
	{
		return false;
	}

	// Create the structure to hold the height map data.
	m_heightMap = new HeightMapType[m_terrainWidth * m_terrainHeight];
	if(!m_heightMap)
	{
		return false;
	}

	// Initialize the position in the image data buffer.
	k=0;

	// Read the image data into the height map.
	for(j=0; j<m_terrainHeight; j++)
	{
		for(i=0; i<m_terrainWidth; i++)
		{
			height = bitmapImage[k];
			
			index = (m_terrainHeight * j) + i;

			m_heightMap[index].x = (float)i;
			m_heightMap[index].y = (float)height;
			m_heightMap[index].z = (float)j;

			k+=3;
		}
	}

	// Release the bitmap image data.
	delete [] bitmapImage;
	bitmapImage = 0;

	return true;
}


void Terrain::NormalizeHeightMap()
{
	int i, j;


	for(j=0; j<m_terrainHeight; j++)
	{
		for(i=0; i<m_terrainWidth; i++)
		{
			m_heightMap[(m_terrainHeight * j) + i].y /= 15.0f;
		}
	}

	return;
}


bool Terrain::CalculateNormals()
{
	int i, j, index1, index2, index3, index, count;
	float vertex1[3], vertex2[3], vertex3[3], vector1[3], vector2[3], sum[3], length;
	VectorType* normals;


	// Create a temporary array to hold the un-normalized normal vectors.
	normals = new VectorType[(m_terrainHeight-1) * (m_terrainWidth-1)];
	if(!normals)
	{
		return false;
	}

	// Go through all the faces in the mesh and calculate their normals.
	for(j=0; j<(m_terrainHeight-1); j++)
	{
		for(i=0; i<(m_terrainWidth-1); i++)
		{
			index1 = (j * m_terrainHeight) + i;
			index2 = (j * m_terrainHeight) + (i+1);
			index3 = ((j+1) * m_terrainHeight) + i;

			// Get three vertices from the face.
			vertex1[0] = m_heightMap[index1].x;
			vertex1[1] = m_heightMap[index1].y;
			vertex1[2] = m_heightMap[index1].z;
		
			vertex2[0] = m_heightMap[index2].x;
			vertex2[1] = m_heightMap[index2].y;
			vertex2[2] = m_heightMap[index2].z;
		
			vertex3[0] = m_heightMap[index3].x;
			vertex3[1] = m_heightMap[index3].y;
			vertex3[2] = m_heightMap[index3].z;

			// Calculate the two vectors for this face.
			vector1[0] = vertex1[0] - vertex3[0];
			vector1[1] = vertex1[1] - vertex3[1];
			vector1[2] = vertex1[2] - vertex3[2];
			vector2[0] = vertex3[0] - vertex2[0];
			vector2[1] = vertex3[1] - vertex2[1];
			vector2[2] = vertex3[2] - vertex2[2];

			index = (j * (m_terrainHeight-1)) + i;

			// Calculate the cross product of those two vectors to get the un-normalized value for this face normal.
			normals[index].x = (vector1[1] * vector2[2]) - (vector1[2] * vector2[1]);
			normals[index].y = (vector1[2] * vector2[0]) - (vector1[0] * vector2[2]);
			normals[index].z = (vector1[0] * vector2[1]) - (vector1[1] * vector2[0]);
		}
	}

	// Now go through all the vertices and take an average of each face normal 	
	// that the vertex touches to get the averaged normal for that vertex.
	for(j=0; j<m_terrainHeight; j++)
	{
		for(i=0; i<m_terrainWidth; i++)
		{
			// Initialize the sum.
			sum[0] = 0.0f;
			sum[1] = 0.0f;
			sum[2] = 0.0f;

			// Initialize the count.
			count = 0;

			// Bottom left face.
			if(((i-1) >= 0) && ((j-1) >= 0))
			{
				index = ((j-1) * (m_terrainHeight-1)) + (i-1);

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}

			// Bottom right face.
			if((i < (m_terrainWidth-1)) && ((j-1) >= 0))
			{
				index = ((j-1) * (m_terrainHeight-1)) + i;

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}

			// Upper left face.
			if(((i-1) >= 0) && (j < (m_terrainHeight-1)))
			{
				index = (j * (m_terrainHeight-1)) + (i-1);

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}

			// Upper right face.
			if((i < (m_terrainWidth-1)) && (j < (m_terrainHeight-1)))
			{
				index = (j * (m_terrainHeight-1)) + i;

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}
			
			// Take the average of the faces touching this vertex.
			sum[0] = (sum[0] / (float)count);
			sum[1] = (sum[1] / (float)count);
			sum[2] = (sum[2] / (float)count);

			// Calculate the length of this normal.
			length = sqrt((sum[0] * sum[0]) + (sum[1] * sum[1]) + (sum[2] * sum[2]));
			
			// Get an index to the vertex location in the height map array.
			index = (j * m_terrainHeight) + i;

			// Normalize the final shared normal for this vertex and store it in the height map array.
			m_heightMap[index].nx = (sum[0] / length);
			m_heightMap[index].ny = (sum[1] / length);
			m_heightMap[index].nz = (sum[2] / length);
		}
	}

	// Release the temporary normals.
	delete [] normals;
	normals = 0;

	return true;
}


void Terrain::ShutdownHeightMap()
{
	if(m_heightMap)
	{
		delete [] m_heightMap;
		m_heightMap = 0;
	}

	return;
}


void Terrain::CalculateTextureCoordinates()
{
	int incrementCount, i, j, tuCount, tvCount;
	float incrementValue, tuCoordinate, tvCoordinate;


	// Calculate how much to increment the texture coordinates by.
	incrementValue = (float)TEXTURE_REPEAT / (float)m_terrainWidth;

	// Calculate how many times to repeat the texture.
	incrementCount = m_terrainWidth / TEXTURE_REPEAT;

	// Initialize the tu and tv coordinate values.
	tuCoordinate = 0.0f;
	tvCoordinate = 1.0f;

	// Initialize the tu and tv coordinate indexes.
	tuCount = 0;
	tvCount = 0;

	// Loop through the entire height map and calculate the tu and tv texture coordinates for each vertex.
	for(j=0; j<m_terrainHeight; j++)
	{
		for(i=0; i<m_terrainWidth; i++)
		{
			// Store the texture coordinate in the height map.
			m_heightMap[(m_terrainHeight * j) + i].tu = tuCoordinate;
			m_heightMap[(m_terrainHeight * j) + i].tv = tvCoordinate;

			// Increment the tu texture coordinate by the increment value and increment the index by one.
			tuCoordinate += incrementValue;
			tuCount++;

			// Check if at the far right end of the texture and if so then start at the beginning again.
			if(tuCount == incrementCount)
			{
				tuCoordinate = 0.0f;
				tuCount = 0;
			}
		}

		// Increment the tv texture coordinate by the increment value and increment the index by one.
		tvCoordinate -= incrementValue;
		tvCount++;

		// Check if at the top of the texture and if so then start at the bottom again.
		if(tvCount == incrementCount)
		{
			tvCoordinate = 1.0f;
			tvCount = 0;
		}
	}

	return;
}


bool Terrain::LoadTextures(ID3D11Device* device, WCHAR* grassTextureFilename, WCHAR* slopeTextureFilename, WCHAR* rockTextureFilename, WCHAR* detailMapFilename, WCHAR* normalTextureFilename)
{
	bool result;


	// Create the grass texture object.
	m_GrassTexture = new Texture;
	if(!m_GrassTexture)
	{
		return false;
	}

	// Initialize the grass texture object.
	result = m_GrassTexture->Initialize(device, grassTextureFilename);
	if(!result)
	{
		return false;
	}

	// Create the slope texture object.
	m_SlopeTexture = new Texture;
	if(!m_SlopeTexture)
	{
		return false;
	}

	// Initialize the slope texture object.
	result = m_SlopeTexture->Initialize(device, slopeTextureFilename);
	if(!result)
	{
		return false;
	}

	// Create the rock texture object.
	m_RockTexture = new Texture;
	if(!m_RockTexture)
	{
		return false;
	}

	// Initialize the rock texture object.
	result = m_RockTexture->Initialize(device, rockTextureFilename);
	if(!result)
	{
		return false;
	}

	// Create the detail map texture object.
	m_DetailTexture = new Texture;
	if(!m_DetailTexture)
	{
		return false;
	}

	// Initialize the detail map texture object.
	result = m_DetailTexture->Initialize(device, detailMapFilename);
	if(!result)
	{
		return false;
	}

	// Create the normal map texture object.
	m_NormalTexture = new Texture;
	if(!m_NormalTexture)
	{
		return false;
	}

	// Create the normal map texture object.
	m_NormalTexture = new Texture;
	if(!m_NormalTexture)
	{
		return false;
	}

	// Initialize the normal map texture object.
	result = m_NormalTexture->Initialize(device, normalTextureFilename);
	if(!result)
	{
		return false;
	}


	return true;
}


void Terrain::ReleaseTexture()
{
	// Release the normal map texture object.
	if(m_NormalTexture)
	{
		m_NormalTexture->Shutdown();
		delete m_NormalTexture;
		m_NormalTexture = 0;
	}

	// Release the detail map texture object.
	if(m_DetailTexture)
	{
		m_DetailTexture->Shutdown();
		delete m_DetailTexture;
		m_DetailTexture = 0;
	}

	// Release the texture objects.
	if(m_GrassTexture)
	{
		m_GrassTexture->Shutdown();
		delete m_GrassTexture;
		m_GrassTexture = 0;
	}

	if(m_SlopeTexture)
	{
		m_SlopeTexture->Shutdown();
		delete m_SlopeTexture;
		m_SlopeTexture = 0;
	}

	if(m_RockTexture)
	{
		m_RockTexture->Shutdown();
		delete m_RockTexture;
		m_RockTexture = 0;
	}

	return;
}

bool Terrain::LoadColorMap(char* filename)
{
	int error, imageSize, i, j, k, index, colorMapWidth, colorMapHeight;
	FILE* filePtr;
	unsigned int count;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	unsigned char* bitmapImage;


	// Open the color map file in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if(error != 0)
	{
		return false;
	}

	// Read in the file header.
	count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	if(count != 1)
	{
		return false;
	}

	// Read in the bitmap info header.
	count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	if(count != 1)
	{
		return false;
	}

	// Make sure the color map dimensions are the same as the terrain dimensions for easy 1 to 1 mapping.
	colorMapWidth = bitmapInfoHeader.biWidth;
	colorMapHeight = bitmapInfoHeader.biHeight;

	if((colorMapWidth != m_terrainWidth) || (colorMapHeight != m_terrainHeight))
	{
		return false;
	}

	// Calculate the size of the bitmap image data.
	imageSize = colorMapWidth * colorMapHeight * 3;

	// Allocate memory for the bitmap image data.
	bitmapImage = new unsigned char[imageSize];
	if(!bitmapImage)
	{
		return false;
	}

	// Move to the beginning of the bitmap data.
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// Read in the bitmap image data.
	count = fread(bitmapImage, 1, imageSize, filePtr);
	if(count != imageSize)
	{
		return false;
	}

	// Close the file.
	error = fclose(filePtr);
	if(error != 0)
	{
		return false;
	}

	// Initialize the position in the image data buffer.
	k=0;

	// Read the image data into the color map portion of the height map structure.
	for(j=0; j<colorMapHeight; j++)
	{
		for(i=0; i<colorMapWidth; i++)
		{
			index = (colorMapHeight * j) + i;

			m_heightMap[index].blue = (float)bitmapImage[k]   / 255.0f;
			m_heightMap[index].green = (float)bitmapImage[k+1] / 255.0f;
			m_heightMap[index].red = (float)bitmapImage[k+2] / 255.0f;

			k+=3;
		}
	}

	// Release the bitmap image data.
	delete [] bitmapImage;
	bitmapImage = 0;

	return true;
}

bool Terrain::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	int index, i, j;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int index1, index2, index3, index4;
	float tu, tv;


	// Calculate the number of vertices in the terrain mesh.
	m_vertexCount = (m_terrainWidth - 1) * (m_terrainHeight - 1) * 6;

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

	// Initialize the index to the vertex buffer.
	index = 0;

	// Load the vertex and index array with the terrain data.
	for(j=0; j<(m_terrainHeight-1); j++)
	{
		for(i=0; i<(m_terrainWidth-1); i++)
		{
			index1 = (m_terrainHeight * j) + i;          // Bottom left.
			index2 = (m_terrainHeight * j) + (i+1);      // Bottom right.
			index3 = (m_terrainHeight * (j+1)) + i;      // Upper left.
			index4 = (m_terrainHeight * (j+1)) + (i+1);  // Upper right.

			// Upper left.
			tv = m_heightMap[index3].tv;

			// Modify the texture coordinates to cover the top edge.
			if(tv == 1.0f) { tv = 0.0f; }

			vertices[index].position = D3DXVECTOR3(m_heightMap[index3].x, m_heightMap[index3].y, m_heightMap[index3].z);
			vertices[index].texture = D3DXVECTOR4(m_heightMap[index3].tu, tv, 0.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index3].nx, m_heightMap[index3].ny, m_heightMap[index3].nz);
			vertices[index].color = D3DXVECTOR4(m_heightMap[index3].red, m_heightMap[index3].green, m_heightMap[index3].blue, 1.0f);
			indices[index] = index;
			index++;

			// Upper right.
			tu = m_heightMap[index4].tu;
			tv = m_heightMap[index4].tv;

			// Modify the texture coordinates to cover the top and right edge.
			if(tu == 0.0f) { tu = 1.0f; }
			if(tv == 1.0f) { tv = 0.0f; }

			vertices[index].position = D3DXVECTOR3(m_heightMap[index4].x, m_heightMap[index4].y, m_heightMap[index4].z);
			vertices[index].texture = D3DXVECTOR4(tu, tv, 1.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index4].nx, m_heightMap[index4].ny, m_heightMap[index4].nz);
			vertices[index].color = D3DXVECTOR4(m_heightMap[index4].red, m_heightMap[index4].green, m_heightMap[index4].blue, 1.0f);
			indices[index] = index;
			index++;

			// Bottom left.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index1].x, m_heightMap[index1].y, m_heightMap[index1].z);
			vertices[index].texture = D3DXVECTOR4(m_heightMap[index1].tu, m_heightMap[index1].tv, 0.0f, 1.0f);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index1].nx, m_heightMap[index1].ny, m_heightMap[index1].nz);
			vertices[index].color = D3DXVECTOR4(m_heightMap[index1].red, m_heightMap[index1].green, m_heightMap[index1].blue, 1.0f);
			indices[index] = index;
			index++;

			// Bottom left.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index1].x, m_heightMap[index1].y, m_heightMap[index1].z);
			vertices[index].texture = D3DXVECTOR4(m_heightMap[index1].tu, m_heightMap[index1].tv, 0.0f, 1.0f);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index1].nx, m_heightMap[index1].ny, m_heightMap[index1].nz);
			vertices[index].color = D3DXVECTOR4(m_heightMap[index1].red, m_heightMap[index1].green, m_heightMap[index1].blue, 1.0f);
			indices[index] = index;
			index++;

			// Upper right.
			tu = m_heightMap[index4].tu;
			tv = m_heightMap[index4].tv;

			// Modify the texture coordinates to cover the top and right edge.
			if(tu == 0.0f) { tu = 1.0f; }
			if(tv == 1.0f) { tv = 0.0f; }

			vertices[index].position = D3DXVECTOR3(m_heightMap[index4].x, m_heightMap[index4].y, m_heightMap[index4].z);
			vertices[index].texture = D3DXVECTOR4(tu, tv, 1.0f, 0.0f);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index4].nx, m_heightMap[index4].ny, m_heightMap[index4].nz);
			vertices[index].color = D3DXVECTOR4(m_heightMap[index4].red, m_heightMap[index4].green, m_heightMap[index4].blue, 1.0f);
			indices[index] = index;
			index++;

			// Bottom right.
			tu = m_heightMap[index2].tu;

			// Modify the texture coordinates to cover the right edge.
			if(tu == 0.0f) { tu = 1.0f; }

			vertices[index].position = D3DXVECTOR3(m_heightMap[index2].x, m_heightMap[index2].y, m_heightMap[index2].z);
			vertices[index].texture = D3DXVECTOR4(tu, m_heightMap[index2].tv, 1.0f, 1.0f);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index2].nx, m_heightMap[index2].ny, m_heightMap[index2].nz);
			vertices[index].color = D3DXVECTOR4(m_heightMap[index2].red, m_heightMap[index2].green, m_heightMap[index2].blue, 1.0f);
			indices[index] = index;
			index++;
		}
	}

	// Set up the description of the static vertex buffer.
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

	// Now create the vertex buffer.
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

	// Release the arrays now that the buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void Terrain::ShutdownBuffers()
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


void Terrain::RenderBuffers(ID3D11DeviceContext* deviceContext)
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


int Terrain::GetIndexCount()
{
	return m_indexCount;
}


ID3D11ShaderResourceView* Terrain::GetGrassTexture() const
{
	return m_GrassTexture->GetTexture();
}

ID3D11ShaderResourceView* Terrain::GetSlopeTexture() const
{
	return m_SlopeTexture->GetTexture();
}

ID3D11ShaderResourceView* Terrain::GetColorTexture() const
{
	return m_ColorTexture->GetTexture();
}

ID3D11ShaderResourceView* Terrain::GetNormalTexture() const
{
	return m_NormalTexture->GetTexture();
}

ID3D11ShaderResourceView* Terrain::GetRockTexture() const
{
	return m_RockTexture->GetTexture();
}

ID3D11ShaderResourceView* Terrain::GetDetailMapTexture() const
{
	return m_DetailTexture->GetTexture();
}

float Terrain::GetMeanTerrainHeight() const
{
	return m_meanTerrainHeight;
}

float Terrain::GetHeightAtPosition(float positionX, float positionZ)
{
	return m_heightMap[int(positionX + m_terrainHeight* positionZ)].y;
}