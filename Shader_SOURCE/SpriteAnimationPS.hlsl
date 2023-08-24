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
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};


float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;
    
    // 1200 1032 // 120 130
    // 1080 -> 540
    // -540 + 1200 
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    
    if (animationType == 1)
    {
        // 상수버퍼 애니메이터 BInds
        float2 diff = (AtlasSize - SpriteSize) / 2.0f;
        float2 UV = (SpriteLeftTop - diff - SpriteOffset)
                + (AtlasSize * In.UV);
    
        // 이게없으면 UV넘어간 1.0뒤의 반복되는 이미지도 보임
        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
            || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;
        
        color = atlasTexture.Sample(anisotropicSampler, UV); // In.UV로 기존들어오는것 확인가능
    }
    
    float4 lightColor = float4(0.4f, 0.4f, 0.4f, 1.0f);
    
    for (int i = 0; i < 2; i++)
    {
        CalculateLight2D(lightColor, In.WorldPos, i);
    }
    
    color *= lightColor;
    
    if (color.a <= 0.0f)
        discard;
        
    return color;
}