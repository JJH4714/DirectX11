matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;
uint Address;   // ���÷� ������ ��ȣ

struct VertexInput
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

// ���ؽ� ���̴�
VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
    
    output.uv = input.uv;
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
    return Texture0.Sample(Sampler0, input.uv);
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