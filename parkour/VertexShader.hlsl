// DEFINES //
#define NUM_LIGHTS 4

// GLOBALS //
cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer CameraBuffer
{
    float3 cameraPosition;
    float padding;
};

cbuffer PointLightPositionBuffer
{
    float4 pointLightPosition[NUM_LIGHTS];
};

// TYPEDEFS //
struct VertexInputType
{
    float4 position : POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR;
    float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR;
    float2 tex : TEXCOORD0;
    float3 viewDirection : TEXCOORD1;
    float3 pointLightPos[NUM_LIGHTS] : TEXCOORD2;
};


// Vertex Shader
PixelInputType Main(VertexInputType input)
{
    PixelInputType output;
    float4 worldPosition;
    int i;

    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    // Store the input color for the pixel shader to use.
    output.color = input.color;
    output.tex = input.tex;
    
    output.normal = normalize(mul(input.normal, (float3x3) worldMatrix));
    worldPosition = mul(input.position, worldMatrix);
    output.viewDirection = normalize(cameraPosition.xyz - worldPosition.xyz);
    
    for (i = 0; i < NUM_LIGHTS; i++)
    {
        output.pointLightPos[i] = normalize(pointLightPosition[i].xyz - worldPosition.xyz);
    }
    
    return output;
}