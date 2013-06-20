////////////////////////////////////////////////////////////////////////////////
// Filename: graphics.cpp
// Code Adapted from a variety of tutorials on http://www.rastertek.com
////////////////////////////////////////////////////////////////////////////////
#include "graphics.h"
#include "camera.h"
#include "shadermanager.h"
#include "object.h"
#include "objectbitmap.h"
#include "objecttext.h"
#include "objectdebugwindow.h"
#include "objectreflectable.h"
#include "objectterrain.h"
#include "objectskydome.h"
#include "objectclouds.h"
#include "objectworld.h"
#include "objectwater.h"
#include "objectparticle.h"
//#include "terrainrendertexture.h"
#include "rendertexture.h"
#include "orthowindow.h"
#include "terrain.h"

Graphics::Graphics()
{
	m_D3D = 0;
	m_ObjectSphere = 0;
	m_ObjectSphere2 = 0;
	m_Object3 = 0;
	m_Object4 = 0;
	m_ObjectFloor = 0;
	m_ObjectBitmap1 = 0;
	m_ObjectCursor = 0;
	m_ObjectText1 = 0;
	m_ObjectTerrain = 0;
	m_ObjectSkyDome = 0;
	m_ObjectClouds = 0;
	m_ObjectWorld = 0;
	m_ObjectWater = 0;
	m_ObjectParticle = 0;

	m_ShaderManager = 0;

	m_TerrainRefractionTexture = 0;
	m_TerrainReflectionTexture = 0;

	m_RenderTexture = 0;
	m_ConvolutionTexture = 0;
	m_DownSampleTexture = 0;
	m_HorizontalBlurTexture = 0;
	m_VerticalBlurTexture = 0;
	m_UpSampleTexture = 0;
	m_SmallWindow = 0;
	m_FullScreenWindow = 0;
	m_MiniMapWindow = 0;
	m_MiniMapTexture = 0;

	renderPass = 0;
	m_ScreenWidth = 0;
	m_ScreenHeight = 0;
	m_MouseX = 0;
	m_MouseY = 0;

	m_collisionCheck = false;
	m_collisionCheck2 = false;
}


Graphics::Graphics(const Graphics& other)
{
}


Graphics::~Graphics()
{
}


