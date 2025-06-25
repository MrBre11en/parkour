#include "LevelManagerClass.h"

LevelManagerClass::LevelManagerClass()
{
	m_World = 0;
	m_Direct3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_Light = 0;
	m_PointLights = 0;
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

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 3.0f, -10.0f);
	m_Camera->SetRotation(15.0f, 0.0f, 0.0f);

	// Create and initialize the model object.
	m_Model = new ModelClass;

	// Set the file name of the model.
	strcpy_s(modelFilename, "Data/Models/Cube.txt");

	// Set the name of the texture file that we will be loading.
	strcpy_s(textureFilename, "Data/Textures/seafloor.tga");

	result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), modelFilename, textureFilename);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the light object.
	m_Light = new LightClass;

	m_Light->SetDirection(1.0f, 0.0f, 1.0f);
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(0.75f, 0.75f, 0.75f, 1.0f);
	m_Light->SetSpecularColor(0.5f, 0.5f, 0.5f, 1.0f);
	m_Light->SetSpecularPower(32.0f);


	// Set the number of lights we will use.
	m_numPointLights = 4;

	// Create and initialize the light objects array.
	m_PointLights = new PointLightClass[m_numPointLights];

	// Manually set the color and position of each light.
	m_PointLights[0].SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);  // Red
	m_PointLights[0].SetPosition(-3.0f, 1.0f, 3.0f);

	m_PointLights[1].SetDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);  // Green
	m_PointLights[1].SetPosition(3.0f, 1.0f, 0.0f);

	m_PointLights[2].SetDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);  // Blue
	m_PointLights[2].SetPosition(-3.0f, 1.0f, -3.0f);

	m_PointLights[3].SetDiffuseColor(1.0f, 0.0f, 1.0f, 1.0f);  // Purpe
	m_PointLights[3].SetPosition(0.0f, 3.0f, 0.0f);

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

	Entity* cube = m_World->CreateEntity();
	Transform* transform = cube->AddComponent<Transform>();
	transform->position = vec3(0.0f, 5.0f, 0.0f);
	cube->AddComponent<PhysicBody>();
	cube->AddComponent<SphereCollider>();

	Entity* plane = m_World->CreateEntity();
	plane->AddComponent<Transform>();
	plane->AddComponent<PlaneCollider>();


	m_World->AddPhysicSystem<PhysicSystem>();

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

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light objects.
	if (m_PointLights)
	{
		delete[] m_PointLights;
		m_PointLights = 0;
	}


	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
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
	m_World->UpdatePhysic();
	m_World->UpdateRender();

	static float rotation = 0.0f;
	bool result;

	// Update the rotation variable each frame.
	rotation -= 0.01f;
	if (rotation < 0.0f)
	{
		rotation += 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}


bool LevelManagerClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, rotateMatrix, translateMatrix, scaleMatrix, srMatrix, orthoMatrix;
	XMFLOAT4 pointLightColor[4], pointLightPosition[4];
	int i;
	bool result;


	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Render the bitmap with the UI shader.
	result = m_ShaderManager->RenderUIShader(m_Direct3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_Direct3D->TurnZBufferOn();

	rotateMatrix = XMMatrixRotationY(rotation);  // Build the rotation matrix.
	scaleMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f);  // Build the scaling matrix.
	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);  // Build the translation matrix.

	// Multiply the scale, rotation, and translation matrices together to create the final world transformation matrix.
	srMatrix = XMMatrixMultiply(scaleMatrix, rotateMatrix);
	worldMatrix = XMMatrixMultiply(srMatrix, translateMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	// Get the light properties.
	for (i = 0; i < m_numPointLights; i++)
	{
		// Create the diffuse color array from the four light colors.
		pointLightColor[i] = m_PointLights[i].GetDiffuseColor();

		// Create the light position array from the four light positions.
		pointLightPosition[i] = m_PointLights[i].GetPosition();
	}

	// Render the model using shader.
	result = m_ShaderManager->RenderShader(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		pointLightColor, pointLightPosition);
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}