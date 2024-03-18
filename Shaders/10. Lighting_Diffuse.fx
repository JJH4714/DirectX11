#include "Common/00. Global.fx"

float3 LightDir; // �� ����
float4 LightDiffuse; // �� ����
float4 MaterialDiffuse; //@@ JJHCHECK ��ü�� ���� �ݻ��ϴ� ����?
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

// Diffuse ( �л걤 )
// ��ü�� ǥ�鿡�� �л�Ǿ� ������ �ٷ� ������ ��
// ������ ���� ��Ⱑ �ٸ��� ( ���ٸ�Ʈ(Lambert) ���� )
// �ȼ� ���̴� , ���ؽ����� ������ �� ��ǲ����
float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    float4 value = dot(normalize(-LightDir), normalize(input.normal)) * LightDiffuse * MaterialDiffuse;
    //float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    return color * value;
}

// ��ũ�� : �н��� ����
technique11 T0
{
    PASS_VP(P0, VS, PS)
}