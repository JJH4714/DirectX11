struct VertexInput
{
    float4 position : POSITION;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
};

// ���ؽ� ���̴�
VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = input.position;
    return output;
}

// �ȼ� ���̴� , ���ؽ����� ������ �� ��ǲ����
float4 PS(VertexOutput input) : SV_TARGET
{
    return float4(1.f, 0.f, 0.f, 1.f);
}

float4 PS2(VertexOutput input) : SV_TARGET
{
    return float4(0.f, 1.f, 0.f, 1.f);
}

float4 PS3(VertexOutput input) : SV_TARGET
{
    return float4(0.f, 0.f, 1.f, 1.f);
}

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
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS2()));
    }
}

technique11 T1
{
    pass P0
    {
        // ���� vs_5_0 , �����Լ� VS
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS3()));
    }
}