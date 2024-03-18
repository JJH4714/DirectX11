#include "Common/00. Global.fx"

float3 LightDir; // 빛 벡터
float4 LightDiffuse; // 빛 색상
float4 MaterialDiffuse; //@@ JJHCHECK 물체가 빛을 반사하는 정도?
Texture2D DiffuseMap;

VertexOutput VS(VertexTextureNormal input)
{
    VertexOutput output;
    output.position = mul(input.position, W);
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) W);
    return output;
}

// Diffuse ( 분산광 )
// 물체의 표면에서 분산되어 눈으로 바로 들어오는 빛
// 각도에 따라 밝기가 다르다 ( 람바르트(Lambert) 공식 )
// 픽셀 셰이더 , 버텍스에서 가공된 게 인풋으로
float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    float4 value = dot(normalize(-LightDir), normalize(input.normal)) * LightDiffuse * MaterialDiffuse;
    //float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    return color * value;
}

// 테크닉 : 패스를 묶음
technique11 T0
{
    PASS_VP(P0, VS, PS)
}