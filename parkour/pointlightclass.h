////////////////////////////////////////////////////////////////////////////////
// Filename: pointlightclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _POINTLIGHTCLASS_H_
#define _POINTLIGHTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <directxmath.h>
using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: PointLightClass
////////////////////////////////////////////////////////////////////////////////
class PointLightClass
{
public:
    PointLightClass();
    PointLightClass(const PointLightClass&);
    ~PointLightClass();

    void SetAmbientColor(float, float, float, float);
    void SetDiffuseColor(float, float, float, float);
    void SetDirection(float, float, float);
    void SetSpecularColor(float, float, float, float);
    void SetSpecularPower(float);
    void SetPosition(float, float, float);

    XMFLOAT4 GetAmbientColor();
    XMFLOAT4 GetDiffuseColor();
    XMFLOAT3 GetDirection();
    XMFLOAT4 GetSpecularColor();
    float GetSpecularPower();
    XMFLOAT4 GetPosition();

private:
    XMFLOAT4 m_ambientColor;
    XMFLOAT4 m_diffuseColor;
    XMFLOAT3 m_direction;
    XMFLOAT4 m_specularColor;
    float m_specularPower;
    XMFLOAT4 m_position;
};

#endif