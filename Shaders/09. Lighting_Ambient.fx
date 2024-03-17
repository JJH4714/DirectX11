#include "Common/00. Global.fx"

float4 LightAmbient;    // 광원의 색상
float4 MaterialAmbient; // 물체의 색상

VertexOutput VS(VertexTextureNormal input)
{
    VertexOutput output;
    output.position = mul(input.position, W);
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) W);
    return output;
}

Texture2D Texture0;

// Ambient(환경광 주변광)
// 수많은 반사를 거쳐 광원이 불분명한 빛
// 일정한 밝기와 색으로 표현

// 픽셀 셰이더 , 버텍스에서 가공된 게 인풋으로
float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = LightAmbient * MaterialAmbient;
    return color;
    //return Texture0.Sample(LinearSampler, input.uv);
}

// 테크닉 : 패스를 묶음
technique11 T0
{
    PASS_VP(P0, VS, PS)
}