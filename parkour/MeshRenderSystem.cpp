#ifndef _MESHRENDER_SYSTEM_
#define _MESHRENDER_SYSTEM_

//////////////
// INCLUDES //
//////////////
#include<cmath>
#include "system.h"
#include "Transform.cpp"
#include "Mesh.cpp"

class MeshRenderSystem : public System
{
public:
	MeshRenderSystem()
	{
	}


	bool Update(vector<Entity*>& entities, float deltaTime) override
	{
		// Clear the buffers to begin the scene.
		m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

		size_t size = entities.size();
		for (int i = 0; i < size; i++)
		{
			Entity* entity = entities[i];
			Transform* transform = entity->GetComponent<Transform>();
			Mesh* mesh = entity->GetComponent<Mesh>();
			if (transform != nullptr && mesh != nullptr)
			{

				XMMATRIX worldMatrix, viewMatrix, projectionMatrix, rotateMatrix, translateMatrix, scaleMatrix, srMatrix, orthoMatrix;
				XMFLOAT4 pointLightColor[4], pointLightPosition[4];
				int i;
				bool result;

				// Generate the view matrix based on the camera's position.
				m_Camera->Render();

				// Get the world, view, and projection matrices from the camera and d3d objects.
				m_Direct3D->GetWorldMatrix(worldMatrix);
				m_Camera->GetViewMatrix(viewMatrix);
				m_Direct3D->GetProjectionMatrix(projectionMatrix);
				m_Direct3D->GetOrthoMatrix(orthoMatrix);

				//// Turn off the Z buffer to begin all 2D rendering.
				//m_Direct3D->TurnZBufferOff();

				//// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
				//result = m_Bitmap->Render(m_Direct3D->GetDeviceContext());
				//if (!result)
				//{
				//	return false;
				//}

				//// Render the bitmap with the UI shader.
				//result = m_ShaderManager->RenderUIShader(m_Direct3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), m_Bitmap->GetTexture());
				//if (!result)
				//{
				//	return false;
				//}

				//// Turn the Z buffer back on now that all 2D rendering has completed.
				//m_Direct3D->TurnZBufferOn();

				rotateMatrix = XMMatrixRotationY(0.0f);  // Build the rotation matrix.
				scaleMatrix = XMMatrixScaling(transform->scale.x, transform->scale.y, transform->scale.z);  // Build the scaling matrix.
				translateMatrix = XMMatrixTranslation(transform->position.x, transform->position.y, transform->position.z);  // Build the translation matrix.

				// Multiply the scale, rotation, and translation matrices together to create the final world transformation matrix.
				srMatrix = XMMatrixMultiply(scaleMatrix, rotateMatrix);
				worldMatrix = XMMatrixMultiply(srMatrix, translateMatrix);

				// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
				mesh->model.Render(m_Direct3D->GetDeviceContext());

				// Get the light properties.
				for (i = 0; i < m_numPointLights; i++)
				{
					// Create the diffuse color array from the four light colors.
					pointLightColor[i] = m_PointLights[i].GetDiffuseColor();

					// Create the light position array from the four light positions.
					pointLightPosition[i] = m_PointLights[i].GetPosition();
				}

				// Render the model using shader.
				result = m_ShaderManager->RenderShader(m_Direct3D->GetDeviceContext(), mesh->model.GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, mesh->model.GetTexture(),
					m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
					pointLightColor, pointLightPosition);
				if (!result)
				{
					return false;
				}

			}
		}

		// Present the rendered scene to the screen.
		m_Direct3D->EndScene();

		return true;
	}
};

#endif