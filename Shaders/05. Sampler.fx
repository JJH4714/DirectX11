matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;
uint Address;   // 샘플러 지정할 번호

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

// 버텍스 셰이더
VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
    
    output.uv = input.uv;
    return output;
}

// 샘플러스테이트
// 딱히 설정을 안 해두면 기본값으로 적용됨.
// 그래서...터레인 깔면 일부분만 정상적인 텍스쳐 나오고 나머진 비정상
// 샘플러스테이트는 uv좌표가 0~1사이인데, 그 범위를 벗어났을 떄에 대해 처리를 함
// Filter : 확대/축소 시 중간값을 처리하는 방식
// Address : uv가 1보다 클 때 나머지 부분을 처리하는 방식
SamplerState Sampler0;  // 기본

SamplerState SamplerAddressWrap
{
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState SamplerAddressMirror
{
    AddressU = Mirror;
    AddressV = Mirror;
};

SamplerState SamplerAddressClamp
{
    AddressU = Clamp;
    AddressV = Clamp;
};

SamplerState SamplerAddressBorder
{
    AddressU = Border;
    AddressV = Border;
    BorderColor = float4(1.f, 0.f, 0.f, 1.f);
};

// 픽셀 셰이더 , 버텍스에서 가공된 게 인풋으로
float4 PS(VertexOutput input) : SV_TARGET
{
    // uv 매핑을 지정한 샘플링 방식으로 하겠다
    if(Address == 0)
        return Texture0.Sample(SamplerAddressWrap, input.uv);
    
    if (Address == 1)
        return Texture0.Sample(SamplerAddressMirror, input.uv);
    
    if (Address == 2)
        return Texture0.Sample(SamplerAddressClamp, input.uv);
    
    if (Address == 3)
        return Texture0.Sample(SamplerAddressBorder, input.uv);
    
    return Texture0.Sample(Sampler0, input.uv);

}


// 테크닉 : 패스를 묶음
technique11 T0
{
    // pass : 버텍스/픽셀 셰이더 두개를 묶어줌
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}