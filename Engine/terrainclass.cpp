////////////////////////////////////////////////////////////////////////////////
// Filename: terrainclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "terrainclass.h"
#include <cmath>
#include <cstdlib>
#include <ctime>


TerrainClass::TerrainClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_heightMap = 0;
	m_rndNumSeed = 0;
	m_IterationCount = 0;
	m_terrainInitializedToggle = false;
	m_terrainGeneratedToggle = false;
	m_seedGeneratedToggle = false;
	m_terrainFlattenedToggle = false;

	m_terrainSmoothedToggle = false;
	m_terrainErodedToggle = false;
}


TerrainClass::TerrainClass(const TerrainClass& other)
{
}


TerrainClass::~TerrainClass()
{
}

bool TerrainClass::InitializeTerrain(ID3D11Device* device, int terrainWidth, int terrainHeight)
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


	//even though we are generating a flat terrain, we still need to normalise it. 
	// Calculate the normals for the terrain data.
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

	return true;

}
bool TerrainClass::Initialize(ID3D11Device* device, char* heightMapFilename)
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

	// Initialize the vertex and index buffer that hold the geometry for the terrain.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	return true;
}


void TerrainClass::Shutdown()
{
	// Release the vertex and index buffer.
	ShutdownBuffers();

	// Release the height map data.
	ShutdownHeightMap();

	return;
}


void TerrainClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int TerrainClass::GetIndexCount()
{
	return m_indexCount;
}