bool Graphics::Initialize(Camera* cam, int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	int downSampleWidth, downSampleHeight;
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;
	// Set the size to sample down to.
	downSampleWidth = m_ScreenWidth;
	downSampleHeight = m_ScreenHeight;

	// Create the Direct3D object.
	m_D3D = new D3D;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(m_ScreenWidth, m_ScreenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the refraction texture object.
	m_TerrainRefractionTexture = new RenderTexture;
	if(!m_TerrainRefractionTexture)
	{
		return false;
	}

	// Initialize refraction texture object.
	result = m_TerrainRefractionTexture->Initialize(m_D3D->GetDevice(), m_ScreenWidth, m_ScreenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		return false;
	}

	// Create the reflection texture object.
	m_TerrainReflectionTexture = new RenderTexture;
	if(!m_TerrainReflectionTexture)
	{
		return false;
	}

	// Initialize the reflection texture object.
	result = m_TerrainReflectionTexture->Initialize(m_D3D->GetDevice(), m_ScreenWidth, m_ScreenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		return false;
	}

	// Create the render to texture object.
	m_RenderTexture = new RenderTexture;
	if(!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the down sample render to texture object.
	m_DownSampleTexture = new RenderTexture;
	if(!m_DownSampleTexture)
	{
		return false;
	}

	// Initialize the down sample render to texture object.
	result = m_DownSampleTexture->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the down sample render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the convolution render to texture object.
	m_ConvolutionTexture = new RenderTexture;
	if(!m_ConvolutionTexture)
	{
		return false;
	}

	// Initialize the down sample render to texture object.
	result = m_ConvolutionTexture->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the convolution render to texture object.", L"Error", MB_OK);
		return false;
	}
	

	// Create the horizontal blur render to texture object.
	m_HorizontalBlurTexture = new RenderTexture;
	if(!m_HorizontalBlurTexture)
	{
		return false;
	}

	// Initialize the horizontal blur render to texture object.
	result = m_HorizontalBlurTexture->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the horizontal blur render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the vertical blur render to texture object.
	m_VerticalBlurTexture = new RenderTexture;
	if(!m_VerticalBlurTexture)
	{
		return false;
	}

	// Initialize the vertical blur render to texture object.
	result = m_VerticalBlurTexture->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the vertical blur render to texture object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the up sample render to texture object.
	m_UpSampleTexture = new RenderTexture;
	if(!m_UpSampleTexture)
	{
		return false;
	}

	// Initialize the up sample render to texture object.
	result = m_UpSampleTexture->Initialize(m_D3D->GetDevice(), m_ScreenWidth, m_ScreenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the up sample render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the mini map Texture render to texture object.
	m_MiniMapTexture = new RenderTexture;
	if(!m_MiniMapTexture)
	{
		return false;
	}

	// Initialize the up sample render to texture object.
	result = m_MiniMapTexture->Initialize(m_D3D->GetDevice(), m_ScreenWidth, m_ScreenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the mini map render to texture object.", L"Error", MB_OK);
		return false;
	}

	

	// Create the small ortho window object.
	m_SmallWindow = new OrthoWindow;
	if(!m_SmallWindow)
	{
		return false;
	}

	// Initialize the small ortho window object.
	result = m_SmallWindow->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the small ortho window object.", L"Error", MB_OK);
		return false;
	}

	// Create the full screen ortho window object.
	m_FullScreenWindow = new OrthoWindow;
	if(!m_FullScreenWindow)
	{
		return false;
	}

	// Initialize the full screen ortho window object.
	result = m_FullScreenWindow->Initialize(m_D3D->GetDevice(), m_ScreenWidth, m_ScreenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the full screen ortho window object.", L"Error", MB_OK);
		return false;
	}

	// Create the mini map ortho window object.
	m_MiniMapWindow = new OrthoWindow;
	if(!m_MiniMapWindow)
	{
		return false;
	}
	m_MiniMapWindow->SetPosition(D3DXVECTOR2(325.0f, -250.0f));
	// Initialize the mini map ortho window object.
	result = m_MiniMapWindow->Initialize(m_D3D->GetDevice(), m_ScreenWidth / 6, m_ScreenHeight / 6);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the mini map ortho window object.", L"Error", MB_OK);
		return false;
	}

	

	// Create the shader manager object.
	m_ShaderManager = new ShaderManager;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the renderable objects.
	int terrainSize = 512;
	cam->GetViewMatrix(m_InitialViewMatrix);

	m_ObjectSphere = new Object(m_D3D, "../Engine/data/sphere.txt", L"../Engine/data/fire01.dds");
	m_ObjectSphere2 = new Object(m_D3D, "../Engine/data/sphere.txt", L"../Engine/data/blue01.dds");
	m_ObjectCursor = new ObjectBitmap(m_D3D, m_ScreenWidth, m_ScreenHeight, L"../Engine/data/mouse.dds", 32, 32, 0, 0, m_InitialViewMatrix); 
	m_ObjectBitmap1 = new ObjectBitmap(m_D3D, m_ScreenWidth, m_ScreenHeight, L"../Engine/data/stone.dds", 8, 8, 0, 0, m_InitialViewMatrix);

	m_ObjectDebugWindow1 = new ObjectDebugWindow(m_D3D, m_ScreenWidth, m_ScreenHeight, 100, 100);
	m_ObjectText1 = new ObjectText(m_D3D, cam, hwnd, m_ScreenWidth, m_ScreenHeight);
	//m_ObjectTerrain = new ObjectTerrain(m_D3D,  "../Engine/data/heightmap04.bmp", L"../Engine/data/dirt01.dds", L"../Engine/data/slope.dds", L"../Engine/data/rock.dds", "../Engine/data/colorm01.bmp", L"../Engine/data/detail001.dds",L"../Engine/data/normal.dds");
	m_ObjectTerrain = new ObjectTerrain(m_D3D, terrainSize, terrainSize, L"../Engine/data/dirt01.dds", L"../Engine/data/slope.dds",  L"../Engine/data/rock.dds", "../Engine/data/cm.bmp", L"../Engine/data/detail001.dds",L"../Engine/data/normal.dds");
	m_ObjectSkyDome = new ObjectSkyDome(m_D3D, hwnd, "../Engine/data/skydome.txt");
	m_ObjectClouds = new ObjectClouds(m_D3D, L"../Engine/data/cloud001.dds", L"../Engine/data/cloud002.dds",L"../Engine/data/perturb002.dds");
	m_ObjectWater = new ObjectWater(m_D3D, L"../Engine/data/waternormal.dds", 3.75f, 256.0f);
	m_ObjectParticle = new ObjectParticle(m_D3D, L"../Engine/data/star.dds");

	return true;
}


