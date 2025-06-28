#include "LevelManagerClass.h"

LevelManagerClass::LevelManagerClass()
{
	m_World = 0;
	m_Direct3D = 0;
	m_Bitmap = 0;
	m_ShaderManager = 0;
}

LevelManagerClass::LevelManagerClass(const LevelManagerClass& other)
{
}


LevelManagerClass::~LevelManagerClass()
{
}


bool LevelManagerClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	Mesh* mesh;
	Transform* transform;

	char bitmapFilename[128];
	char modelFilename[128];
	char textureFilename[128];
	bool result;


	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Set the file name of the bitmap file.
	strcpy_s(bitmapFilename, "Data/Textures/seafloor.tga");

	// Create and initialize the bitmap object.
	m_Bitmap = new BitmapClass;

	result = m_Bitmap->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, bitmapFilename, 50, 50);
	if (!result)
	{
		return false;
	}

	// Create and initialize the normal map shader object.
	m_ShaderManager = new ShaderManagerClass;

	result = m_ShaderManager->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	// WORLD CREATING //
	//////////////////////////////////////////////////////////////////////////////////////////////

	m_World = new World;
	result = m_World->Initialize(m_Direct3D, m_Bitmap, m_ShaderManager);
	if (!result)
	{
		return false;
	}

	Entity* cube = m_World->CreateEntity();
	transform = cube->AddComponent<Transform>();
	transform->position = vec3(0.0f, 3.0f, 0.0f);
	cube->AddComponent<PhysicBody>();
	cube->AddComponent<SphereCollider>();
	mesh = cube->AddComponent<Mesh>();

	strcpy_s(modelFilename, "Data/Models/Cube.txt");
	strcpy_s(textureFilename, "Data/Textures/seafloor.tga");

	result = mesh->model.Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	Entity* plane = m_World->CreateEntity();
	transform = plane->AddComponent<Transform>();
	transform->position = vec3(0.0f, -2.0f, 0.0f);
	transform->scale = vec3(5.0f, 0.001f, 5.0f);
	plane->AddComponent<PlaneCollider>();
	mesh = plane->AddComponent<Mesh>();

	result = mesh->model.Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	m_World->AddPhysicSystem<PhysicSystem>();
	m_World->AddRenderSystem<RenderSystem>(m_Direct3D, m_Bitmap, m_ShaderManager, m_World->m_Camera, m_World->m_Light, m_World->m_PointLights, m_World->m_numPointLights);

	//////////////////////////////////////////////////////////////////////////////////////////////
	// WORLD CREATING //
	//////////////////////////////////////////////////////////////////////////////////////////////


	return true;
}


void LevelManagerClass::Shutdown()
{
	if (m_World)
	{
		m_World->Shutdown();
		delete m_World;
		m_World = 0;
	}

	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the shader manager object.
	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the Direct3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	return;
}


bool LevelManagerClass::Frame()
{
	bool result;

	result = m_World->UpdatePhysic();
	if (!result)
	{
		return false;
	}

	result = m_World->UpdateRender();
	if (!result)
	{
		return false;
	}

	return true;
}