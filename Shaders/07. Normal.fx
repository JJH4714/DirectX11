matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;
float3 LightDir;

struct VertexInput
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

// ���ؽ� ���̴�
VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
    
    output.uv = input.uv;
    // uv�� �״������, normal�� �ٸ� ��ǥ��� �̵� �� �븻��ǥ�� �ٲ�
    // ȸ�� �ʿ��� ������ �ǹǷ� ���� ��� ������� ��
    output.normal = mul(input.normal, (float3x3) World);
    return output;
}

SamplerState Sampler0
{
    AddressU = Wrap;
    AddressV = Wrap;
};

// �ȼ� ���̴� , ���ؽ����� ������ �� ��ǲ����
float4 PS(VertexOutput input) : SV_TARGET
{
    float3 normal = normalize(input.normal);
    // ������ �� �ְ� ���� ������ �ݴ�� ��������
    float3 light = -LightDir;
    // dot : ����
    // |A||B|cos(x) �ε� A,B�� ���������̸� ���󰡼� ���̰��� ����
    // x�� 0�� �� ���� ũ�ϱ�(1) ������ �� ���� ���� ���� �´ٴ� ��
    //return float4(1.f, 1.f, 1.f, 1.f) * dot(normal, light);
    return Texture0.Sample(Sampler0, input.uv) * float4(1.f, 1.f, 1.f, 1.f) * dot(normal, light);
}

RasterizerState FillModeWireFrame
{
    FillMode = WireFrame;
};

// ��ũ�� : �н��� ����
technique11 T0
{
    // pass : ���ؽ�/�ȼ� ���̴� �ΰ��� ������
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

    pass P1
    {
        SetRasterizerState(FillModeWireFrame);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}