void Graphics::Shutdown()
{
	// Release the mini map ortho window object.
	if(m_MiniMapWindow)
	{
		m_MiniMapWindow->Shutdown();
		delete m_MiniMapWindow;
		m_MiniMapWindow = 0;
	}

	// Release the full screen ortho window object.
	if(m_FullScreenWindow)
	{
		m_FullScreenWindow->Shutdown();
		delete m_FullScreenWindow;
		m_FullScreenWindow = 0;
	}

	// Release the small ortho window object.
	if(m_SmallWindow)
	{
		m_SmallWindow->Shutdown();
		delete m_SmallWindow;
		m_SmallWindow = 0;
	}

	// Release the mini map render to texture object.
	if(m_MiniMapTexture)
	{
		m_MiniMapTexture->Shutdown();
		delete m_MiniMapTexture;
		m_MiniMapTexture = 0;
	}

	// Release the up sample render to texture object.
	if(m_UpSampleTexture)
	{
		m_UpSampleTexture->Shutdown();
		delete m_UpSampleTexture;
		m_UpSampleTexture = 0;
	}

	// Release the vertical blur render to texture object.
	if(m_VerticalBlurTexture)
	{
		m_VerticalBlurTexture->Shutdown();
		delete m_VerticalBlurTexture;
		m_VerticalBlurTexture = 0;
	}

	// Release the convolution render to texture object.
	if(m_ConvolutionTexture)
	{
		m_ConvolutionTexture->Shutdown();
		delete m_ConvolutionTexture;
		m_ConvolutionTexture = 0;
	}
	// Release the horizontal blur render to texture object.
	if(m_HorizontalBlurTexture)
	{
		m_HorizontalBlurTexture->Shutdown();
		delete m_HorizontalBlurTexture;
		m_HorizontalBlurTexture = 0;
	}

	// Release the down sample render to texture object.
	if(m_DownSampleTexture)
	{
		m_DownSampleTexture->Shutdown();
		delete m_DownSampleTexture;
		m_DownSampleTexture = 0;
	}

	// Release the render to texture object.
	if(m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the terrain reflection texture object.
	if(m_TerrainReflectionTexture)
	{
		m_TerrainReflectionTexture->Shutdown();
		delete m_TerrainReflectionTexture;
		m_TerrainReflectionTexture= 0;
	}

	// Release the terrain refraction texture object.
	if(m_TerrainRefractionTexture)
	{
		m_TerrainRefractionTexture->Shutdown();
		delete m_TerrainRefractionTexture;
		m_TerrainRefractionTexture = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool Graphics::Frame(Camera* cam, int fps, int cpu, float frameTime, int mouseX, int mouseY)
{
	bool result;
	m_Camera = cam;

	m_MouseX = mouseX;
	m_MouseY = mouseY;
	// Do object frame processing.
	TestIntersection(400, 300);
	//m_collisionCheck2 = TestSphericalRadiusCollision();
	//m_collisionCheck2 = TestBoundingBoxCollision();
	m_ObjectText1->Frame(m_D3D, fps, cpu, mouseX, mouseY, m_collisionCheck);
	m_ObjectClouds->Frame();
	m_ObjectWater->Frame();
	m_ObjectParticle->Frame(m_D3D, frameTime);
	
	//m_ObjectWorld->Frame();

	//result = RenderPostProcessing(cam);
	//if(!result)
	//{
	//	return false;
	//}

	result = RenderPreProcessing(cam);
	if(!result)
	{
		return false;
	}

	return true;
}


bool Graphics::RenderPostProcessing(Camera* cam)
{
	bool result;

	// First render the scene to a render texture.
	result = RenderSceneToTexture(cam);
	if(!result)
	{
		return false;
	}

	//// Next down sample the render texture to a smaller sized texture.
	//result = DownSampleTexture(cam, m_RenderTexture);
	//if(!result)
	//{
	//	return false;
	//}

	for (int pass = 0; pass < 1; pass++)
	{
		// Perform a convolution pass.
		// Perform a horizontal blur on the down sampled render texture.
		result = RenderConvolutionToTexture(cam, m_RenderTexture, D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f), D3DXVECTOR4(-1.0f, 5.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f));
		//result = RenderConvolutionToTexture(cam, m_RenderTexture, D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, -2.9f, 1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f));
		if(!result)
		{
			return false;
		}

		//result = RenderConvolutionToTexture(cam, m_RenderTexture, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR4(-1.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		//if(!result)
		//{
		//	return false;
		//}

		// Perform a horizontal blur on the down sampled render texture.
		result = RenderHorizontalBlurToTexture(cam, m_ConvolutionTexture);
		if(!result)
		{
			return false;
		}

		// Now perform a vertical blur on the horizontal blur render texture.
		result = RenderVerticalBlurToTexture(cam, m_HorizontalBlurTexture);
		if(!result)
		{
			return false;
		}

		//m_RenderTexture = m_UpSampleTexture;
		//m_RenderTexture = m_HorizontalBlurTexture;
		*m_RenderTexture = *m_VerticalBlurTexture;
		//*m_RenderTexture = *m_HorizontalBlurTexture;
	}

	// Up sample the final blurred render texture to screen size again.
	//result = UpSampleTexture(cam, m_HorizontalBlurTexture);
	//result = UpSampleTexture(cam, m_VerticalBlurTexture);
	result = UpSampleTexture(cam, m_RenderTexture);	
	if(!result)
	{
		return false;
	}

	RenderTestToTexture(cam, m_MiniMapTexture);
	//result = RenderConvolutionToTexture(cam, m_MiniMapTexture, D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f), D3DXVECTOR4(-1.0f, 5.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f));
	//result = RenderConvolutionToTexture(cam, m_MiniMapTexture, D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, -4.0f, 1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f));
	result = RenderConvolutionToTexture(cam, m_MiniMapTexture, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));

	if(!result)
		{
			return false;
	}

	//*m_MiniMapTexture = *m_ConvolutionTexture;

	// Render the blurred up sampled render texture to the screen.
	result = Render2DTextureScene(cam, m_UpSampleTexture);
	if(!result)
	{
		return false;
	}
	
	return true;
}


bool Graphics::RenderPreProcessing(Camera* cam)
{
	bool result;

	renderPass = 0;

	// Render the scene as normal to the back buffer.
	result = RenderScene(cam, renderPass);
	if(!result)
	{
		return false;
	}
	

	renderPass = 1;
	
	// Render the refraction of the scene to a texture.
	result = RenderRefractionToTexture(cam, renderPass);
	if(!result)
	{
		return false;
	}

	renderPass = 2;
	// Render the reflection of the scene to a texture.
	result = RenderReflectionToTexture(cam, renderPass);
	if(!result)
	{
		return false;
	}
	

	return true;
}


bool Graphics::RenderScene(Camera* cam, int renderPass)
{
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	cam->Render();

	m_D3D->GetWorldMatrix(worldMatrix);
	cam->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);	

	m_ObjectSkyDome->Render(*this, renderPass);
	m_ObjectClouds->Render(*this, renderPass);
	
	m_ObjectSphere->SetPosition(D3DXVECTOR3(40.0f, 20.0f, 7.0f));
	m_ObjectSphere->SetRotation(D3DXVECTOR3(10.0f, 10.0f, 10.0f));
	m_ObjectSphere->Render(*this, renderPass);

	m_ObjectSphere2->SetPosition(D3DXVECTOR3(51.5f, 20.0f, 7.0f));
	m_ObjectSphere2->Render(*this, renderPass);	

	m_ObjectWater->Render(*this, renderPass);
	m_ObjectTerrain->Render(*this, renderPass);
	//m_ObjectParticle->SetPosition(cam->GetPosition());
	m_ObjectParticle->Render(*this, renderPass);
	
	//m_ObjectText1->Render(*this, renderPass);
	//m_ObjectCursor->SetPosition(m_MouseX, m_MouseY);
	//m_ObjectCursor->Render(*this, renderPass);

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}


