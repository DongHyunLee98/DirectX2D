#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

// 글로벌스로 이동(spritePS에도 해당됨)
// Texture2D albedoTexture : register(t0);

// SamplerState pointSampler : register(s0);
// SamplerState anisotropicSampler : register(s1);


float4 main(VSOut In) : SV_TARGET
{
    //return In.Color;
    float4 color = (float) 0.0f;
    
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
        
    return color;
}