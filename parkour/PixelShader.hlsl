// DEFINES //
#define NUM_LIGHTS 4

// GLOBALS //
Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

cbuffer LightBuffer
{
    float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float specularPower;
    float4 specularColor;
};

cbuffer PointLightColorBuffer
{
    float4 pointLightColor[NUM_LIGHTS];
};

// TYPEDEFS //
struct PixelInputType
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR;
    float2 tex : TEXCOORD0;
    float3 viewDirection : TEXCOORD1;
    float3 pointLightPos[NUM_LIGHTS] : TEXCOORD2;
};


// Pixel Shader
float4 Main(PixelInputType input) : SV_TARGET
{
    float4 color;
    float4 textureColor;
    
    float3 lightDir;
    float lightIntensity;
    float3 reflection;
    float4 specular;
    
    float pointLightIntensity[NUM_LIGHTS];
    float4 colorArray[NUM_LIGHTS];
    float4 colorSum;
    int i;

    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
    textureColor = shaderTexture.Sample(SampleType, input.tex);
    
    for(i = 0; i < NUM_LIGHTS; i++)
    {
        pointLightIntensity[i] = saturate(dot(input.normal, input.pointLightPos[i]));
        colorArray[i] = pointLightColor[i] * pointLightIntensity[i];
    }
    
    colorSum = float4(0.0f, 0.0f, 0.0f, 1.0f);
    for (i = 0; i < NUM_LIGHTS; i++)
    {
        colorSum.r += colorArray[i].r;
        colorSum.g += colorArray[i].g;
        colorSum.b += colorArray[i].b;
    }

    // Invert the light direction for calculations.
    lightDir = -lightDirection;

    // Calculate the amount of light on this pixel.
    lightIntensity = saturate(dot(input.normal, lightDir));

    // Calculate the reflection vector based on the light intensity, normal vector, and light direction.
    reflection = normalize(2.0f * lightIntensity * input.normal - lightDir); 

    // Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
    specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);

    color = ambientColor + diffuseColor * lightIntensity + saturate(colorSum);
    color = color * textureColor;
    
    color = saturate(color + specularColor * specular);

    return color;
}