bool Graphics::RenderRefractionToTexture(Camera* cam, int renderPass)
{
	// Setup a clipping plane based on the height of the water to clip everything above it to create a refraction.
	clipPlane = D3DXVECTOR4(0.0f, -1.0f, 0.0f, m_ObjectWater->GetWaterHeight() + 0.1f);

	// Set the render target to be the refraction render to texture.
	m_TerrainRefractionTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the refraction render to texture.
	m_TerrainRefractionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	cam->Render();

	m_ObjectTerrain->Render(*this, renderPass);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}


bool Graphics::RenderReflectionToTexture(Camera* cam, int renderPass)
{
	// Setup a clipping plane based on the height of the water to clip everything below it.
	clipPlane = D3DXVECTOR4(0.0f, 1.0f, 0.0f, -m_ObjectWater->GetWaterHeight());

	// Set the render target to be the reflection render to texture.
	m_TerrainReflectionTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the reflection render to texture.
	m_TerrainReflectionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Use the camera to render the reflection and create a reflection view matrix.
	cam->RenderReflection(m_ObjectWater->GetWaterHeight());

	// Get the camera reflection view matrix instead of the normal view matrix.
	cam->GetReflectionViewMatrix(reflectionMatrix);

	// Get the world and projection matrices from the d3d object.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	//m_ObjectSphere->Render(*this, renderPass);
	//m_ObjectSphere2->Render(*this, renderPass);
	//m_ObjectParticle->Render(*this, renderPass);
	m_ObjectSkyDome->Render(*this, renderPass);
	m_ObjectClouds->Render(*this, renderPass);
	//m_ObjectTerrain->Render(*this, renderPass);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}


bool Graphics::RenderSceneToTexture(Camera* cam)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	bool result;

	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Render scene here
	result = RenderPreProcessing(cam);
	if(!result)
	{
		return false;
	}
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}


