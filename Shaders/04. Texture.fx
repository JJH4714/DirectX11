matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;

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

SamplerState Sampler0;
// ���� ������ �� �صθ� �⺻������ �����.
// �׷���...�ͷ��� ��� �Ϻκи� �������� �ؽ��� ������ ������ ������
// ���÷�������Ʈ�� uv��ǥ�� 0~1�����ε�, �� ������ ����� ���� ���� ó���� ��

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
        // ���� vs_5_0 , �����Լ� VS
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