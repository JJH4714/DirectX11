#include "Common/00. Global.fx"

float3 LightDir; // �� ����
float4 LightSpecular;
float4 MaterialSpecular;

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

// Specular ( �ݻ籤 )
// �� �������� ������ �ݻ�Ǵ� �� ( Phong )

float4 PS(MeshOutput input) : SV_TARGET
{
    // �ݻ�Ǵ� �� ���ϱ� ��� 1 �����Լ�
    // �� ����, ������ ��ֺ��� �־��ָ� �ݻ�Ǵ� �� ���� ����
    float3 R = reflect(LightDir, input.normal);
    
    // ��� 2 ���� ������ ���ϱ�
    // �ݻ�� ���� ���ʹ� ��� ���ұ�?
    // ���� �ε��� �������� �ñ��� �ʰ� �� ���ٰ� �����ϸ�, LightDir�� ǥ���� �հ� ������
    // �� �� ������ ��ֺ��Ϳ� LightDir�� �����ϸ�, �ϴ� �а��̹Ƿ� ���� ( cos < 0 )�̰�
    // ��ֺ����� �ݴ������� LightDir�� ������Ų ���� ��Į��� ����
    // �� ����ŭ ��ֺ��� �������� '�� ��' �̵���Ű�� ���� ������ ����
    // �׷��� '�� �� ��' �� �ι� �̵���Ű�� ������ �ݻ�Ǵ� ���Ͱ� ����( �ڼ��� �� �׸� ����... )
    //float3 R2 = LightDir - (2 * input.normal * dot(LightDir, input.normal));
    
    R = normalize(R);
    // JJHCHECK
    //ī�޶� �� ��Ŀ��� ��ǥ ������ ->  ī�޶� ��ġ
    float3 cameraPosition = -V._41_42_43;
    // ��ü���� ī�޶�� ���� ����
    float3 E = cameraPosition - input.worldPosition;
    E = normalize(E);
    
    float value = dot(R, E);
    value = saturate(value);    // saturate : clamp( 0 ~ 1 )
    // value�� 0~1���̰��̶� �����Ҽ��� ���� �۾���
    // �����ϸ鼭 ������ �������� �� ����(ũ���ҰŸ� �� �ص� �ǰ�)
    float specular = pow(value, 10);
    
    float4 color = LightSpecular * MaterialSpecular * specular;

    return color;
}

// ��ũ�� : �н��� ����
technique11 T0
{
    PASS_VP(P0, VS, PS)
}