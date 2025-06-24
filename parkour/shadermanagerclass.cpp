////////////////////////////////////////////////////////////////////////////////
// Filename: shadermanagerclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "shadermanagerclass.h"


ShaderManagerClass::ShaderManagerClass()
{
    m_UIShader = 0;
    m_Shader = 0;
}


ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other)
{
}


ShaderManagerClass::~ShaderManagerClass()
{
}


bool ShaderManagerClass::Initialize(ID3D11Device* device, HWND hwnd)
{
    bool result;

    // Create and initialize the texture shader object.
    m_UIShader = new UIShaderClass;

    result = m_UIShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    // Create and initialize the light shader object.
    m_Shader = new ShaderClass;

    result = m_Shader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    return true;
}


void ShaderManagerClass::Shutdown()
{
    // Release the light shader object.
    if (m_Shader)
    {
        m_Shader->Shutdown();
        delete m_Shader;
        m_Shader = 0;
    }

    // Release the texture shader object.
    if (m_UIShader)
    {
        m_UIShader->Shutdown();
        delete m_UIShader;
        m_UIShader = 0;
    }

    return;
}


bool ShaderManagerClass::RenderUIShader(ID3D11DeviceContext* deviceContext, int indexCount, ID3D11ShaderResourceView* texture)
{
    bool result;


    result = m_UIShader->Render(deviceContext, indexCount, texture);
    if (!result)
    {
        return false;
    }

    return true;
}


bool ShaderManagerClass::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor,
    XMFLOAT3 cameraPosition, XMFLOAT4 specularColor, float specularPower, XMFLOAT4 pointLightColor[], XMFLOAT4 pointLightPosition[])
{
    bool result;


    result = m_Shader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambientColor,
        diffuseColor, cameraPosition, specularColor, specularPower, pointLightColor, pointLightPosition);
    if (!result)
    {
        return false;
    }

    return true;
}