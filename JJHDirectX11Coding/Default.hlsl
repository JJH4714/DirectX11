// 셰이더 문법이 있긴 하지만 C++과 꽤나 비슷
struct VS_INPUT
{
    // float4 : 이것도 구조체로, float 4개
    // POSITION, COLOR : CreateInputLayout에서 D3D11_INPUT_ELEMENT_DESC 적을 때
    // layout 이름. 나중에 쓸 지 모르겠는데... 삼각형 만들 때 "POSITION", "COLOR"로 했었음
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;   //SV : System Value
    float2 uv : UV;
};

// 이것도 함수인데, C++처럼 (반환타입) (함수이름)(인자)로 했음
// 즉 반환타입이 위의 VS_OUTPUT , 함수이름 VS, 함수 인자 위의 VS_INPUT 이다
// 얘는 메인함수 같은 거

// 참고로 렌더링 파이프라인 핵심 5단계는
// IA - VS - RS - PS - OM

// Game.cpp - _CreateGeometry에서 버텍스 정보 만들고, 버텍스 버퍼까지 만들어 GPU에 전달했다
// 근데 그렇게 정적인 것만 주면...게임에서 움직임에 따른 계산이 안 된다.
// 그렇다고 움직임에 따라 정점 정보를 다 바꿔서 다시 버텍스 버퍼로 만들기엔 부담이 크니,
// 변하지 않는 기하학 정보는 두고 버텍스 셰이더 쪽에서 움직임에 따라 계산을 다시하자
cbuffer CameraData : register(b0)
{
    row_major matrix matView;
    row_major matrix matProjection;
}


cbuffer TransformData : register(b1)
{
    row_major matrix matWorld;
}

cbuffer AnimationData : register(b2)
{
    float2 spriteOffset;
    float2 spriteSize;
    float2 textureSize;
    float useAnimation;
}

// 버텍스 셰이더
// 참고로, 디폴트로 만들어진 함수 보면 알겠지만 이것도 main함수가 있음
// 우리가 만든 버텍스셰이더.hlsl 파일 속성 들어가면 진입점 이름 : main 인데
// 우린 VS라는 이름으로 했으니 이름을 바꿔주자 ( main 쓸 거면 쓰고...)
VS_OUTPUT VS(VS_INPUT input)
{
    // input은 기하학 정보로 변하지 않고, 추가정보(offset)만 전달
    // 버텍스 셰이더기 때문에 정점 단위로 실행됨
    VS_OUTPUT output;

    // W - V - P
    float4 position = mul(input.position, matWorld);
    position = mul(position, matView);
    position = mul(position, matProjection);
    
    output.position = position;
    output.uv = input.uv;

    if(useAnimation == 1.f)
    {
        //@@ JJHCHECK
        output.uv *= spriteSize / textureSize;
        output.uv += spriteOffset / textureSize;
    }

    return output;
}


// RS (래스터라이저) : 버텍스 셰이더에서 정점들을 가지고 삼각형 데이터로 뽑아내줌
// 삼각형 기준, 정점 3개만 있으면 그냥 점이니까...이걸 삼각형으로 연결


Texture2D texture0 : register(t0);  //t0 레지스터에 texture0을 등록
SamplerState sampler0 : register(s0);

// 픽셀 셰이더. 버텍스 셰이더에서 처리한 걸 RS(래스터라이저)에서 처리하고, 이쪽으로 넘어옴
// 참고로 픽셀 셰이더는...화면에 찍을 각 픽셀들의 색 계산
float4 PS(VS_OUTPUT input) : SV_Target  /*JJHCheck*/
{
    // 텍스쳐 0번에 uv 좌표로 거기에 해당하는 색상을 추출
    float4 color = texture0.Sample(sampler0, input.uv);
    
    return color;
}