bool Graphics::DownSampleTexture(Camera* cam, RenderTexture *renderTexture)
{
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	bool result;


	// Set the render target to be the render to texture.
	m_DownSampleTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_DownSampleTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 1.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	cam->Render();

	// Get the world and view matrices from the camera and d3d objects.
	cam->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	
	// Get the ortho matrix from the render to texture since texture has different dimensions being that it is smaller.
	m_DownSampleTexture->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the small ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_SmallWindow->Render(m_D3D->GetDeviceContext());

	// Render the small ortho window using the texture shader and the render to texture of the scene as the texture resource.
	result =m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_SmallWindow->GetIndexCount(), worldMatrix, m_InitialViewMatrix, orthoMatrix, 
					 renderTexture->GetShaderResourceView());
	if(!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();
	
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}


bool Graphics::RenderConvolutionToTexture(Camera* cam, RenderTexture* renderTexture, D3DXVECTOR4 kernelRow1, D3DXVECTOR4 kernelRow2, D3DXVECTOR4 kernelRow3)
{
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	float screenSizeY;
	bool result;


	// Store the screen height in a float that will be used in the vertical blur shader.
	screenSizeY = (float)m_ConvolutionTexture->GetTextureHeight();

	// Set the render target to be the render to texture.
	m_ConvolutionTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_ConvolutionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	cam->Render();

	// Get the world and view matrices from the camera and d3d objects.
	cam->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the ortho matrix from the render to texture since texture has different dimensions.
	m_ConvolutionTexture->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the small ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_SmallWindow->Render(m_D3D->GetDeviceContext());

	// Render the small ortho window using the vertical blur shader and the horizontal blurred render to texture resource.
	result = m_ShaderManager->RenderConvolutionShader(m_D3D->GetDeviceContext(), m_SmallWindow->GetIndexCount(), worldMatrix, m_InitialViewMatrix, orthoMatrix, 
		renderTexture->GetShaderResourceView(), screenSizeY, kernelRow1, kernelRow2, kernelRow3);
	if(!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}


bool Graphics::RenderHorizontalBlurToTexture(Camera* cam, RenderTexture* renderTexture)
{
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	float screenSizeX;
	bool result;


	// Store the screen width in a float that will be used in the horizontal blur shader.
	screenSizeX = (float)m_HorizontalBlurTexture->GetTextureWidth();

	// Set the render target to be the render to texture.
	m_HorizontalBlurTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_HorizontalBlurTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	cam->Render();

	// Get the world and view matrices from the camera and d3d objects.
	cam->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the ortho matrix from the render to texture since texture has different dimensions.
	m_HorizontalBlurTexture->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the small ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_SmallWindow->Render(m_D3D->GetDeviceContext());

	// Render the small ortho window using the horizontal blur shader and the down sampled render to texture resource.
	result = m_ShaderManager->RenderHorizontalBlurShader(m_D3D->GetDeviceContext(), m_SmallWindow->GetIndexCount(), worldMatrix, m_InitialViewMatrix, orthoMatrix, 
		renderTexture->GetShaderResourceView(), screenSizeX);
	if(!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}


bool Graphics::RenderVerticalBlurToTexture(Camera* cam, RenderTexture* renderTexture)
{
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	float screenSizeY;
	bool result;


	// Store the screen height in a float that will be used in the vertical blur shader.
	screenSizeY = (float)m_VerticalBlurTexture->GetTextureHeight();

	// Set the render target to be the render to texture.
	m_VerticalBlurTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_VerticalBlurTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	cam->Render();

	// Get the world and view matrices from the camera and d3d objects.
	cam->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the ortho matrix from the render to texture since texture has different dimensions.
	m_VerticalBlurTexture->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the small ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_SmallWindow->Render(m_D3D->GetDeviceContext());

	// Render the small ortho window using the vertical blur shader and the horizontal blurred render to texture resource.
	result = m_ShaderManager->RenderVerticalBlurShader(m_D3D->GetDeviceContext(), m_SmallWindow->GetIndexCount(), worldMatrix, m_InitialViewMatrix, orthoMatrix, 
		renderTexture->GetShaderResourceView(), screenSizeY);
	if(!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}


bool Graphics::UpSampleTexture(Camera* cam, RenderTexture *renderTexture)
{
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	bool result;


	// Set the render target to be the render to texture.
	m_UpSampleTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_UpSampleTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	cam->Render();

	// Get the world and view matrices from the camera and d3d objects.
	cam->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the ortho matrix from the render to texture since texture has different dimensions.
	m_UpSampleTexture->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the full screen ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_FullScreenWindow->Render(m_D3D->GetDeviceContext());

	// Render the full screen ortho window using the texture shader and the small sized final blurred render to texture resource.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_FullScreenWindow->GetIndexCount(), worldMatrix, m_InitialViewMatrix, orthoMatrix, 
		renderTexture->GetShaderResourceView());
	if(!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}


bool Graphics::Render2DTextureScene(Camera* cam, RenderTexture* renderTexture)
{
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	cam->Render();

	// Get the world, view, and ortho matrices from the camera and d3d objects.
	cam->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the full screen ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_FullScreenWindow->Render(m_D3D->GetDeviceContext());

	// Render the full screen ortho window using the texture shader and the full screen sized blurred render to texture resource.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_FullScreenWindow->GetIndexCount(), worldMatrix, m_InitialViewMatrix, orthoMatrix, 
		renderTexture->GetShaderResourceView());
	if(!result)
	{
		return false;
	}

	m_ObjectBitmap1->SetPosition(400, 300);
	m_ObjectBitmap1->Render(*this, renderPass);
	m_ObjectText1->Render(*this, renderPass);
	m_ObjectCursor->SetPosition(m_MouseX, m_MouseY);
	m_ObjectCursor->Render(*this, renderPass);

	m_MiniMapWindow->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_MiniMapWindow->GetIndexCount(), worldMatrix, m_InitialViewMatrix, orthoMatrix, m_ConvolutionTexture->GetShaderResourceView());


	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}


bool Graphics::RenderTestToTexture(Camera* cam, RenderTexture* renderTexture)
{
	bool result;
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	
	// Set the render target to be the render to texture.
	m_MiniMapTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_MiniMapTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);

	// Render the scene now and it will draw to the render to texture instead of the back buffer.
	result = RenderPreProcessing(cam);
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();
	
	return true;
}


