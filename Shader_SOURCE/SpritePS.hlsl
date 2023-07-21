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


float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4)0.0f;
    //color.r = 1.0f;
    //color.b = 1.0f;
    
    //if (In.UV.y < 0.2f)
    //{
    //    discard;
    //}
    //else
    //{
    //    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    //}
    
    
     // 1200 1032 // 120 130
    // 1080 -> 540
    // -540 + 1200 
    color = albedoTexture.Sample(pointSampler, In.UV);
    
    if (animationType == 1)
    {
        float2 diff = (AtlasSize - SpriteSize) / 2.0f;
        float2 UV = (SpriteLeftTop - diff - SpriteOffset)
                + (AtlasSize * In.UV);
    
        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
        || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;
        
        color = atlasTexture.Sample(anisotropicSampler, UV);
    }
    // 애니메이션 작업 전까지 임시
   // color = albedoTexture.Sample(pointSampler, In.UV);    // 알베도였던거 변경
   // 
   // if ( color.a <= 0.0f)
   //     discard;
    
    return color;
}