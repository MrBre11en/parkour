// GLOBALS //
Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

// TYPEDEFS //
struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
};


// Pixel Shader
float4 Main(PixelInputType input) : SV_TARGET
{
    float4 textureColor;


    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
    textureColor = shaderTexture.Sample(SampleType, input.tex);

    return saturate(input.color * textureColor);
}
