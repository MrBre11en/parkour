// TYPEDEFS //
struct VertexInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
};

struct PixelInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
};


// Vertex Shader
PixelInputType Main(VertexInputType input)
{
    PixelInputType output;
    
    
    // Change the position vector to be 4 units for proper matrix calculations.
    output.position.w = 1.0f;
    
    // Store the texture coordinates for the pixel shader.
    output.color = input.color;
    output.tex = input.tex;

    return output;
}