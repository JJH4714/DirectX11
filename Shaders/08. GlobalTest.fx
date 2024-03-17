#include "Common/00. Global.fx"

// 버텍스 셰이더
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

// 픽셀 셰이더 , 버텍스에서 가공된 게 인풋으로
float4 PS(VertexOutput input) : SV_TARGET
{
    return Texture0.Sample(LinearSampler, input.uv);
}

// 테크닉 : 패스를 묶음
technique11 T0
{
    PASS_VP(P0, VS, PS)
}