bool TerrainClass::GenerateHeightMap(ID3D11Device* device, bool keyDown)
{

	bool result;

	//the toggle is just a bool that I use to make sure this is only called ONCE when you press a key
	//until you release the key and start again. We dont want to be generating the terrain 500
	//times per second. 
	if(keyDown&&(!m_terrainGeneratedToggle))
	{
		srand(51);
		m_IterationCount++;
		//DoFaultFormation(m_terrainHeight, m_IterationCount, -0.2f, 0.2f, 5, 1.0f);
		DoMidpointDisplacement(m_terrainHeight, GenerateRndNum(0.6f,2.0f));
		//GenerateSphere(m_terrainHeight);
		//ErodeHeightMap(1.0f);
		//SmoothTerrain(3.0f);
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

bool TerrainClass::FlattenTerrain(ID3D11Device* device, bool keyDown)
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


bool TerrainClass::GenerateNewSeed(bool keydown)
{
	if(keydown&&(!m_seedGeneratedToggle))
	{
		m_rndNumSeed = rand() % 32000 + 1;

		m_seedGeneratedToggle = true;
	}

	return true;
}

void TerrainClass::GenerateSphere(int size)
{
	float height = 0.0f;
	int index;

	// Flatten the height.  m_terrainHeight  m_terrainWidth
	for(int j=0; j<m_terrainHeight; j++)
	{
		for(int i=0; i<m_terrainWidth; i++)
		{			
			index = (m_terrainHeight * j) + i;
			double pi = 3.14159265359;

			double theta = ( double(j) * 1.0 * pi ) / double(m_terrainHeight);
			double phi = ( double(i) * 2.0 * pi ) / double(m_terrainHeight);
			double radius = 10.0;
			m_heightMap[index].x = float( radius * sin ( theta ) * cos ( phi ) );
			m_heightMap[index].y = float( radius * cos( theta) );
			m_heightMap[index].z = float( radius * sin ( theta ) * sin ( phi ) );

		}
	}

	NormalizeTerrain(size);
}

void TerrainClass::GenerateMultiFractal(int size)
{
	float height = 0.0f;
	int index;

	// Flatten the height.  m_terrainHeight  m_terrainWidth
	for(int j=0; j<m_terrainHeight; j++)
	{
		for(int i=0; i<m_terrainWidth; i++)
		{			
			index = (m_terrainHeight * j) + i;
			m_heightMap[index].x = float(i);
			m_heightMap[index].y = GenerateMultifractal(float(i), float(j), 2.0f, 2.0f, 2.0f, 1.0f, 1.0f);
			m_heightMap[index].z = float(j);

		}
	}

	NormalizeTerrain(size);
}

void TerrainClass::DoMidpointDisplacement(int size, float roughness)
{
	int ni, nj, mi, mj, pmi, pmj;
	int rectSize = size;
	float dh = float(rectSize/2);
	float r = float( pow(2,(-1*roughness)) );

	m_heightMap[0].x = 0;
	m_heightMap[0].y = 0;
	m_heightMap[0].z = 0;

	while(rectSize > 0)
	{
		// Diamond Step.
		for (int i=0; i<size; i+=rectSize)
		{
			for (int j=0; j<size; j+=rectSize)
			{
				ni = (i+rectSize) % size;
				nj = (j+rectSize) % size;

				mi = (i+rectSize)/2;
				mj = (j+rectSize)/2;

				//double theta = (double(i) * 2.0 * 3.14159265359) / double(m_terrainHeight);
				//double phi = (double(j) * 2.0 * 3.14159265359) / double(m_terrainHeight);
				//double radius = 10.0;

				//m_heightMap[mi+mj*size].x = float( radius * sin ( theta ) * cos ( phi ) );
				//m_heightMap[mi+mj*size].y = (-1.0f * float( radius * cos(theta) )) * (m_heightMap[i+j*size].y + m_heightMap[ni+j*size].y+m_heightMap[i+nj*size].y + m_heightMap[ni+nj*size].y)/4+GenerateRndNum(-dh/2, dh/2);
				//m_heightMap[mi+mj*size].z = float( radius * sin ( theta ) * sin ( phi ) );

				//m_heightMap[mi+mj*size].x = (float)i;
				//m_heightMap[mi+mj*size].y = (m_heightMap[i+j*size].y + m_heightMap[ni+j*size].y+m_heightMap[i+nj*size].y + m_heightMap[ni+nj*size].y)/4+GenerateRndNum(-dh/2, dh/2);
				//m_heightMap[mi+mj*size].z = (float)j;
			}
		}

		// Square Step

		for (int i=0; i<size; i+=rectSize)
		{
			for(int j=0; j<size; j+=rectSize)
			{
				ni = (i+rectSize)%size;
				nj = (j+rectSize)%size;

				mi = (i+rectSize/2);
				mj = (j+rectSize/2);

				pmi = (i-rectSize/2+size)%size;
				pmj = (j-rectSize/2+size)%size;

				// Calcuate the square value for the top side of the rectangle.
				//m_heightMap[mi+j*size].x = (float)i;
				m_heightMap[mi+j*size].y = (m_heightMap[i+j*size].y + m_heightMap[ni+j*size].y + m_heightMap[mi+pmj*size].y + m_heightMap[mi+mj*size].y)/4 + GenerateRndNum(-dh/2, dh/2);
				//m_heightMap[mi+j*size].z = (float)j;

				// Calculate the square value for the left side of the rectangle.
				//m_heightMap[i+mj*size].x = (float)i;
				m_heightMap[i+mj*size].y = (m_heightMap[i+j*size].y + m_heightMap[i+nj*size].y + m_heightMap[pmi+mj*size].y + m_heightMap[mi+mj*size].y)/4 + GenerateRndNum(-dh/2, dh/2);
				//m_heightMap[i+mj*size].z = (float)j;
			}
		}
		rectSize/=2;
		dh*=r;
	}
	NormalizeTerrain(size);
}

void TerrainClass::DoFaultFormation(int size, int iterations, float minDelta, float maxDelta, int iterationsPerFilter, float filter)
{
	int x1,y1,x2,y2,dx1,dy1,dx2,dy2;
	float dHeight;

	for (int i=0; i<iterations; i++)
	{
		// Perform linear interpolation from maxDelta to minDelta by calculating the dHeight for this iteration.
		dHeight = maxDelta - ((maxDelta - minDelta)*i)/float(iterations);

		x1 = rand() % size;
		y1 = rand() % size;

		do
		{
			x2 = rand() % size;
			y2 = rand() % size;
		} while (x2 == x1 && y2 == y1);

		// Calculate the direction of the line.
		dx1 = x2 - x1;
		dy1 = y2 - y1;

		for (x2=0; x2<size; x2++)
		{
			for (y2=0; y2<size; y2++)
			{
				dx2 = x2-x1;
				dy2 = y2-y1;

				if (dx2*dy1 - dx1*dy2 > 0)
				{
					m_heightMap[x2+size*y2].y += dHeight;
				}
			}
		}
		if (iterationsPerFilter!=0 && (i%iterationsPerFilter)==0)
		{
			//ErodeHeightMap(filter);
		}
	}
	NormalizeTerrain(size);
}

//void TerrainClass::DoParticleDeposition(int jumps, int peakWalk, int minParticlesPerJump, int maxParticlesPerJump, float caldera)
//{
//	int x, y, m, px, py, minx, miny, maxx, maxy, sx, sy, numParticles, tx, ty, done;
//	int dx[] = {0 ,1 ,0 ,m_terrainHeight-1 ,1 ,1 , m_terrainHeight-1, m_terrainHeight-1};
//	int dy[] = {1, 0, m_terrainHeight-1, 0, m_terrainHeight-1, 1 , m _terrainHeight-1, 1};
//	float ch, ph;
//	int *calderaMap = (int *)malloc(m_terrainHeight*m_terrainHeight*sizeof(int));
//
//	for (int p=0; p<jumps; p++)
//	{
//		// Pick a random spot.
//		x = rand() % m_terrainHeight;
//		y = rand() % m_terrainHeight;
//
//		// Px and py track the position of the caldera.
//		px = x;
//		py = y;
//
//		// Determine the number of particles to drop.
//		numParticles = int(GenerateRndNum( float(minParticlesPerJump), float(maxParticlesPerJump));
//
//		for (int i=0; i<numParticlesl i++)
//		{
//			// Determine whether to move the drop point and move it in a random direction.
//			if (peakWalk != 0 && (i % peakWalk) == 0)
//			{
//				m = rand() % 8;
//				x = (x + dx[m] + m_terrainHeight) % m_terrainHeight);
//				y = (y + dy[m] + m_terrainHeight) % m_terrainHeight;
//			}
//
//			// Drop the particle.
//			m_heightMap[x + y*m_terrainHeight].y += 1.0f;
//
//			// Agitate the particle until it settles.
//
//			sx = x;
//			sy = y;
//			done = 0;
//
//			while (done == 0)
//			{
//				done = 1;
//
//				// Pick a random neighbour to inspect.
//				m = rand();
//				for (int j=0; j<8; j++)
//				{
//					tx = (sx + dx[(j + m) % 8]) % m_terrainHeight;
//					ty = (sy + dy[(j + m) % 8]) % m_terrainHeight;
//
//					// Move to neighbour if possible.
//					if ( m_heightMap[tx + ty*m_terrainHeight].y + 1.0f < m_heightMap[sx + sy].y)
//					{
//						m_heightMap[tx + ty*m_terrainHeight] += 1.0f;
//						m_heightMap[sx + sy*m_terrainHeight] -= 1.0f;
//						sx = tx;
//						sy = ty;
//						done = 0;
//						break;
//					}
//				}
//			}
//
//			// Check to see if the latest point is higher than the caldera point
//			// and if so move the caldera point there.
//			if (m_heightMap[sx + m_*sy] > m_heightMap[px + m_terrainHeight*py])
//			{
//				px = sx;
//				py = sy;
//			}
//		}
//
//		// Now that we're done with the peak, invert the caldera where ch is the caldera cutoff altitude and
//		// ph is the height at the caldera start point. Note that this technique will not create a caldera at every
//		// peak, rather it will create one caldera per jump.  It is	possible for the algorithm to generate multiple peaks per jump.
//		ph = m_heightMap[px + 
//
//
//}

void TerrainClass::NormalizeTerrain(int size)
{
	float min, max;
	float dh;

	min = m_heightMap[0].y;
	max = m_heightMap[0].y;

	for (int i=1; i<size*size ;i++)
	{
		if(m_heightMap[i].y > max) { 
			max = m_heightMap[i].y; 
		} else if(m_heightMap[i].y < min) { 
			min = m_heightMap[i].y;
		}
	}

	if(max <= min) { 
		return; 
	} dh = max - min;

	for (int i=0; i<size; i++) {
		m_heightMap[i].y = (m_heightMap[i].y-min)/dh;
	}
}

bool TerrainClass::SmoothTerrain(ID3D11Device* device, bool keyDown)
{
	bool result;
	int index;
	float smoothness = 0.5f;
	if (keyDown&&(!m_terrainSmoothedToggle))
	{
		//for(int j=0; j<m_terrainHeight; j++)
		//{
		//	for(int i=0; i<m_terrainWidth; i++)
		//	{			
		//		index = (m_terrainHeight * i) + j;
		//		m_heightMap[index].y = (m_heightMap[index-2].y +m_heightMap[index-1].y + m_heightMap[index].y + m_heightMap[index+1].y +m_heightMap[index+2].y )/5;
		//		/*m_heightMap[index].y = ((smoothness*m_heightMap[index-1].y) + ((1-smoothness)*m_heightMap[index].y));*/
		//	}
		//}

		//// Erode Horizontally.
		//for(int i=0; i < m_terrainWidth * m_terrainWidth; i++)
		//{			
		//	m_heightMap[i].y = (m_heightMap[i - 1].y + m_heightMap[i].y + m_heightMap[i + 1].y) / 3;
		//}

		////Erode Vertically.
		//for (int j = 0; j < m_terrainHeight * m_terrainHeight ; j++)
		//{
		//	m_heightMap[j].y = ( m_heightMap[(j * m_terrainHeight) - 1].y + m_heightMap[j * m_terrainHeight].y + m_heightMap[(j * m_terrainHeight) + 1].y ) / 3;
		//}

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
	}
	else
	{
		m_terrainSmoothedToggle = false;
	}

	return true;
}


//bool TerrainClass::ErodeHeightMap(float smoothness)
//{
//	// Rows: Left to right.
//	for (int x=0; x<m_terrainWidth; x++) 
//{
//		for (int z=0; z<m_terrainHeight; z++) 
//{
//			m_heightMap[x+z].y = m_heightMap[(x-1)+z].y * (1-smoothness) + m_heightMap[x+z].y;
//		}
//	}
//
//	// Rows: Right to left.
//	for (int x=m_terrainWidth-2; x<-1; x--) 
//{
//
//	}
//}

bool TerrainClass::ErodeHeightMap(ID3D11Device* device, bool keyDown, float smoothness)
{
	bool result;

	if (keyDown&&(!m_terrainErodedToggle))
	{
		int size = m_terrainHeight * m_terrainHeight;
		for (int i=0; i<size; i++)
		{
			Erode(&m_heightMap[size*i].y, 1, size, smoothness);
		}

		for (int i=0; i<m_terrainHeight; i++)
		{
			Erode(&m_heightMap[size*i+size-1].y, -1, size, smoothness);
		}

		for (int i=0; i<m_terrainHeight; i++)
		{
			Erode(&m_heightMap[i].y, size, size, smoothness);
		}

		for (int i=0; i<m_terrainHeight; i++)
		{
			Erode(&m_heightMap[size*(size-1)+i].y, -size, size, smoothness);
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

		m_terrainErodedToggle = true;
	}
	else
	{
		m_terrainErodedToggle = false;
	}

	return true;
}

void TerrainClass::Erode(float* heightMap, int index, int count, float smoothness)
{
	int j = index;
	float h = heightMap[0];
	for (int i=0; i<count; i++)
	{
		heightMap[j] = smoothness*h + (1-smoothness)*heightMap[j];
		h = heightMap[j];
		j+=index;
	}
}

float TerrainClass::GenerateMultifractal(float x, float y, float octaves, float amplitude, float frequency, float deltaAmplitude, float offset)
{
	float value = 0.0f;

	for (int i=0; i<(octaves-1); i++)
	{ 
		value +=(offset*GenerateNoise(x*frequency, y*frequency) * amplitude);
		amplitude *= deltaAmplitude;
	}

	return value;
}
float TerrainClass::GenerateRndNum(float min, float max)
{
	return min+(max-min)*((float)((rand() % 1000 + 1))/1000);
}

float TerrainClass::GenerateRandomNumber(int x, int y)
{ 
	int n = x+y*57;
	n=(n<<13)^n;

	return (1- ((n* (n*n*19417*189851)+4967243) & 4945007) / 3354251.0);
}

float TerrainClass::SmoothRandomNumber(int x, int y)
{
	float corners =  (GenerateRandomNumber(x-1, y-1) + GenerateRandomNumber(x+1, y-1) + GenerateRandomNumber(x-1, y+1) + GenerateRandomNumber(x+1, y+1))/16;
	float sides =  (GenerateRandomNumber(x-1, y) + GenerateRandomNumber(x+1, y) + GenerateRandomNumber(x, y-1) + GenerateRandomNumber(x, y+1))/8;
	float centre = GenerateRandomNumber(x, y )/4;
	return corners + sides + centre;
}

float TerrainClass::DoInterpolation(float num1, float num2, float x)
{
	float f;
	f = (1-cos(x*3.1415927f))*0.5f;

	return num1*(1-f) + num2*f;
}

float TerrainClass::GenerateNoise(float x, float y)
{
	int xInt = x;
	float xFraction = x - xInt;
	int yInt = y;
	float yFraction = y - yInt;
	float rndNum1, rndNum2, rndNum3, rndNum4, interpolatedNum1, interpolatedNum2;

	rndNum1 = SmoothRandomNumber(xInt, yInt);
	rndNum2 = SmoothRandomNumber(xInt+1, yInt);
	rndNum3 = SmoothRandomNumber(xInt, yInt+1);
	rndNum4 = SmoothRandomNumber(xInt+1, yInt+1);
	interpolatedNum1 = DoInterpolation(rndNum1, rndNum2, xFraction);
	interpolatedNum2 = DoInterpolation(rndNum3, rndNum4, xFraction);

	return DoInterpolation(interpolatedNum1, interpolatedNum2, yFraction);
}

bool TerrainClass::LoadHeightMap(char* filename)
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


void TerrainClass::NormalizeHeightMap()
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


bool TerrainClass::CalculateNormals()
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


void TerrainClass::ShutdownHeightMap()
{
	if(m_heightMap)
	{
		delete [] m_heightMap;
		m_heightMap = 0;
	}

	return;
}


bool TerrainClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	int index, i, j;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int index1, index2, index3, index4;


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
			vertices[index].position = D3DXVECTOR3(m_heightMap[index3].x, m_heightMap[index3].y, m_heightMap[index3].z);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index3].nx, m_heightMap[index3].ny, m_heightMap[index3].nz);
			indices[index] = index;
			index++;

			// Upper right.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index4].x, m_heightMap[index4].y, m_heightMap[index4].z);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index4].nx, m_heightMap[index4].ny, m_heightMap[index4].nz);
			indices[index] = index;
			index++;

			// Bottom left.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index1].x, m_heightMap[index1].y, m_heightMap[index1].z);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index1].nx, m_heightMap[index1].ny, m_heightMap[index1].nz);
			indices[index] = index;
			index++;

			// Bottom left.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index1].x, m_heightMap[index1].y, m_heightMap[index1].z);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index1].nx, m_heightMap[index1].ny, m_heightMap[index1].nz);
			indices[index] = index;
			index++;

			// Upper right.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index4].x, m_heightMap[index4].y, m_heightMap[index4].z);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index4].nx, m_heightMap[index4].ny, m_heightMap[index4].nz);
			indices[index] = index;
			index++;

			// Bottom right.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index2].x, m_heightMap[index2].y, m_heightMap[index2].z);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index2].nx, m_heightMap[index2].ny, m_heightMap[index2].nz);
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


void TerrainClass::ShutdownBuffers()
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


void TerrainClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
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