void Graphics::TestIntersection(int mouseX, int mouseY)
{
	float pointX, pointY;
	D3DXMATRIX projectionMatrix, viewMatrix, inverseViewMatrix, worldMatrix, translateMatrix, inverseWorldMatrix;
	D3DXVECTOR3 direction, origin, rayOrigin, rayDirection;
	bool intersect;
	//bool result;


	// Change the mouse cursor coordinates into the -1 to +1 range in both x and y axes.
	pointX = ((2.0f * (float)mouseX) / (float)m_ScreenWidth) - 1.0f;
	pointY = (((2.0f * (float)mouseY) / (float)m_ScreenHeight) - 1.0f) * -1.0f;
		
	// Adjust the points using the projection matrix to account for the aspect ratio of the viewport.
	m_D3D->GetProjectionMatrix(projectionMatrix);
	pointX = pointX / projectionMatrix._11;
	pointY = pointY / projectionMatrix._22;

	// Get the inverse of the view matrix since a 2D point is being transformed into 3D space.
	m_Camera->GetViewMatrix(viewMatrix);
	D3DXMatrixInverse(&inverseViewMatrix, NULL, &viewMatrix);

	// Calculate the direction vector of the picking ray in view space for the mouse cursor.
	direction.x = (pointX * inverseViewMatrix._11) + (pointY * inverseViewMatrix._21) + inverseViewMatrix._31;
	direction.y = (pointX * inverseViewMatrix._12) + (pointY * inverseViewMatrix._22) + inverseViewMatrix._32;
	direction.z = (pointX * inverseViewMatrix._13) + (pointY * inverseViewMatrix._23) + inverseViewMatrix._33;

	// Set the origin of the picking ray to be the position of the camera.
	origin = m_Camera->GetPosition();

	// Get the world matrix and translate to the location of the sphere.
	m_D3D->GetWorldMatrix(worldMatrix);

	D3DXMatrixTranslation(&translateMatrix, m_ObjectSphere->GetPosition().x, m_ObjectSphere->GetPosition().y, m_ObjectSphere->GetPosition().z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix); 

	// Now get the inverse of the translated world matrix.
	D3DXMatrixInverse(&inverseWorldMatrix, NULL, &worldMatrix);

	// Now transform the ray origin and the ray direction from view space to world space.
	D3DXVec3TransformCoord(&rayOrigin, &origin, &inverseWorldMatrix);
	D3DXVec3TransformNormal(&rayDirection, &direction, &inverseWorldMatrix);

	// Normalize the ray direction.
	D3DXVec3Normalize(&rayDirection, &rayDirection);

	// Now perform the ray-sphere intersection test.
	intersect = RaySphereIntersect(rayOrigin, rayDirection, 1.0f);
	
	if(intersect == true)
	{
		// If it does intersect then set the intersection to "yes" in the text string that is displayed to the screen.
		//result = m_Text->SetIntersection(true, m_D3D->GetDeviceContext());
		m_collisionCheck = true;
	}
	else
	{
		// If not then set the intersection to "No".
		//result = m_Text->SetIntersection(false, m_D3D->GetDeviceContext());
		m_collisionCheck = false;
	}

	return;
}


