struct VS_INPUT
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;   //SV : System Value
    float4 color : COLOR;
};

cbuffer TransformData : register(b0)
{
    //@@JJHCHECK row_major : 
    row_major matrix matWorld;
    row_major matrix matView;
    row_major matrix matProjection;
    
    //float4 offset;
}

// 버텍스 셰이더
// 참고로, 디폴트로 만들어진 함수 보면 알겠지만 이것도 main함수가 있음
// 우리가 만든 버텍스셰이더.hlsl 파일 속성 들어가면 진입점 이름 : main 인데
// 우린 VS라는 이름으로 했으니 이름을 바꿔주자 ( main 쓸 거면 쓰고...)
VS_OUTPUT VS(VS_INPUT input)
{
    // 버텍스 셰이더기 때문에 정점 단위로 실행됨
    VS_OUTPUT output;

    float4 position = mul(input.position, matWorld);
    position = mul(position, matView);
    position = mul(position, matProjection);
    
    output.position = position;
    output.color = input.color;
    
    // input은 기하학 정보로 변하지 않고, 추가정보(offset)만 전달
    //output.position = input.position + offset;
    ////output.color = input.color;
    //output.uv = input.uv;

    return output;
}


// RS (래스터라이저) : 버텍스 셰이더에서 정점들을 가지고 삼각형 데이터로 뽑아내줌
// 삼각형 기준, 정점 3개만 있으면 그냥 점이니까...이걸 삼각형으로 연결


Texture2D texture0 : register(t0);  //t0 레지스터에 texture0을 등록
SamplerState sampler0 : register(s0);

// 픽셀 셰이더. 버텍스 셰이더에서 처리한 걸 RS(래스터라이저)에서 처리하고, 이쪽으로 넘어옴
// 참고로 픽셀 셰이더는...화면에 찍을 각 픽셀들의 색 계산
float4 PS(VS_OUTPUT input) : SV_Target
{
    //return input.color;

    // 텍스쳐 0번에 uv 좌표로 거기에 해당하는 색상을 추출
    //float4 color = texture0.Sample(sampler0, input.uv);
    float4 color = input.color;
    
    return color;
}


// 디폴트로 있던 함수
//float4 main( float4 pos : POSITION ) : SV_POSITION
//{
//	return pos;
//}