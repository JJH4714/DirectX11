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
// �ܰ��� ���� �� ��� (������Ʈ)

float4 PS(MeshOutput input) : SV_TARGET
{
    float3 cameraPosition = -V._41_42_43;
    float3 E = normalize(cameraPosition - input.worldPosition);
    
    // ��ü�� ���ϴ� �ü���, ��ü ������ ��� ���� ����
    // ��ü�� �ܰ����� �츮 �ü����� �� ���̴� ���̹Ƿ�, ���� �ݴ�ǰ�
    // �������� 1�̶� ���� �츮 ������ ���� �� ��� ��, 0�� �ܰ��� �����ٴ� ��
    // ���� 0�ϼ��� ���ϰ� ǥ���Ͽ� �ܰ��� ǥ�ø� ����
    float value = saturate(dot(E, input.normal));
    float emissive = 1.f - value;
    
    emissive = smoothstep(0.f, 1.f, emissive);
    emissive = pow(emissive, 5);    // �ܰ��� �����ϰ�...
    float4 color = MaterialEmissive * emissive;
    
    return color;
}

// ��ũ�� : �н��� ����
technique11 T0
{
    PASS_VP(P0, VS, PS)
}