bool Graphics::RaySphereIntersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDirection, float radius)
{
	float a, b, c, discriminant;

	// Calculate the a, b, and c coefficients.
	a = (rayDirection.x * rayDirection.x) + (rayDirection.y * rayDirection.y) + (rayDirection.z * rayDirection.z);
	b = ((rayDirection.x * rayOrigin.x) + (rayDirection.y * rayOrigin.y) + (rayDirection.z * rayOrigin.z)) * 2.0f;
	c = ((rayOrigin.x * rayOrigin.x) + (rayOrigin.y * rayOrigin.y) + (rayOrigin.z * rayOrigin.z)) - (radius * radius);

	// Find the discriminant.
	discriminant = (b * b) - (4 * a * c);

	// if discriminant is negative the picking ray missed the sphere, otherwise it intersected the sphere.
	if (discriminant < 0.0f)
	{
		return false;
	}

	return true;
}


bool Graphics::TestSphericalRadiusCollision()
{
	
	float distance = 0.0f;

	D3DXVECTOR3 pos1 = m_ObjectSphere->GetPosition();
	D3DXVECTOR3 pos2= m_ObjectSphere2->GetPosition();

	float distX = pos2.x - pos1.x;
	float distY = pos2.y - pos1.y;
	float distZ = pos2.z - pos1.z;	

	distance = sqrt(distX*distX + distY*distY + distZ*distZ);

	if( distance <= (m_ObjectSphere->GetSphericalBoundingRadius() + m_ObjectSphere2->GetSphericalBoundingRadius() ) )
	{

		////This is where we will do something if the objects have collided. What we do here is move the object we have collided with, then check to see if the object we just moved has collided with another object, by calling the DetectCollision() function again. First we get the objects position that we want to move. The distX, distY, and distZ together are basically the vector that explains the angle the two objects have collided at. We can use this vector to "push back" the object we are colliding with, in the right direction, which is what we do, we add the negative distX and distZ, times the "speed" which we want to move at, to the objects x and z position values. Then we transform the local space matrix of the object, call DetectCollision() to see if it has collided with another object, then finally return true, and as you can see below that, if we did not collide with anything, we return false.
		//D3DXVECTOR3 objPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//D3DXVec3TransformCoord(&objPos, &objPos, &SphereLocalSpace[i]);

		//objPos.x += -distX * 0.075f;
		//objPos.z += -distZ * 0.075f;

		//D3DXMatrixScaling( &Scale, 2.0f, 2.0f, 2.0f );
		//D3DXMatrixTranslation( &Translation, objPos.x, 1.0f, objPos.z );

		//SphereLocalSpace[i] = Scale * Translation;

		//DetectCollision(SphereLocalSpace[i]);
		return true;
	}
	return false;
}


