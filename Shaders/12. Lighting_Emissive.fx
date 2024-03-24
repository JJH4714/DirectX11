#include "Common/00. Global.fx"

float4 MaterialEmissive;

MeshOutput VS(VertexTextureNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, W);
    output.worldPosition = output.position;
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) W);
    return output;
}

// Emissive
// 외곽선 구할 때 사용 (림라이트)

float4 PS(MeshOutput input) : SV_TARGET
{
    float3 cameraPosition = -V._41_42_43;
    float3 E = normalize(cameraPosition - input.worldPosition);
    
    // 물체를 향하는 시선과, 물체 정점의 노멀 벡터 내적
    // 물체의 외곽선은 우리 시선에서 안 보이는 쪽이므로, 빛과 반대되게
    // 내적값이 1이라 함은 우리 눈에서 가장 잘 띄는 곳, 0은 외곽에 가깝다는 뜻
    // 따라서 0일수록 진하게 표시하여 외곽선 표시를 해줌
    float value = saturate(dot(E, input.normal));
    float emissive = 1.f - value;
    
    emissive = smoothstep(0.f, 1.f, emissive);
    emissive = pow(emissive, 5);    // 외곽선 선명하게...
    float4 color = MaterialEmissive * emissive;
    
    return color;
}

// 테크닉 : 패스를 묶음
technique11 T0
{
    PASS_VP(P0, VS, PS)
}