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

// 버텍스 셰이더
VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
    
    output.uv = input.uv;
    // uv야 그대로지만, normal은 다른 좌표계로 이동 시 노말좌표도 바뀜
    // 회전 쪽에서 문제가 되므로 월드 행렬 곱해줘야 함
    output.normal = mul(input.normal, (float3x3) World);
    return output;
}

SamplerState Sampler0
{
    AddressU = Wrap;
    AddressV = Wrap;
};

// 픽셀 셰이더 , 버텍스에서 가공된 게 인풋으로
float4 PS(VertexOutput input) : SV_TARGET
{
    float3 normal = normalize(input.normal);
    // 내적할 수 있게 빛의 방향을 반대로 뒤집어줌
    float3 light = -LightDir;
    // dot : 내적
    // |A||B|cos(x) 인데 A,B가 단위벡터이면 날라가서 사이각만 남음
    // x가 0일 때 가장 크니까(1) 수직일 때 빛이 가장 세게 온다는 거
    //return float4(1.f, 1.f, 1.f, 1.f) * dot(normal, light);
    return Texture0.Sample(Sampler0, input.uv) * float4(1.f, 1.f, 1.f, 1.f) * dot(normal, light);
}

RasterizerState FillModeWireFrame
{
    FillMode = WireFrame;
};

// 테크닉 : 패스를 묶음
technique11 T0
{
    // pass : 버텍스/픽셀 셰이더 두개를 묶어줌
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