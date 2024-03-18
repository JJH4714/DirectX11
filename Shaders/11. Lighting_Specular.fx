#include "Common/00. Global.fx"

float3 LightDir; // 빛 벡터
float4 LightSpecular;
float4 MaterialSpecular;

MeshOutput VS(VertexTextureNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, W);
    output.worldPosition = output.position;
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) W);
    return output;
}

// Specular ( 반사광 )
// 한 방향으로 완전히 반사되는 빛 ( Phong )

float4 PS(MeshOutput input) : SV_TARGET
{
    // 반사되는 빛 구하기 방법 1 내장함수
    // 빛 벡터, 정점의 노멀벡터 넣어주면 반사되는 빛 벡터 나옴
    float3 R = reflect(LightDir, input.normal);
    
    // 방법 2 직접 식으로 구하기
    // 반사된 빛의 벡터는 어떻게 구할까?
    // 빛이 부딪힐 정점에서 팅기지 않고 쭉 간다고 가정하면, LightDir은 표면을 뚫고 지나감
    // 그 때 정점의 노멀벡터와 LightDir을 내적하면, 일단 둔각이므로 음수 ( cos < 0 )이고
    // 노멀벡터의 반대쪽으로 LightDir을 투영시킨 값이 스칼라로 나옴
    // 이 값만큼 노멀벡터 방향으로 '한 번' 이동시키면 평면과 평행한 벡터
    // 그래서 '한 번 더' 총 두번 이동시키면 완전히 반사되는 벡터가 나옴( 자세한 건 그림 보기... )
    //float3 R2 = LightDir - (2 * input.normal * dot(LightDir, input.normal));
    
    R = normalize(R);
    // JJHCHECK
    //카메라 뷰 행렬에서 좌표 데이터 ->  카메라 위치
    float3 cameraPosition = -V._41_42_43;
    // 물체에서 카메라로 가는 벡터
    float3 E = cameraPosition - input.worldPosition;
    E = normalize(E);
    
    float value = dot(R, E);
    value = saturate(value);    // saturate : clamp( 0 ~ 1 )
    // value는 0~1사이값이라 제곱할수록 값이 작아짐
    // 제곱하면서 영역을 좁혀나갈 수 있음(크게할거면 덜 해도 되고)
    float specular = pow(value, 10);
    
    float4 color = LightSpecular * MaterialSpecular * specular;

    return color;
}

// 테크닉 : 패스를 묶음
technique11 T0
{
    PASS_VP(P0, VS, PS)
}