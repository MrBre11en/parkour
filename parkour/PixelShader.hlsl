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

// TYPEDEFS //
struct PixelInputType
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR;
    float2 tex : TEXCOORD0;
    float3 viewDirection : TEXCOORD1;
};

// Pixel Shader
float4 Main(PixelInputType input) : SV_TARGET
{
    float4 textureColor;
    float3 lightDir;
    float lightIntensity;
    float4 color;
    float3 reflection;
    float4 specular;

    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
    textureColor = shaderTexture.Sample(SampleType, input.tex);

    // Invert the light direction for calculations.
    lightDir = -lightDirection;

    // Calculate the amount of light on this pixel.
    lightIntensity = saturate(dot(input.normal, lightDir));

    // Calculate the reflection vector based on the light intensity, normal vector, and light direction.
    reflection = normalize(2.0f * lightIntensity * input.normal - lightDir); 

    // Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
    specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);

    // Set the default output color to the ambient light value for all pixels.
    // Determine the final diffuse color based on the diffuse color and the amount of light intensity.
    color = ambientColor + diffuseColor * lightIntensity;

    // Multiply the texture pixel and the final diffuse color to get the final pixel color result.
    color = color * textureColor;

    // Add the specular component last to the output color.
    color = saturate(color + specular);

    return color;
}