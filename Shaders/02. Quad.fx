struct VertexInput
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

// ���ؽ� ���̴�
VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = input.position;
    output.color = input.color;
    return output;
}

// �ȼ� ���̴� , ���ؽ����� ������ �� ��ǲ����
float4 PS(VertexOutput input) : SV_TARGET
{
    return input.color;
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