bool Graphics::TestBoundingBoxCollision()
{
	float* bbVertices =	m_ObjectSphere->GetBoundingBoxVertices();
	float* bbVertices2 = m_ObjectSphere2->GetBoundingBoxVertices();

	// Check if object 1's maxX is greater than object 2's minX.  Else object 1 is left of object 2.
	if (bbVertices[1] > bbVertices2[0])
		// Check if object 1's minX is less than object 2's maxX.  Else object 1 is right of object 2.
		if (bbVertices[0] < bbVertices2[1])
			// Check if object 1's maxY is greater than object 2's minY.  Else object 1 is under object 2.
			if(bbVertices[3] > bbVertices2[2])
				// Check if object 1's minY is less than object 2's maxY.  Else object 1 is above object 2.
				if(bbVertices[2] < bbVertices2[3])
					// Check if object 1's maxZ is greater than object 2's minZ.  Else object 1 is in front of object 2.
					if (bbVertices[5] > bbVertices2[4])
						// Check if object 1's minZ is less than object 2's maxZ.  Else object 1 is behind object 2.
						if(bbVertices[4] < bbVertices2[5])
							//The two bounding boxes intersect.
							return true;
	//Bounding boxes do not intersect
	return false;
}


D3DXMATRIX Graphics::GetWorldMatrix() const
{
	return worldMatrix;
}

D3DXMATRIX Graphics::GetViewMatrix() const
{
	return viewMatrix;
}

D3DXMATRIX Graphics::GetProjectionMatrix() const
{
	return projectionMatrix;
}

D3DXMATRIX Graphics::GetReflectionMatrix() const
{
	return reflectionMatrix;
}

D3DXMATRIX Graphics::GetOrthoMatrix() const
{
	return orthoMatrix;
}

D3DXVECTOR4 Graphics::GetClipPlane() const
{
	return clipPlane;
}

RenderTexture * Graphics::GetTerrainRefractionTexture() const
{
	return m_TerrainRefractionTexture;
} 
RenderTexture * Graphics::GetTerrainReflectionTexture() const
{
	return m_TerrainReflectionTexture;
}

D3D * Graphics::GetD3DObject() const
{
	return m_D3D;
}

ShaderManager * Graphics::GetShaderManager() const
{
	return m_ShaderManager;
}

Camera * Graphics::GetCamera()
{
	return m_Camera;
}

ObjectTerrain* Graphics::GetObjectTerrain()
{
	return m_ObjectTerrain;
}

void Graphics::GetMouseLocation(int& mouseX, int& mouseY)
{
	mouseX = m_MouseX;
	mouseY = m_MouseY;
	return;
}



