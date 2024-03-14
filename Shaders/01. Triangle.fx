struct VertexInput
{
    float4 position : POSITION;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
};

// 버텍스 셰이더
VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = input.position;
    return output;
}

// 픽셀 셰이더 , 버텍스에서 가공된 게 인풋으로
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

// 테크닉 : 패스를 묶음
technique11 T0
{
    // pass : 버텍스/픽셀 셰이더 두개를 묶어줌
    pass P0
    {
        // 버전 vs_5_0 , 메인함수 VS
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
        // 버전 vs_5_0 , 메인함수 VS
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS3()));
    }
}